<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
      <%
	dim rsL, rsT, c(2), q
	q=0
	
	sql="select * from linktypes order by sortvalue"
	set rst=myconn.execute(sql)
	while not rst.eof
%>
      <table width="95%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr bgcolor=<%=GetTableColor(0)%>> 
          <td colspan="2"> 
            <div align="center"> <font color="#FFFFFF"><b><font size="5" face="Courier New, Courier, mono"><%=rst("linktype")%> 
              </font></b></font></div>
          </td>
        </tr>
<%		sql="select * from links where linkcat=" & rst("linktypeid") & " order by linksort;"
		set rsl=myconn.execute(sql)
		while not rsl.eof
		
%>
        <tr bgcolor='<%=GetAlternatingTableColor%>'> 
          <td width=150 align="left" valign="top"><a href='<%=rsl("linksrc")%>' target=#_new><%=rsL("LinkName")%></a></td>
          <td align="left" valign="top"><font face="Arial, Helvetica, sans-serif"><%=rsl("linktext")%></font></td>
        </tr>
<%		rsl.movenext
		wend
%>
      </table>
	  <p></p>
	  <%	  rst.movenext
	wend
%>
      <p></p>
      <hr>
      <form name="linkform" method="post" action="addlink.asp">
        <p align="center"><font size="4"><b>Submit a Link</b></font></p>
        <table width="62%" border="0" cellpadding="0" cellspacing="0" align="center">
          <tr align="left" valign="top"> 
            <td width="12%"><b>Link Name</b></td>
            <td width="88%"> 
              <input type="text" name="linkname" size="50" maxlength="50">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="12%"><b>URL</b></td>
            <td width="88%"> 
              <input type="text" name="url" size="60" maxlength="150">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="12%" height="17"><b>Description </b></td>
            <td width="88%" height="17"> 
              <input type="text" name="desc" size="80" value="" maxlength="255">
            </td>
          </tr>
        </table>
        <p align="center"> 
          <input type="submit" name="Submit" value="Submit">
          <input type="reset" name="Submit2" value="Reset">
        </p>
      </form>
      <!-- #include file="footer.asp" -->