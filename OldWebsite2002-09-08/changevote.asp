<!-- #include file="header.asp" -->
      <%
	landate = request.form("LANDate")
	if Session("LoginName")><"" then
		myconn.execute("Update Logins Set LANDate=" & landate & " where Login='" & session("LoginName") & "';")
		if landate="" then %>
      No Date Selected 
      <% else %>
      Thank you for voting. You can change your vote by revoting.
      <% End if
	else %>
      Not Logged in 
      <% end if %>
      <!-- #include file="footer.asp" -->