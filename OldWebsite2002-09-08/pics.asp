<!-- #include file="header.asp" -->
    
        
      <center>
        <%
			dim rstC
			sql="Select LANPartyID from LANParties where LANDate<now() order by [LANDate]"
			
			set rst=myconn.execute(sql)
			while not rst.eof
		%>
        <font size=5>
<hr>LAN Party <%=rst("LANPartyID")%>:</font><br><font size=4>
		<%
				set rstC=myconn.execute("Select LANPartyPicCategoryID,Category from LANPartyPicCategories where LANPartyID='" & rst("LANPartyID") & "';")
				while not rstC.eof
		%>
				<a href="showpics.asp?Category=<%=rstC("LANPartyPicCategoryID")%>"><%=rstC("Category")%><br></a>
		<%	
				rstC.movenext
				wend
		%>
			</font>
		<%
				rst.movenext
			wend
		%>
		</center>
<!-- #include file="footer.asp" -->