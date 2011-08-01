<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
      <center>
      </center> 
      <%
	set rst = myconn.execute("Select * from Story order by LastDate DESC;")
	while not rst.eof
%>
      <form name="<%=rst("ID")%>" method="post" action="addword.asp"> 
		<table width=90% cellspacing=0 align=center>
          <tr bgcolor=#000000><td align=center colspan=3><font color=#FFFFFF size=4><%=rst("Title")%></font></td>
		</tr>
		<tr bgcolor=<%=GetTableColor(3)%>>
			<td align=center width=33%><font size=3>Started</font><br>
              <font color=#FFFFFF><%=rst("Started")%></font></td>
			<td align=center width=34%><font size=3>Last To Add</font><br>
              <font color=#FFFFFF><%=rst("LastAdder")%></font></td>
			<td align=center width=33%><font size=3>Modified</font><br>
              <font color=#FFFFFF><%=rst("LastDate")%></font></td>
			
		</tr>
		<tr bgcolor=<%=GetTAbleColor(5)%>><td colspan=3><%=rst("Text")%>
		<% if rst("LastAdder")><Session("LoginName") and Session("LoginName")><"" then%>
			
			  <input type="text" name="word" size="15" maxlength="20">
              <input type="hidden" name="ID" value="<%=rst("ID")%>"><input type="submit" name="Submit" value="Add Word To Story">
			
		<% end if %>
		</td></tr>
		</table>
	</form>
	  <%	rst.movenext
	wend
	if Session("LoginName")><"" then %>
      <div align="center"><font size="4">Create a New Story </font></div>
      <form name="form3" method="post" action="addstory.asp">
	  <table align=center>
	  <tr>
	<td>Title: </td>
        <td><input type="text" name="title" maxlength="255" size="40"></td>
      </tr>
	<tr><td>First Word of Story: </td>
        <td><input type="text" name="word" maxlength="20" size="15"></td>
		</tr>
		</table>
		<center><input type="submit" name="Submit" value="Add Story"></center>
	</form>
	<% end if %>

<!-- #include file="footer.asp" -->