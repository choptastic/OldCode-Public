<!-- #include file="header.asp" -->
<!-- #include file="stringfunctions.asp" -->
      <%
	dim w, id, rsta, story
	w=trim(request.form("word"))
	id=trim(request.form("ID"))
	response.write id
	if w = "" then
		response.write("Error: Must Provide a Word")
	else
		set rsta=myconn.execute("Select text from Story where ID=" & id)
		story = rsta("text") & " " & ReplaceChar(w,"'","&#39;")
		rsta.close
		myconn.execute "update story set [text]='" & story & "', LastDate=#" & now & "#, LastAdder='" & Session("LoginName") & "'  where id=" & id
		response.write(story)
		response.redirect("story.asp")
	end if
%>
      <!-- #include file="footer.asp" -->