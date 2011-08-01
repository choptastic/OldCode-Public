VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Counts Calculator v2.0 - Office Side"
   ClientHeight    =   7950
   ClientLeft      =   1530
   ClientTop       =   615
   ClientWidth     =   4335
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00000000&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   7950
   ScaleWidth      =   4335
   Begin VB.CommandButton view 
      Caption         =   "View Counts"
      Height          =   375
      Left            =   2520
      TabIndex        =   10
      Top             =   7200
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Minimize"
      Height          =   255
      Left            =   3360
      TabIndex        =   5
      Top             =   7680
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "<-"
      Height          =   375
      Left            =   2040
      TabIndex        =   4
      Top             =   7560
      Width           =   375
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Waste"
      Height          =   375
      Left            =   1320
      TabIndex        =   3
      Top             =   7560
      Width           =   735
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Done"
      Height          =   375
      Left            =   0
      TabIndex        =   2
      Top             =   7560
      Width           =   1095
   End
   Begin VB.ListBox List2 
      Height          =   7080
      ItemData        =   "OFFICE.frx":0000
      Left            =   1560
      List            =   "OFFICE.frx":0002
      MultiSelect     =   1  'Simple
      TabIndex        =   1
      Top             =   360
      Width           =   855
   End
   Begin VB.ListBox List1 
      Height          =   7080
      ItemData        =   "OFFICE.frx":0004
      Left            =   0
      List            =   "OFFICE.frx":0006
      MultiSelect     =   1  'Simple
      TabIndex        =   0
      Top             =   360
      Width           =   1575
   End
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   5280
      Top             =   720
   End
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   4440
      Top             =   840
   End
   Begin VB.Label Label4 
      Caption         =   "Count"
      Height          =   255
      Left            =   1680
      TabIndex        =   9
      Top             =   120
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "Item Name"
      Height          =   255
      Left            =   360
      TabIndex        =   8
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Counts Calculator v2.0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   2520
      TabIndex        =   7
      Top             =   0
      Width           =   1695
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   $"OFFICE.frx":0008
      ForeColor       =   &H80000008&
      Height          =   6615
      Left            =   2520
      TabIndex        =   6
      Top             =   480
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim rec() As Integer
Dim oldwastes As Integer

Sub LoadWastes(Optional Autocheck = False)
    Dim add As String
    Form6.List1.Clear
    On Error GoTo noload
    Open Wastefile For Input As #2
    While Not EOF(2)
        Line Input #2, add
        Form6.List1.AddItem add
    Wend
    Close #2
    
    If Not Autocheck Then
        If oldwastes <> Form6.List1.ListCount Then Form6.Show
        oldwastes = Form6.List1.ListCount
    Else
        oldwastes = 0
    End If
noload:
    
End Sub


Sub PrintCounts()
    PrintHTMLFile textfile
End Sub

Sub MakeList()
    
    List1.Clear
    List2.Clear

    
    Dim add As String
    'Load Item List
On Error GoTo noitemlist
'MsgBox CurDir
    Open Itemsloc For Input As #2
    While (Not EOF(2))
        Input #2, add
        List1.AddItem (add)
    Wend
    Close #2
    ReDim Preserve rec(List1.ListCount)
 'Load Check File with final counts
On Error GoTo nocheckfile
    Open Checkloc For Input As #2
    If (Not EOF(2)) Then Line Input #2, add

    While (Not EOF(2))
        Line Input #2, add
        List2.AddItem (add)
    Wend
    Close #2
On Error Resume Next
    'Restore previous counts
    For i = 0 To List1.ListCount - 1
        If rec(i) = 1 Then
            List1.Selected(i) = True
            List2.Selected(i) = True
        Else
            List1.Selected(i) = False
            List2.Selected(i) = False
        End If
    Next
    
    GoTo pastall
noitemlist:
    If (Form3.Visible = False) Then
        d = MsgBox("Critical file 'item.lst' not found . . . exiting", vbCritical)
        End
    End If
nocheckfile:
    If (Form3.Visible = False) Then
        d = MsgBox("Critical file 'check.cts' not found" + Chr(13) + "Going back into 'Waiting for Counts' mode", vbExclamation)
        Form5.Timer1.Enabled = True
        Form5.Timer2.Enabled = True
        Form5.Show
        Form1.Hide
    End If
pastall:
End Sub





Private Sub Command1_Click()

If Command1.Caption = "->" Then
    Command1.Caption = "<-"
    Form1.Width = 4425
Else
    Command1.Caption = "->"
    Form1.Width = 2595
End If

    
    

End Sub



Private Sub Command2_Click()
    If (Form6.Visible = False) Then
        Form6.List1.Clear
        LoadWastes
    End If
    Form6.Show
End Sub

Private Sub Command3_Click()
Form1.WindowState = 1
End Sub

Public Function StoreRecounts() As Integer
        Dim i As Integer
        ReDim Preserve rec(List1.ListCount) As Integer
        
        'Figure out and store recounts
        For i = 0 To List1.ListCount - 1
            If List1.Selected(i) Then
                numrecounts = numrecounts + 1
                rec(i) = 1
            Else
                rec(i) = 0
            End If
        Next

        'Write Check File for the Vending Terminal
        Open Checkloc For Output As #1
        If numrecounts = 0 Then
            Write #1, CountsDone
        Else
            Write #1, Recounts
        End If
        
        For i = 0 To List1.ListCount - 1
            If List1.Selected(i) Then
              Write #1, i
            End If
        Next
        
        Close #1
        StoreRecounts = numrecounts
End Function

Public Sub LoadEverything(Autocheck As Boolean)
    Dim val, ItemCount, ItemName, strs, i, Recounts As Integer, Threshold As Integer
    Dim RecountList As String
    'on Error GoTo NoThresholdFile
    Open ThresholdFile For Input As #2
        Input #2, Threshold
    Close #2
    itemcout = 0
    MakeList
    LoadWastes Autocheck
    Recounts = 0
    RecountList = ""
    If Autocheck Then
        Open AutoCheckFile For Input As #2
        While Not EOF(2)
            'ReDim Preserve ItemList(ItemCount) As String
            'ReDim Preserve ItemCounts(ItemCount) As Integer
            Line Input #2, val
            strs = Split(val, ",")
            ItemName = strs(0)
            ItemCount = CLng(strs(1))
            ItemCount = ItemCount - Form6.NumWastes(ItemName)
            Debug.Print ItemName & " : " & strs(1) & "->" & ItemCount
            For i = 0 To List1.ListCount - 1
                If UCase(ItemName) = UCase(List1.List(i)) Then
                    If ItemCount - Threshold > CLng(List2.List(i)) Or _
                        ItemCount + Threshold < CLng(List2.List(i)) Then
                        List1.Selected(i) = True
                        List2.Selected(i) = True
                        Recounts = Recounts + 1
                        RecountList = RecountList & ItemName & " : "
                        If CLng(List2.List(i)) > ItemCount Then
                            RecountList = RecountList & " Over " & CLng(List2.List(i)) - ItemCount
                        Else
                            RecountList = RecountList & " Short " & ItemCount - CLng(List2.List(i))
                        End If
                        RecountList = RecountList & vbCrLf
                    Else
                        List1.Selected(i) = False
                        List2.Selected(i) = False
                    End If
                    Exit For
                End If
            Next i
        Wend
        If Recounts > 0 Then
            StoreRecounts
            If MsgBox("There were " & Recounts & " recounts after this pass." & vbCrLf & _
                "The Recounts were as follows: " & vbCrLf & RecountList & vbCrLf & _
                "Would you like Counts Calculator to continue to Autocheck counts?" & vbCrLf & vbCrLf & _
                "Click Yes to let Counts Calculator Autocheck." & vbCrLf & _
                "Click No to check manually for the next pass.", vbQuestion Or vbYesNo) = vbYes Then
                Form5.Autocheck = 1
            Else
                Form5.Autocheck = 0
            End If
            Close #2
            
            Me.Hide
            Form5.Timer1.Enabled = True
            Form5.Timer2.Enabled = True
            Form5.Show
        Else
            Close #2
            Me.Show
            MsgBox "AutoChecking of Counts has assessed Counts are done." & vbCrLf & _
                "Enter the values into your Management System, and verify this"
        End If
    Else
        Close #2
        Me.Show
    End If
    Exit Sub
NoThresholdFile:
    Threshold = 0
    Resume Next
End Sub

Private Sub Command4_Click()
On Error Resume Next
    
    Dim numrecounts As Integer
    numrecounts = 0
    If MsgBox("Are you sure you are ready to send back to vending?", vbYesNo) = vbYes Then
        Form6.Hide
        numrecounts = StoreRecounts
        If numrecounts = 0 Then
            Form3.Timer2.Enabled = True
            PrintCounts
            Kill ("temp\waste.cts")
            Kill AutoCheckFile
            Form3.Timer3.Interval = 10000
            Form5.Autocheck = 1
            
        Else
            Form5.Timer1.Enabled = True
            Form5.Timer2.Enabled = True
            Form5.Show
            Form5.Autocheck = 0
        End If
        Form1.Hide
    End If
End Sub

Private Sub Form_Load()
     Me.Caption = "Counts Calculator " & GetVersion & " - Office Side"
     Label2.Caption = "Counts Calculator " & GetVersion


    SetWindowPos Me.hWnd, HWND_TOPMOST, 0, 0, 0, 0, FLAGS

     

End Sub


Private Sub List1_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)

On Error Resume Next
    Dim i As Integer
    Dim num As Integer
    num = 0
    
    For i = 0 To List1.ListCount - 1
    List2.Selected(i) = List1.Selected(i)
    If (List2.Selected(i) = True) Then num = num + 1

    Next

    If num = 0 Then
        Command4.Caption = "Done"
    Else
        Command4.Caption = "Back"
    End If



    
End Sub

Private Sub List1_Scroll()
    List2.TopIndex = List1.TopIndex
    
End Sub

Private Sub List2_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    On Error Resume Next
    Dim i As Integer
    Dim num As Integer
    num = 0
    
    For i = 0 To List2.ListCount - 1
    List1.Selected(i) = List2.Selected(i)
    If (List2.Selected(i) = True) Then num = num + 1
    Next
    
    
    If num = 0 Then
        Command4.Caption = "Done"
    Else
        Command4.Caption = "Back"
    End If



End Sub

Private Sub List2_Scroll()
    List1.TopIndex = List2.TopIndex
End Sub

Public Sub view_Click()
    RunFile textfile
End Sub
