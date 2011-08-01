Attribute VB_Name = "Module1"
Function GetLANPArtyID() As Integer
    Dim d As Database
    Dim rst As Recordset
    Set d = OpenDatabase("\\server\webserver\GummLANParty.mdb")
    Set rst = d.OpenRecordset("select * from NextLANParties")
    GetLANPArtyID = rst![lanpartyid]
End Function


Function IsEmailValid(e) As Boolean
    Dim s
    s = Split(e, "@")
    IsEmailValid = False
    If UBound(s) = 1 Then
        s = Split(s(1), ".")
        If UBound(s) > 0 Then
            IsEmailValid = True
        End If
    End If
End Function
