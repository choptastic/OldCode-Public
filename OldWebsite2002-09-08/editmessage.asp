
<!-- #include file="functions.asp" -->
<!-- #include file="StringFunctions.asp" -->
<%

	Set MyConn = Server.CreateObject("ADODB.Connection")
	MyConn.Open "DSN=Main"

	dim name,text,date,subject,sql, id
	dim rsf,e
	set rsf=Server.CreateObject("ADODB.recordset")
	e=false
	
	if Session("LoginName") = "" then
		response.write("Error: Not Logged In<p>")
	else
		id=trim(request.form("ID"))
		text=trim(request.form("text"))
		subject=trim(request.form("subject"))
		name=trim(request.form("name"))
		
		if name><Session("LoginName") and Session("LoginName")><"Chops" then
			response.write("Error: Not Owner of Post")
			e=true
		end if
		if text="" then
			response.write("Error: Must give some text<br>")
			e=true
		end if
		if subject="" then
			response.write("Error: Must provide a subject<br>")
			e=true
		end if
		
		if e=false then
			set rst = Server.CreateObject("ADODB.Recordset")
			rst.ActiveConnection = myconn
			rst.open "Select * from forum where ID=" & id, ,1,2,1
			rst("subject") = subject
			rst("text") = text
			rst.update
			
			if(Session("BlockStyle")=true) then
				response.redirect("viewblock.asp?C=" & id)
			else
				response.redirect("messageboard.asp")
			end if
		end if
	end if

%>
