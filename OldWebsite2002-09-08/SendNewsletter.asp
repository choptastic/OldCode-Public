<!-- #include file="header.asp" -->

<% If Session("LoginName") = "Chops" then %>

	
<form name="form2" method="post" action="SendEmails.asp">
        <p> 
          <select name="Table" size="2">
            <option value="Contacts">Contacts</option>
            <option value="qryLogins">qryLogins</option>
          </select>
          
		  <select name="NewsLetter" size="7">
            <% set rst =Myconn.execute("Select * from Newsletters order by [NewsDate]")
		  		while not rst.eof
			%>
            <option value="<%=rst("NewsFilename")%>"><%=rst("NewsDate") & " : " & rst("NewsTitle")%></option>
            <% 	rst.movenext
				wend %>
          </select>
		  
          <input type="submit" name="Submit2" value="Send Nigga">
        </p>
</form>

<form name="form3" method="post" action="UpdateNewsLetters.asp">
	<input type="text" name="Subject" value="Subject">
	<input type="text" name="Filename" value="Filename.txt">
	<input type="text" name="Date" value="<%=Now%>">
	<input type="submit" name="submit3" value="Add Newsletter">
</form>

<% end if %>
<!-- #include file="footer.asp" -->