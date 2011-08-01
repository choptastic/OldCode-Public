<!-- #include file="header.asp" -->
<font size=6>
<%
	dim u,n,d,e
	e=false
	u=trim(request.form("url"))
	n=trim(request.form("linkname"))
	d=trim(request.form("desc"))
	if n= "" then
		response.write("Error: Must supply a Name for the Link<br>")
		e=true
	end if
	if u = "" then 
		response.write("Error: Must supply a URL<br>")
		e=true
	end if
	if d = "" then
		response.write("Error: Must supply a Description<br>")
		e=true
	end if
	if e=false then
		sql="Insert into Links(linkcat,linkname,linktext,linksrc) values(5,'" & n & "','" & d & "','" & u & "');"
		myconn.execute sql
		response.redirect("links.asp")
	end if
%>
</font>

<!-- #include file="footer.asp" -->