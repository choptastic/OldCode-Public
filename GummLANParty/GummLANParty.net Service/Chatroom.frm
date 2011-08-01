VERSION 5.00
Begin VB.Form Chatroom 
   Caption         =   "Chat Channel (a cheap, not as functional, relativelyuseless Chatroom)"
   ClientHeight    =   5190
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7005
   LinkTopic       =   "Form1"
   ScaleHeight     =   5190
   ScaleWidth      =   7005
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Op 
      Caption         =   "Op"
      Enabled         =   0   'False
      Height          =   255
      Left            =   6240
      TabIndex        =   6
      Top             =   4440
      Width           =   735
   End
   Begin VB.CommandButton Kick 
      Caption         =   "Kick"
      Enabled         =   0   'False
      Height          =   255
      Left            =   5280
      TabIndex        =   5
      Top             =   4440
      Width           =   735
   End
   Begin VB.TextBox chatView 
      Height          =   4110
      Left            =   0
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   240
      Width           =   5175
   End
   Begin VB.CommandButton Send 
      Caption         =   "Send"
      Height          =   375
      Left            =   5280
      TabIndex        =   3
      Top             =   4800
      Width           =   1695
   End
   Begin VB.TextBox SendView 
      Height          =   735
      Left            =   0
      MultiLine       =   -1  'True
      TabIndex        =   2
      Top             =   4440
      Width           =   5175
   End
   Begin VB.ListBox UserList 
      Height          =   4350
      Left            =   5280
      TabIndex        =   0
      Top             =   0
      Width           =   1695
   End
   Begin VB.Label ChatName 
      Caption         =   "Chat Channel Name: "
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   0
      Width           =   5055
   End
End
Attribute VB_Name = "Chatroom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim ChatViewHeight
Dim SendViewTop
Dim ChatWidth
Dim SendLeft, SendTop
Dim UserListLeft, UserListHeight
Dim FuncTop, KickLeft, OpLeft


Private Sub Form_Load()
    ChatViewHeight = Me.Height - chatView.Height
    ChatWidth = Me.Width - chatView.Width
    SendViewTop = Me.Height - SendView.Top
    SendLeft = Me.Width - Send.Left
    SendTop = Me.Height - Send.Top
    UserListLeft = Me.Width - UserList.Left
    UserListHeight = Me.Height - UserList.Height
    FuncTop = Me.Height - Kick.Top
    KickLeft = Me.Width - Kick.Left
    OpLeft = Me.Width - Op.Left
End Sub


Private Sub Form_Resize()
    chatView.Height = Me.Height - ChatViewHeight
    chatView.Width = Me.Width - ChatWidth
    SendView.Width = Me.Width - ChatWidth
    SendView.Top = Me.Height - SendViewTop
    Send.Left = Me.Width - SendLeft
    Send.Top = Me.Height - SendTop
    UserList.Left = Me.Width - UserListLeft
    UserList.Height = Me.Height - UserListHeight
    Kick.Top = Me.Height - FuncTop
    Op.Top = Me.Height - FuncTop
    Kick.Left = Me.Width - KickLeft
    Op.Left = Me.Width - OpLeft
End Sub
