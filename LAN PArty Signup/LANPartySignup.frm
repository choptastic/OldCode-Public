VERSION 5.00
Begin VB.Form LANPartySignup 
   BorderStyle     =   0  'None
   Caption         =   "Form1"
   ClientHeight    =   5880
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   8385
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   24
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   5880
   ScaleWidth      =   8385
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton exitbutton 
      Caption         =   "E&XIT"
      Height          =   555
      Left            =   360
      TabIndex        =   7
      Top             =   4680
      Width           =   2535
   End
   Begin VB.CommandButton reset 
      Cancel          =   -1  'True
      Caption         =   "Clear"
      Height          =   735
      Left            =   120
      TabIndex        =   6
      Top             =   3360
      Width           =   8175
   End
   Begin VB.CommandButton add 
      Caption         =   "Do It!"
      Default         =   -1  'True
      Height          =   735
      Left            =   120
      TabIndex        =   5
      Top             =   2520
      Width           =   8175
   End
   Begin VB.TextBox e 
      Appearance      =   0  'Flat
      Height          =   675
      Left            =   2160
      TabIndex        =   4
      Top             =   1680
      Width           =   6135
   End
   Begin VB.TextBox n 
      Appearance      =   0  'Flat
      Height          =   675
      Left            =   2160
      TabIndex        =   2
      Top             =   840
      Width           =   6135
   End
   Begin VB.Label Label3 
      Caption         =   "Email"
      Height          =   735
      Left            =   120
      TabIndex        =   3
      Top             =   1680
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "Name"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label signin 
      Alignment       =   2  'Center
      Caption         =   "Sign in to Gumm LAN Party"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8175
   End
End
Attribute VB_Name = "LANPartySignup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub add_Click()
    Screen.MousePointer = 11
    If Not IsEmailValid(e) Then
        MsgBox "Email Address Not Valid"
    End If
    On Error GoTo errr
    e = Trim(e)
    n = Trim(n)
    Dim rst As Recordset
    Dim retval
    Dim d As Database
    Set d = OpenDatabase("\\server\webserver\GummLANParty.mdb")
    Set rst = d.OpenRecordset("select * from RSVP where name='" & n & "'")
    If rst.RecordCount > 0 Then
        If e <> rst![email] Then
            retval = MsgBox("Would you like to update your previously stored email Address of " & rst![email] & " to " & e & "?", vbYesNoCancel)
            If retval = vbYes Then
                d.Execute "update RSVP set email='" & e & "' where name='" & n & "'"
            ElseIf retval = vbNo Then
                MsgBox "Not Updated"
                e = rst![email]
            Else
                Exit Sub
            End If
        End If
    End If
    Set rst = d.OpenRecordset("select * from RSVP where email='" & e & "'")
    If rst.RecordCount > 0 Then
        If e <> rst![Name] Then
            retval = MsgBox("Would you like to update your previously stored Name of " & rst![Name] & " to " & n & "?", vbYesNoCancel)
            If retval = vbYes Then
                d.Execute "update RSVP set name='" & n & "' where email='" & e & "'"
            ElseIf retval = vbNo Then
                n = rst![Name]
            Else
                Exit Sub
            End If
        End If
    End If
    d.Execute ("insert into LANPartyAttendees(email,name,LANPartyID) values('" & e & "','" & n & "'," & GetLANPArtyID() & ")")
    Screen.MousePointer = 0
    Exit Sub
    
errr:
    MsgBox "Server is not available right now.  Please notify Gumm"
    Screen.MousePointer = 0
    Exit Sub
End Sub

Private Sub exitbutton_Click()
    End
End Sub

Private Sub Form_Load()
    Me.Left = 1
    Me.Top = 1
    Me.Height = Screen.Height
    Me.Width = Screen.Width
    n.Width = Screen.Width - 120 - n.Left
    e.Width = Screen.Width - 120 - e.Left
    add.Width = Screen.Width - 120 - add.Left
    reset.Width = Screen.Width - 120 - reset.Left
    signin.Width = Screen.Width - 120 - signin.Left
    signin.Caption = signin.Caption & " " & GetLANPArtyID
    exitbutton.Left = Screen.Width + 120
End Sub

Private Sub reset_Click()
    n = ""
    e = ""
    n.SetFocus
End Sub
