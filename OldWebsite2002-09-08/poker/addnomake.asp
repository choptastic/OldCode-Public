<!-- #include file="connection.asp" -->
<!-- #include file="GenerateEmail.asp" -->

<%
	dim who, reason
	who = request.form("Who")
	reason = request.form("reason")
	
	if len(who)=0 then
		response.write "Please Provide a Name"
	else
		dim sql
		if len(reason)>0 then
			sql="insert into NoMake(Who, Reason) values('" & who & "','" & reason & "')"
		else
			sql="insert into NoMake(Who) values('" & who & "')"
		end if
		
		myconn.execute sql
		
		
		dim body
		body = Who & " can't come to the picnic." & vbcrlf & vbcrlf
		if len(reason)>0 then
			body = body & "because of the following reason: " & vbcrlf & reason
		else
			body = body & "They did not specify a reason"
		end if
		SendMail GetVariable("CoordinatorEmail"),"Family Picnic<" & GetVariable("CoordinatorEmail") & ">","Someone can't come",body
		%>
		<center><h2>Thank you for letting us know you won't be there</h2>
		<h3><a href="index.asp">Go Back</a></h3></center>
<%	end if %>