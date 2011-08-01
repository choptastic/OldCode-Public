Attribute VB_Name = "Module1"



Sub CreateProgramGroup(WorkingDir As String)
    'fCreateShellLink "Startup", "Counts Calculator Startup", WorkingDir & "\office.exe", "-noprompt"
    'fCreateShellLink ".", "Counts Calculator Office Side", WorkingDir & "\office.exe", ""
    'fCreateShellLink ".", "Counts Calculator Setup", WorkingDir & "\setup.exe", ""
    Dim d
    d = Dir("Counts Calculator*.doc")
    'fCreateShellLink ".", "Counts Calculator Manual", WorkingDir & "\" & d, ""
End Sub
