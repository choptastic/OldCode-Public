Attribute VB_Name = "ClientFunctions"
Option Explicit

Global NextLANParty As Date
Global NextLANName As String

Public Sub SetNextLANParty(ByVal LANDate As Date, ByVal LANName As String)
    'On Error Resume Next
    NextLANParty = LANDate
    NextLANName = LANName
    ListView.LANCountdown.Enabled = True
End Sub

Public Sub glpSendMessage(msg As String, Optional Arg1, Optional Arg2, Optional Arg3)
    If ClientForm.Winsock1.state = sckConnected Then
        Dim message
        message = msg
        If Not IsMissing(Arg1) Then
            msg = msg & conDelim & Arg1
            If Not IsMissing(Arg2) Then
                msg = msg & conDelim & Arg2
                If Not IsMissing(Arg3) Then
                    msg = msg & conDelim & Arg3
                End If
            End If
        End If
    Else
        ClientForm.Disconnected
        Exit Sub
    End If
    ClientForm.Winsock1.SendData msg & conEnd
    
End Sub

Public Function GetLoginName() As String
    GetLoginName = ClientForm.Login
End Function

Public Function GetWindowsStartup() As Boolean
    If QueryValue(HKLM, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", "GuLP") <> "" Then
        GetWindowsStartup = True
    Else
        GetWindowsStartup = False
    End If
End Function

Public Sub SetWindowsStartup(val As Integer)
    Dim q
    q = Chr(34)
    If val = 1 Then
        SetStringValue HKLM, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", "GuLP", q & App.Path & "\GuLP.exe" & q
    Else
        DeleteValue HKLM, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", "GuLP"
    End If
        
End Sub

Function IsOnline(ChatName As String) As Boolean
    Dim i
    For i = 0 To ListView.LoginList.ListCount - 1
        If ListView.LoginList.List(i) = ChatName Then
            IsOnline = True
            Exit Function
        End If
    Next i
    IsOnline = False
End Function
