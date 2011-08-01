<html>
<body bgcolor="#FFFFFF" text="#000000">
<div align="center">
  <b>Welcome to the Palm Version of GummLANParty.net</b>
  <hr> |
                <% while not rs.eof 
                 	response.write("<a href='" & rs("link") & "'>" & rs("linktext") & "</a> | ") 
                	rs.movenext
				wend %>
  <hr>
  <b>Next Party:</b>
        <i><%= weekdayname(weekday(rsd("landate"))) %>,
        <%=monthname(month(rsd("landate")),true) & " " & day(rsd("landate"))%>, <%=year(rsd("landate"))%> @ 
		<%=formattime(rsd("landate"))%></i>
		<hr>
			  	<% if Session("LoginName")="" then %>
                <form name="form1" method="post" action="login.asp">
                  <input type="hidden" name="page" value="<%=Request.ServerVariables("SCRIPT_NAME")%>">
                  Login:<br>
                    <input type="text" name="login" size="8" maxlength="50">
                    <br>
                    Password:<br>
                    <input type="password" name="pw" size="8" maxlength="50">
                    <br>
                    <input type="submit" name="Submit" value="Login">
                  <br>
                  <a href="newmember.asp">No Login? Register</a><br>
                </form>
				  
                <% else %>
                Logged in as:<br><font size=+0><b><%=formatname(10)%></b></font><br>
				  <a href="profile.asp"><font size=+0>Edit Profile</font></a><br>
				  <a href="logout.asp?P=<%=Request.ServerVariables("SCRIPT_NAME")%>">Logout</a>
				  
				  <% end if %>
				  
                
                 
  	
  
</div>
</body>
</html>
