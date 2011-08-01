<%
	dim MyConn
		Set MyConn = Server.CreateObject("ADODB.Connection")
		MyConn.Open "DSN=Poker"
	
	function GetVariable(VariableName)
		dim rst
		
		set rst=MyConn.execute("Select * from Variables where Variable='" & VariableName & "'")
		if rst.eof then
			getvariable=""
		else
			GetVariable=rst("Value")
		end if
	end function
	
	sub SetVariable(VariableName, Value)
		dim sql
		sql="Update Variables Set [Value]='" & Value & "' Where [Variable]='" & VariableName & "'"
		'response.write sql & vbcrlf
		myconn.execute sql
	end sub
%>
		