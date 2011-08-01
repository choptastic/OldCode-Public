VERSION 5.00
Begin VB.Form SysTrayForm 
   Caption         =   "GummLANParty.net Messanger"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   Icon            =   "SysTrayForm.frx":0000
   LinkTopic       =   "Form1"
   OLEDropMode     =   1  'Manual
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   WindowState     =   1  'Minimized
   Begin VB.Menu mPopupSys 
      Caption         =   "Systray"
      NegotiatePosition=   1  'Left
      Begin VB.Menu mHomepage 
         Caption         =   "GummLANParty.net Homepage"
      End
      Begin VB.Menu mMessageboard 
         Caption         =   "Goto the Messageboard"
      End
      Begin VB.Menu mTimeSync 
         Caption         =   "Synchronize Time"
         Checked         =   -1  'True
      End
      Begin VB.Menu mOnTop 
         Caption         =   "Always On Top"
         Checked         =   -1  'True
      End
      Begin VB.Menu mEditProfile 
         Caption         =   "Edit Profile"
      End
      Begin VB.Menu break2 
         Caption         =   "-"
      End
      Begin VB.Menu mRestore 
         Caption         =   "Restore GLP.net"
         Visible         =   0   'False
      End
      Begin VB.Menu mHelp 
         Caption         =   "Help (Frequently Asked Questions)"
      End
      Begin VB.Menu mBugReport 
         Caption         =   "Submit Bug Report"
      End
      Begin VB.Menu mLogout 
         Caption         =   "Logout"
      End
      Begin VB.Menu break1 
         Caption         =   "-"
      End
      Begin VB.Menu mShutdown 
         Caption         =   "Shut Down"
      End
      Begin VB.Menu mAbout 
         Caption         =   "About and Version Info"
      End
      Begin VB.Menu CloseMenu 
         Caption         =   "Close Menu"
      End
   End
End
Attribute VB_Name = "SysTrayForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'******************************************************8
' SysTray Editor by Jesse Gumm
' How to Use:
' Make sure project has Modules: SysTrayCustomizable and SysTrayMod
' The Caption of SysrayForm is the tooltip when the mosue moves over the system tray icon
' The Menu executed by PopupMenu will use the menu for SysTrayForm
' You should customize this menu and the code fro the menu items on this form
' Change the contents of the code in the SysTrayCustomizable Functions
' Call RestoreSystemTrayIcon to Show the icon
' Call RemoveSystemTrayIcon to Hide the icon
' Call CreateSystemTrayIcon to initialize the icon
'   Advisable to use at beginning
'   a Window will flash on the screen quickly



Private Sub Form_MouseMove(Button As Integer, Shift As Integer, x As _
         Single, Y As Single)
      Dim Result As Long
      Dim msg As Long
      If Me.ScaleMode = vbPixels Then
        msg = x
       Else
        msg = x / Screen.TwipsPerPixelX
       End If
       Select Case msg
        Case WM_LBUTTONUP        '514 restore form window
         SysTrayLeftButton
        Case WM_LBUTTONDBLCLK    '515 restore form window
         SysTrayDoubleClick
        Case WM_RBUTTONUP        '517 display popup menu
         SysTrayRightClick
       End Select
      End Sub
      
      Private Sub Form_Unload(Cancel As Integer)
      
        RemoveSystemTrayIcon
        
      End Sub



Private Sub mAbout_Click()
    'MsgBox "GuLP Messenger Beta 0.2." & vbCrLf & "Current Features: Instant Messaging and Message board post notification.", vbInformation, "About GuLP"
    glpSendMessage conSERVERVERSION
    About.Show
End Sub

Private Sub mBugReport_Click()
    BugReport.Show
End Sub

Private Sub mEditProfile_Click()
    OpenURL "http://www.gummlanparty.net/login.asp?login=" & ClientForm.Login & "&pw=" & ClientForm.Password & "&page=/profile.asp"
End Sub

Private Sub mHelp_Click()
    OpenURL "http://www.gummlanparty.net/login.asp?login=" & ClientForm.Login & "&pw=" & ClientForm.Password & "&page=/faq.asp"
End Sub

Private Sub mHomepage_Click()
    'System.Diagnostics.Process.Start ("http://www.gummlanparty.net")
    OpenURL "http://www.gummlanparty.net/login.asp?login=" & ClientForm.Login & "&pw=" & ClientForm.Password & "&page=http://www.gummlanparty.net"
End Sub

Private Sub mLogout_Click()
    ClientForm.Disconnected
End Sub

Private Sub mMessageboard_Click()
    OpenURL "http://www.gummlanparty.net/login.asp?login=" & ClientForm.Login & "&pw=" & ClientForm.Password & "&page=/newforum.asp"
End Sub

Private Sub mOnTop_Click()
    mOnTop.Checked = Not (mOnTop.Checked)
    MakeTopMost ListView.hWnd, mOnTop.Checked
End Sub

Private Sub mRestore_Click()
    ListView.WindowState = vbNormal
    ListView.Show
End Sub

Private Sub mShutdown_Click()
    RemoveSystemTrayIcon
    End
End Sub

Private Sub mTimeSync_Click()
    mTimeSync.Checked = Not (mTimeSync.Checked)
    SetRegValue regCLIENT, "TimeSync", mTimeSync.Checked
    If mTimeSync.Checked Then
        glpSendMessage conNEWTIME
    End If
End Sub
