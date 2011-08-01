VERSION 5.00
Begin VB.Form BugReport 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Bug Report"
   ClientHeight    =   5730
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5295
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5730
   ScaleWidth      =   5295
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CancelIt 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1200
      TabIndex        =   6
      Top             =   5160
      Width           =   1215
   End
   Begin VB.CommandButton Send 
      Caption         =   "Send"
      Height          =   375
      Left            =   2760
      TabIndex        =   5
      Top             =   5160
      Width           =   1335
   End
   Begin VB.TextBox Description 
      Height          =   2775
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Top             =   2280
      Width           =   5055
   End
   Begin VB.TextBox Subject 
      Height          =   285
      Left            =   840
      TabIndex        =   1
      Top             =   1680
      Width           =   4335
   End
   Begin VB.Label Label3 
      Caption         =   "Description of Bug"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Subject"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1680
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   $"BugReport.frx":0000
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5055
   End
End
Attribute VB_Name = "BugReport"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub CancelIt_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Me.Icon = ClientForm.Icon
    SetTransparent Me.hWnd, True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If Trim(Subject) = "" Or Trim(Description) = "" Then Exit Sub
    If MsgBox("Are you sure you want to close without sending the bug report?", vbYesNo) = vbNo Then
        Cancel = 1
    End If
End Sub

Private Sub Send_Click()
    
    If Len(Trim(Subject)) < 5 Then
        MsgBox "Subject Must be at least length 5"
        Exit Sub
    End If
    
    If InStr(1, Subject, "/") Or InStr(1, Subject, "\") Or InStr(1, Subject, "\") Or InStr(1, Subject, "*") _
        Or InStr(1, Subject, ":") Or InStr(1, Subject, "?") Or InStr(1, Subject, Chr(34)) _
        Or InStr(1, Subject, "<") Or InStr(1, Subject, ">") Or InStr(1, Subject, "|") Then
        MsgBox "Subject must not contain any of the following characters, as it is stored as a filename on the server:" & vbCrLf & _
            "/\:*?" & Chr(34) & "<>|" & vbCrLf & vbCrLf & "Sorry for the inconvenience", , "Invalid Subject"
        Exit Sub
    End If
        
    
    If Len(Trim(Description)) < 30 Then
        MsgBox "Description must be at least length 30"
        Exit Sub
    End If
    glpSendMessage conBUG, Subject, Description
    Subject = ""
    Description = ""
    Unload Me
End Sub
