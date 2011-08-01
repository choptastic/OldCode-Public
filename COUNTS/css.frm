VERSION 5.00
Begin VB.Form css 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Case/Sleeve/Cabinet Counts"
   ClientHeight    =   6795
   ClientLeft      =   1785
   ClientTop       =   525
   ClientWidth     =   3930
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6795
   ScaleWidth      =   3930
   Begin VB.ListBox fields 
      Height          =   1035
      Left            =   2760
      MultiSelect     =   1  'Simple
      TabIndex        =   5
      Top             =   480
      Width           =   1095
   End
   Begin VB.CommandButton set_fields 
      Appearance      =   0  'Flat
      Caption         =   "Set"
      Height          =   285
      Left            =   2880
      TabIndex        =   11
      Top             =   6480
      Width           =   855
   End
   Begin VB.ListBox displaycase 
      Height          =   4545
      Left            =   2760
      TabIndex        =   8
      Top             =   1800
      Width           =   1095
   End
   Begin VB.CommandButton loadbutton 
      Appearance      =   0  'Flat
      Caption         =   "Load"
      Height          =   495
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton savebutton 
      Appearance      =   0  'Flat
      Caption         =   "Save"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton set_css 
      Appearance      =   0  'Flat
      Caption         =   "Set"
      Default         =   -1  'True
      Height          =   285
      Left            =   1680
      TabIndex        =   10
      Top             =   6480
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   240
      MaxLength       =   4
      TabIndex        =   9
      Top             =   6480
      Width           =   1095
   End
   Begin VB.ListBox stacklist 
      Appearance      =   0  'Flat
      Height          =   225
      Left            =   5280
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   1200
      Visible         =   0   'False
      Width           =   1815
   End
   Begin VB.ListBox sleevelist 
      Appearance      =   0  'Flat
      Height          =   225
      Left            =   5280
      TabIndex        =   13
      TabStop         =   0   'False
      Top             =   720
      Visible         =   0   'False
      Width           =   1815
   End
   Begin VB.ListBox caselist 
      Appearance      =   0  'Flat
      Height          =   225
      Left            =   5280
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   960
      Visible         =   0   'False
      Width           =   1815
   End
   Begin VB.ListBox visual_values 
      Height          =   4545
      Left            =   1560
      TabIndex        =   7
      Top             =   1800
      Width           =   1215
   End
   Begin VB.ListBox items 
      Height          =   4545
      Left            =   120
      TabIndex        =   6
      Top             =   1800
      Width           =   1455
   End
   Begin VB.OptionButton Option3 
      Caption         =   "Stack"
      Height          =   255
      Left            =   1680
      TabIndex        =   4
      Top             =   1440
      Width           =   855
   End
   Begin VB.OptionButton Option2 
      Caption         =   "Sleeve"
      Height          =   255
      Left            =   1680
      TabIndex        =   3
      Top             =   1200
      Width           =   1095
   End
   Begin VB.OptionButton Option1 
      Caption         =   "Case"
      Height          =   255
      Left            =   1680
      TabIndex        =   2
      Top             =   960
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Full Case"
      Height          =   255
      Left            =   2880
      TabIndex        =   18
      Top             =   1560
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Item List"
      Height          =   255
      Left            =   240
      TabIndex        =   17
      Top             =   1440
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Case/Sleeve/ Stack Values"
      Height          =   495
      Left            =   1560
      TabIndex        =   16
      Top             =   360
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Case Fields"
      Height          =   375
      Left            =   2880
      TabIndex        =   15
      Top             =   0
      Width           =   855
   End
End
Attribute VB_Name = "css"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim selected As Integer
Const R_CASE = 1
Const R_SLEEVE = 2
Const R_STACK = 3
Const endfieldmessage = 8467
Dim Changed As Boolean

Sub savelistsub()
    Changed = False
    Open "cssfield.cts" For Output As #1
        For i = 0 To fields.ListCount - 1
            Write #1, Int(fields.selected(i))
            Write #1, fields.List(i)
        Next
        Write #1, endfieldmessage
        For i = 0 To items.ListCount - 1
            Write #1, items.List(i)
            Write #1, Int(caselist.List(i))
            Write #1, Int(sleevelist.List(i))
            Write #1, Int(stacklist.List(i))
            Write #1, Int(displaycase.List(i))
        Next
    Close #1
End Sub

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


Private Sub displaycase_Click()
    'displaycase.ListIndex = displaycase.ListIndex
    'items.ListIndex = displaycase.ListIndex
    
    Text1.Text = displaycase.List(displaycase.ListIndex)
    set_css.Default = False
    set_fields.Default = True
    Text1.SetFocus
    Text1.SelLength = 4
    

    'visual_values.ListIndex = -1
End Sub

Private Function find_field(s As String)
    For i = 0 To fields.ListCount - 1
        If fields.List(i) = s Then
            find_field = i
        End If
    Next
End Function

Private Function find_item(s As String) As Integer

    For i = 0 To items.ListCount - 1
        If items.List(i) = s Then
            find_item = i
            i = items.ListCount - 1
        End If
    Next

End Function

Private Sub displaycase_Scroll()
    visual_values.TopIndex = displaycase.TopIndex
    items.TopIndex = displaycase.TopIndex
End Sub

Private Sub Form_Load()
    Changed = False
    'ChDrive "c"
    'ChDir "c:\counts"
    'form1.MousePointer = 11
    selected = R_CASE
    Dim s As String
    Dim v As Integer

    items.Visible = False
    displaycase.Visible = False
    visual_values.Visible = False
    fields.Visible = False
    On Error GoTo noload
    Open "items.lst" For Input As #1

    
    While Not EOF(1)
        Input #1, s
        items.AddItem s
        caselist.AddItem "-1"
        sleevelist.AddItem "-1"
        stacklist.AddItem "-1"
        visual_values.AddItem "-1"
        displaycase.AddItem "-1"
    Wend
    Close #1

    Open "fields.cts" For Input As #1
    While Not EOF(1)
        Input #1, s
        fields.AddItem s
    Wend
    Close #1

    Dim i As Integer
    On Error GoTo noload

    Open "cssfield.cts" For Input As #1
    
    While v <> endfieldmessage
        Input #1, v
        If v <> endfieldmessage Then
            Input #1, s
            i = find_field(s)
            fields.selected(i) = v
        End If
    Wend




    While Not EOF(1)
        Input #1, s
        i = find_item(s)
        Input #1, v
        caselist.List(i) = v
        visual_values.List(i) = v
        Input #1, v
        sleevelist.List(i) = v
        Input #1, v
        stacklist.List(i) = v
        Input #1, v
        displaycase.List(i) = v
    Wend
    Close #1

    
noload:
    'form1.MousePointer = 0
     items.Visible = True
    displaycase.Visible = True
    visual_values.Visible = True
    fields.Visible = True
    Exit Sub
'nolist:
'    MsgBox "No itemlist or no field list . . . Cannot execute this part of the program"
'    css.Visible = False
    

End Sub

Private Sub Form_Unload(Cancel As Integer)
    'r = MsgBox("Save before terminating this window?", vbYesNo)
    'If r = vbYes Then
    '    savebutton_Click
    'End If
    Dim msg
    msg = PromptIfChangedAndSave
    If msg = True Then
        form1.Top = css.Top
        form1.Left = css.Left
        form1.Show
    Else
        Cancel = 1
    End If

End Sub

Private Sub items_Scroll()

    visual_values.TopIndex = items.TopIndex
    displaycase.TopIndex = items.TopIndex
    
    
End Sub

Private Sub loadbutton_Click()
    If Changed = False Then Exit Sub
    If (MsgBox("Are you sure you want to load the last saved setup, losing changes.", vbYesNo) = vbYes) Then
        'form1.MousePointer = 11
        visual_values.Clear
        displaycase.Clear
        items.Clear
        caselist.Clear
        sleevelist.Clear
        stacklist.Clear
        fields.Clear
        Form_Load
        Option1.Value = True
        'form1.MousePointer = 0
         
    End If

End Sub

Private Sub Option1_Click()
    visual_values.Visible = False
    If selected = R_SLEEVE Then
        For i = 0 To items.ListCount - 1
            sleevelist.List(i) = visual_values.List(i)
        Next
    ElseIf selected = R_STACK Then
        For i = 0 To items.ListCount - 1
            stacklist.List(i) = visual_values.List(i)
        Next
    End If
    
    selected = R_CASE
    
    For i = 0 To items.ListCount - 1
        visual_values.List(i) = caselist.List(i)
    Next
    visual_values.Visible = True
End Sub

Private Sub Option2_Click()
    visual_values.Visible = False

    If selected = R_CASE Then
        For i = 0 To items.ListCount - 1
            caselist.List(i) = visual_values.List(i)
        Next
    ElseIf selected = R_STACK Then
        For i = 0 To items.ListCount - 1
            stacklist.List(i) = visual_values.List(i)
        Next
    End If
    
    selected = R_SLEEVE
    
    For i = 0 To items.ListCount - 1
        visual_values.List(i) = sleevelist.List(i)
    Next
    visual_values.Visible = True
End Sub

Private Sub Option3_Click()

    visual_values.Visible = False
    If selected = R_CASE Then
        For i = 0 To items.ListCount - 1
            caselist.List(i) = visual_values.List(i)
        Next
    ElseIf selected = R_SLEEVE Then
        For i = 0 To items.ListCount - 1
            sleevelist.List(i) = visual_values.List(i)
        Next
    End If
    
    selected = R_STACK
    
    For i = 0 To items.ListCount - 1
        visual_values.List(i) = stacklist.List(i)
    Next

    visual_values.Visible = True
End Sub

'
Private Sub savebutton_Click()

    'PromptIfChangedAndSave vbYesNo
    If Changed = False Then Exit Sub
    If MsgBox("Save Lists?", vbYesNo) = vbYes Then
        savelistsub
    End If
End Sub

Private Sub set_css_Click()
    Dim i As Integer

    On Error GoTo noint
    i = Int(Text1.Text)
    On Error GoTo 0
    visual_values.List(visual_values.ListIndex) = Text1.Text
    If (selected = R_CASE) Then
        caselist.List(visual_values.ListIndex) = Text1.Text
    ElseIf selected = R_SLEEVE Then
        sleevelist.List(visual_values.ListIndex) = Text1.Text
    ElseIf selected = R_STACK Then
        stacklist.List(visual_values.ListIndex) = Text1.Text
    End If
   
    If (visual_values.ListIndex + 1 < visual_values.ListCount) Then
        visual_values.ListIndex = visual_values.ListIndex + 1
    Else
        visual_values.ListIndex = 0
    End If
    Changed = True
    GoTo skip
noint:
    MsgBox ("Value in text box must be an integer")
    Exit Sub
skip:
    


End Sub

Private Sub set_fields_Click()

    Dim i As Integer

    On Error GoTo nointe
    i = Int(Text1.Text)
    On Error GoTo 0
    displaycase.List(displaycase.ListIndex) = Text1.Text
    
    If (displaycase.ListIndex + 1 < displaycase.ListCount) Then
        displaycase.ListIndex = displaycase.ListIndex + 1
    Else
        displaycase.ListIndex = 0
    End If
    'displaycase_Click
    Changed = True
    GoTo skip1
nointe:
    MsgBox ("Value in text box must be an integer")
    Exit Sub
skip1:


End Sub

Private Sub visual_values_click()

    
    Text1.Text = visual_values.List(visual_values.ListIndex)
    If (set_fields.Default = True) Then
    
        set_fields.Default = False
        set_css.Default = True
    End If
    Text1.SetFocus
    Text1.SelLength = 4
    
    

    
End Sub

Private Sub visual_values_Scroll()
    items.TopIndex = visual_values.TopIndex
    displaycase.TopIndex = visual_values.TopIndex
End Sub
