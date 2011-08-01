<!-- #include file="header.asp" -->
	<center>
      <%
		dim Category, ID, Directory, count
		count=0
		id=request.querystring("Category")
		
		sql="Select * from LANPartyPicCategories where LANPartyPicCategoryID=" & ID
		set rst=myconn.execute(sql)
		if rst.eof then
			response.write "Error: No Category with that ID found<br>"
		else
			
			response.write("<font size=6>" & rst("Category") & "</font>")
			rst.close
			
			sql="Select * from LANPartyPics where CategoryId=" & ID
			
			set rst=myconn.execute(sql)
			Directory=rst("Directory")
		%>
		<table>
		<tr Valign="top">
		<% 
		while not rst.eof
			if count=3 then %>
				</tr><tr  Valign="top">
		<%  	count = 0	
			end if 
			count=count+1 %>
		  <td width="33%" align="Center"><a href="pics/<%=Directory%>/<%=rst("filename")%>"><img src="pics/<%=Server.HTMLEncode(Directory)%>/thumbs/s_<%=rst("filename")%>" border="0"></a><br>
		<%=	rst("Description")%></td>
		<% 	rst.movenext
		wend %>
		</tr>
		</table>
		</center>
		<% end if %>	
<!-- #include file="footer.asp" -->