VERSION 5.00
Begin VB.Form ExpectedCounts 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Set Autocheck Counts"
   ClientHeight    =   7545
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   2940
   ControlBox      =   0   'False
   LinkTopic       =   "Form7"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7545
   ScaleWidth      =   2940
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command1 
      Caption         =   "I don't want to Autocheck"
      Height          =   255
      Left            =   120
      TabIndex        =   38
      Top             =   7200
      Width           =   2775
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   15
      Left            =   1560
      TabIndex        =   36
      Top             =   5640
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   14
      Left            =   1560
      TabIndex        =   34
      Top             =   5280
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   13
      Left            =   1560
      TabIndex        =   32
      Top             =   4920
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   12
      Left            =   1560
      TabIndex        =   30
      Top             =   4560
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   11
      Left            =   1560
      TabIndex        =   28
      Top             =   4200
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   10
      Left            =   1560
      TabIndex        =   26
      Top             =   3840
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   9
      Left            =   1560
      TabIndex        =   24
      Top             =   3480
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   8
      Left            =   1560
      TabIndex        =   22
      Top             =   3120
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   7
      Left            =   1560
      TabIndex        =   20
      Top             =   2760
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   6
      Left            =   1560
      TabIndex        =   18
      Top             =   2400
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   5
      Left            =   1560
      TabIndex        =   16
      Top             =   2040
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   4
      Left            =   1560
      TabIndex        =   14
      Top             =   1680
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   3
      Left            =   1560
      TabIndex        =   12
      Top             =   1320
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   2
      Left            =   1560
      TabIndex        =   10
      Top             =   960
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   1
      Left            =   1560
      TabIndex        =   8
      Top             =   600
      Width           =   975
   End
   Begin VB.TextBox Counts 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      Height          =   285
      Index           =   0
      Left            =   1560
      TabIndex        =   6
      Top             =   240
      Width           =   975
   End
   Begin VB.CommandButton Cancel 
      Caption         =   "Cancel Changes"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   6840
      Width           =   2775
   End
   Begin VB.CommandButton Reset 
      Caption         =   "Clear Values"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   6480
      Width           =   2775
   End
   Begin VB.CommandButton SetValues 
      Caption         =   "Set End Counts"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   6120
      Width           =   2775
   End
   Begin VB.VScrollBar VScroll1 
      Height          =   5655
      Left            =   2640
      TabIndex        =   0
      Top             =   240
      Width           =   255
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   15
      Left            =   120
      TabIndex        =   37
      Top             =   5640
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   14
      Left            =   120
      TabIndex        =   35
      Top             =   5280
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   13
      Left            =   120
      TabIndex        =   33
      Top             =   4920
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   12
      Left            =   120
      TabIndex        =   31
      Top             =   4560
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   11
      Left            =   120
      TabIndex        =   29
      Top             =   4200
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   10
      Left            =   120
      TabIndex        =   27
      Top             =   3840
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   9
      Left            =   120
      TabIndex        =   25
      Top             =   3480
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   8
      Left            =   120
      TabIndex        =   23
      Top             =   3120
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   7
      Left            =   120
      TabIndex        =   21
      Top             =   2760
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   6
      Left            =   120
      TabIndex        =   19
      Top             =   2400
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   5
      Left            =   120
      TabIndex        =   17
      Top             =   2040
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   4
      Left            =   120
      TabIndex        =   15
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   3
      Left            =   120
      TabIndex        =   13
      Top             =   1320
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   2
      Left            =   120
      TabIndex        =   11
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   1
      Left            =   120
      TabIndex        =   9
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label Item 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   0
      Left            =   120
      TabIndex        =   7
      Top             =   240
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Count"
      Height          =   255
      Left            =   1560
      TabIndex        =   5
      Top             =   0
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Item"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   0
      Width           =   615
   End
End
Attribute VB_Name = "ExpectedCounts"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Dim ItemCount As Integer
Dim ItemList()
Dim ItemCounts() As Integer

Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub Command1_Click()
    Form5.Autocheck = 0
    Unload Me
End Sub

Private Sub Counts_Change(Index As Integer)
    With Counts(Index)
    If IsNumeric(.Text) Then
        ItemCounts(Index + VScroll1) = .Text
    ElseIf Trim(.Text) = "" Then
        ItemCounts(Index + VScroll1) = -1
    Else
        .Text = Left(.Text, Len(.Text) - 1)
        .SelStart = Len(.Text)
    End If
    End With
End Sub

Private Sub Counts_GotFocus(Index As Integer)
    Counts(Index).BackColor = vbYellow
    Item(Index).BackColor = vbYellow
    Counts(Index).SelStart = 0
    Counts(Index).SelLength = Len(Counts(Index).Text)
End Sub



Private Sub Counts_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
    If KeyCode = vbKeyDown Or KeyCode = vbKeyReturn Then
        If Index = 15 Then
            If VScroll1 = VScroll1.Max Then
                VScroll1 = 0
                Counts(0).SetFocus
            Else
                VScroll1 = VScroll1 + 1
                Counts(0).SetFocus
                Counts(15).SetFocus
            End If
        ElseIf Index = ItemCount - 1 Then
            VScroll1 = 0
            Counts(0).SetFocus
            Counts(Index).SetFocus
        Else
            Counts(Index + 1).SetFocus
        End If
    ElseIf KeyCode = vbKeyUp Then
        If Index = 0 Then
            If VScroll1 = 0 Then
                VScroll1 = VScroll1.Max
                If ItemCount >= 16 Then
                    Counts(0).SetFocus
                    Counts(15).SetFocus
                Else
                    Counts(ItemCount - 1).SetFocus
                End If
            Else
                VScroll1 = VScroll1 - 1
                Counts(15).SetFocus
                Counts(0).SetFocus
            End If
        Else
            Counts(Index - 1).SetFocus
        End If
    End If
        
        
    
End Sub

Private Sub Counts_LostFocus(Index As Integer)
        Counts(Index).BackColor = vbWhite
    Item(Index).BackColor = vbWhite
End Sub

Private Sub Form_Load()
    'ChDir "D:\counts"
    'ChDrive "D:"
    SetWindowPos Me.hWnd, HWND_TOPMOST, 0, 0, 0, 0, FLAGS
    Form5.Enabled = False
    Form5.Timer1 = False
    Form5.Timer2 = False
    Dim val, strs
    ItemCount = 0
    ' Load Item List
    Open Itemsloc For Input As #1
        While (Not EOF(1))
            Input #1, val
            ReDim Preserve ItemList(ItemCount)
            ReDim Preserve ItemCounts(ItemCount)
            ItemList(ItemCount) = val
            ItemCounts(ItemCount) = -1
            ItemCount = ItemCount + 1
        Wend
        Close #1
        ' Set scrollbar
        If ItemCount > 15 Then
            VScroll1.Max = ItemCount - 16
            'VScroll1.Enabled = True
        Else
            'VScroll1.Enabled = False
            VScroll1.Max = 0
        End If
        Dim i
        ' Set Item List
        For i = 0 To UBound(ItemList)
            If i > 15 Then Exit For
            Item(i).Caption = ItemList(i + VScroll1)
            Item(i).Visible = True
            Counts(i).Visible = True
        Next i
        ' Hide unused items
        For i = UBound(ItemList) + 1 To 15
            Item(i).Visible = False
            Counts(i).Visible = False
        Next i
        'Load Previous Values
        On Error GoTo NoOldFile
        Open AutoCheckFile For Input As #1
        While Not EOF(1)
            Line Input #1, val
            strs = Split(val, ",")
            For i = 0 To ItemCount - 1
                If UCase(ItemList(i)) = UCase(strs(0)) Then
                    ItemCounts(i) = strs(1)
                    Exit For
                End If
            Next i
        Wend
    Close #1
NoOldFile:
    Me.Show
    VScroll1_Change
    Counts(0).SetFocus
End Sub



Private Sub Form_Unload(Cancel As Integer)
    Form5.Enabled = True
    Form5.Timer1 = True
    Form5.Timer2 = True
End Sub

Private Sub Item_MouseDown(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    Counts(Index).SetFocus
End Sub

Private Sub Reset_Click()
    Dim i
    If (MsgBox("Are you sure you want to set all values to NULL?", vbYesNo Or vbQuestion) = vbYes) Then
        For i = 0 To UBound(ItemList)
           ItemCounts(i) = -1
        Next i
    End If
    VScroll1_Change
End Sub

Private Sub SetValues_Click()
    Open AutoCheckFile For Output As #1
        Dim i
        For i = 0 To ItemCount - 1
            If ItemCounts(i) = -1 Then
                MsgBox "You must fill all values to use autocheck."
                Close #1
                Exit Sub
            End If
            Print #1, ItemList(i) & "," & ItemCounts(i)
        Next i
    Close #1
    Unload Me
End Sub

Private Sub VScroll1_Change()
    Dim i
    For i = 0 To UBound(ItemList)
        If i > 15 Then Exit For
        Item(i).Caption = ItemList(i + VScroll1)
        If ItemCounts(i + VScroll1) <> -1 Then
            Counts(i).Text = ItemCounts(i + VScroll1)
        Else
            Counts(i).Text = ""
        End If
    Next i
End Sub
