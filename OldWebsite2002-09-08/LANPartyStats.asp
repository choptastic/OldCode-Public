<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
      <div align="center"> 
        <hr>
        <p><font size="5"><b>Next LAN Party - Projected</b></font><br>
          (based on RSVPs, editable in your profile) </p>
        <hr width="30%">
      
          <%set rst = myconn.execute("Select * from NextLANPArties order by LANDate")
			LANPArtyID=rst("LANPArtyID") 
		  	set rst=myconn.execute("Select * from rsvpcounts where LANPartyID='" & LANPArtyID & "'")	
		  		if not rst.eof then
				%>
          <font size="4" color="#FFFFFF">Totals</font>
        <table width="75%" border="0" cellpadding="1" cellspacing="1">
          <tr bgcolor="#000000"> 
            <td =50%> 
              <div align="center"><font size="4">Number of People</font></div>
            </td>
            <td> 
              <div align="center"><font size="4">Number of Computers</font></div>
            </td>
          </tr>
          <tr bgcolor="<%=GetTableColor(7)%>"> 
            <td> 
              <div align="center"><%=rst("ID")%></div>
            </td>
            <td> 
              <div align="center"><%=rst("Fast")%></div>
            </td>
          </tr>
        </table>
	
		<hr width="30%">
        <font color="#FFFFFF"><b><font size="4">Inviduals Signed Up</font></b></font><br>
        <table width="75%" border="0" cellpadding="1" cellspacing="1">
          <tr bgcolor=#000000>
				
            <td width="31%"><b>Login Name</b></td>
				
            <td width="34%"><b>Real Name</b></td>
				
            <td width="35%"><b>Number of computers</b></td>
			  </tr>
		<%			rst.close
					dim curColor
					
					set rst=myconn.execute("Select * from RSVPLogins where LANPArtyID='" & LANPartyID & "'")
					while not rst.eof
						curcolor=GetAlternatingTableColor
		%>
			
			  <tr bgcolor=<%=curColor%>>
				
            <td width="31%"><%=rst("Login")%></td>
				
            <td width="34%"><%=rst("Name")%></td>
				
            <td width="35%"><%=rst("FastCount")%></td>
			  </tr>
			
 
				 <% 	rst.movenext
				 	wend  %> </table>
				 <% end if %>
      </div>
	  	<%
		dim rstS, rstA
	  	sql="Select * from LANParties where LANDate<Now() order by LANDate DESC"
		set rst = myconn.execute(sql)
		while not rst.eof
		%>
		<hr><center><font size=5><b>LAN Party <%=rst("LANPartyID")%></b></font><br>
		<%
			set rsts=myconn.execute("Select * from ComputerStatistics where LANPartyID='" & rst("LANPartyID") & "'")
			if not rsts.eof then
		%>
		<hr width="30%"><font size=4 color="FFFFFF"><b>Statistics</b></font></center>
		
      <table width="300" border="0" align="center" cellpadding="1" cellspacing="0">
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Number of Fast Computers:</div>
          </td>
          <td width="37%"><div align="right"><%=rstS("CountOfComputerID")%> 
            </div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Collective CPU Speed:</div>
          </td>
          <td width="37%"><div align="right"><%=rstS("SumOfCPU")/1000%> 
            GHz</div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>"> 
          <td width="63%"> 
            <div align="right">Total RAM:</div>
          </td>
          <td width="37%"><div align="right"><%=rstS("SumOfMemory")%> 
            MB</div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Total Hard Disk Space:</div>
          </td>
          <td width="37%"><div align="right"><%=rstS("SumOfHardDrive")%> 
            GB</div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Average CPU Speed:</div>
          </td>
          <td width="37%"><div align="right"><%=FormatNumber(rstS("AvgOfCPU"),2)%> 
            GHz</div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Average RAM:</div>
          </td>
          <td width="37%"><div align="right"><%=FormatNumber(rstS("AvgOfMemory"),2)%> 
            MB</div>
          </td>
        </tr>
        <tr bgcolor=<%=GetAlternatingTableColor%>> 
          <td width="63%"> 
            <div align="right">Average Hard Disk Space:</div>
          </td>
          <td width="37%"><div align="right"><%=FormatNumber(rstS("AvgOfHardDrive"),2)%> 
            GB</div>
          </td>
        </tr>
      </table>
		<% 	end if
			rsts.close
			
			set rstS=myConn.execute("Select * from Awards where LANPArtyId='" & rst("LANPARTYID") & "';")
			if not rsts.eof then
		%>
				<font size=4 color="FFFFFF"><center><hr width="30%"><b>Awards</b></center></font>
				
      <table  align="center" cellpadding="2" cellspacing="0">
        <tr bgcolor="#000000"> 
          <td width="170"><b>Award Name</b></td>
				  
          <td width="120"><b>To Whom</b></td>
				  
          <td width="350"><b>Reasoning</b></td>
				</tr>
			<%
	
				
				while not rsts.eof
					curcolor=GetAlternatingTableColor
				%>
				<tr bgcolor="<%=CurColor%>">
				  <td width="170"><%=rsts("AwardName")%></td>
				  <td width="120"><%=rsts("AwardWinner")%></td>
				  <td width="350"><%=rsts("Description")%></td>
      			</tr>
				<%	
				rsts.movenext
				wend
				%>
				</table>
				<%
			end if
			rst.movenext
		wend %>
      <!-- #include file="footer.asp" -->