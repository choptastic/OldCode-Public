<!-- #include file="header.asp" -->

<%
	dim FileContents, Subject

	sub SendEmail(name, email)
		dim objNewMail
		set objNewMail = server.createObject("CDONTS.NewMail")
	
		objNewMail.To = name & "<" & email & ">"
		objNewMail.Subject = Subject
		objNewMail.From = "GummLANParty.net<jgumm@wi.rr.com>"
		objNewMail.Body = Filecontents
		objNewMail.send
		
		response.write("Email Sent to : " & name & " - " & email & "<BR>")
	
	end sub
	
	
	dim email, name, table, textfile
	
	filecontents = ""
	Subject = ""
	table = request.form("Table")
	textfile = request.form("newsletter")
	
	
	sql="Select * from Newsletters where [NewsFilename] like '" & textfile & "'"
	'response.write(sql)
	set rst=myconn.execute(sql)
	subject = rst("NewsTitle")
	
	dim fs,a,i
	Set fs = CreateObject("Scripting.FileSystemObject")
	set a = fs.OpenTextFile(server.MapPath("Newsletters/" & request.form("NewsLetter")))
			while not a.AtEndOfStream
				i=a.readline
				filecontents = filecontents & i & vbcrlf
			wend
	a.close 
	
	sql = "Select * from  [" & table & "]"
	set rst=myconn.execute(sql)
	while not rst.eof
		SendEmail rst("name"),rst("email")
		rst.movenext
	wend
			
	
	'set rst = myconn.execute("Select * from " & request.from("Table"))
	
	
	

%>
	
<!-- #include file="footer.asp" -->