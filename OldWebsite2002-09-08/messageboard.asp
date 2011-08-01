<!-- #include file="header.asp" -->
      
        <!-- #include file="functions.asp" -->
      <div align="center"> 
        <p><b><font size="5"> </font></b><font color="#00FF66"><a href="newforum.asp"><font size="4">[To 
          Flat Style]</font></a></font></p>
        <table border="1" width="715">
          <tr> 
            <td> 
              <div align="center"><font color="#FFFFFF">Posted in the Past 2 hours, 
                </font><font color="#00FF00">Posted in the past 24 hours, <font color="#FF6699">Posted 
                in the past 72 hours,</font> </font>Normal Post</div>
            </td>
          </tr>
          <tr> 
            <td> 
              <p>The messageboard now supports Images and Hyperlinks. To add an 
                image, just specify the location of the image, same applies to 
                hyperlinks. If the text is parsed as an image, it will autmatically 
                convert the text to an image HTML tag. Same applies to Hyperlinks.</p>
              <p>NOTE: Only GIF, JPG, JPE, and JPEG file extensions are supported 
                for images. If you can think of another filetype. Also, the FULL 
                WEB ADDRESS IS REQUIRED.</p>
              <p>Example:<br>
                <font color="#00FF00">Good : http://www.blahblah.com/blah.jpg</font><br>
                <font color="#FF0000">Bad : www.blahblah.com/blah.jpg</font></p>
            </td>
          </tr>
        </table>
        <br>
        <table width="75%" border="0">
          <tr>
            <td width="52%">Number of Threads: 
              <% dim rsq
			  Session("BlockStyle")=false
			set rsq=myconn.execute("select * from NumberThreads")
			response.write(rsq("CountofID"))%>
            </td>
            <td width="48%"> 
              <div align="right">Number of Individual Posts: 
                <%
			set rsq=myconn.execute("select * from NumberPosts")
			response.write(rsq("CountofID"))%>
              </div>
            </td>
          </tr>
        </table>
      </div>
        <% 	dim num
			num=request.querystring("C")
			if num="" then
				num=20
			end if
			Displaythread 0,clng(num),false, -1 %>
      
      <p align="right"><% if num >< 2000000 and session("Palm") >< true then %>
	  	<a href="messageboard.asp?C=2000000">Expand to show all 
        threads &gt;&gt;</a> <% end if %></p>
      <hr>
      <p align="center"><font size="4"><b>Post your own message</b></font></p>
	  <% if Session("LoginName")="" then %>
	  	<p align="center"><font size="4">You must login to post a message</font></p>
		<% else %>
      <form name="form1" method="post" action="addmessage.asp">
        <input type="hidden" name="name"  value="<%=Session("LoginName")%>">
        <input type="hidden" name="threadID" value="0">
		<input type="hidden" name="RootThread" value="0">
        <table width="90%" border="0" cellspacing="0" cellpadding="0" align="center">
          <tr> 
            <td width="13%">Subject</td>
            <td width="87%"> 
              <input type="text" name="subject" size="50" maxlength="50">
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
	  <% end if %>
<!-- #include file="footer.asp" -->
