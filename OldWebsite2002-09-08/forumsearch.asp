

<!-- #include file="header.asp" -->
<!-- #include file="Functions.asp" -->

<%
	dim searchtext
	searchtext=request.form("SearchText")
%>
<center>
<a href="newforum.asp">[Forum Index]</a>
<form name="form1" method="post" action="forumsearch.asp">
        
          <font size="4">Enter search string:</font><br>
          <input type="text" name="SearchText">
    <input type="submit" name="Submit" value="Search like mad">
  
</form>
</center>
<%
	
	if len(searchtext)>0 then %> <hr> 
	<%
		searchtext=replacechar(searchtext,"'","&#39;")
		set rst=Server.CreateObject("adodb.recordset")
		rst.activeconnection=myconn
		rst.open "Select * from forum where Instr(1,[text],'" & Searchtext & "') or Instr(1,subject,'" & Searchtext & "')", ,1,2,1
	%> <center>
        <font size="4">Results : <%=rst.recordcount %></font> 
      </center>
	<table width="97%" align=center border=0 cellspacing=1>
			<tr bgcolor=#000000>
				
				<td width=60%><font color="#FFFFFF">Subject</font></td>
				<td width="20%"><font color="#FFFFFF">Poster:</font></td>
				<td width="20%"><font color="#FFFFFF">Date:</font></td>
			</tr>
		<%
		while not rst.eof
			curColor=GetAlternatingTableColor
		%>
		<tr bgcolor=<%=curcolor%>>
			<td><a href="viewblock.asp?C=<%=rst("RootThread")%>#<%=rst("ID")%>" ><%=rst("subject")%></a></td>
			<td><%=rst("name")%></td>
			<td><%=rst("date")%></td>
		</tr>
		<% 	rst.movenext
			wend %>
		</table>
	<% end if %>

<!-- #include file="footer.asp" -->