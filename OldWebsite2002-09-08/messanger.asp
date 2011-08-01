<!-- #include file="header.asp" -->
      <div align="center">
        <p><font size="+3">GuLP Messenger</font></p>
        <p><font size="+2">Have Questions?<br>
          <a href="faq.asp">Check out the Frequently Asked Questions</a></font></p>
        <p><font size="4">Current Features:</font></p>
        <table width="616" cellspacing="1" border="1">
          <%	
			rst.close
			set rst=myconn.execute("Select * from Gulpfeatures where future<>yes order by FeatureVersion DESC;")
			while not rst.eof 
		%>
          <tr>
            <td width="65"><%=rst("FeatureVersion")%> 
              <% if rst("Beta") then response.write(" Beta") %>
            </td>
            <td width="123"><b><%=rst("FeatureName")%></b></td>
            <td width="412"><%=rst("FeatureDescription")%></td>
          </tr>
		 <% rst.movenext
		 Wend 
		 rst.close
		 %>
		</table>
        <p><br>
          <font size="4">Future Features </font></p>
        <table width="616" cellspacing="1" border="1">
          <%	
			
			set rst=myconn.execute("Select * from Gulpfeatures where future=yes")
			while not rst.eof 
		%>
          <tr> 
            <td width="123"><b><%=rst("FeatureName")%></b></td>
            <td width="412"><%=rst("FeatureDescription")%></td>
          </tr>
          <% rst.movenext
		 Wend 
		 rst.close
		 %>
        </table>
        <p>&nbsp; </p>
        <p><a href="GuLP.zip"><font size="4"><img src="GLP/icon.gif" width="33" height="33" border="0" align="absmiddle"> 
          Download Now! (1.68 MB zip) </font></a></p>
        <p><font size="+1">A Few Screenshots</font></p>
        <p><img src="GLP/login.gif"></p>
        <p> <img src="GLP/ListView.gif"></p>
        <p><img src="GLP/SysMenu.gif"></p>
        <p><img src="GLP/chattin.gif"></p>
        <p><img src="GLP/newpost.gif"></p>
      </div>
      <!-- #include file="footer.asp"-->