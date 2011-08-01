<!-- #include file="header.asp" -->
      <div align="center"> 
        <!-- #include file="functions.asp" -->
        <b><font size="5">Gumm LAN Party Message Board</font></b> 
        <hr>
		<a href="messageboard.asp">[Back to Index]</a><br>
        <b><font size="5"> </font></b> 
		
        <%

	dim id, Rootthread
	dim rsf
	id=request.querystring("ID")
	sql = "Select * from forum where ID=" & id
	set rsf=myconn.execute(sql)
	if rsf.eof then
		response.write("Error: No record with Specified ID found<br>")
	else
		RootThread=rsf("RootThread")
		%>
      </div>
      <center>
        <b><font size=5><%=rsf("subject")%> </font><br>
        <font size=4>Submitted by <%=rsf("name")%></font></b>
      </center>
      <p></p>
	  <blockquote>
      <%
		printtextfile("d:\forum\" & id & ".txt")
	end if 
%>
	</blockquote>
      <hr>
      <p align="center"><font size="4"><b>Reply to this Message</b></font></p>
	  <% if Session("LoginName") = "" then %>
      <div align="center"><font size="+1">You must be logged in to post a message 
        </font> </div>
		<% else %>
      <form name="form1" method="post" action="addmessage.asp">
	  	<input type="hidden" name="threadID" value="<%=id%>">
		<input type="hidden" name="RootThread" value="<%=RootThread%>">
        <table width="90%" border="0" cellspacing="0" cellpadding="0" align="center">
          <tr>
            <td width="13%">Subject</td>
            <td width="87%">
              <input type="text" name="subject" size="50" maxlength="50" value="<%if ucase(left(rsf("Subject"),3)) >< "RE:" then response.write("Re: ") %> <%=rsf("Subject")%>">
            </td>
          </tr>
          <tr>
            <td width="13%" height="219">Text</td>
            <td width="87%" height="219"> 
              <textarea name="text" cols="80" rows="15"></textarea>
            </td>
          </tr>
        </table>
        <p align="center"> 
          <input type="submit" name="Submit" value="Submit">
          <input type="reset" name="Submit2" value="Reset">
        </p>
      </form>
	  <% end if  %>
	  <p>
	
	  <%
	  DisplayThread RootOfThread(id),32000, true, id
	  %>
	  
      <!-- #include file="footer.asp" -->