VERSION 5.00
Begin VB.Form MessageBoardList 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "There are new posts"
   ClientHeight    =   2370
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4515
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2370
   ScaleWidth      =   4515
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox MessageList 
      Height          =   1815
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   4335
   End
   Begin VB.CommandButton CloseWindow 
      Caption         =   "Close and Purge List"
      Height          =   255
      Left            =   2640
      TabIndex        =   1
      Top             =   2040
      Width           =   1815
   End
   Begin VB.CommandButton ViewPost 
      Caption         =   "View Post"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   2040
      Width           =   1815
   End
End
Attribute VB_Name = "MessageBoardList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub ClearList_Click()
    PostList.Clear
End Sub



Public Sub AddPost(ByVal ID As Long, ByVal Poster As String, ByVal Subject As String)
    MessageList.AddItem ID & PostDelim & Poster & PostDelim & Subject
    Me.Show
    MakeTopMost Me.hWnd, True
    Beep
End Sub

Private Sub CloseWindow_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Me.Icon = ClientForm.Icon
End Sub

Private Sub MessageList_DblClick()
    ViewPost_Click
End Sub

Private Sub ViewPost_Click()
    Dim URL
    If MessageList.ListIndex > -1 Then
        URL = "http://www.gummlanparty.net/login.asp?Login=" & ClientForm.Login & "&pw=" & ClientForm.Password & "&page=/viewblock.asp?C=" & GetPostID()
    
        OpenURL URL
    End If
End Sub

Function GetPostID() As Long
    On Error Resume Next
        GetPostID = CLng(Split(MessageList.List(MessageList.ListIndex), PostDelim)(0))
End Function
