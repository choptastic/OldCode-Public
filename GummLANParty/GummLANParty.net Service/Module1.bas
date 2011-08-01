Attribute VB_Name = "Module1"
Option Explicit
Global Const glpSERVER = 0
Global Const glpUNKNOWN = -1
Global Const glpALL = -2

Global MAXConnections  As Integer
Global NumberConnections As Integer
Global Logins() As String
Global db As Database
Global LastPost As Date

Sub SendNextLAN(ByVal ToIndex As Integer)
    On Error Resume Next
    Dim LANDate
    Dim LANName
    Dim rst As Recordset
    Set rst = db.OpenRecordset("Select * from LANParties where LANDate>now() order by LANDate;")
    If Not rst.EOF Then
        LANDate = rst![LANDate]
        LANName = "LAN Party " & rst![LANPartyID]
    End If
    ServerForm.SendPacket conNEXTLAN, ToIndex, LANDate, LANName
End Sub

Sub SendCurrentVersion(ByVal ToIndex As Integer)
    On Error Resume Next
    If ServerForm.VersionText <> "" Then
        ServerForm.SendPacket conCLIENTVERSION, ToIndex, ServerForm.VersionText
    End If
End Sub

Function IsValidLogin(log, pw) As Boolean
    Dim rs As Recordset
    Set rs = db.OpenRecordset("Select * from logins where login='" & log & "' and password='" & pw & "' and active=yes;")
    If rs.RecordCount > 0 Then
        IsValidLogin = True
    Else
        IsValidLogin = False
    End If
End Function


Function BuildConnectedList()
    Dim cl() As String
    Dim i
    Dim num
    num = 0
    For i = 0 To UBound(Logins)
        If Logins(i) <> "" Then
            num = num + 1
            ReDim Preserve cl(num)
            cl(num - 1) = Logins(i)
        End If
    Next i
    BuildConnectedList = cl
End Function

Function GetLoginInfo(ByVal LoginName As String) As String
    'On Error Resume Next
    Dim rst As Recordset
    Set rst = db.OpenRecordset("Select * from logins where Login='" & LoginName & "'")
    If Not rst.EOF Then
        GetLoginInfo = rst![First] & " " & rst![Last]
    End If
End Function

Sub Main()
    Dim dbloc As String
    dbloc = GetRegValue(regSERVER, "Database")
    If dbloc = "" Then
        MsgBox "Database not found.  Set up, g-dog"
        End
    End If
    Set db = OpenDatabase(dbloc)
    ServerForm.Show
End Sub
