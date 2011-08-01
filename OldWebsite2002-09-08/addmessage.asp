
<!-- #include file="functions.asp" -->
<!-- #include file="StringFunctions.asp" -->
<%

	Set MyConn = Server.CreateObject("ADODB.Connection")
	MyConn.Open "DSN=Main"

	dim name,threadid,text,date,subject,sql, rootthread, newid
	dim rsf,e
	set rsf=Server.CreateObject("ADODB.recordset")
	e=false
	
	name=Session("LoginName")
	if name = "" then
		response.write("Not Logged In<p>")
	else
		threadid=trim(request.form("threadid"))
		text=trim(request.form("text"))
		subject=trim(request.form("subject"))
		rootthread=trim(request.form("RootThread"))
		response.write rootthread & "<P>"
		if name = "" then
			response.write("Error: Must speficy Name<br>")
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
			'sql="Insert into forum(name,threadid,subject,ip,[date], [text]) values('" & name & "'," & threadid & ",'" & subject & "','" & Request.ServerVariables("REMOTE_ADDR") & "','" & now & "','" & text & "');"
			set rst=Server.CreateObject("ADODB.Recordset")
			rst.ActiveConnection=myconn
			rst.open "select * from forum",,1,2,1
			rst.addnew
				rst("name")=name
				rst("threadid") = threadid
				rst("subject")=subject
				rst("ip")=Request.ServerVariables("REMOTE_ADDR")
				rst("date")=now
				rst("text")=text
			rst.update
			rst.movelast
			newid=rst("id")
			rst.close
			
			if clng(rootthread)=0 then
				rootthread=newid
				response.write newid
			end if
			sql = "Update forum set RootThread=" & rootthread & " where Id=" & newid
			myconn.execute sql
			sql = "Update Forum set LastReply='" & now & "' where rootthread=" & rootthread & " and threadid=0"
			myconn.execute sql
			if(Session("BlockStyle")=true) then
				response.redirect("viewblock.asp?C=" & rootthread)
			else
				response.redirect("messageboard.asp")
			end if
		end if
	end if

%>
