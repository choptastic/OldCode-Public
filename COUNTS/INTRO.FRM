VERSION 5.00
Begin VB.Form Form3 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Counts Calculator"
   ClientHeight    =   3210
   ClientLeft      =   510
   ClientTop       =   1170
   ClientWidth     =   2715
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
   Icon            =   "INTRO.frx":0000
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   45.12
   ScaleMode       =   0  'User
   ScaleWidth      =   2715
   Begin VB.Timer Timer3 
      Interval        =   3000
      Left            =   2040
      Top             =   840
   End
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   10000
      Left            =   480
      Top             =   840
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   960
      Top             =   840
   End
   Begin VB.CommandButton Command2 
      Appearance      =   0  'Flat
      Caption         =   "About this Program"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   2760
      Width           =   2535
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      Caption         =   "Launch Standby Mode"
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   2040
      Width           =   2535
   End
   Begin VB.Label Label2 
      Caption         =   "Counts Calculator v2.0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   240
      TabIndex        =   3
      Top             =   0
      Width           =   2175
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Welcome to Counts Calculator.  Please Make a selection. . ."
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   2535
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Function timenow()
    Dim h, m As Integer
    h = Hour(Now)
    m = Minute(Now)
    timenow = h * 60 + m
End Function

Private Sub Command1_Click()
    Open Setupfile For Input As #1
        Input #1, message
        Input #1, hh
        Input #1, mm
    Close #1
    GoTo skip
noload:
    hh = 21
    mm = 55
skip:
    act_time = hh * 60 + mm
    
    Open Setupfile For Output As #1
        Write #1, message
        Write #1, hh
        Write #1, mm
    Close #1
    Timer1.Enabled = True
    Timer3.Interval = 10000
    Form3.Hide
End Sub

Private Sub Command2_Click()
    Form4.Show
End Sub



Private Sub Form_Load()
    'ChDir "c:\counts"
    If (App.PrevInstance = True) Then
        MsgBox "There is already an instance of this program running.  Exiting. . . ", vbCritical
        End
    End If
    
    Label2.Caption = "Counts Calculator " & GetVersion
    Form1.Caption = "Counts Calculator " & GetVersion & " - Office Side"
    Form1.Label2.Caption = "Counts Calculator " & GetVersion
    Form4.Text1.Text = "Counts Calculator " & GetVersion & "    Programming and concepts by Jesse Gumm"
    On Error GoTo noload
    activate = 0
    
    Open Setupfile For Input As #1
        Input #1, message
        Input #1, hh
        Input #1, mm
    Close #1
    GoTo skip
noload:
    hh = 21
    mm = 55
skip:
    act_time = hh * 60 + mm
    
    Open Setupfile For Output As #1
        Write #1, StayOpenMessage
        Write #1, hh
        Write #1, mm
    Close #1
    If InStr(1, Command, "-noprompt") > 0 Then
        Command1_Click
    End If
End Sub

Private Sub Timer1_Timer()
    
    If timenow() > act_time Then
        Form5.Show
        Form5.Timer1.Enabled = True
        Form5.Timer2.Enabled = True
        Timer1.Enabled = False
        Timer3.Interval = 2000
        maketextfilename
        Form5.Command1_Click
    End If

End Sub

Private Sub Timer2_Timer()
    If timenow() > Resettime1 And timenow() < Resettime2 Then
        Timer1.Enabled = True
        Timer2.Enabled = False
    End If
End Sub

Private Sub Timer3_Timer()
    Dim mesasge, hh, mm As Integer
    
    On Error GoTo noload
        Open Setupfile For Input As #1
            Input #1, message
            Input #1, hh
            Input #1, mm
        Close #1
    If message = CloseMessage Then
        Open Setupfile For Output As #1
            Write #1, StayOpenMessage
            Write #1, hh
            Write #1, mm
        Close #1
        'If (Form1.Visible = True Or Form2.Visible = True Or _
        '    Form3.Visible = True Or Form4.Visible = True _
        '    Or Form5.Visible = True Or Form6.Visible = True) Then
                MsgBox "Halt Message Occured", vbExclamation
            
        'End If
        End
        
    End If
    act_time = hh * 60 + mm
    GoTo skip
noload:
    act_time = 21 * 60 + 55
skip:
End Sub
