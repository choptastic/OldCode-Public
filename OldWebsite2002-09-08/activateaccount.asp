<!-- #include file="header.asp" -->
      <%
	dim act,login,pw,errors
	
	act=trim(request.form("activation"))
	login=trim(request.form("login"))
	pw=trim(request.form("pw"))
	
	dim rst
	set rst = myconn.execute("select * from logins where login='" & login & "'")
	if rst.eof then
		response.write("Error: Invalid Login<p>")
		errors = true
	else
		if rst("password") >< pw then
			response.write("Error: Invalid Password<p>")
			errors = true
		end if
		if rst("activation") >< act then
			response.write("Error: Invalid Activation Code<p>")
			errors = true
		end if
		if rst("Active") = true then
			response.write("Error: Account Already Active<p>")
			errors = true
		end if
	end if
	
	if not errors then
		myconn.execute("update logins set Active=Yes where login='" & login & "'")
	%>
      <p align="center"><font size="5">Registration Complete</font></p>
      <p align="center"><font size="4">Thank you . . . Registration is complete, 
        you may now login using the form on the menu.</font> 
        <%
	end if %>
      </p>
      <!-- #include file="footer.asp" -->

