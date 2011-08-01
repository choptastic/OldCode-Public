VERSION 5.00
Begin VB.Form form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Counts Calculator 2.0 - Setup"
   ClientHeight    =   8235
   ClientLeft      =   1590
   ClientTop       =   645
   ClientWidth     =   4170
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
   Icon            =   "setup.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   8235
   ScaleWidth      =   4170
   Begin VB.CommandButton PrintOldCounts 
      Caption         =   "Print Past 'End of Day' Sheets"
      Height          =   255
      Left            =   120
      TabIndex        =   34
      Top             =   7920
      Width           =   3975
   End
   Begin VB.Frame Frame3 
      Caption         =   "AutoCheck"
      Height          =   855
      Left            =   1800
      TabIndex        =   30
      Top             =   720
      Width           =   1575
      Begin VB.HScrollBar AutoThreshold 
         Height          =   255
         LargeChange     =   3
         Left            =   120
         Max             =   20
         TabIndex        =   33
         Top             =   480
         Width           =   1335
      End
      Begin VB.Label ThresholdVal 
         Alignment       =   1  'Right Justify
         Height          =   255
         Left            =   1080
         TabIndex        =   32
         Top             =   240
         Width           =   375
      End
      Begin VB.Label Label9 
         Caption         =   "Threshold : "
         Height          =   255
         Left            =   120
         TabIndex        =   31
         Top             =   240
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Item and Field Lists"
      Height          =   2775
      Left            =   1800
      TabIndex        =   22
      Top             =   3360
      Width           =   2295
      Begin VB.OptionButton fieldlist_radio 
         Caption         =   "Field List"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   2400
         Width           =   1215
      End
      Begin VB.OptionButton itemlist_radio 
         Caption         =   "Item List"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton del 
         Caption         =   "&Delete"
         Height          =   495
         Left            =   1440
         TabIndex        =   9
         Top             =   960
         Width           =   735
      End
      Begin VB.CommandButton insertafter 
         Caption         =   "&After"
         Height          =   255
         Left            =   720
         TabIndex        =   8
         Top             =   1200
         Width           =   735
      End
      Begin VB.CommandButton insertbefore 
         Caption         =   "&Before"
         Height          =   255
         Left            =   720
         TabIndex        =   7
         Top             =   960
         Width           =   735
      End
      Begin VB.CommandButton set 
         Caption         =   "S&et"
         Default         =   -1  'True
         Height          =   495
         Left            =   120
         TabIndex        =   6
         Top             =   960
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Height          =   375
         Left            =   240
         TabIndex        =   10
         Top             =   1560
         Width           =   1695
      End
      Begin VB.CommandButton savelist 
         Caption         =   "&Save List"
         Height          =   375
         Left            =   1200
         TabIndex        =   14
         Top             =   360
         Width           =   975
      End
      Begin VB.CommandButton loadlist 
         Caption         =   "&Load List"
         Height          =   375
         Left            =   120
         TabIndex        =   13
         Top             =   360
         Width           =   975
      End
      Begin VB.Label Label6 
         BackStyle       =   0  'Transparent
         Caption         =   "Insert"
         Height          =   255
         Left            =   840
         TabIndex        =   24
         Top             =   720
         Width           =   495
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Activation Time"
      Height          =   1695
      Left            =   1800
      TabIndex        =   18
      Top             =   1560
      Width           =   1575
      Begin VB.CommandButton Command2 
         Caption         =   "De&fault"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   1320
         Width           =   1215
      End
      Begin VB.VScrollBar m 
         Height          =   375
         Left            =   960
         Max             =   0
         Min             =   59
         TabIndex        =   1
         Top             =   600
         Width           =   255
      End
      Begin VB.VScrollBar h 
         Height          =   375
         Left            =   360
         Max             =   0
         Min             =   23
         TabIndex        =   0
         Top             =   600
         Width           =   255
      End
      Begin VB.CommandButton Command6 
         Caption         =   "Sa&ve"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   1080
         Width           =   1215
      End
      Begin VB.Label Label5 
         Caption         =   "00"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   960
         TabIndex        =   21
         Top             =   240
         Width           =   255
      End
      Begin VB.Label Label4 
         Caption         =   ":"
         Height          =   255
         Left            =   720
         TabIndex        =   20
         Top             =   240
         Width           =   135
      End
      Begin VB.Label Label3 
         Caption         =   "0"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   360
         TabIndex        =   19
         Top             =   240
         Width           =   255
      End
   End
   Begin VB.CommandButton Command7 
      Caption         =   "Print Counts Sheet"
      Height          =   255
      Left            =   120
      TabIndex        =   29
      Top             =   7680
      Width           =   3975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Halt Counts Program"
      Height          =   255
      Left            =   1800
      TabIndex        =   16
      Top             =   7080
      Width           =   2295
   End
   Begin VB.CommandButton Command5 
      Caption         =   "&Waste Definitions"
      Height          =   375
      Left            =   1800
      TabIndex        =   28
      Top             =   6600
      Width           =   2295
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Create Ve&nding Startup Diskette"
      Height          =   255
      Left            =   120
      TabIndex        =   27
      Top             =   7440
      Width           =   3975
   End
   Begin VB.CommandButton Command3 
      Caption         =   "&Cases/Sleeves/Cabinets"
      Height          =   375
      Left            =   1800
      MaskColor       =   &H0080FFFF&
      TabIndex        =   15
      Top             =   6240
      Width           =   2295
   End
   Begin VB.ListBox List2 
      Height          =   1425
      Left            =   120
      TabIndex        =   5
      Top             =   5640
      Width           =   1575
   End
   Begin VB.ListBox List1 
      Height          =   4935
      Left            =   120
      TabIndex        =   4
      Top             =   240
      Width           =   1575
   End
   Begin VB.Label Label8 
      Caption         =   "Field List"
      Height          =   255
      Left            =   480
      TabIndex        =   26
      Top             =   5400
      Width           =   855
   End
   Begin VB.Label Label7 
      Caption         =   "Item List"
      Height          =   255
      Left            =   480
      TabIndex        =   25
      Top             =   0
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "G u L P !"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   2655
      Left            =   3600
      TabIndex        =   23
      Top             =   360
      Width           =   375
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Counts Calculator v2.0 Setup Program"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00004000&
      Height          =   735
      Left            =   1680
      TabIndex        =   17
      Top             =   0
      Width           =   1815
   End
End
Attribute VB_Name = "form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim selectedindex As Integer
Dim Changed As Boolean

Function PromptIfChangedAndSave(Optional vb = vbYesNoCancel) As Boolean
    Dim msg
    If Changed = True Then
        msg = MsgBox("Save Changes?", vb)
        If msg = vbYes Then
            savelistsub
            PromptIfChangedAndSave = True
        ElseIf msg = vbNo Then
            PromptIfChangedAndSave = True
            Exit Function
        Else
            PromptIfChangedAndSave = False
        End If
    Else
        PromptIfChangedAndSave = True
    End If
End Function

Sub savelistsub()
    Open "items.lst" For Output As #1
        For i = 0 To List1.ListCount - 1
            Write #1, List1.List(i)
        Next
    Close #1
    Open "fields.cts" For Output As #1
        For i = 0 To List2.ListCount - 1
            Write #1, List2.List(i)
        Next
    Close #1
    Changed = False
End Sub

Sub loadlistsub()
On Error GoTo noload
    Dim Add As String
    List1.Clear
    Open "items.lst" For Input As #1
        While Not (EOF(1))
            Input #1, Add
            List1.AddItem (Add)
        Wend
    Close #1
    Changed = False
noload:
End Sub

Private Sub AutoThreshold_Change()
    ThresholdVal.Caption = AutoThreshold
    Open ThresholdFile For Output As #1
        Write #1, CInt(AutoThreshold)
    Close #1
End Sub

Private Sub Command1_Click()
    If (MsgBox("Are you sure you want to kill the instance of 'Counts Calculator'?", vbOKCancel) = vbOK) Then
        Open setupfile For Output As #1
            Write #1, closemessage
            Write #1, h.Value
            Write #1, m.Value
        Close #1
    End If
End Sub

Private Sub Command2_Click()

    h.Value = 22
    m.Value = 15
End Sub


Private Sub Command3_Click()
    If PromptIfChangedAndSave = True Then
        form1.Hide
        css.Top = form1.Top
        css.Left = form1.Left
        css.Show
        loadlistsub
    End If
End Sub

Private Sub Command4_Click()
On Error GoTo nomake
    If (MsgBox("Please insert a diskette into drive A: to be the new vending startup diskette.  Please ote this process will take about 5 minutes and DOES involve human interaction.", vbOKCancel) = vbOK) Then
        DoEvents
        FileCopy "disk\autoexec.bat", "a:\autoexec.bat"
        DoEvents
        FileCopy "disk\autoexec.nfo", "a:\autoexec.nfo"
        DoEvents
        FileCopy "autofix.exe", "a:\autofix.exe"
        DoEvents
        MsgBox "Startup diskette preparation complete.  Go to the vending stand and insert the newly created diskette.  Break out of the Radaint System by pressig CTRL+C.  Then type 'sys a:' (without the quotes)." & vbCrLf & "Now restart the computer, makig sure to leave the diskette in the drive and follow the on screen instructions.  Problems, call Whoa! at: " & PhoneNumber & "."
        Form2.Show
        Form2.Timer1.Enabled = True
        Form2.Timer2.Enabled = True
    End If
    GoTo pastnomake
nomake:
    MsgBox "Disk directory incomplete . . cannot create startup diskette."
pastnomake:
        
        
    
End Sub

Private Sub Command5_Click()
    Wastes.LoadWastes
    Wastes.Show
    Me.Hide
End Sub

Private Sub Command7_Click()
    GenerateHTMLSheet "CountsSheet.htm"
    'RunFile App.path & "\CountsSheet.htm"
    PrintHTMLFile CurDir & "\CountsSheet.htm"
End Sub

Private Sub fieldlist_radio_Click()
    Text1.MaxLength = 5
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim res
    res = PromptIfChangedAndSave
    If res = True Then
        End
    Else
        Cancel = 1
    End If
    Me.Show
End Sub

Private Sub insertafter_Click()
    If Trim(Text1) = "" Then Exit Sub
    Changed = True
    Dim f As Object
    If (itemlist_radio.Value = True) Then
        Set f = List1
    Else
        Set f = List2
    End If
    
    Dim s As String
    Dim ind As Integer
    ind = f.ListIndex + 1
    If f.ListCount > 2 And ind > -1 Then
        For i = f.ListCount To ind Step -1
            f.List(i) = f.List(i - 1)
        Next
    End If
    If ListIndex = -1 Then
        f.AddItem (Text1.Text)
    Else
        f.List(ind) = Text1.Text
    End If
    'List1.Selected(ind) = True
    
End Sub

Private Sub insertbefore_Click()
    If Trim(Text1) = "" Then Exit Sub
    Changed = True
    Dim f As Object
    If (itemlist_radio.Value = True) Then
        Set f = List1
    Else
        Set f = List2
    End If
    
    Dim index As Integer
    index = f.ListIndex
    If f.ListCount > 2 And index > -1 Then
        For i = f.ListCount To index Step -1
            f.List(i) = f.List(i - 1)
        Next
    End If
    If ListIndex = -1 Then
        f.AddItem (Text1.Text)
    Else
        f.List(index) = Text1.Text
    End If


End Sub

Private Sub itemlist_radio_Click()
    Text1.MaxLength = 11
End Sub

Private Sub List2_Click()
    itemlist_radio.Value = False
    fieldlist_radio.Value = True
    Text1.Text = List2.List(List2.ListIndex)
    Text1.SetFocus
    Text1.SelLength = 15
    
End Sub

Private Sub PrintOldCounts_Click()
    Me.Enabled = False
    OldPrinter.Show
    OldPrinter.SetFocus
End Sub

Private Sub set_Click()
    If Trim(Text1) = "" Then Exit Sub
    Changed = True
    Dim f As Object
    If (itemlist_radio.Value = True) Then
        Set f = List1
    Else
        Set f = List2
    End If
        
    
    If f.ListIndex >= 0 Then
        f.List(f.ListIndex) = Text1.Text
        On Error GoTo fixed
            f.ListIndex = f.ListIndex + 1
            GoTo skipfix
fixed:
            f.ListIndex = -1
            Text1.Text = ""
skipfix:
On Error GoTo 0
        
    Else
        f.AddItem (Text1.Text)
        Text1.Text = ""
        f.ListIndex = -1
    End If
End Sub


Private Sub del_Click()
    Changed = True
    Dim li
    Dim f As Object
    If (itemlist_radio.Value = True) Then
        Set f = List1
    Else
        Set f = List2
    End If
    If (f.ListIndex > -1) Then
        li = f.ListIndex
        f.RemoveItem (f.ListIndex)
        If li > f.ListCount Then
            li = f.ListCount
        End If
        If f.ListCount > 0 Then
            If li > f.ListIndex Then li = f.ListIndex
            f.ListIndex = li
        End If
        
    End If
End Sub

Private Sub savelist_Click()
    
    If MsgBox("Are you sure you want to save the new list . . . this will replace the older list and there is no undo?", 1) = 1 Then
        savelistsub
    End If

End Sub

Private Sub loadlist_click()
    Dim saveit As Boolean
    If Changed = True Then
        saveit = True
    Else
        If (MsgBox("Are you sure you want to overwrite any changes that may have been made?", vbYesNo) = vbYes) Then
    End If
        List1.Clear
        List2.Clear
        loadlistsub
        loadfieldsub
    End If



End Sub

Private Sub Command6_Click()
    On Error GoTo noload
    Open setupfile For Input As #1
        Input #1, message
    Close #1
    GoTo skipnoload:
noload:
        message = stayopenmessage
skipnoload:
    Open setupfile For Output As #1
        Write #1, message
        Write #1, h.Value
        Write #1, m.Value
    Close #1
End Sub

Sub loadfieldsub()
    On Error GoTo noload2
    Open "fields.cts" For Input As #1
    While Not EOF(1)
        Input #1, v
        List2.AddItem v
    Wend
    Close #1
noload2:
End Sub
Private Sub Form_Load()
    Dim temp
    Me.Caption = "Counts Calculator " & GetVersion & " - Setup"
    Label1.Caption = "Counts Calculator " & GetVersion & " Setup Program"
    'ChDir "c:\counts"
    loadlistsub
    loadfieldsub
    On Error GoTo noThresh
    Open ThresholdFile For Input As #1
        Input #1, temp
    Close #1
    AutoThreshold = temp
    ThresholdVal.Caption = AutoThreshold
    On Error GoTo noload
    Open setupfile For Input As #1
        Input #1, message
        Input #1, hh
        Input #1, mm
    Close #1
    h.Value = hh
    m.Value = mm
    
    GoTo skip
noload:
    hh = 21
    mm = 55
    Resume Next
noThresh:
    AutoThreshold = 0
    Resume Next
skip:





End Sub

Private Sub h_Change()
    Label3.Caption = h.Value
End Sub

Private Sub List1_Click()
    fieldlist_radio.Value = False
    itemlist_radio.Value = True
    Text1.Text = List1.List(List1.ListIndex)
    Text1.SetFocus
    Text1.SelLength = 15
    
    
    
End Sub

Private Sub m_Change()
    If m.Value >= 10 Then
        Label5.Caption = m.Value
    Else
        Label5.Caption = "0" & m.Value
    End If
    
End Sub


Private Sub Text1_Change()
    If Text1 = "" Then
        Exit Sub
    End If
    
    If (fieldlist_radio.Value = True) Then
        Text1.MaxLength = 5
    Else
        Text1.MaxLength = 11
    End If

End Sub

Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 32 Then SendKeys ("{Backspace}")
End Sub

