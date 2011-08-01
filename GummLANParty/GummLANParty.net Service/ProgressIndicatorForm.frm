VERSION 5.00
Begin VB.Form ProgressIndicatorForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "GuLP Update Download Progress"
   ClientHeight    =   285
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4215
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   285
   ScaleWidth      =   4215
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Interval        =   200
      Left            =   3120
      Top             =   0
   End
   Begin VB.Label downloadProgress 
      Alignment       =   2  'Center
      Caption         =   "0 Bytes"
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
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   3975
   End
End
Attribute VB_Name = "ProgressIndicatorForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const OFS_MAXPATHNAME = 128
Const OF_READ = &H0
Private Type OFSTRUCT
        cBytes As Byte
        fFixedDisk As Byte
        nErrCode As Integer
        Reserved1 As Integer
        Reserved2 As Integer
        szPathName(OFS_MAXPATHNAME) As Byte
End Type

Private Const GENERIC_READ = &H80000000

Private Declare Function OpenFile Lib "kernel32" (ByVal lpFileName As String, lpReOpenBuff As OFSTRUCT, ByVal wStyle As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function GetFileSize Lib "kernel32" (ByVal hFile As Long, lpFileSizeHigh As Long) As Long

    

Private Sub Timer1_Timer()
    If Command = "" Then End
    On Error Resume Next
    Dim hand As Long, Size As Long
    Dim OF As OFSTRUCT
    hand = OpenFile(Command, OF, GENERIC_READ)
    Size = GetFileSize(hand, Size)
    downloadProgress.Caption = Size & " bytes"
    CloseHandle hand
    DoEvents
    'Timer1.Enabled = False
End Sub
