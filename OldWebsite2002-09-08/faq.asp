<!-- #include file="header.asp" -->
      <div align="center"></div>
		  <ul>
		  
        <%
			set rst = myconn.execute("Select * from FAQ where [A] is not null")
			while not rst.eof
		%>
        <li><font size="4" color="#FFFFFF"><b><%=rst("Q")%></b></font> 
        <blockquote> <font color="#99CC00"><%=rst("A")%></font></blockquote></li>
      	
      <%
			rst.movenext
		Wend 
		%>
		</UL>
		<%
		if Session("LoginName") >< "" then%>
		<center>
      <form name="form2" method="post" action="addfaq.asp">
          <p><font size="4"><b>Submit a question regarding GuLP Messenger.<br></font>
		  (your identity is kept completely anonymous)<br>
            </b>(255 Character Max)<br>
            <input type="text" name="Q" size="40" maxlength="255">
            <input type="submit" name="Submit2" value="Submit">
          </p>
        </form>
	  </center>
	  <% end if %>
      <!-- #include file="footer.asp" -->