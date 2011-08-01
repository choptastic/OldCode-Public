VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomct2.ocx"
Begin VB.Form OldPrinter 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "End of Day Counts Sheets"
   ClientHeight    =   2535
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5640
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2535
   ScaleWidth      =   5640
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   2040
      Width           =   2535
   End
   Begin VB.CommandButton Preview 
      Caption         =   "Pre&view"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1440
      Width           =   2535
   End
   Begin VB.CommandButton OKPrint 
      Caption         =   "&Print"
      Default         =   -1  'True
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   2535
   End
   Begin MSComCtl2.MonthView DatePicker 
      CausesValidation=   0   'False
      Height          =   2370
      Left            =   2880
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   120
      Width           =   2700
      _ExtentX        =   4763
      _ExtentY        =   4180
      _Version        =   393216
      ForeColor       =   -2147483630
      BackColor       =   -2147483633
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      StartOfWeek     =   55902209
      CurrentDate     =   37369
   End
   Begin VB.Label Label1 
      Caption         =   "Print the End of Day Counts for which day?"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2535
   End
End
Attribute VB_Name = "OldPrinter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Cancel_Click()
    Unload Me
End Sub

Private Sub DatePicker_DateClick(ByVal DateClicked As Date)
    OKPrint.SetFocus
End Sub

Private Sub Form_Load()
    DatePicker.Value = Now
End Sub

Private Sub Form_Unload(Cancel As Integer)
    form1.Enabled = True
    form1.Show
End Sub

Function FindFile() As String
    Dim dselect As Date
    dselect = DatePicker
    Dim filename, d, FoundFile As String
    filename = Format(dselect, "yyyymmdd")
    d = Dir("daily\" & filename & ".txt")
    If d <> "" Then FoundFile = d
    d = Dir("daily\" & filename & ".htm")
    If d <> "" Then FoundFile = d
    FindFile = FoundFile
End Function

Private Sub OKPrint_Click()
    Dim FoundFile
    FoundFile = FindFile
    If FoundFile = "" Then
        MsgBox "No files found for selected date."
        Exit Sub
    Else
        PrintHTMLFile CurDir & "\daily\" & FoundFile
        Unload Me
    End If
End Sub

Private Sub Preview_Click()
    Dim FoundFile
    FoundFile = FindFile
    If FoundFile = "" Then
        MsgBox "No files found for selected date."
        Exit Sub
    Else
        RunFile CurDir & "\daily\" & FoundFile
    End If
End Sub
