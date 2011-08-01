Attribute VB_Name = "SetTransparentWindow"
Option Explicit

Const LWA_COLORKEY = &H1
Const LWA_ALPHA = &H2
Const GWL_EXSTYLE = (-20)
Const WS_EX_LAYERED = &H80000
Private Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hWnd As Long, ByVal nIndex As Long) As Long
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Private Declare Function SetLayeredWindowAttributes Lib "user32" (ByVal hWnd As Long, ByVal crKey As Long, ByVal bAlpha As Byte, ByVal dwFlags As Long) As Long

Private Const TransparentLevel = 240

Public Sub SetTransparent(ByVal hWnd As Long, Transparent As Boolean)
    On Error Resume Next
    Dim Ret As Long
    Ret = GetWindowLong(hWnd, GWL_EXSTYLE)
    Ret = Ret Or WS_EX_LAYERED
    'SetWindowLong hWnd, GWL_EXSTYLE, Ret
    'If IsMissing(RGB) Or RGB = 0 Then
    If Transparent = True Then
        SetLayeredWindowAttributes hWnd, 0, TransparentLevel, LWA_ALPHA
    Else
        SetLayeredWindowAttributes hWnd, 0, 255, LWA_ALPHA
    'Else
    '    SetLayeredWindowAttributes hWnd, RGB, 0, LWA_COLORKEY
    End If
End Sub
