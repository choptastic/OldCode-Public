Attribute VB_Name = "CountsVersion"
Global Version As String

Function GetVersion() As String
    'ChDir "d:\counts"
    'ChDrive "D:"
    On Error Resume Next
    If Version <> "" Then
        GetVersion = Version
    Else
    
        Open "version.cts" For Input As #1
            Input #1, Version
        Close #1
        GetVersion = Version
        If GetVersion = "" Then
            GetVersion = "<No Version>"
            Version = "<No Version>"
        End If
    End If
End Function

