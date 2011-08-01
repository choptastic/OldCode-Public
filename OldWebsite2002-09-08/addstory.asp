<!-- #include file="header.asp" -->
<!-- #include file="stringfunctions.asp" -->
      <%
	dim w, rsta, title
	w=trim(request.form("word"))
	title=trim(request.form("title"))
	response.write id
	if w = "" then
		response.write("Error: Must Provide a Word")
	elseif title="" then
		response.write("Error: Must Provide a Title")
	else
		title=ReplaceChar(title,"'","&#39;")
		w=ReplaceChar(w,"'","&#39;")
		sql= "Insert into story([title],[text],lastadder,lastdate,started) values('" & title & "','" & w & "','" & session("LoginName") & "',#" & now & "#,#" & now & "#);"
		response.write sql
		myconn.execute sql
		response.redirect "story.asp"
	end if
%>
      <!-- #include file="footer.asp" -->