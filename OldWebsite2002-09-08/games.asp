<%
		function VotesToNumber(v)
			if isnull(v) then
				votestonumber=0
			else
				votestonumber=v
			end if
		end function
		%>

<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
      <div align="center">
        <%
		dim rsg,stri,rss
		sql="Select * From Games where Display=Yes"
		set rsg=myconn.execute(sql)
		while not rsg.eof
	%>
      </div>
	  <form name='<%="form" & rsg("GameID")%>' method="post" action="votegame.asp">
      <input type="hidden" name="gameid" value='<%=rsg("GameID")%>'>
      <table width="95%" border="0" cellspacing="0" cellpadding="0" align="center">
        <tr> 
          <td colspan="4" bgcolor=<%=GetTableColor(0)%>> 
            <div align="center"><b><font face="Courier New, Courier, mono" size="4" color="<%=GetTableColor("F")%>"><%= rsg("gametitle")%> 
              </font></b></div>
          </td>
        </tr>
        <tr> 
          <td rowspan="3" width="13%" bgcolor=<%=GetTableColor(0)%>> 
              <div align="center"><img src='<%=rsg("gamethumb")%>'><br>
              </div>
          </td>
            <td rowspan="3" width="59%" bordercolor="1"> 
              <p><font face="Verdana, Arial, Helvetica, sans-serif" size="2"> 
                <%
			  	stri="d:\games\" & rsg("GameTextFile") 
			  	PrintTextFile stri
				
			  %>
                </font></p>
              <p align="center"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"> 
                <!--<input type="submit" name="Vote" value="Vote for this Game"> -->
                </font><font face="Geneva, Arial, Helvetica, san-serif"> </font></p>
          </td>
          <td width="12%" bgcolor=<%=GetTableColor(1)%>>Release Date:</td>
          <td width="16%"bgcolor=<%=GetTableColor(1)%>> 
            <div align="right"> <%=rsg("release")%></div>
          </td>
        </tr>
        <tr bgcolor=<%=GetTableColor(2)%>> 
          <td width="12%">Developer:</td>
          <td width="16%" > 
            <div align="right"><a href='<%=rsg("website")%>'><%=rsg("developer")%></a></div>
          </td>
        </tr>
        <tr bgcolor=<%=GetTableColor(3)%>> 
          <td colspan="2"  height="11"> 
            <div align="right"><a href='<%=rsg("download")%>'>Download Demo</a> 
            </div>
          </td>
        </tr>
      </table>
	  
      <table width="95%" border="0" cellspacing="0" cellpadding="0" align="center">
	  <% sql = "Select * from ScreenShots where GameID=" & rsg("gameid") & ";"
	  	set rss=myconn.execute(sql)
	  %>
        <tr>
		<% while not rss.eof %>
          <td bgcolor=<%=GetTableColor(0)%>> 
            <div align="center"> <a href='games/<%= rss("filename")%>'>Screen 
              Shot</a> </div>
          </td>
		 <%	rss.movenext 
		 wend %>
        </tr>
      </table>
	  </form>
      <hr>
      <%
	  	rsg.movenext
		wend
	  %>
      <hr>
      <div align="center"><b><font size="5">Add a Game to the List </font></b></div>
	  <% if Session("LoginName") = "" then %>
      <div align="center">Must be logged in to suggest a Game 
        <% else %>
      </div>
      <form name="gameform" method="post" action="addgame.asp">
        <input type="hidden" name="submitter" size="25" value="<%=Session("LoginName")%>">
        <table width="80%" border="0" cellpadding="0" cellspacing="2" align="center">
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Game Name:</td>
            <td width="75%"> 
              <input type="text" name="gamename" size="30">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Release Date:</td>
            <td width="75%"> 
              <input type="text" name="release" size="25">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Developer:</td>
            <td width="75%"> 
              <input type="text" name="developer" size="25">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Developer Website:</td>
            <td width="75%"> 
              <input type="text" name="developerweb" size="50">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Thumbnail Picture URL:</td>
            <td width="75%"> 
              <input type="text" name="thumb" size="50">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Demo Download URL:</td>
            <td width="75%"> 
              <input type="text" name="demo" size="50">
            </td>
          </tr>
          <tr align="left" valign="top"> 
            <td width="25%" align="right">Description</td>
            <td width="75%"> 
              <textarea name="desc" wrap="VIRTUAL" cols="55" rows="10"></textarea>
            </td>
          </tr>
        </table>
        <p align="center"> 
          <input type="submit" name="Submit" value="Submit">
          <input type="reset" name="re" value="Reset">
        </p>
      </form>
	  <% end if %>
      <!-- #include file="footer.asp" -->
