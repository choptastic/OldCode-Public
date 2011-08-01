<!-- #include file="header.asp"-->
     <% sql="SELECT Count(Contacts.ContactID) AS CountOfContacts FROM Contacts GROUP BY Contacts.Verified HAVING (((Contacts.Verified)=Yes));"
		dim rsp,c
		set rsp=myconn.execute(sql)
		if rsp.eof then
			c=0
		else
			c=rsp("countofcontacts")
		end if
	%>	 
      <div align="center">
<form name="form1" method="post" action="addcontact.asp">
          <table width="82%" border="0" cellspacing="0" cellpadding="0">
            <tr> 
              <td width="33%" height="24">Name</td>
              <td width="67%" height="24"> 
                <input type="text" name="name" size="50">
              </td>
            </tr>
            <tr> 
              <td width="33%" height="24">Email Address</td>
              <td width="67%" height="24"> 
                <input type="text" name="email" size="50">
              </td>
            </tr>
          </table>
          <p> 
            <input type="submit" name="Submit" value="Submit">
            <input type="reset" name="Submit2" value="Reset">
          </p>
        </form>
        <p>&nbsp;</p>
      </div>
      <!-- #include file="footer.asp"-->