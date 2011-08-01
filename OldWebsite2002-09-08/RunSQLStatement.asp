<!-- #include file="header.asp" -->

<% 
if Session("loginName") = "Chops" then
	sql=request.form("SQL")
	myconn.execute sql
end if
%>
<!-- #include file="footer.asp" -->

