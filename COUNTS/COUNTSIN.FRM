VERSION 5.00
Begin VB.Form Form2 
   Appearance      =   0  'Flat
   BackColor       =   &H000000FF&
   BorderStyle     =   0  'None
   Caption         =   " "
   ClientHeight    =   4830
   ClientLeft      =   3255
   ClientTop       =   1965
   ClientWidth     =   6045
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   -1  'True
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00000000&
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4830
   ScaleWidth      =   6045
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer3 
      Interval        =   100
      Left            =   3720
      Top             =   3960
   End
   Begin VB.Timer Timer2 
      Interval        =   1000
      Left            =   1920
      Top             =   3120
   End
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Click Anywhere here to continue"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   1695
      Left            =   2880
      TabIndex        =   1
      Top             =   1800
      Width           =   3135
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H000000FF&
      BackStyle       =   0  'Transparent
      Caption         =   "COUNTS ARE IN!!"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   72
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   4815
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6135
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()

     #If Win32 Then

     Dim lResult As Long
     lResult = SetWindowPos(Me.hWnd, HWND_TOPMOST, _
     0, 0, 0, 0, FLAGS)

     #Else '16-bit API uses a Sub, not a Function

     SetWindowPos Me.hWnd, HWND_TOPMOST, _
     0, 0, 0, 0, FLAGS

     #End If

End Sub

Private Sub Label1_Click()
    
    Form3.Timer1.Enabled = False

    Timer2.Enabled = False
    Timer3.Enabled = False
    Acknowledged = 1
    
    Form2.Enabled = False
    Form2.Enabled = True
    Form2.Hide
    Form1.LoadEverything False
End Sub

Private Sub Label2_Click()
    Label1_Click
End Sub

Private Sub Timer2_Timer()
    If Acknowledged = False Then
        Beep
    Else
        Timer2.Enabled = False
    End If


End Sub

Private Sub Timer3_Timer()
        
        If Label1.ForeColor + 1000 < &HFFFFFF Then
            Label1.ForeColor = Label1.ForeColor + 1000
        Else: ForeColor = 0

        End If
End Sub

