VERSION 5.00
Object = "{E4D5D928-FD35-4D0A-92CD-F3CE02D68455}#1.1#0"; "ahtmlle2.ocx"
Begin VB.Form Chat 
   Caption         =   "Chat"
   ClientHeight    =   4185
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3945
   LinkTopic       =   "Form1"
   ScaleHeight     =   4185
   ScaleWidth      =   3945
   StartUpPosition =   3  'Windows Default
   Begin HTMLCtlsLE.HTMLView Conversation 
      Height          =   2415
      Left            =   120
      TabIndex        =   4
      Top             =   0
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   4260
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Text            =   ""
   End
   Begin VB.Timer Timer1 
      Interval        =   2000
      Left            =   1320
      Top             =   1320
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Send"
      Height          =   255
      Left            =   2880
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   3840
      Width           =   975
   End
   Begin VB.TextBox Sending 
      Height          =   1215
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   2520
      Width           =   3735
   End
   Begin VB.CheckBox TopMost 
      Caption         =   "Always on Top"
      Height          =   255
      Left            =   1320
      TabIndex        =   3
      Top             =   3840
      Width           =   1455
   End
   Begin VB.Timer Activity 
      Interval        =   1000
      Left            =   720
      Top             =   2880
   End
   Begin VB.Timer fixChat 
      Enabled         =   0   'False
      Interval        =   20
      Left            =   2160
      Top             =   3120
   End
   Begin VB.Shape status 
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   255
      Left            =   120
      Shape           =   3  'Circle
      Top             =   3840
      Width           =   255
   End
   Begin VB.Label StatusLabel 
      Caption         =   "Away"
      Height          =   255
      Left            =   480
      TabIndex        =   2
      Top             =   3840
      Width           =   735
   End
End
Attribute VB_Name = "Chat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Window Coordinates

Dim ConversationWidthDistance, ConversationHeightDistance As Double
Dim SendingWidthDistance, SendingTopDistance As Double, SendingHeight As Double
Dim StatusTopDistance, StatusLabelTopDistance
Dim SendLeftDistance, SendTopDistance
Dim TopmostTopDistance, TopmostLeftDistance

Dim LastTime As Integer
Dim CurrentStatus As String

Private Function GetLocationInfo()
    ConversationWidthDistance = Me.Width - Conversation.Width
    ConversationHeightDistance = Me.Height - Conversation.Height
    SendingTopDistance = Me.Height - Sending.Top
    SendingWidthDistance = Me.Width - Sending.Width
    StatusTopDistance = Me.Height - status.Top
    StatusLabelTopDistance = Me.Height - StatusLabel.Top
    SendLeftDistance = Me.Width - Command1.Left
    SendTopDistance = Me.Height - Command1.Top
    TopmostTopDistance = Me.Height - TopMost.Top
    'TopmostLeftDistance = Me.Width - TopMost.Left
End Function

Private Sub ResizeWindow()
    On Error Resume Next
    Conversation.Width = Me.Width - ConversationWidthDistance
    Conversation.Height = Me.Height - ConversationHeightDistance
    Sending.Top = Me.Height - SendingTopDistance
    Sending.Width = Me.Width - SendingWidthDistance
    status.Top = Me.Height - StatusTopDistance
    StatusLabel.Top = Me.Height - StatusLabelTopDistance
    Command1.Left = Me.Width - SendLeftDistance
    Command1.Top = Me.Height - SendTopDistance
    'TopMost.Left = Me.Width - TopmostLeftDistance
    TopMost.Top = Me.Height - TopmostTopDistance
End Sub



Public Function GetChatName() As String
    On Error Resume Next
    GetChatName = Trim(Split(Me.Caption, "-->")(1))
End Function

Public Sub SetChatName(ToName As String)
    Me.Caption = "Chatting with --> " & ToName
    Conversation.Text = ""
    Sending = ""
End Sub

Public Sub Incoming(msg As String)
    If Me.Visible = False Then
        Me.Show
    End If
    Conversation.Text = Conversation.Text & GetChatName & " : " & msg & vbCrLf
    UpdateStatus stsACTIVE
    CurrentStatus = stsACTIVE
    Beep
End Sub

Private Sub Activity_Timer()
    
    LastTime = LastTime + 1
    Update = False
    If LastTime < 10 Then
        If CurrentStatus <> stsACTIVE Then
            CurrentStatus = stsACTIVE
            Update = True
        End If
    ElseIf LastTime > 60 Then
        If CurrentStatus <> stsAWAY Then
            CurrentStatus = stsAWAY
            Update = True
        End If
    Else
        If CurrentStatus <> stsIDLE Then
            CurrentStatus = stsIDLE
            Update = True
        End If
    End If
    If Update Then
        glpSendMessage conCHATSTATUS, GetChatName, CurrentStatus
    End If
End Sub

Private Sub Command1_Click()
    If Sending <> "" Then
        glpSendMessage conMSG, GetChatName, Sending
        Conversation.Text = Conversation.Text & ClientForm.Login & " : " & Sending & vbCrLf
        Sending = ""
        Sending.Locked = True
        fixChat.Enabled = True
    End If
End Sub

Public Sub UpdateStatus(sts As String)
    Select Case sts
        Case stsAWAY
            status.FillColor = vbRed
            StatusLabel.Caption = "Away"
        Case stsIDLE
            status.FillColor = vbYellow
            StatusLabel.Caption = "Idle"
        Case stsACTIVE
            status.FillColor = vbGreen
            StatusLabel.Caption = "Active"
        Case stsOFFLINE
            status.FillColor = vbBlack
            StatusLabel.Caption = "Offline"
    End Select
End Sub

Private Sub Conversation_Change(ByVal Text As String)
    'If Len(Conversation) > 30000 Then
    '    Conversation = Right(Conversation, 30000)
    'End If
    'On Error Resume Next
    'Conversation.SelStart = Len(Conversation.Text) - 1
    'Conversation.SelStart
End Sub





Private Sub fixChat_Timer()
    Sending = ""
    Sending.Locked = False
    fixChat.Enabled = False
End Sub

Private Sub Timer1_Timer()
    If Not IsOnline(GetChatName) Then
        UpdateStatus stsOFFLINE
    End If
End Sub

Private Sub Form_Activate()
    LastTime = 0
End Sub

Private Sub Form_Load()
    GetLocationInfo
    SetTransparent Me.hWnd, True
    Me.Icon = ClientForm.Icon
End Sub

Private Sub Form_Resize()
    If Me.WindowState <> vbMinimized Then
        ResizeWindow
        Me.Refresh
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Cancel = 1
    Me.Hide
End Sub

Private Sub Sending_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim CtrlDown As Integer, AltDown As Integer
    CtrlDown = (Shift And vbCtrlMask) > 0
    AltDown = (Shift And vbAltMask) > 0
    If (KeyCode = vbKeyReturn And CtrlDown) Or (KeyCode = vbKeyS And AltDown) Then
        Command1_Click
    End If
    LastTime = 0
End Sub

Private Sub TopMost_Click()
    MakeTopMost Me.hWnd, TopMost
End Sub
