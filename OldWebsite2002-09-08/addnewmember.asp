<!-- #include file="header.asp" -->
      <% 
	dim first,last,email,login,pw1,pw2,address,city,state,zip,errors,phone,howfound
	first=trim(request.form("first"))
	last=trim(request.form("last"))
	email=trim(request.form("email"))
	email2=trim(request.form("email2"))
	login=trim(request.form("login"))
	pw1=trim(request.form("pw1"))
	pw2=trim(request.form("pw2"))
	address=trim(request.form("address"))
	city=trim(request.form("city"))
	state=trim(request.form("state"))
	zip=trim(request.form("zip"))
	phone=trim(request.form("phone"))
	howfound=trim(request.form("howfound"))
	
	if first="" then 
		response.write("Error: First Name Missing<p>")
		errors=true
	end if
	
	if last="" then 
		response.write("Error: Last Name Missing<p>")
		errors=true
	end if
	
	if email="" then 
		response.write("Error: Email Address Missing<p>")
		errors=true
	end if
	if login="" then 
		response.write("Error: Login Missing<p>")
		errors=true
	end if
	if pw1="" then 
		response.write("Error: Password Missing<p>")
		errors=true
	end if
	if pw2="" then 
		response.write("Error: Password confirm Missing<p>")
		errors=true
	end if
	if address="" then
		response.write("Error: Address Missing<p>")
		errors=true
	end if
	if city="" then 
		response.write("Error: City Missing<p>")
		errors=true
	end if
	if state="" then 
		response.write("Error: State Missing<p>")
		errors=true
	end if
	if zip="" then 
		response.write("Error: Zip Missing<p>")
		errors=true
	end if
	if phone="" then 
		response.write("Error: Phone Missing<p>")
		errors=true
	end if
	
	if howfound="" then
		response.write("Error: How You found out is missing<p>")
		errors=true
	end if
	
	if pw1 >< pw2 then 
		response.write("Error: Passwords do not match<p>")
		errors=true
	end if
	
	if email >< email2 then
		response.write("Error: Email Addresses do not match<p>")
		errors=true
	end if
	
	dim rst
	set rst = myconn.execute("select * from logins where login like '" & login & "'")
	if not rst.eof then
		response.write("Error: Login Already Taken, please choose another<p>")
		errors=true
	end if
	
	set rst = myconn.execute("select * from logins where email like '" & email & "'")
	if not rst.eof then
		response.write("Error: Email Address already in use<p>")
		errors=true
	end if
		
	
	if not errors then
	%>
      <div align="center">
        <p><font size="5">Welcome to GummLANParty.net</font></p>
        <p><font size="5">There is one more step to complete the registration 
          process. The instructions to complete the process have been emailed 
          to the address specified:<font color=#ff0000><%=email%>.</font> </font> 
    <%
	dim objNewMail,activationcode
	Randomize Timer
	activationcode = clng(rnd*10000000)
	

	set rst = myconn.execute("insert into Logins(First,Last,Login,Password,Email,Address,City,State,Zip,Activation,HowFound,Phone) values('" & _
				first & "','" & last & "','" & login & "','" & pw1 & "','" & email & "','" & address & "','" & _
				city & "','" & state & "','" & zip & "','" & activationcode & "','" & howfound & "','" & Phone & "')")
	
	set objNewMail = server.createObject("CDONTS.NewMail")
	
	objNewMail.To = email
	objNewMail.Subject = "GummLANParty.net Registration"
	objNewMail.From = "GummLANParty.net<jgumm@wi.rr.com>"
	objNewMail.Body = "Thank you for registering with GummLANParty.net.  " & vbcrlf & "Please go to the " & _
						"following URL to activate your account: http://www.gummlanparty.net/activate.asp" & vbcrlf & _
						"Type in the following Information : " & vbcrlf & _
						"Login : " & login & vbcrlf & _
						"Password : " & pw1 & vbcrlf & _
						"Activation Code : " & activationcode & vbcrlf & vbcrlf & _
						"Thanx," & vbcrlf & "-Gumm"
	objNewMail.send
	
	set objNewMail = server.createObject("CDONTS.NewMail")
	
	objNewMail.To = "jgumm@wi.rr.com"
	objNewMail.Subject = "GummLANParty.net New Registration"
	objNewMail.From = "GummLANParty.net<jgumm@wi.rr.com>"
	objNewMail.Body = 	"There's been a new Login: " & vbcrlf & _
						"Login : " & login & vbcrlf & _
						"Name : " & first & " " & last
	objNewMail.send
	
	end if
%>
        </p>
      </div>
      <!-- #include file="footer.asp" -->