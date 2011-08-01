Attribute VB_Name = "GotoURL"
Private Const SW_SHOW = 5       ' Displays Window in its current size
                                      ' and position
Private Const SW_SHOWNORMAL = 1 ' Restores Window if Minimized or
                                ' Maximized

Private Declare Function ShellExecute Lib "shell32.dll" Alias _
   "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As _
   String, ByVal lpFile As String, ByVal lpParameters As String, _
   ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long

Private Declare Function FindExecutable Lib "shell32.dll" Alias _
   "FindExecutableA" (ByVal lpFile As String, ByVal lpDirectory As _
   String, ByVal lpResult As String) As Long
   
Sub OpenURL(ByVal URL As String)
    Dim Dummy As String
    Dim BrowserExec As String * 255
    Dim RetVal As Long
    Dim FileNumber As Integer
    BrowserExec = Space(255)
    FileNumber = FreeFile
    Open "temp.htm" For Output As #FileNumber
        Write #FileNumber, "<HTML> <\HTML>"
    Close #FileNumber
    RetVal = FindExecutable("temp.htm", Dummy, BrowserExec)
    BrowserExec = Trim(BrowserExec)
    If RetVal <= 32 Or IsEmpty(BrowserExec) Then ' Error
        MsgBox "Could not find associated Browser", vbExclamation, _
          "Browser Not Found"
    Else
        RetVal = ShellExecute(0, "open", BrowserExec, _
          URL, Dummy, SW_SHOWNORMAL)
    End If

End Sub
