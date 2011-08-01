Attribute VB_Name = "TopMost"
Declare Function SetWindowPos Lib "user32" _
     (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, _
     ByVal x As Long, ByVal Y As Long, ByVal cx As Long, _
     ByVal cy As Long, ByVal wFlags As Long) As Long

     

Global Const SWP_NOMOVE = 2
Global Const SWP_NOSIZE = 1
Global Const FLAGS = SWP_NOMOVE Or SWP_NOSIZE
Global Const HWND_TOPMOST = -1
Global Const HWND_NOTOPMOST = -2

Sub MakeTopMost(hWnd As Long, TopMost As Boolean)
    Dim hWndT As Long
    If TopMost = True Then
        hWndT = HWND_TOPMOST
    Else
        hWndT = HWND_NOTOPMOST
    End If
    SetWindowPos hWnd, hWndT, 0, 0, 0, 0, FLAGS
End Sub

