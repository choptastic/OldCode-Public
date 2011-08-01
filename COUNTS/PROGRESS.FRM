VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "Installing"
   ClientHeight    =   1335
   ClientLeft      =   5085
   ClientTop       =   915
   ClientWidth     =   3195
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   LinkTopic       =   "Form3"
   ScaleHeight     =   1335
   ScaleWidth      =   3195
   Begin VB.Label Label5 
      Caption         =   "Working Dir"
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label4 
      Caption         =   "Status:"
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   600
      Width           =   615
   End
   Begin VB.Label Label3 
      BackStyle       =   0  'Transparent
      Height          =   375
      Left            =   960
      TabIndex        =   2
      Top             =   960
      Width           =   2175
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Height          =   255
      Left            =   600
      TabIndex        =   1
      Top             =   600
      Width           =   2535
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Progress"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1080
      TabIndex        =   0
      Top             =   120
      Width           =   1095
   End
   Begin VB.Shape ind 
      BackStyle       =   1  'Opaque
      FillColor       =   &H00FFFFFF&
      FillStyle       =   0  'Solid
      Height          =   375
      Left            =   480
      Top             =   120
      Width           =   135
   End
   Begin VB.Shape Shape1 
      BackStyle       =   1  'Opaque
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   375
      Left            =   480
      Top             =   120
      Width           =   2295
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
