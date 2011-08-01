<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
<%
	dim i
	i=request.querystring("Index")
	
	sql="Select * from Newsletters where NewsID=" & i
	set rsn=myconn.execute(sql)
	
	if rsn.eof then 
		response.write("Invalid Newsletter ID")
	else
		response.write("<hr><center><font size=4>" & rsn("newstitle") & "</font><br><font size=3><i>Sent " & rsn("newsdate") & "</i></font></center>")
		response.write("<blockquote><font face='courier new' size=2>")
		printtextfile(Server.MapPath("newsletters/" & rsn("newsfilename")))
		response.write("</font></blockquote></p>")
	end if
	%>
	
<!-- #include file="footer.asp" -->