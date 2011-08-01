<!-- #include file="header.asp" -->
      <% if Session("LoginName") >< "" then 
	  set rst = myconn.execute("Select * from logins where Login='" & Session("LoginName") & "'")
	  
	  if rst.eof then %>
	  	An Error Occured Reading your information, please contact Gumm<p>
	  <% else %>
      <div align="center">
<form name="form1" action="editprofile.asp" method="post">
          <table width="60%" border="0">
            <tr> 
              <td width="56%"> 
                <div align="right">Login(Not changable): </div>
              </td>
              <td width="44%"> 
                <input type="hidden" name="login" value="<%=Session("LoginName")%>">
                <%=Session("LoginName")%> </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">Email Address(Not Changable yet): </div>
              </td>
              <td width="44%"> 
                <input type="hidden" name="email" value="<%=rst("email")%>">
                <%=rst("email")%> </td>
            </tr>
            <tr> 
              <td colspan="2">
                <div align="center"><b>Do not type anything in the password boxes 
                  unless you intend on changing your password.</b></div>
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">New Password: </div>
              </td>
              <td width="44%"> 
                <input type="password" name="pw1" size="15" maxlength="50">
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">New Password Confirm: </div>
              </td>
              <td width="44%"> 
                <input type="password" name="pw2" size="15" maxlength="50">
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">First Name: </div>
              </td>
              <td width="44%"> 
                <input type="text" name="first" size="15" value="<%=rst("first")%>">
              </td>
            </tr>
            <tr> 
              <td height="29" width="56%"> 
                <div align="right">Last Name: </div>
              </td>
              <td height="29" width="44%"> 
                <input type="text" name="last" size="15" value="<%=rst("last")%>">
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">Snail Mail Address: </div>
              </td>
              <td width="44%"> 
                <input type="text" name="address" size="30" value="<%=rst("address")%>">
              </td>
            </tr>
            <tr> 
              <td width="56%" height="28"> 
                <div align="right">City: </div>
              </td>
              <td width="44%" height="28"> 
                <input type="text" name="city" size="20" value="<%=rst("city")%>">
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">State: </div>
              </td>
              <td width="44%"> 
                <input type="text" name="state" size="2" value="<%=rst("state")%>" maxlength="2">
              </td>
            </tr>
            <tr> 
              <td width="56%"> 
                <div align="right">Phone Number: </div>
              </td>
              <td width="44%"> 
                <input type="text" name="phone" size="15" value="<%=rst("phone")%>" maxlength="14">
              </td>
            </tr>
            
          </table>
		  <hr width="40%">
          <b><font size="5">RSVP </font></b>
		  <% if Request.querystring("rsvp") then %> 
		  <SCRIPT>
		  	<!--
				 alert("Since you have not yet RSVPed, please do so.  I've taken you to the Profile page automatically where you can RSVP on the bottom.\n\nThis will happen every time you log in until you at least say you are or are not going.\n\nPlease just do it, it's really quick.\n\nThanx\n-Gumm");
		  	-->
		  </SCRIPT>
		  <% end if %>
          <table width=80%>
            <tr align="center"> 
              
              <td width="22%"><b>LAN Party</b></td>
              <td width="25%"><b>Date & Time</b></td>
			  <td width="21%"><b>Will Attend</b></td>
              <td width="32%"><b>Number of Computers you are Bringing <font size=-1>(<a href="computernote.asp" target="nwin" onClick="new_win = window.open('','nwin','scrollbars=no,width=400,height=150');new_win.focus()">Note</a>)</font></b></td>
            </tr>
            <%
				dim rstR, LANDate, LANPartyID, WillAttend, NumFast
				set rstR=myconn.execute("Select * from NextLANParties order by LANDate")
				if not rstr.eof then
					LANDate = rstR("LANDate")
					LANPArtyID = rstR("LANPArtyID")
					set rstr=myconn.execute("Select * from RSVP where LANPartyID='" & rstR("LANPArtyID") & "' and Login='" & Session("LoginName") & "'")
					if rstr.eof then
						WillAttend = True
						NumFast = 0
					else
						WillAttend=rstR("Going")
						FastCount=rstR("FastCount")
					end if
				end if
				
			%>
            <tr align=center> 
              
              <td width="22%"><font size=6><%=LANPartyID%></font></td>
              <td width="25%"><%=LANDate%></td>
			  <td width="21%">
                <input type="checkbox" name="Going" <%if WillAttend then response.write(" checked ")%>>
                </td>
              <td width="32%"> 
                <input type="text" name="Computers" value="<%=FastCount%>" size="2" maxlength="2">
              </td>
            </tr>
          </table>
		  <p>
            <input type="Submit" name="Submit2" value="Submit Changes">
          </p>
        </form>
		</div>
        <%
		End If
		End If
		%>
        
      <!-- #include file="footer.asp" -->