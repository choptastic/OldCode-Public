VERSION 5.00
Begin VB.Form Form6 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Wastes"
   ClientHeight    =   4650
   ClientLeft      =   9555
   ClientTop       =   330
   ClientWidth     =   3135
   ClipControls    =   0   'False
   LinkTopic       =   "Form6"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4650
   ScaleWidth      =   3135
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   4260
      Left            =   0
      TabIndex        =   0
      Top             =   360
      Width           =   3135
   End
   Begin VB.Label Label1 
      Caption         =   "Item,   Reason,  amt"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   9
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   2295
   End
End
Attribute VB_Name = "Form6"
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

Function NumWastes(ItemName) As Integer
    Dim i, WasteName, WasteVal As Integer
    For i = 0 To List1.ListCount - 1
        WasteName = Split(List1.List(i), ",")(0)
        If WasteName = Left(ItemName, Len(WasteName)) Then
            WasteVal = Split(List1.List(i), ",")(2)
            NumWastes = WasteVal
            Exit Function
        End If
    Next i
    NumWastes = 0
End Function
