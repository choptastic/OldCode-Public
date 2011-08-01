VERSION 5.00
Begin VB.Form Wastes 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Waste Definitions"
   ClientHeight    =   3675
   ClientLeft      =   1605
   ClientTop       =   1260
   ClientWidth     =   2175
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3675
   ScaleWidth      =   2175
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command3 
      Caption         =   "&Delete"
      Height          =   255
      Left            =   1440
      TabIndex        =   4
      Top             =   2760
      Width           =   735
   End
   Begin VB.CommandButton Command2 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   1200
      TabIndex        =   6
      Top             =   3240
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&OK"
      Height          =   375
      Left            =   0
      TabIndex        =   5
      Top             =   3240
      Width           =   975
   End
   Begin VB.CommandButton Change 
      Caption         =   "Chan&ge"
      Height          =   255
      Left            =   720
      TabIndex        =   3
      Top             =   2760
      Width           =   735
   End
   Begin VB.CommandButton Add 
      Caption         =   "&Add"
      Default         =   -1  'True
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   2760
      Width           =   735
   End
   Begin VB.TextBox NewWaste 
      Height          =   285
      Left            =   0
      TabIndex        =   1
      Top             =   2400
      Width           =   2175
   End
   Begin VB.ListBox WasteList 
      Height          =   2400
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2175
   End
End
Attribute VB_Name = "Wastes"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Add_Click()
    If Trim(NewWaste) = "" Then Exit Sub
    
    WasteList.AddItem (Trim(NewWaste))
    
    NewWaste = ""
End Sub

Private Sub Change_Click()
    
    If Trim(NewWaste) = "" Then Exit Sub
    
    If WasteList.ListIndex = -1 Then Exit Sub
    
    WasteList.List(WasteList.ListIndex) = Trim(NewWaste)
    
    NewWaste = ""
    
    
End Sub

Public Sub LoadWastes()
    WasteList.Clear
    Dim wr
    On Error GoTo nofile
    Open "wreason.cts" For Input As #1
        While Not EOF(1)
            Line Input #1, wr
            If Trim(wr) <> "" Then
                WasteList.AddItem (wr)
            End If
        Wend
    Close #1
nofile:
End Sub

Private Sub Command1_Click()
    Dim i
    Open "wreason.cts" For Output As #1
        For i = 0 To WasteList.ListCount
            Print #1, WasteList.List(i)
        Next i
    Close #1
    Command2_Click
End Sub

Private Sub Command2_Click()
    Me.Hide
    form1.Show
End Sub

Private Sub Command3_Click()
    If WasteList.ListIndex = -1 Then Exit Sub
    If MsgBox("Are you sure you want to delete the selected Waste Reason?", vbYesNo) = vbYes Then
        WasteList.RemoveItem WasteList.ListIndex
    End If
End Sub

