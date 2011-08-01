Attribute VB_Name = "ModForm"
Option Explicit

Global ChatForms() As Chat
Global NumForms As Integer

Public Sub InitChatforms()
    NumForms = 0
End Sub

Public Sub CreateChatWindow(ToName As String, Optional ByVal InitMsg As String)
    Dim i, found As Boolean, Loc As Integer
    For i = 0 To NumForms - 1
        If UCase(ChatForms(i).GetChatName) = UCase(ToName) Then
            ChatForms(i).Show
            Loc = i
            found = True
        End If
    Next i
    'If found = False Then
    '    For i = 0 To NumForms - 1
    '        If ChatForms(i).Visible = False Then
    '            ChatForms(i).SetChatName (ToName)
    '            ChatForms(i).Show
    '            Exit Sub
    '        End If
    '    Next i
    'End If
    
    If Not found Then
        NumForms = NumForms + 1
        ReDim Preserve ChatForms(0 To NumForms - 1) As Chat
        Set ChatForms(NumForms - 1) = New Chat
        ChatForms(NumForms - 1).SetChatName (ToName)
        ChatForms(NumForms - 1).Show
        Loc = NumForms - 1
    End If
    If InitMsg <> "" Then
        ChatForms(Loc).Incoming InitMsg
    End If
End Sub


Public Sub SendMessageToCorrectForm(ByVal ToName As String, ByVal msg As String)
    Dim i
    For i = 0 To NumForms - 1
        If UCase(ChatForms(i).GetChatName) = UCase(ToName) Then
            ChatForms(i).Incoming msg
            Exit Sub
        End If
    Next i
    
    CreateChatWindow ToName, msg
End Sub

Public Sub updateChatStatus(ByVal ToName As String, ByVal status As String)
    Dim i
    For i = 0 To NumForms - 1
        If ChatForms(i).GetChatName = ToName Then
            ChatForms(i).UpdateStatus (status)
        End If
    Next i
End Sub

