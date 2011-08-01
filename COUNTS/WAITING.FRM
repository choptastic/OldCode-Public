VERSION 5.00
Begin VB.Form Form5 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Waiting for Counts"
   ClientHeight    =   765
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2400
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form5"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   765
   ScaleWidth      =   2400
   Begin VB.CheckBox Autocheck 
      Caption         =   "Autocheck Counts"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   0
      Value           =   1  'Checked
      Width           =   1935
   End
   Begin VB.Timer Timer2 
      Interval        =   1000
      Left            =   600
      Top             =   120
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   120
      Top             =   120
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Set AutoCheck Numbers"
      Height          =   375
      Left            =   60
      TabIndex        =   0
      Top             =   360
      Width           =   2295
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim titlestatus As Integer
Dim captions(4) As String


Private Sub Autocheck_Click()
    If Autocheck.Value = 1 Then
        Command1.Enabled = True
    Else
        Command1.Enabled = False
    End If
End Sub

Public Sub Command1_Click()
    ExpectedCounts.Show
End Sub

Private Sub Form_Load()
    captions(0) = " --"
    captions(1) = " /"
    captions(2) = " |"
    captions(3) = " \"

    
    'Open "counts.ini" For Input As #1
    'Line Input #1, itemsloc
    'Line Input #1, dailyloc
    'Line Input #1, checkloc
    'Close #1


End Sub

Private Sub Timer1_Timer()

    titlestatus = titlestatus + 1
    If titlestatus > 3 Then titlestatus = 0
    Caption = "Waiting for Counts" + captions(titlestatus)

End Sub

Private Sub Timer2_Timer()
    Dim message As Integer
    On Error GoTo aftertimer2
    Open Checkloc For Input As #1
        If (Not EOF(1)) Then
            Input #1, message
        End If
    Close #1
    If message = CheckCounts Then
        Timer1.Enabled = False
        Acknowledged = False
        Timer2.Enabled = False
        Form5.Hide
        If Autocheck = 1 Then
            Form1.LoadEverything True
        Else
            Form2.Enabled = True
            Form2.Show
            Form2.Timer2.Enabled = True
            Form2.Timer3.Enabled = True
        End If
    End If
    Exit Sub
aftertimer2:
    If Err.Number = 76 Then
        d = MsgBox("Directory 'temp' not found in current directory" + Chr(13) + "Program cannot function without directory" + Chr(13) + "Exiting Counts Calculator", vbCritical)
        End
    End If
End Sub

