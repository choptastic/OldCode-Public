<!-- #include file="header.asp" -->
      <center>
        <p>
          <!-- #include file="functions.asp" -->
      </center>
          <% 	
		dim i,f,d,t,rsn
		
	sql="Select * from Newsletters order by newsdate desc"
	set rsn=myconn.execute(sql)
	dim col
	col="#555555"
	%>
	<Table width=80% cellspacing=0 align=center>
	<Tr bgcolor=#000000>
		<td><b><font color=#FFFFFF>Title</font></b></td>
		<td align=right><b><font color=#FFFFFF>Date Sent</font></b></td>
	</tr>
	<%
	while not rsn.eof
		col=GetAlternatingTAbleColor
		%>
		<Tr bgcolor=<%=col%>>
			<td>
				<a href="displaynewsletter.asp?Index=<%=rsn("newsid")%>"><%=rsn("newstitle")%></a>
			</td>
			<td align=right>
				<%=rsn("newsdate")%>
			</td>
		</tr>
		<%
		rsn.movenext
	wend
	'printtextfile("d:\newsletters\" & f)
%></table>
      
      
      <!-- #include file="footer.asp" -->