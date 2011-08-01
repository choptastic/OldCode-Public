VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Radiant Systems Theater Management System"
   ClientHeight    =   6765
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   1560
   LinkTopic       =   "Form1"
   ScaleHeight     =   6765
   ScaleWidth      =   1560
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim num, x, y As Integer

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    

    If KeyCode >= 48 And KeyCode <= 57 Then
        Print KeyCode - 48
    ElseIf KeyCode = 38 Then
        Print "up"
    ElseIf KeyCode = 40 Then
        Print "down"
    ElseIf KeyCode = 37 Then
        Print "left"
    ElseIf KeyCode = 39 Then
        Print "right"
    ElseIf KeyCode = 13 Then
        Cls
    Else
        Print KeyCode
    End If
    
    
End Sub


   


Private Sub Form_Load()
    num = 0
End Sub
