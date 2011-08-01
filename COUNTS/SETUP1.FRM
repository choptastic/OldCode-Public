VERSION 5.00
Begin VB.Form form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Counts Calculator"
   ClientHeight    =   6765
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
   Icon            =   "setup1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6765
   ScaleWidth      =   4170
   Begin VB.CommandButton Command4 
      Caption         =   "Create Vending Startup Diskette"
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   27
      Top             =   6840
      Width           =   3975
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Edit Specific Item and Field Information"
      Height          =   495
      Left            =   1800
      MaskColor       =   &H0080FFFF&
      TabIndex        =   15
      Top             =   5640
      Width           =   2295
   End
   Begin VB.ListBox List2 
      Height          =   1425
      Left            =   120
      TabIndex        =   5
      Top             =   5280
      Width           =   1575
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Halt Counts Program"
      Height          =   495
      Left            =   1800
      TabIndex        =   16
      Top             =   6240
      Width           =   2295
   End
   Begin VB.Frame Frame2 
      Caption         =   "Item and Field Lists"
      Height          =   2775
      Left            =   1800
      TabIndex        =   22
      Top             =   2760
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
      Top             =   960
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
   Begin VB.ListBox List1 
      Height          =   4740
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
      Top             =   5040
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
      Caption         =   "W H O A !"
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
      Top             =   0
      Width           =   375
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "Counts Calculator "
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
      Top             =   120
      Width           =   1815
   End
End
Attribute VB_Name = "form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim selectedindex As Integer

Sub loadlistsub()
On Error GoTo noload
    Dim add As String
    List1.Clear
    Open "items.lst" For Input As #1
        While Not (EOF(1))
            Input #1, add
            List1.AddItem (add)
        Wend
    Close #1
    
noload:
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

    h.Value = 21
    m.Value = 55
End Sub


Private Sub Command3_Click()
    If (MsgBox("Save item and field information before proceeding (recommended)?", vbYesNo) = vbYes) Then
        savelist_Click
    End If
    form1.Hide
    css.Top = form1.Top
    css.Left = form1.Left
    
    css.Show
    
        
    
    
End Sub
Sub increment()
    Form2.Shape2.Width = Form2.Shape2.Width + 375
    'Form2.Label3.Caption = Str(Form2.Shape2.Width / Form2.dude.Width)
    
End Sub
Private Sub Command4_Click()
On Error GoTo nomake
    If (MsgBox("Please insert a diskette into drive A: to be the new vending startup diskette.", vbOKCancel) = vbOK) Then
        Form2.Shape2.Width = 375
        Form2.Show
        Form2.Label2.Caption = "msdos.sys"
        FileCopy "disk\msdos.sys", "a:\msdos.sys"
        Form2.Label2.Caption = "io.sys"
        increment
        
        FileCopy "disk\io.sys", "a:\io.sys"
        Form2.Label2.Caption = "command.com"
        increment
        
        FileCopy "disk\command.com", "a:\command.com"
        Form2.Label2.Caption = "drvspace.bin"
        increment
        
        FileCopy "disk\drvspace.bin", "a:\drvspace.bin"
        Form2.Label2.Caption = "autoexec.bat"
        increment
        
        FileCopy "disk\autoexec.bat", "a:\autoexec.bat"
        Form2.Label2.Caption = "config.sys"
        increment
        
        FileCopy "disk\config.sys", "a:\config.sys"
        'increment
        MsgBox "Creation of vending terminal startup diskette complete!"
        Form2.Hide
    End If
    GoTo pastnomake
nomake:
    MsgBox "Disk directory incomplete . . cannot create startup diskette."
    Form2.Hide
pastnomake:
        
        
    
End Sub

Private Sub fieldlist_radio_Click()
    Text1.MaxLength = 5
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End

End Sub

Private Sub insertafter_Click()
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
    Text1.MaxLength = 13
End Sub

Private Sub List2_Click()
    itemlist_radio.Value = False
    fieldlist_radio.Value = True
    Text1.Text = List2.List(List2.ListIndex)
    Text1.SetFocus
    Text1.SelLength = 15
    
End Sub

Private Sub set_Click()

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
    Dim f As Object
    If (itemlist_radio.Value = True) Then
        Set f = List1
    Else
        Set f = List2
    End If
    If (f.ListIndex > -1) Then
        f.RemoveItem (f.ListIndex)
    End If
End Sub

Private Sub savelist_Click()

    If MsgBox("Are you sure you want to save the new list . . . this will replace the older list and there is no undo?", 1) = 1 Then
        Open "items.lst" For Output As #1
            For i = 0 To List1.ListCount - 1
                Write #1, List1.List(i)
            Next
        Close #1
    End If

End Sub

Private Sub loadlist_click()

If (MsgBox("Are you sure you want to overwrite any changes that may have been made?", vbYesNo) = vbYes) Then
    loadlistsub
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
    'ChDir "c:\counts"
    loadlistsub
    loadfieldsub
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
    h.Value = 21
    m.Value = 55
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
    If (fieldlist_radio.Value = True) Then
        Text1.MaxLength = 5
    Else
        Text1.MaxLength = 13
    End If
End Sub
