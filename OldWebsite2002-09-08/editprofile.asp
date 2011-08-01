<!-- #include file="header.asp" -->
      <%
	dim email, login, first, last, pw1, pw2, address, city, state, phone, errors
	login=Session("LoginName")
	email=trim(request.form("email"))
	first=trim(request.form("first"))
	last=trim(request.form("last"))
	pw1=trim(request.form("pw1"))
	pw2=trim(request.form("pw2"))
	address=trim(request.form("address"))
	city=trim(request.form("city"))
	state=trim(request.form("state"))
	phone=trim(request.form("phone"))
	
	if email="" then
		response.write("Error: Must Provide Email Address<p>")
		errors=true
	end if
	
	if first="" then
		response.write("Error: Must Provide First Name<p>")
		errors=true
	end if
	
	if last="" then
		response.write("Error: Must Provide Last Name<p>")
		errors=true
	end if
	
	if address="" then
		response.write("Error: Must Provide Address<p>")
		errors=true
	end if
	
	if city="" then
		response.write("Error: Must Provide City<p>")
		errors=true
	end if
	
	if state="" then
		response.write("Error: Must Provide State<p>")
		errors=true
	end if
	
	if phone="" then
		response.write("Error: Must Provide Phone<p>")
		errors=true
	end if
	
	if pw1 >< "" or pw2 >< "" then
		if pw1 >< pw2 then
			response.write("Error: Passwords do not match<p>")
			errors=true
		end if
	end if
	
	if not errors then
		
		 sql= "Update Logins set Email='" & email & "',First='" & first & _
				"', Last='" & last & "',Address='" & address & "', City='" & city & _
				"', State='" & state & "', Phone='" & phone & "' "
		if pw1 >< "" and pw2 >< "" then
			sql = sql & ", Password='" & pw1 & "' "
		end if
		sql =sql & " Where login='" & Login & "';"
		myconn.execute(sql)
		
		set rst=myconn.execute("Select * from NextLANPArties")
		dim FastComp, Going
		if not rst.eof then
			Going=request.form("Going")
				'response.write Going
			if Going="on" then 
				Going="Yes"
			else
				Going="No"
			end if
			
		
			FastComp=request.form("Computers")
			if not IsNumeric(FastComp) then  FastComp="0"
			if Cint(FastComp) < 0 then FastComp="0"
			myconn.execute("delete * from RSVP where Login='" & Login & "' and LANPartyID='" & rst("LANPartyID") & "';")
			sql="insert into RSVP(LANPArtyID,Login,FastCount,Going) values('" & rst("LANPartyID") & "','" & _
				Login & "'," & FastComp & "," & Going & ");"
			'response.write(sql)
			myConn.execute(sql)
			
			rst.movenext
		end if
	
	set objNewMail = server.createObject("CDONTS.NewMail")
	Dim body
	objNewMail.To = email
	objNewMail.Subject = "GummLANParty.net Profile Update"
	objNewMail.From = "GummLANParty.net<jgumm@wi.rr.com>"
	Body = "You have updated your profile.  This email is to verify your changes." & vbcrlf & _
						"Login : " & login & vbcrlf
						if pw1>< "" then
							Body = body & "Password : " & pw1 & vbcrlf
						end if
						
	Body = body & "Email Address : " & email & vbcrlf & _
						"First Name : " & first &  vbcrlf & _
						"Last Name : " & last & vbcrlf & _
						"Address : " & address & vbcrlf & _
						"City : " & city & vbcrlf & _
						"State : " & state & vbcrlf & _
						"Phone : " & phone & vbcrlf & vbcrlf & "http://www.GummLANParty.net"
	objNewMail.body = body				
	objNewMail.send
		
		%>
      <div align="center">
        <p><font size="+2">You've successfully updated your profile.</font></p>
        <p><font size="+2">An E-mail has been sent to <%=email%> with the information 
          on your changes.</font></p>
        <p align="left"> 
          <%
	end if
	'
	
	%>
        </p>
      </div>
      <!-- #include file="footer.asp" -->