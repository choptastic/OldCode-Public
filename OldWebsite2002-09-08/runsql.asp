<!-- #include file="header.asp" -->

<% 
if Session("loginName") = "Chops" then
%>


<form method="POST" action="RunSQLStatement.asp">
  <input type="text" name="SQL" size="20" tabindex="1"><input type="submit" value="Run SQL" name="B1" tabindex="2"><input type="reset" value="Reset" name="B2" tabindex="3">
</form>

<%
end if
%>
<!-- #include file="footer.asp" -->

