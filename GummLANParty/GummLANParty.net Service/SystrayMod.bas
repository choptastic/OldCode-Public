Attribute VB_Name = "SystrayMod"
'user defined type required by Shell_NotifyIcon API call
      Public Type NOTIFYICONDATA
       cbSize As Long
       hWnd As Long
       uId As Long
       uFlags As Long
       uCallBackMessage As Long
       hIcon As Long
       szTip As String * 64
      End Type

      'constants required by Shell_NotifyIcon API call:
      Public Const NIM_ADD = &H0
      Public Const NIM_MODIFY = &H1
      Public Const NIM_DELETE = &H2
      Public Const NIF_MESSAGE = &H1
      Public Const NIF_ICON = &H2
      Public Const NIF_TIP = &H4
      Public Const WM_MOUSEMOVE = &H200
      Public Const WM_LBUTTONDOWN = &H201     'Button down
      Public Const WM_LBUTTONUP = &H202       'Button up
      Public Const WM_LBUTTONDBLCLK = &H203   'Double-click
      Public Const WM_RBUTTONDOWN = &H204     'Button down
      Public Const WM_RBUTTONUP = &H205       'Button up
      Public Const WM_RBUTTONDBLCLK = &H206   'Double-click

      Public Declare Function SetForegroundWindow Lib "user32" _
      (ByVal hWnd As Long) As Long
      Public Declare Function Shell_NotifyIcon Lib "shell32" _
      Alias "Shell_NotifyIconA" _
      (ByVal dwMessage As Long, pnid As NOTIFYICONDATA) As Boolean

      Public nid As NOTIFYICONDATA
      

Public Sub CreateSystemTrayIcon()

    Dim f As Form
    Set f = Screen.ActiveForm
    SysTrayForm.Show
    SysTrayForm.Refresh
    InitSystemTrayIcon
    SysTrayForm.Hide
    On Error Resume Next
    f.Show
End Sub

Public Sub InitSystemTrayIcon()
    With nid
        .cbSize = Len(nid)
        .hWnd = SysTrayForm.hWnd
        .uId = vbNull
        .uFlags = NIF_ICON Or NIF_TIP Or NIF_MESSAGE
        .uCallBackMessage = WM_MOUSEMOVE
        .hIcon = SysTrayForm.Icon
        .szTip = SysTrayForm.Caption & vbNullChar
       End With
       
End Sub

Public Sub RestoreSystemTrayIcon()
    Shell_NotifyIcon NIM_ADD, nid
End Sub

Public Sub RemoveSystemTrayIcon()
    Shell_NotifyIcon NIM_DELETE, nid
    'Unload SysTrayForm
End Sub

Public Sub PopupMenu()
    SysTrayForm.PopupMenu SysTrayForm.mPopupSys
End Sub
