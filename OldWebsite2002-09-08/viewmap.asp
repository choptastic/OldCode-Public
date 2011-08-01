<!-- #include file="header.asp" -->
	<center>
        <%
	dim mapid, curdate, mapname, filename, path
	mapid=request.querystring("ID")
	set rst = myconn.execute("select * from Maps where MapID=" & mapid)
	if not rst.eof then
		mapname = rst("mapname")
		%>
        <table><tr>
		<td bgcolor=#333333><font size=4 color=#ffffff>Map Name : </font><font size=4 color=#00ff00><%=mapname%></font></td>
		<td bgcolor=#444444><font size=4 color=#ffffff>Developer(s) : </font><font size=4 color=#00ff00><%=rst("maker")%></font></td>
		<td bgcolor=#555555><font size=4 color=#ffffff>Description :</font><font size=3 color=#00ff00><%=rst("desc")%></font></td>
		</tr></table>
		
	<%
	end if
	rst.close
	
	path = "maps/" & mapname & "/"
	set rst = myconn.execute("select Picture, [Date] from mapScreenShots where mapid=" & mapid & " group by [date],picture order by date DESC;")
	while not rst.eof
		if curdate >< rst("date") then
			response.write("<hr><font size=4>" & rst("date") & "</font><br>")
			curdate = rst("Date")
		end if
		%>
		<a href=<%=path & rst("picture")%> ><img src=<%=path & "thumbs\tn_" & rst("picture")%> border=0></a>
		<% rst.movenext
	wend
	rst.close
	%>

	</center>
<!-- #include file="footer.asp" -->