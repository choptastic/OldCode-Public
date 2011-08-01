VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form ServerForm 
   Caption         =   "GummLANParty Update Server"
   ClientHeight    =   5355
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6600
   LinkTopic       =   "Form1"
   ScaleHeight     =   5355
   ScaleWidth      =   6600
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox VersionText 
      Height          =   285
      Left            =   3840
      TabIndex        =   11
      Top             =   5040
      Width           =   735
   End
   Begin VB.Timer Scheduled 
      Interval        =   65535
      Left            =   4200
      Top             =   120
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Send Announcement"
      Height          =   255
      Left            =   2520
      TabIndex        =   9
      Top             =   4680
      Width           =   3975
   End
   Begin VB.TextBox Announcement 
      Height          =   975
      Left            =   2520
      TabIndex        =   8
      Top             =   3600
      Width           =   3975
   End
   Begin VB.Timer ForumChecker 
      Interval        =   1000
      Left            =   2400
      Top             =   600
   End
   Begin VB.CommandButton ClearEvents 
      Caption         =   "Clear"
      Height          =   255
      Left            =   5640
      TabIndex        =   7
      Top             =   0
      Width           =   855
   End
   Begin VB.ListBox EventList 
      Height          =   3180
      Left            =   2520
      TabIndex        =   5
      Top             =   360
      Width           =   3975
   End
   Begin VB.CommandButton Kick 
      Caption         =   "Kick"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   5040
      Width           =   2295
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Index           =   0
      Left            =   600
      Top             =   1560
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      LocalPort       =   24365
   End
   Begin VB.ListBox loginlist 
      Height          =   2400
      Left            =   120
      TabIndex        =   2
      Top             =   2520
      Width           =   2295
   End
   Begin VB.TextBox MOTD 
      Height          =   1815
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Text            =   "ServerForm.frx":0000
      Top             =   360
      Width           =   2295
   End
   Begin VB.Label Label4 
      Caption         =   "Current Version:"
      Height          =   255
      Left            =   2520
      TabIndex        =   10
      Top             =   5040
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "Events"
      Height          =   255
      Left            =   2520
      TabIndex        =   6
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Currently Logged In"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2280
      Width           =   2295
   End
   Begin VB.Label Label1 
      Caption         =   "Welcome Message/ MOTD"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2295
   End
End
Attribute VB_Name = "ServerForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim CurrentPerson As Integer

Public Sub ClearFromList(ByVal Login As String)
    Dim i
    For i = 0 To loginlist.ListCount - 1
        If Logins(i) = Login Then
            Winsock1_Close (i)
        End If
    Next i
End Sub

Public Sub SendNewTime(toindex As Integer)
    SendPacket conNEWTIME, toindex, CStr(Now)
End Sub


Public Sub SendPacket(cmd As String, ByVal toindex As Integer, Optional Param1, Optional Param2, Optional Param3)
    On Error Resume Next
    Dim msg
    msg = cmd
    If Not IsMissing(Param1) Then
        msg = cmd & conDelim & Param1
        If Not IsMissing(Param2) Then
            msg = msg & conDelim & Param2
            If Not IsMissing(Param3) Then
                msg = msg & conDelim & Param3
            End If
        End If
    End If
    'On Error GoTo SendErr
    
    'If Cmd = conMSG Then MsgBox msg
    'Winsock1(ToIndex).state
    If Winsock1(toindex).state = sckConnected Then
        Winsock1(toindex).SendData msg & conEnd
        AddEvent glpSERVER, msg, Winsock1(toindex).RemoteHostIP
    End If
End Sub

Public Sub SendMassMessage(message As String)
    Dim i As Integer
    For i = 1 To loginlist.ListCount - 1
        If Winsock1(i).state = sckConnected Then
            SendPacket conANNOUNCEMENT, i, message
        End If
    Next i
End Sub


Public Function SendMsg(ByVal ToName As String, ByVal FromName As String, ByVal msg As String) As Boolean
    Dim wsi As Integer ' Winsock Index
    wsi = -1
    Dim i
    For i = 0 To loginlist.ListCount - 1
        If loginlist.List(i) = ToName Then
            wsi = i
            Exit For
        End If
    Next i
    If wsi = -1 Then
        SendMsg = False
    Else
        SendPacket conMSG, wsi, FromName, msg
    End If
    
End Function

Public Sub SendPostMessage(ByVal ID As Integer, ByVal Subject As String, ByVal From As String)
    Dim i As Integer
    For i = 0 To loginlist.ListCount - 1
        If Winsock1(i).state = sckConnected Then
            SendPacket conNEWPOST, i, ID, Subject, From
        End If
    Next i
End Sub

Function FindDest(ByVal DestName As String)
    Dim i
    For i = 0 To loginlist.ListCount - 1
        If DestName = loginlist.List(i) Then
            FindDest = i
            Exit Function
        End If
    Next i
End Function

Public Sub SetLoginList()
    Dim i
    loginlist.Clear
    For i = 0 To UBound(Logins)
        loginlist.AddItem Logins(i)
    Next i
End Sub

Public Sub AddEvent(index, data, ip)
    Dim n, strs, formatted, cmd
    Dim fn
    strs = Split(data, conDelim)
    cmd = strs(0)
    formatted = strs(0)
    For n = 1 To UBound(strs) - 1
        formatted = formatted & " : " & strs(n)
    Next n
    If cmd <> conLOGINLIST And cmd <> conNEXTLAN And cmd <> conNEWTIME Then
        fn = FreeFile
        
        
        If index = glpSERVER Then
            n = "Server"
        ElseIf index = glpUNKNOWN Then
            n = ""
        ElseIf index = glpALL Then
            n = "All"
        Else
            n = Logins(index)
        End If
        EventList.AddItem Now & " > " & ip & " > " & n & " -- " & formatted
        If EventList.ListCount > 1000 Then
            EventList.Clear
            EventList.AddItem "EventList Cleared, stored in Log File"
        End If
        
        Open "log.txt" For Append As #fn
            Print #fn, Now & " > " & ip & " > " & n & " -- " & formatted
        Close #fn
    End If
End Sub


Public Function FindOpenWinsock() As Integer
    Dim i
    For i = 1 To MAXConnections
        If Winsock1(i).state = 0 Then
        FindOpenWinsock = i
        Exit Function
        End If
    Next i
    FindOpenWinsock = -1
End Function

Private Sub Command1_Click()
    If Trim(Announcement) = "" Then
        MsgBox "empty . . . not sent"
    Else
        SendMassMessage (Announcement)
    End If
    Announcement = ""
End Sub

Private Sub EventList_DblClick()
    MsgBox EventList
End Sub

Private Sub Form_Load()
    MOTD = GetRegValue(regSERVER, "motd")
    Winsock1(0).Listen
    Dim rst As Recordset
    Set rst = db.OpenRecordset("Select * from forum order by [date] DESC;")
    If Not rst.EOF Then
        LastPost = rst![Date]
    End If
    rst.Close
    VersionText = ClientVersion
End Sub

Private Sub List1_Click()

End Sub

Private Sub Form_Resize()
    If Me.Width < 2745 Then
        EventList.Width = 1
    Else
        EventList.Width = Me.Width - 2745
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    db.Execute "update logins set online=no"
End Sub

Private Sub ForumChecker_Timer()
    
    'Check forum
    Dim rst As Recordset
    Set rst = db.OpenRecordset("Select * from forum order by [date] DESC;")
    If Not rst.EOF Then
        If rst![Date] > LastPost Then
            LastPost = rst![Date]
            SendPostMessage rst![ID], rst![Subject], rst![Name]
        End If
    End If
    rst.Close
    
    'Check winsock states
    Dim i
    For i = 1 To loginlist.ListCount - 1
        If Winsock1(i).state <> sckConnected And Winsock1(i).state <> sckClosed Then
            Winsock1_Close (i)
        End If
    Next i
End Sub

Private Sub Kick_Click()
    If loginlist.ListIndex > 0 Then
        Winsock1(loginlist.ListIndex).Close
        Logins(loginlist.ListIndex) = ""
        SetLoginList
    End If
End Sub

Private Sub MOTD_Change()
    SetRegValue regSERVER, "MOTD", MOTD
End Sub



Private Sub Scheduled_Timer()
    'On Error Resume Next
    CurrentPerson = CurrentPerson + 1
    If CurrentPerson > loginlist.ListCount - 1 Then
        CurrentPerson = 1
    End If
    SendNextLAN CurrentPerson
    'SendCurrentVersion CurrentPerson
    SendNewTime CurrentPerson
    
    Dim rst As Recordset
    Set rst = db.OpenRecordset("Select * from ScheduledMessages where now()>ScheduledDate and Sent=No")
    While Not rst.EOF
        SendMassMessage rst![scheduledmessage]
        rst.MoveNext
    Wend
    rst.Close
    db.Execute "Update ScheduledMessages set Sent=Yes where now()>ScheduledDate"
End Sub

Private Sub Winsock1_Close(index As Integer)
    'MsgBox "Connection with index " & Index & " lost"
    db.Execute "update logins set online=no where login='" & loginlist.List(index) & "';"
    
    AddEvent index, "Disconnected", Winsock1(index).RemoteHostIP
    
    Logins(index) = ""
    Winsock1(index).Close
    SetLoginList
End Sub

Private Sub Winsock1_ConnectionRequest(index As Integer, ByVal requestID As Long)
    Dim i, used
    If index = 0 Then
        i = FindOpenWinsock
        If i = -1 Then
            MAXConnections = MAXConnections + 1
            Load Winsock1(MAXConnections)
            ReDim Preserve Logins(MAXConnections)
            
            Winsock1(MAXConnections).Close
            Winsock1(MAXConnections).Accept requestID
            'MsgBox "Connection Accepted"
            used = MAXConnections
        Else
            Winsock1(i).Close
            Winsock1(i).Accept requestID
            used = i
        End If
        AddEvent glpUNKNOWN, "Con Req", Winsock1(used).RemoteHostIP
        Winsock1(used).SendData conLOGIN
    Else
        Winsock1(index).Close
        Winsock1(index).Listen
    End If
    
End Sub

Private Sub Winsock1_DataArrival(index As Integer, ByVal bytesTotal As Long)
    Dim data, datain
    Winsock1(index).GetData data, vbString, bytesTotal
    data = Split(data, conEnd)
    Dim dest, i
    'MsgBox LBound(data) & " : " & UBound(data)
    For i = LBound(data) To UBound(data)
        If data(i) = "" Then Exit For
        AddEvent index, data(i), ""
        Dim strs
        strs = Split(data(i), conDelim)
        Select Case (strs(0))
            Case conLOGIN
                If IsValidLogin(strs(1), strs(2)) Then
                    SendPacket conWELCOME, index, MOTD
                    SendNextLAN index
                    SendCurrentVersion index
                    ClearFromList strs(1)
                    Logins(index) = strs(1)
                    SetLoginList
                    db.Execute "update logins set online=yes where login='" & Logins(index) & "';"
                    SendNewLoginList (index)
                Else
                    SendPacket conBADLOGIN, index, "Invalid Login or Password"
                    
                    Winsock1(index).Close
                End If
            Case conMSG
                SendMsg strs(1), loginlist.List(index), strs(2)
            Case conIP
                dest = FindDest(strs(1))
                SendPacket conIP, index, strs(1), Winsock1(dest).RemoteHostIP
            Case conINFO
                Dim UserInfo
                'dest = FindDest(strs(1))
                UserInfo = GetLoginInfo(strs(1))
                SendPacket conINFO, index, strs(1), UserInfo
            Case conLOGINLIST
                SendNewLoginList (index)
            Case conSERVERVERSION
                SendPacket conSERVERVERSION, index, ServerVersion
            Case conNEWTIME
                SendNewTime index
            Case conBUG
                Open strs(1) & ".txt" For Append As #1
                    Print #1, "---Begin New Bug Report from " & loginlist.List(index) & "---"
                    Print #1, strs(2)
                Close #1
                SendMsg loginlist.List(index), SERVERNAME, "Thank you for your bug report, it has been archived and Gumm has been notified"
            Case conCHATSTATUS
                dest = FindDest(strs(1))
                If dest > 0 Then
                    SendPacket conCHATSTATUS, dest, loginlist.List(index), strs(2)
                End If
        End Select
    Next i
End Sub

Sub SendNewLoginList(toindex As Integer)
    Dim msg
    Dim i As Integer, c
    For i = 0 To loginlist.ListCount - 1
        If Trim(loginlist.List(i)) <> "" Then
           msg = msg & loginlist.List(i) & ","
        End If
    Next i
    'MsgBox msg
    'For i = 0 To loginlist.ListCount - 1
        If IsStateAcceptable(Winsock1(toindex).state) Then
            SendPacket conLOGINLIST, toindex, msg
            
        End If
    'Next i
    'AddEvent glpALL, msg, ""
    
End Sub
