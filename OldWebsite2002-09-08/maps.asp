<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
      <div align="center"><font size="5">Maps developed by LAN Party Attendees.</font> </div>
	  <div align="center"><font size="4">Select a Map to view:</font> </div>
      <table cellpadding=3 cell align=center cellspacing="0">
        <%
	  	dim rst,curcolor
		curcolor=GetAlternatingTableColor
	%>
        <tr bgcolor=#000000>
          <td width=100><font size=4 color="#FFFFFF">Map Name</font></td>
          <td width=115><font size=4 color="#FFFFFF">Developer(s)</font></td>
          <td><font size=4 color="#FFFFFF">Description</font></td>
        </tr>
		
        <%
	  	
		set rst = myconn.execute("maps")
		while not rst.eof
		
		%>
        <tr bgcolor=<%=curcolor%>>
          <td><font size=4><a href="viewmap.asp?ID=<%=rst("MapID")%>"><%=rst("MapName")%></a></font></td>
          <td><font size=4 color=#ffffff><%=rst("Maker")%></font></td>
          <td><%=rst("Desc")%> </td>
        </tr>
        <%
		
			curcolor=GetAlternatingTableColor
			rst.movenext
		wend
		%>
		<tr bgcolor=<%=curcolor%>>
          <td><font size=4><a href="southshoremap.asp">South Shore Map</a></font></td>
          <td><font size=4 color=#ffffff>Gumm</font></td>
          <td>The Infamous South Shore Map for Red Faction that was and never will be finished.</td>
        </tr>
      </table>
	  
      <!-- #include file="footer.asp" -->