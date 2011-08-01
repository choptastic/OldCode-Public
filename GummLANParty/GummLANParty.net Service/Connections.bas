Attribute VB_Name = "Connections"
Global Const conLOGIN = "LOGIN"
Global Const conMSG = "MSG"
Global Const conINVALID = "INVALID"
Global Const conNEWPOST = "NEWPOST"
Global Const conWELCOME = "WELCOME"
Global Const conBADLOGIN = "BADLOGIN"
Global Const conLOGINLIST = "LOGINLIST"
Global Const conDISCONNECT = "DISCONNECT"
Global Const conIP = "IP"
Global Const conINFO = "INFO"
Global Const conANNOUNCEMENT = "ANNOUNCEMENT"
Global Const conCHAT = "CHAT"
Global Const conCHATSTATUS = "CHATSTATUS"
Global Const conNEXTLAN = "NEXTLAN"
Global Const conSERVERVERSION = "SERVERVERSION"
Global Const conBUG = "BUG"
Global Const conCLIENTVERSION = "CLIENTVERSION"
Global Const conNEWTIME = "NEWTIME"

Global Const conDelim = "%Delim%"
Global Const conEnd = "%End%"

Global Const SERVERNAME = "Server"

Global Const stsACTIVE = "ACTIVE"
Global Const stsIDLE = "IDLE"
Global Const stsAWAY = "AWAY"
Global Const stsOFFLINE = "OFFLINE"


Global Const regSERVER = 0
Global Const regCLIENT = 1

Global Const PostDelim = " -> "

Global Const ServerRootKey = HKLM
Global Const ClientRootKey = HKLM
Global Const ServerKey = "software\GummLANParty.net\Server"
Global Const ClientKey = "software\GummLANParty.net\Client"

Public Function GetRegValue(ByVal ServerOrClient As Integer, ByVal value As String) As String
    Dim Root As Long, Key As String
    If ServerOrClient = regSERVER Then
        Root = ServerRootKey
        Key = ServerKey
    ElseIf ServerOrClient = regCLIENT Then
        Root = ClientRootKey
        Key = ClientKey
    Else
        Err.Raise 11112, "Server or Client ot specified", "Expected regSERVER or regCLIENT"
    End If
    GetRegValue = QueryValue(Root, Key, value)
End Function

Public Sub SetRegValue(ByVal ServerOrClient As Integer, ByVal SValue As String, value As String)
    Dim Root As Long, Key As String
    If ServerOrClient = regSERVER Then
        Root = ServerRootKey
        Key = ServerKey
    ElseIf ServerOrClient = regCLIENT Then
        Root = ClientRootKey
        Key = ClientKey
    Else
        Err.Raise 11112, "Server or Client ot specified", "Expected regSERVER or regCLIENT"
    End If
    SetStringValue Root, Key, SValue, value
End Sub


Public Function IsStateAcceptable(state As Integer) As Boolean
    IsStateAcceptable = False
    If state = sckConnected Then
        IsStateAcceptable = True
    End If
End Function
