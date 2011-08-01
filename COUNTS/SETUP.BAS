Attribute VB_Name = "SETUP"
Global act_time As Integer
Global activate As Integer
Global Const Resettime1 = 60 * 1 + 0
Global Const Resettime2 = 60 * 2 + 0
Global Const CheckCounts = 203
Global Const CountsDone = 205
Global Const Recounts = 204
Global Acknowledged As Integer
Global Const ThresholdFile = "threshold.cts"
Global Const Checkloc = "temp\check.cts"
Global Const Dailyloc = "daily\"
Global Const Itemsloc = "items.lst"
Global Const Wastefile = "temp\waste.cts"
Global Const Setupfile = "counts.stp"
Global Const CloseMessage = 2000
Global Const StayOpenMessage = 1999
Global Const AutoCheckFile = "temp\autocheck.cts"
Global datefilename As String
Global textfile As String


Declare Function SetWindowPos Lib "user32" _
(ByVal hWnd As Long, ByVal hWndInsertAfter As Long, _
ByVal X As Long, ByVal Y As Long, ByVal cx As Long, _
ByVal cy As Long, ByVal wFlags As Long) As Long

Global Const SWP_NOMOVE = 2
Global Const SWP_NOSIZE = 1
Global Const FLAGS = SWP_NOMOVE Or SWP_NOSIZE
Global Const HWND_TOPMOST = -1
Global Const HWND_NOTOPMOST = -2



Sub maketextfilename()
Dim yyyy, mm, dd As String
    yyyy = Year(Now)
    If (Month(Now) < 10) Then
        mm = "0" & Month(Now)
    Else
        mm = Month(Now)
    End If
    If (Day(Now) < 10) Then
        dd = "0" & Day(Now)
    Else
        dd = Day(Now)
    End If
    textfile = App.path & "\" & Dailyloc & yyyy & mm & dd & ".htm"
End Sub







