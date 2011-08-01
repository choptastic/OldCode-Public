<!-- #include file="header.asp" -->
      <div align="center">
        <form name="newmember" method="post" action="addnewmember.asp">
          <table width="62%" border="0">
            <tr> 
              <td height="29">Desired Login Name</td>
              <td height="29"> 
                <input type="text" name="login" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td>Password</td>
              <td> 
                <input type="password" name="pw1" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td>Password Confirm</td>
              <td> 
                <input type="password" name="pw2" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td height="29">E-Mail Address</td>
              <td height="29"> 
                <input type="text" name="email" maxlength="50" size="30">
              </td>
            </tr>
            <tr>
              <td>E-Mail Address Confirm</td>
              <td>
                <input type="text" name="email2" maxlength="50" size="30">
              </td>
            </tr>
            <tr> 
              <td>First Name</td>
              <td> 
                <input type="text" name="first" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td>Last Name</td>
              <td> 
                <input type="text" name="last" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td>Physical Mail Address (not Email)</td>
              <td> 
                <input type="text" name="address" maxlength="50" size="30">
              </td>
            </tr>
            <tr> 
              <td>City</td>
              <td> 
                <input type="text" name="city" maxlength="30" size="30">
              </td>
            </tr>
            <tr> 
              <td>State</td>
              <td> 
                <input type="text" name="state" maxlength="2" size="2">
              </td>
            </tr>
            <tr> 
              <td>Zip Code</td>
              <td> 
                <input type="text" name="zip" maxlength="5" size="5">
              </td>
            </tr>
			<tr> 
              <td>Phone</td>
              <td> 
                <input type="text" name="phone" maxlength="12" size="12">
              </td>
            </tr>
			<tr> 
              <td>How did you find out about GummLANParty.net?</td>
              <td> 
                <input type="text" name="howfound" value="" size="30">
              </td>
            </tr>
          </table>
          <p> 
            <input type="submit" name="Submit" value="Submit">
            <input type="reset" name="Submit2" value="Reset">
          </p>
        </form>
        <p>&nbsp;</p>
        <p>&nbsp;</p>
      </div>
      <!-- #include file="footer.asp" -->