<!-- #include file="header.asp" -->
      
        <!-- #include file="functions.asp" -->
		
      <div align="center"> 
        <table border="1" width="715">
          <tr>
            <td height="26">
              <div align="center"><font color="#FFFFFF">The most recently replied 
                to posts appear toward the top.</font></div>
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
        <table width="85%" border="0">
          <tr>
            <td width="33%">
              <div align="center">Number of Threads: 
                <% 
				Session("BlockStyle")=true
				dim rsq
			set rsq=myconn.execute("select * from NumberThreads")
			response.write(rsq("CountofID"))%>
              </div>
            </td>
            <td width="33%"> 
              <div align="center">Number of Individual Posts: 
                <%
			set rsq=myconn.execute("select * from NumberPosts")
			response.write(rsq("CountofID"))%>
              </div>
            </td>
			<td>
              <div align="center">Deepst Thread:
			  <%
			set rsq=myconn.execute("select * from ThreadSize order by CountofID DESC;")
			response.write(rsq("CountofID"))%>
			  </div>
            </td>
          </tr>
        </table>
        <font size="4"><b><a href="#NewPost">[Make a Post]</a></b></font></div>
        <% 	dim num
			num=request.querystring("C")
			if num="" then
				num=20
			end if
			DisplayBlockthreads %>
      <hr>
      <p align="center"><font size="4"><b><a name="NewPost"></a>Post your own 
        message</b></font></p>
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
