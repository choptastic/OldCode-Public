<!-- #include file="header.asp" -->

<%
	dim err, LoginPage
	err = false
	
	login=request.querystring("login")
	pw=request.querystring("pw")
	LoginPage=request.querystring("page")
	
	'response.write(login & " : " & pw & " : " & LoginPage)
	
	if login = "" then
		login = trim(request.form("login"))
		pw=trim(request.form("pw"))
		LoginPage=request.form("page")
	end if
	
	if login = "" then
		err=true
		response.write("Error: No Login Specified<p>")
	end if
	
	if pw = "" then
		err=true
		response.write("Error: No Password Specified<p>")
	end if
	
	if not err then
		set rst = myconn.execute("Select * from logins where login='" & login & "' and password='" & pw & "'")
		if rst.eof then
			response.write("Error: Invalid Login/Password combo<p>")
		elseif rst("Active") = false then
			response.write("Error: Account Not Active, please refer to your confirmation email<p>")
		else
			'Session("LoginName") = login
			Response.Cookies("LoginName")=login
			Response.Cookies("LoginName").Expires=now + 30
			set rst= myconn.execute("Select * from NextLANParties order by LANDate;")
			dim NextLANParty
			if Now>rst("RequireDate") then
				NextLANParty = rst("LANPArtyID")
				rst.close
				set rst = myconn.execute("Select login From RSVP where Login='" & login & "' And LANPArtyID='" & NextLANPArty & "'")
				if rst.eof then
					response.redirect("profile.asp?rsvp=1")
				end if
			end if
			if trim(Session("QS")) >< "" then
				response.redirect(LoginPage & "?" & Session("QS"))
			else
				response.redirect(LoginPage)
			end if
				
		end if
	end if
		
	
%>
<!-- #include file="footer.asp" -->