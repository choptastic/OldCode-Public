<!-- #include file="header.asp" -->
<%
	'response.write request.form("Date")
	MyConn.execute ("Update Logins Set LANDate='" & request.form("date") & "' Where Login='" & Session("LoginName") & "'")
%>

Thank you for voting
<!-- #include file="footer.asp" -->

