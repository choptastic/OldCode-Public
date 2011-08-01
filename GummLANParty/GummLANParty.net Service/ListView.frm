VERSION 5.00
Begin VB.Form ListView 
   Caption         =   "GuLP - "
   ClientHeight    =   4275
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   2655
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4275
   ScaleWidth      =   2655
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer LANCountdown 
      Interval        =   256
      Left            =   2040
      Top             =   2880
   End
   Begin VB.TextBox Countdown 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   0
      Locked          =   -1  'True
      TabIndex        =   3
      Text            =   "200 days, 23:10:04"
      Top             =   3960
      Width           =   2655
   End
   Begin VB.CommandButton SendMessage 
      Caption         =   "Send Message"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1080
      TabIndex        =   2
      Top             =   3600
      Width           =   1575
   End
   Begin VB.CommandButton Disconnect 
      Caption         =   "Menu"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   3600
      Width           =   975
   End
   Begin VB.Timer ListTimer 
      Interval        =   10000
      Left            =   1080
      Top             =   2400
   End
   Begin VB.ListBox LoginList 
      Height          =   3570
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2655
   End
   Begin VB.Menu ListViewMenu 
      Caption         =   "ListViewMenu"
      Visible         =   0   'False
      Begin VB.Menu mMessage 
         Caption         =   "Message"
      End
      Begin VB.Menu mInfo 
         Caption         =   "Info"
      End
      Begin VB.Menu mIP 
         Caption         =   "IP"
      End
   End
End
Attribute VB_Name = "ListView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim ListHeightDistance, ListWidthDistance
Dim MenuTopDistance
Dim SendTopDistance, SendWidthDistance
Dim CountdownTopDistance, CountdownWidthDistance

Public Sub GetControlLocations()
    ListHeightDistance = Me.Height - LoginList.Height
    ListWidthDistance = Me.Width - LoginList.Width
    MenuTopDistance = Me.Height - Disconnect.Top
    SendWidthDistance = Me.Width - SendMessage.Width
    SendTopDistance = Me.Height - SendMessage.Top
    CountdownWidthDistance = Me.Width - Countdown.Width
    CountdownTopDistance = Me.Height - Countdown.Top
End Sub

Public Sub ResizeForm()
    On Error Resume Next
    If Me.WindowState <> vbMinimized Then
    
        LoginList.Height = Me.Height - ListHeightDistance
        LoginList.Width = Me.Width - ListWidthDistance
        Disconnect.Top = Me.Height - MenuTopDistance
        SendMessage.Top = Me.Height - SendTopDistance
        SendMessage.Width = Me.Width - SendWidthDistance
        Countdown.Width = Me.Width - CountdownWidthDistance
        Countdown.Top = Me.Height - CountdownTopDistance
    End If
End Sub

Public Function IsValueInList(ByVal val As String)
    Dim i
    For i = 0 To LoginList.ListIndex - 1
        If LoginList.List(i) = val Then
            IsValueInList = True
            Exit Function
        End If
    Next i
    IsValueInList = False
End Function

Public Sub ParseLoginList(str As String)
    Dim arr, i, change As Boolean
    change = False
    
    arr = Split(str, ",")
    If UBound(arr) + 1 <> LoginList.ListCount Then
        change = True
    Else
        For i = 0 To UBound(arr)
            If Trim(arr(i)) <> "" And Trim(arr(i)) <> GetLoginName Then
                If Not IsValueInList(arr(i)) Then
                    change = True
                    Exit For
                End If
            End If
        Next i
    End If
    If change Then
        Dim selected As String
        selected = LoginList
        LoginList.Clear
        For i = 0 To UBound(arr)
            If Trim(arr(i)) <> "" And Trim(arr(i)) <> GetLoginName Then
                LoginList.AddItem (arr(i))
                If arr(i) = selected Then
                    LoginList.selected(LoginList.ListCount - 1) = True
                End If
            End If
        Next i
    End If
End Sub

Private Sub Disconnect_Click()
    SystrayMod.PopupMenu
End Sub

Private Sub Form_Activate()
    If ClientForm.AutoLogging = True Then
        Form_Unload (0)
        ClientForm.AutoLogging = False
    End If
End Sub

Private Sub Form_Load()
    Me.Icon = ClientForm.Icon
    GetControlLocations
    SetTransparent Me.hWnd, True
     
     Dim lResult As Long
     MakeTopMost Me.hWnd, True
     
End Sub

Private Sub Form_Resize()
    ResizeForm
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Cancel = 1
    Me.WindowState = vbMinimized
    Me.Hide
End Sub

Private Sub Timer1_Timer()

End Sub

Private Sub LANCountdown_Timer()
    Dim time As Double
    time = NextLANParty - Now
    Countdown = NextLANName & "->" & Fix(time) & " days," & Format(time, "hh:mm:ss")
    'NextLAN.Caption = NextLANName
End Sub

Private Sub ListTimer_Timer()
    glpSendMessage conLOGINLIST
End Sub


Private Sub LoginList_DblClick()
    Me.PopupMenu Me.ListViewMenu
End Sub

Private Sub mInfo_Click()
    glpSendMessage conINFO, LoginList
End Sub

Private Sub mIP_Click()
    glpSendMessage conIP, LoginList
End Sub

Private Sub mMessage_Click()
    SendMessage_Click
End Sub

Private Sub SendMessage_Click()
    If LoginList.ListIndex = -1 Then
        MsgBox "Please select someone from the list"
    Else
        CreateChatWindow LoginList
    End If
End Sub
