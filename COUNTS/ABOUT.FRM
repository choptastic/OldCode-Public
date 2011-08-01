VERSION 5.00
Begin VB.Form Form4 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About Counts Calculator"
   ClientHeight    =   4035
   ClientLeft      =   5250
   ClientTop       =   1920
   ClientWidth     =   4440
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
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4035
   ScaleWidth      =   4440
   Begin VB.TextBox Text1 
      BackColor       =   &H80000004&
      Enabled         =   0   'False
      Height          =   975
      Left            =   720
      MultiLine       =   -1  'True
      TabIndex        =   4
      Top             =   480
      Width           =   3015
   End
   Begin VB.Timer bounce 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   3840
      Top             =   120
   End
   Begin VB.Label Label5 
      BackStyle       =   0  'Transparent
      Caption         =   "Counts Calculator is Copyright 2000 by Jesse Gumm."
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   3600
      Width           =   4215
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      Caption         =   $"ABOUT.frx":0000
      Height          =   1095
      Left            =   120
      TabIndex        =   1
      Top             =   2400
      Width           =   4215
   End
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      Caption         =   $"ABOUT.frx":00C4
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   1560
      Width           =   4215
   End
   Begin VB.Label Label6 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "GuLP Theatre Software"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   120
      Width           =   4455
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim xvel As Integer
Dim yvel As Integer


Private Sub bounce_Timer()

    If (Label6.Top + yvel <= 0) Then yvel = Abs(yvel)
    If (Label6.Left + xvel <= 0) Then xvel = Abs(xvel)
    If (Label6.Top + Label6.Height + yvel > Form4.Height - 400) Then yvel = -Abs(yvel)
    If (Label6.Left + Label6.Width + xvel > Form4.Width) Then xvel = -Abs(xvel)
    Label6.Left = Label6.Left + xvel
    Label6.Top = Label6.Top + yvel
End Sub

Private Sub Form_Load()
xvel = 100
yvel = 100
End Sub


Private Sub Label1_Click()

End Sub

