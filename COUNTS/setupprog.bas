Attribute VB_Name = "Module1"
Option Explicit
Global Const stayopenmessage = 1999
Global Const closemessage = 2000
Global Const PhoneNumber = "(414) 530-0669"
Global hh, mm As Integer
Global Const setupfile = "counts.stp"
Global Const ThresholdFile = "threshold.cts"

Sub GenerateHTMLSheet(filename As String)
    Dim NumCols
    Dim ColPerc, i, ii
    Dim sTD, eTD, EmptyCell
    NumCols = 4 + form1.List2.ListCount
    ColPerc = 100 / NumCols
    sTD = "<td width=" & ColPerc & "%>"
    eTD = "</td>"
    EmptyCell = "<td>&nbsp;</td>"
    Open filename For Output As #1
        Print #1, "<Title>Counts Sheet: " & Now & "</title>"
        Print #1, "<Table width=100% align=center border=1 cellspacing=0 bordercolorlight=#ffffff>"
        Print #1, "<tr><td width=" & ColPerc * 2; "%></td>"
        For i = 0 To form1.List2.ListCount - 1
            Print #1, sTD & form1.List2.List(i) & eTD
        Next i
        Print #1, sTD & "&nbsp;" & eTD & "</tr>"
        
        For i = 0 To form1.List1.ListCount - 1
            Print #1, "<tr><td>" & form1.List1.List(i) & "</td>"
            For ii = 2 To NumCols - 2
                Print #1, EmptyCell
            Next ii
            Print #1, "</tr>"
        Next i
        Print #1, "</table>"
    Close #1
End Sub
