<!-- #include file="connection.asp" -->
<!-- #include file="mapquest.asp" -->
<%
	dim StartAddress, StartCSZ
	dim ToAddress, ToCSZ
	
	StartAddress=request.form("address")
	StartCSZ=request.form("csz")
	ToAddress=GetVariable("Address")
	ToCSZ=GetVariable("City") & ", " & GetVariable("State") & " " & GetVariable("Zip")
	response.write StartAddress
	response.write StartCSZ
	response.write ToAddress
	response.write ToCSZ
	response.redirect MapQuestDirections(StartAddress,StartCSZ, ToAddress, ToCSZ)
%>
	