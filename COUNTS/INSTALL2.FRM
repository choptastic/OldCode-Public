VERSION 5.00
Begin VB.Form Form2 
   Appearance      =   0  'Flat
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Waiting for Response from Vending Stand"
   ClientHeight    =   30
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4710
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
   LinkTopic       =   "Form2"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   30
   ScaleWidth      =   4710
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   5000
      Left            =   1800
      Top             =   120
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   600
      Top             =   600
   End
   Begin VB.Menu canc 
      Caption         =   "&Cancel"
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim formstatus As Integer

Private Sub canc_Click()
    If MsgBox("Are you sure you want to cancel?", vbOKCancel) = vbOK Then
        Timer2.Enabled = False
        Timer1.Enabled = False
        Me.Hide
    End If
    

End Sub

Private Sub Form_Load()
    formstatus = 0
End Sub

Private Sub Timer1_Timer()
    formstatus = formstatus + 1
    If formstatus >= 4 Then formstatus = 0
    Form2.Caption = "Waiting for Response from Vending Stand"
    If formstatus = 0 Then Form2.Caption = Form2.Caption + " --"
    If formstatus = 1 Then Form2.Caption = Form2.Caption + " \"
    If formstatus = 2 Then Form2.Caption = Form2.Caption + " |"
    If formstatus = 3 Then Form2.Caption = Form2.Caption + " /"

End Sub

Private Sub Timer2_Timer()
    Dim v As Integer
    On Error Resume Next

    Open "vendres.cts" For Input As #1
        Input #1, v
    Close #1
    If (v = 2000) Then
        Kill "vendres.cts"
        Me.Hide
    End If

    


End Sub

