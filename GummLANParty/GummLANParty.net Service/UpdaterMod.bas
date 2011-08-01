Attribute VB_Name = "UpdaterMod"
Private Declare Function URLDownloadToFile Lib "urlmon" Alias "URLDownloadToFileA" _
        (ByVal pCaller As Long, _
            ByVal szURL As String, _
            ByVal szFileName As String, _
            ByVal dwReserved As Long, _
            ByVal lpfnCB As Long) As Long

Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function DestroyWindow Lib "user32" (ByVal hwnd As Long) As Long




Public Sub Main()
    'ChDir "d:\gummlanparty.net service"
    'ChDrive "d"
    Dim CurProc As String
    On Error Resume Next
    MkDir "backup"
    On Error GoTo 0
    Dim hwnd As Long
    Dim RemoteFile() As String, LocalFile() As String
    ReDim RemoteFile(0) As String
    ReDim LocalFile(0) As String
    
    Dim line As String
    DoEvents
    'On Error Resume Next
    Dim d
    CurProc = "Deleting Previous Updates"
    d = Dir("*.gulp")
    While d <> ""
        Kill d
        d = Dir
    Wend
    CurProc = "Downloading File List"
    Dim URL As String
    URL = "http://www.gummlanparty.net/GuLPUpdates/"
    ExecCmd "URLDownloadToFile.exe " & URL & "update.gulp " & "update.gulp"
    On Error GoTo Unsuccessful
    
    CurProc = "Parsing File List"
    Open "update.gulp" For Input As #1
        While Not EOF(1)
            Line Input #1, line
            RemoteFile(UBound(RemoteFile)) = Split(line, ":")(0)
            LocalFile(UBound(LocalFile)) = Split(line, ":")(1)
            ReDim Preserve LocalFile(UBound(LocalFile) + 1) As String
            ReDim Preserve RemoteFile(UBound(RemoteFile) + 1) As String
        Wend
    Close #1
    CurProc = "Generating Command Line for Update Downloads"
    line = "URLDownloadtofile.exe "
    For i = 0 To UBound(RemoteFile) - 1
        line = line & URL & RemoteFile(i) & " " & RemoteFile(i) & " "
    Next i
    CurProc = "Downloading New Files : " & vbCrLf & line
    ExecCmd line
    
    
    For i = 0 To UBound(LocalFile) - 1
        d = Dir(LocalFile(i))
         While d <> ""
            CurProc = "Backing Up " & LocalFile(i)
            FileCopy LocalFile(i), "backup\" & LocalFile(i)
            
            CurProc = "Deleting " & LocalFile(i)
            If UCase(LocalFile(i)) = "GULP.EXE" Then
                On Error Resume Next
            Else
                On Error GoTo 0
            End If
            Kill LocalFile(i)
            On Error GoTo 0
            d = Dir(LocalFile(i))
        Wend
        CurProc = "Renaming " & RemoteFile(i)
        Name RemoteFile(i) As LocalFile(i)
    Next i
    
    CurProc = "Deleging Update File List"
    d = Dir("update.gulp")
    If d <> "" Then Kill d
        
    MsgBox "Update Complete"
    Shell "gulp.exe", vbNormalFocus
    End
Unsuccessful:
    MsgBox "There were errors in the update process:" & CurProc
    Shell "gulp.exe", vbNormalFocus
    End
End Sub

