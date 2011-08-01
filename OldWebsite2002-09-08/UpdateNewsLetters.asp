<!-- #include file="header.asp" -->

<%
	dim subject, filename, d
	subject=trim(request.form("subject"))
	filename=trim(request.form("filename"))
	d=trim(request.form("date"))
	
	sql = "Insert into Newsletters(NewsTitle,NewsFilename,NewsDate) values('" & subject & "','" & filename & "','" & d & "')"
	
	
	myconn.execute sql
	
	response.redirect("SendNewsletter.asp")
%>

<!-- #include file="footer.asp" -->

