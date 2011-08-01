VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form ClientForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "GuLP"
   ClientHeight    =   2940
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4590
   Icon            =   "ClientForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2940
   ScaleWidth      =   4590
   StartUpPosition =   2  'CenterScreen
   Begin VB.CheckBox StartWithWindows 
      Caption         =   "Startup With Windows"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   2640
      Width           =   2775
   End
   Begin VB.CheckBox autologin 
      Caption         =   "Auto-login at startup"
      Enabled         =   0   'False
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   2400
      Width           =   2655
   End
   Begin VB.CommandButton Command3 
      Caption         =   "New? Sign Up!!"
      Height          =   375
      Left            =   120
      TabIndex        =   7
      Top             =   1680
      Width           =   4335
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   10000
      Left            =   4080
      Top             =   1920
   End
   Begin VB.CommandButton Command2 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   1200
      Width           =   4335
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   2280
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.CheckBox Remember 
      Caption         =   "Remember Login and Password"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2160
      Width           =   2655
   End
   Begin VB.TextBox Password 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2400
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   360
      Width           =   2055
   End
   Begin VB.TextBox Login 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Connect"
      Default         =   -1  'True
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   4335
   End
   Begin VB.Label Label2 
      Caption         =   "Password"
      Height          =   255
      Left            =   3000
      TabIndex        =   5
      Top             =   120
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Login"
      Height          =   255
      Left            =   840
      TabIndex        =   4
      Top             =   120
      Width           =   495
   End
End
Attribute VB_Name = "ClientForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public AutoLogging As Boolean


Private Sub Command1_Click()
    If Login = "" Or Password = "" Then
        MsgBox "Please Enter a Login and Password"
        Exit Sub
    End If
    If Remember Then
        SetRegValue regCLIENT, "Login", Login
        SetRegValue regCLIENT, "Password", Password
        SetRegValue regCLIENT, "AutoLogin", autologin
    Else
        SetRegValue regCLIENT, "Login", ""
        SetRegValue regCLIENT, "Password", ""
        SetRegValue regCLIENT, "AutoLogin", ""
    End If
    Timer1.Enabled = True
    Me.Caption = "Connecting . . . "
    Dim ip As String
    ip = GetRegValue(regCLIENT, "IPAddress")
    If ip = "" Then
        MsgBox "Registry Value IP Not found."
    Else
        Winsock1.Connect ip, 24365
        Command1.Enabled = False
        Password.Enabled = False
        Login.Enabled = False
    End If
End Sub

Sub Disconnected()
    Me.Caption = "Disconnected"
    Me.WindowState = vbNormal
    Command1.Enabled = True
    Login.Enabled = True
    Password.Enabled = True
    ListView.Hide
    If ClientForm.Visible = False Then
        ClientForm.Show
    End If
    Winsock1.Close
    Timer1.Enabled = False
    ListView.ListTimer.Enabled = False
    RemoveSystemTrayIcon
End Sub

Private Sub Command2_Click()
    Disconnected
End Sub

Private Sub Command3_Click()
    OpenURL "http://www.gummlanparty.net/newmember.asp"
End Sub

Private Sub Form_Load()
    'DoEvents
    Me.Show

    StartWithWindows = Abs(GetWindowsStartup)
        
    SetTransparent Me.hWnd, True
    DoEvents
    CreateSystemTrayIcon
    Dim auto, timesync
    Login = GetRegValue(regCLIENT, "Login")
    Password = GetRegValue(regCLIENT, "Password")
    auto = GetRegValue(regCLIENT, "AutoLogin")
    timesync = GetRegValue(regCLIENT, "TimeSync")
    If timesync = "" Then
        timesync = False
    End If
    SysTrayForm.mTimeSync.Checked = timesync
    If Login <> "" Then
        Remember = 1
        autologin.Enabled = True
    End If
    If auto = 1 Then
        autologin = 1
    Else
        autologin = 0
    End If
    If autologin.Enabled And autologin = 1 Then
        AutoLogging = True
        Me.WindowState = vbMinimized
        'Me.Hide
        Command1_Click
    Else
        AutoLogging = False
    End If
    RemoveSystemTrayIcon
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

Private Sub Login_GotFocus()
    Login.SelStart = 0
    Login.SelLength = Len(Login)
End Sub

Private Sub Password_GotFocus()
    Password.SelStart = 0
    Password.SelLength = Len(Password)
End Sub

Private Sub Remember_Click()
    If Remember.value = 0 Then
        autologin.Enabled = False
    Else
        autologin.Enabled = True
    End If
End Sub



Private Sub StartWithWindows_Click()
    SetWindowsStartup StartWithWindows
End Sub

Private Sub Timer1_Timer()
    MsgBox "Timed Out"
    Disconnected
End Sub

Private Sub Winsock1_Close()
    Disconnected
End Sub

Private Sub Winsock1_Connect()
    Me.Caption = "Connected"
End Sub

Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
    Dim data, strs, DataIn, i
    Winsock1.GetData DataIn, vbString, bytesTotal
    'MsgBox DataIn
    data = Split(DataIn, conEnd)
    For i = LBound(data) To UBound(data)
        If data(i) = "" Then Exit For
        strs = Split(data(i), conDelim)
        'On Error GoTo DAErrors
        
        Select Case strs(0)
            Case conLOGIN
                glpSendMessage conLOGIN, Login, Password
            Case conWELCOME
                ListView.Caption = "GuLP - " & Login
                Timer1.Enabled = False
                If AutoLogging = False Then
                    MsgBox strs(1)
                End If
                Me.Hide
                ListView.Show
                RestoreSystemTrayIcon
                ListView.ListTimer.Enabled = True
            Case conLOGINLIST
                ListView.ParseLoginList (strs(1))
            Case conBADLOGIN
                MsgBox "Login Rejected: " & strs(1)
            Case conMSG
                SendMessageToCorrectForm strs(1), strs(2)
            Case conIP
                 SendMessageToCorrectForm SERVERNAME, vbCrLf & "IP Address Query:" & vbCrLf & vbTab & "User : " & strs(1) & vbCrLf & vbTab & "IP Address : " & strs(2)
            Case conANNOUNCEMENT
                SendMessageToCorrectForm SERVERNAME, strs(1)
            Case conINFO
                Dim f As Info
                Set f = New Info
                f.Show
                f.Login = strs(1)
                f.fullname = strs(2)
            Case conNEXTLAN
                SetNextLANParty CDate(strs(1)), strs(2)
            Case conCHATSTATUS
                updateChatStatus strs(1), strs(2)
            Case conSERVERVERSION
                About.Server = strs(1)
            Case conCLIENTVERSION
                If strs(1) > ClientVersion Then
                    If MsgBox("Your Version : " & ClientVersion & vbCrLf & "Newest Version : " & strs(1) & vbCrLf & vbCrLf & "Would you like to download and install the newest version?  This process is completely automatic.", vbYesNo) = vbYes Then
                        Shell "AutoUpdater.exe", vbNormalFocus
                        RemoveSystemTrayIcon
                        End
                    End If
                End If
            Case conNEWTIME
                If SysTrayForm.mTimeSync.Checked Then
                    time = strs(1)
                    Date = strs(1)
                End If
            Case conNEWPOST
                If strs(3) <> Login Then
                    MessageBoardList.AddPost strs(1), strs(3), strs(2)
                End If
            Case Else
                glpSendMessage conINVALID, data(i)
        End Select
    Next i
    Exit Sub
DAErrors:
    MsgBox "There was a command from the server which was unrecognized by the GuLP Messenger, you may need to upgrade."
    glpSendMessage conINVALID, data(i)
    Exit Sub
End Sub
