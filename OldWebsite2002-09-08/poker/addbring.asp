<!-- #include file="connection.asp" -->
<!-- #include file="GenerateEmail.asp" -->
<%
	dim Who, Email, What
	Who=request.form("Who")
	Email=request.form("Email")
	What=request.form("What")
	
	If Not(Len(Who)>0 and Len(What)>0) then
		response.write "Form not completely Filled out"
	else
	
		dim sql
		if Email="" then
			sql="insert into Bringing(Who,What) values('" & Who & "','" & What & "');"
		else
			sql="insert into Bringing(Who,What, Email) values('" & Who & "','" & What & "','" & Email & "');"
		end if
		
		myconn.execute sql
		if len(email)> 0 then
			dim Body, From
			From="Poker Family Picnic<" & GetVariable("CoordinatorEmail") & ">"
			Body = Who & "," & vbcrlf & "Thank you for signing up to bring something to our little shin-dig..." & vbcrlf & vbcrlf & _
			"You've signed up to bring : " & What & vbcrlf & vbcrlf & _
			"And remember you can always find out information on the Poker Family Annual Picnic/Reunion at : " & _
			"http://www.gummlanparty.net/poker"
			SendMail email,From,"Poker Family Picnic Signup",Body
		end if
		
		Body = "Someone has signed up to bring something" & vbcrlf & vbcrlf & _
		"Who : " & who & vbcrlf & "What : " & what & vbcrlf & vbcrlf & "http://www.gummlanparty.net/poker"
		SendMail GetVariable("CoordinatorEmail"),From,"Someone has signed up to bring something",Body
		response.redirect "index.asp"
	end if
%>
	