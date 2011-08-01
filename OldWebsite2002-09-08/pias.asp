<!-- #include file="header.asp" -->
      <div align="center">
        <p><img src="pias/piaslogo.jpg"></p>
        <p><font size="4">Everyone who attends the Gumm LAN Party is an honarary 
          member of PiaS as well as those that have been recruited. Here is a 
          depository for screenshots of PiaS members winning.</font></p>
        <table align="center">
		<%
			dim curname
			
			set rst=myconn.execute("select filename, PiaSName from PiaSmembers Inner Join PiasScreenshots on piasmembers.PiaSMemberId = piasscreenshots.piasmemberid order by PiasName")
			while not rst.eof
				if curname >< rst("PiaSName") then 
					curname=rst("PiaSName") %>
					<tr bgcolor=#000000><td><center><font size=4 color=#FFFFFF><%=rst("PiasName")%></font></center></td></tr>
					<tr><td>
					<center>
				<% end if %>
				<a href=pias/<%=rst("filename")%>><img src=pias/thumbs/tn_<%=rst("filename")%> border=0></a>
				
			<%
				rst.movenext
			wend %>
			</center>
			</td></tr>
		</table>
      </div>
      <!-- #include file="footer.asp" -->

