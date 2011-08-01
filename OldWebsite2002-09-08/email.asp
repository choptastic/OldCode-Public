<!-- #include file="header.asp" -->
<%
dim rst
set rst = myconn.execute("Select * from logins")
%>
<table>
<% while not rst.eof %>
<tr>
	<td><%=rst("Login")%></td>
	<td><%=rst("First")%></td>
	<td><%=rst("Last")%></td>
	<td><%=rst("Email")%></td>
	<td><%=rst("address")%></td>
	<td><%=rst("City")%></td>
	<td><%=rst("State")%></td>
	<td><%=rst("phone")%></td>
	<td><%=rst("howfound")%></td>
</tr>
<% rst.movenext %>
<% wend %>
</table>
	


<!-- #include file="footer.asp" -->