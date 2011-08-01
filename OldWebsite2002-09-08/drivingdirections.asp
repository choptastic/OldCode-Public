<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
<!-- #include file="tooltiphead.asp" -->

	<% if Session("LoginName")="" then
			response.write("Must be logged in to view directions to LAN Party")
		else
	%>
      <div align="center">
        <p>
          
          <font size="5">Driving Directions From Pretty Much Everywhere</font></p>
	<table width="90%" border="0" cellpadding="0" cellspacing="0">
		  <%
		  	dim rsd
			sql="select * from drivingdirections order by dirid;"
			set rsd=myconn.execute(sql)
			while not rsd.eof
		  %>	
        
          <tr>
            <td bgcolor="<%=GetTableColor(2)%>"> 
              <center><font size="4"><b><font color="#FFFFFF">
		<span OnClick="showhide(direction<%=rsd("DirID")%>)" style="cursor:hand">
		From <%=rsd("DirName")%>
		</span>
                </font></b></font></center>
            </td>
          </tr>

	 
          <tr id="direction<%=rsd("DirID")%>" style="display:'none'"> 
            <td bgcolor=<%=GetTableColor(5)%>> 
              <% PrintDrivingdirections("d:\drivingdirections\" & rsd("dirtext")) %>
            </td>
          </tr>
   	   

        
        <p></p>
		<% rsd.movenext
			wend %>
	</table>
      </div>
	  <% end if %>
      <!-- #include file="footer.asp" -->