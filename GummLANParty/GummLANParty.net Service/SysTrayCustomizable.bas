Attribute VB_Name = "SysTrayCustomizable"
Option Explicit


Public Sub SysTrayLeftButton()
        ListView.WindowState = vbNormal
    ListView.Show
End Sub

Public Sub SysTrayDoubleClick()
    ListView.WindowState = vbNormal
    ListView.Show
End Sub

Public Sub SysTrayRightClick()
    PopupMenu
End Sub
