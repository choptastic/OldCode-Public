<!-- #include file="Connection.asp" --><title>Poker Family Picnic/Reunion</title>
<body bgcolor="#FFFFFF" text="#000000">
<center>
  <p><font size="5"><b>Poker Family Annual Picnic/Reunion</b><br>
    </font><font size="4"><b>We will have a volleyball pit on the premises! WooHoo!</b></font></p>
  <hr>
  <table width="50%" border="0">
    <tr valign="top"> 
      <td width="45%" align="right"><font size="4">Date :</font></td>
      <td width="55%"><font size="4"><%=GetVariable("StartDate")%></font></td>
    </tr>
    <tr valign="top"> 
      <td width="45%" align="right"><font size="4">Time :</font></td>
      <td width="55%"><font size="4"><%=GetVariable("StartTime")%></font></td>
    </tr>
    <tr valign="top"> 
      <td width="45%" align="right"><font size="4">Location :</font></td>
      <td width="55%"><font size="4"><%=GetVariable("Address")%><br>
        <%=GetVariable("City")%>, <%=GetVariable("State") & " " & GetVariable("Zip")%> 
        </font></td>
    </tr>
  </table>
  <font size="4"><br>
  </font> 
  <form name="form1" method="post" action="directions.asp">
    <p><font size="4">To get directions from your house, enter your address below 
      and click &quot;Get Directions&quot;</font></p>
    <table width="50%" border="1">
      <tr> 
        <td height="111" bgcolor="#FFFFCC"> 
          <div align="center"> 
            <table width="100%" border="0">
              <tr> 
                <td>Address :</td>
                <td> 
                  <input type="text" name="address">
                </td>
              </tr>
              <tr> 
                <td>City, State and/or Zip : </td>
                <td> 
                  <input type="text" name="csz">
                </td>
              </tr>
            </table>
          </div>
          <p align="center"> 
            <input type="submit" name="Submit" value="Get Directions">
          </p>
        </td>
      </tr>
    </table>
  </form>
  <hr>
  <font size="4">If you have any questions or comments on the picnic, please contact 
  either the host or organizer :</font><br>
  Organizer : 
  <% if GetVariable("CoordinatorEmail")><"" then %>
  <a href="mailto:<%=GetVariable("CoordinatorEmail")%>"> 
  <% End If %>
  <%=GetVariable("CoordinatorName")%></a><br>
  Phone Number: <%=GetVariable("CoordinatorPhone")%> 
  <p>Hosted by : <%=GetVariable("ContactName")%><br>
    Phone Number: <%=GetVariable("ContactPhone")%></p>
  <hr>
  <font size="4">What your family should bring</font><br>
  For yourselves, bring Lawn Chairs, Food, and Drink for <b>your</b> family. 
</center>
    <center>
      <form name="form2" method="post" action="addbring.asp">
        <table width="50%" border="1" align="center" bgcolor="#FFFFCC">
          <% dim rst
	   set rst=Myconn.execute("Select * from Bringing")
	   if not rst.eof then
	%>
          <tr> 
            <td align="center"> <b>Here is what other people are bringing:</b><br>
              <Table>
                <%
	  	
		while not rst.eof
	  %>
                <tr align="left"> 
                  <td>
                    <li><%=rst("What")%></li>
                  </td>
                </tr>
                <%
			rst.movenext
		wend %>
              </table>
          </tr>
          <% end if %>
          <tr> 
            <td align="center"> If you would like to bring something to share 
              with the <b>whole</b> family, please sign up here by filling in 
              the requested information and pressing &quot;Submit.&quot; If you 
              do not have an email address, just leave the field blank.: 
              <table width="100%" border="0">
                <tr> 
                  <td height="28">Who are you?</td>
                  <td height="28"> 
                    <input type="text" name="Who">
                  </td>
                </tr>
                <tr> 
                  <td>What's your Email Address?</td>
                  <td> 
                    <input type="text" name="email">
                  </td>
                </tr>
                <tr> 
                  <td>What are you Bringing?</td>
                  <td> 
                    <input type="text" name="what">
                  </td>
                </tr>
              </table>
              <input type="submit" name="Submit" value="Submit">
            </td>
          </tr>
        </table>
      
    <hr>
  </form>
    </center>

<center>
  <font size="4">People/Families who will be unable to attend. </font> 
  <form name="form3" method="post" action="addnomake.asp">
    <table width="50%" border="1" bgcolor="#FFFFCC">
      <% set rst=myconn.execute("Select * from NoMake")
		if not rst.eof then %>
      <tr> 
        <td align="center"> <font size="3"><b>The following people have already 
          let us know that they will be unable to make it:</b></font> 
          <table width="50%" border="0">
            <tr> 
              <td>
                <%
		  while not rst.eof
		  %>
                <li><%=rst("Who")%></li>
                <% rst.movenext
		  wend %>
              </td>
            </tr>
          </table>
      </tr>
      <% end if %>
      <tr> 
        <td align="center"> <font size="3"><b>If you can't make it, please put 
          your name in here and Click Submit.</b></font> 
          <table width="100%" border="0" align="center">
            <tr> 
              <td height="31">Who are you?</td>
              <td height="31"> 
                <input type="text" name="who">
              </td>
            </tr>
            <tr> 
              <td>Why can't you make it?<br>
                <font color="#990000">(Not required)</font></td>
              <td> 
                <textarea name="reason" rows="3" cols="25"></textarea>
              </td>
            </tr>
          </table>
          <input type="submit" name="Submit2" value="Submit">
        </td>
      </tr>
    </table>
  </form>
  <hr>
  <font size="4">Comments and Suggestions.</font> <font size="4"></font> 
  <form name="form3" method="post" action="addcomment.asp">
    <table width="50%" border="1" bgcolor="#FFFFCC">
      <% set rst=myconn.execute("Select * from Comments")
		if not rst.eof then %>
      <tr> 
        <td align="center"> <font size="3"><b>Posted Comments:</b></font> 
          <table width="100%" border="0">
            <tr> 
              <td>
                <%
		  while not rst.eof
		  %>
                <li><b><%=rst("Who")%> : </b><%=rst("comment")%></li>
                <% rst.movenext
		  wend %>
              </td>
            </tr>
          </table>
      </tr>
      <% end if %>
      <tr> 
        <td align="center"> <font size="3"><b>If you would like to leave a comment 
          or suggestion for the this site, please fill out the form below.</b></font> 
          <table width="100%" border="0" align="center">
            <tr> 
              <td height="31">Who are you?</td>
              <td height="31"> 
                <input type="text" name="who">
              </td>
            </tr>
            <tr> 
              <td>What is your comment?</td>
              <td> 
                <textarea name="comment" rows="3" cols="25"></textarea>
              </td>
            </tr>
          </table>
          <input type="submit" name="Submit2" value="Submit">
        </td>
      </tr>
    </table>
    <hr>
  </form>
  <p>I apologize for the simplicity of this website...I whipped it up in a hurry. 
    After the picnic, I'll give it a nicer layout and give it some much needed 
    flair, along with posting some pictures of the family here, for everyone to 
    see and download. Enjoy.</p>
  <p>If you have any questions or comments about the website, feel free to let 
    Jesse know at : <a href="mailto:jgumm@wi.rr.com">jgumm@wi.rr.com</a> </p>
</center>
  <p align="right">
  <% dim val
  val=GetVariable("Count")
  
  val=Cint(val) + 1
  if Session("Counted")><true then
  	SetVariable "Count",val
	Session("Counted")=true
  end if
  response.write val
  %>

