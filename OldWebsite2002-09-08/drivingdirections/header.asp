<% 


	function formatname(size)
		dim name
		name=Session("LoginName")
		dim num, i
		num = len(name)/size
		if num><cint(num) then
			num=fix(num)+1
		end if
		if len(name)<=size then
			formatname = name
		else 
			for i=0 to num-2
				formatname = formatname & mid(name,i*size+1,size) & "-<br>"
			next
			formatname = formatname & mid(name,(num-1)*size+1,size)
		end if
		
	end function
	
	function FormatTime(t)
		dim h,m,ap
		h=hour(t)
		if h>12 then
			h=h-12
			ap="PM"
		elseif h=12 then
			ap="PM"
		elseif h=0 then
			h=12
			ap="AM"
		else
			ap="AM"
		end if
		m=minute(t)
		if m < 10 then
			m = "0" & m
		end if
		formattime=h & ":" & m & " " & ap
	end function
		Session("LoginName")=Request.Cookies("LoginName")
		if Session("LoginName") >< "" then
			Response.Cookies("LoginName").Expires=now + 30
		end if
		dim ScriptName
		ScriptName=Request.ServerVariables("SCRIPT_NAME")
	
		if UCase(ScriptName)><"/LOGIN.ASP" then
			Session("QS")=Request.querystring
		end if
		dim myconn,sql,rs,bs
		Set bc = Server.CreateObject("MSWC.BrowserType") 
		Set MyConn = Server.CreateObject("ADODB.Connection")
		MyConn.Open "DSN=Main"
		myconn.execute "insert into hits(hitdatetime,hitip,page,browser) values('" & now() & "','" & Request.ServerVariables("REMOTE_ADDR") & "','" & ScriptName & "','" & bc.browser & "-" & bc.platform & "');"
		SQL = "SELECT * FROM [menu] where display=Yes order by sortval;"
		Set RS = MyConn.Execute(SQL)
		sql="Select * from lanparties where landate >= now() order by landate;"
		set rsd = myconn.execute(sql)
		sql = "Select First,Last,Login from Logins where Active=Yes Order By LoginID DESC;"
		dim newmember
		set newmember=myconn.execute(sql)
		dim rsstat
		set rsstat=myconn.execute("Select * from rsvpcounts where LANPartyID='" & rsd("LANPartyID") & "'")
		if rsstat.eof then
			RSVPedPeople=0
			RSVpedComputers=0
		else
			RSVPedPeople=rsstat("ID")
			RSVPEdComputers=rsstat("fast")
		end if
		
			
		Dim rsPosts, Post24, Post7
		set rsPOsts = myconn.execute("Select Count(ID) as Counted from Forum where [date]+1>Now()")
		Post24 = rsPosts("Counted")
		rsPosts.close
		set rsPOsts = myconn.execute("Select Count(ID) as Counted from Forum where [date]+7>Now()")
		Post7 = rsPosts("Counted")
		rsposts.close
		dim PageTitle,PageDescription
		dim page
		page=Right(ScriptName,len(ScriptName)-1)
		set rsposts=myconn.execute("Select * from PageTitles where [Page] like '" & page & "';")
		'response.write "Select * from PageTitles where [Page] like '" & page & "';"
		if rsposts.eof then 
			PageTitle=""
			PageDescription=""
		else
			PageTitle=rsposts("Title")
			PAgeDescription=rsposts("Description")
		end if
			
		
%> 
<html>
<head>
<script language="Javascript">
<!--
	referal.referrer.value=document.referrer;
	if(document.referrer.indexOf('gummlanparty')=-1 && document.referrer)
		refer.submit();
//-->
</script>
<title>Gumm LAN Party</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<style type="text/css">
<!--
a:link {  text-decoration: none}
a:visited {  text-decoration: none}
a:active {  text-decoration: none}
a:hover {  text-decoration: underline}
-->
</style>
</head>
<body bgcolor="#440011" text="#FFcc99" link="#FFCC00" vlink="#FF6600" alink="#CC0000">
<form name="referal" method="post" action="referrer.asp?src=<%=ScriptName%>">
<input type="hidden" name="referrer">
</form>
<% if Session("Palm")=false then %><table width="100%" border="0" cellspacing="0" cellpadding="0" height="376" align="left"> 
<tr> 
    <td height="47" rowspan=2><b><font size="4">GummLANParty.net</font></b></td>
    <td height="26" width="343" bgcolor="#330000"> 
      <div align="center"><font face="Arial, Helvetica, sans-serif" color="#FFFFFF"><font size="2">LAN 
        Party </font><font face="Arial, Helvetica, sans-serif" color="#FFFFFF"><font size="2"> <%=rsd("LANPartyID")%> </font></font><font size="2"> : <%= weekdayname(weekday(rsd("landate"))) %>, 
        <%=monthname(month(rsd("landate")),true) & " " & day(rsd("landate"))%>, 
        <%=year(rsd("landate"))%> @ <%=formattime(rsd("landate"))%></font></font></div>
    </td>
    <td height="26" width="327" bgcolor="#330000"> 
      <p align="center"><font face="Arial, Helvetica, sans-serif" size="2" color="#FFFFFF">People 
        RSVPed : <%=RSVPEdPeople%> </font></p>
    </td>
    <td height="26" width="276" bgcolor="#330000"> 
      <div align="center"><font face="Arial, Helvetica, sans-serif" size="2" color="#FFFFFF">Computers 
        RSVPed : <%=RSVPedComputers%> </font></div>
    </td>
  </tr>
  <tr align=center bgcolor=#000000> 
    <td height="21" bgcolor="#330000"><A href="forumsearch.asp">Search the Forum</a></td>
    <td height="21" bgcolor="#330000" ><font color="#FFFFFF" face="Arial, Helvetica, sans-serif" size="2">Posts 
      in Last 24 Hours : <%=post24%></font></td>
    <td height="21" bgcolor="#330000"><font color="#FFFFFF" size="2" face="Arial, Helvetica, sans-serif">Posts 
      in Last Week : <%=post7%></font></td>
  </tr>
  <tr> 
    <td align="left" valign="top" height="810" width="169"> 
      <center>
	  	<table bgcolor="#330000" width=100% border=0 cellpadding=2 cellspacing=0>
			<tr>
				<td>
					<font size=2>
					<center><b>Newest Members</b></center>
					<hr>
					
					<% Count=0 %>
					<% while Count<3 %>
						<li>
							<B><%=Newmember("Login")%></b>(<%=NewMember("First")%>&nbsp;<%=NewMember("Last")%>)
						</li>
						<% 
							NewMember.movenext
							Count=Count+1	
						%>
					<% wend %>
					
				</font>
				</td>
			</tr>
		</table>
							
				
        <!-- #include file="MenuTop.asp" -->
              <font color="#FFCC33" size="+1" face="Arial"> 
              <center>
                <font size="-2"> 
                <% if Session("LoginName")="" then %>
					<a name="Login"></a>
					<form name="form1" method="post" action="login.asp">
					  <input type="hidden" name="page" value="<%=Request.ServerVariables("SCRIPT_NAME")%>">
					  Login:<br>
					  <input type="text" name="login" size="8" maxlength="50">
					  <br>
					  Password:<br>
					  <input type="password" name="pw" size="8" maxlength="50">
					  <br>
					  <input type="submit" name="Submit" value="Login">
					  <br>
					  <a href="newmember.asp">No Login? Register</a><br>
					</form>
                <% else %>
					Logged in as:<br>
					<font size=+0><b><%=formatname(10)%></b></font><br>
					<a href="profile.asp"><font size=+0>Edit Profile</font></a><br>
					<a href="logout.asp?P=<%=ScriptName%>">Logout</a> 
                <% end if %>
                </font> 
                <hr>
                <% while not rs.eof %>
                <% response.write("<a href='" & rs("link") & "'>" & rs("linktext") & "</a><br>") %>
                <br>
                <%	rs.movenext
			wend %>
                <a href="palm.asp">Palm Version</a><br>
              </center>
              </font> 
              <% if Session("LoginName") >< "" then %>
              Gumm ICQ: <img src="http://wwp.icq.com/scripts/online.dll?icq=996541&img=5"> 
              <% end if
				 if Session("LoginName") = "Chops" then %>
              <a href="/SendNewsletter.asp"> Newsletters </a> 
              <% end if %>
              <!-- #include file="MenuBottom.asp" -->
        <!-- Begin User List of logged in -->
        <!-- #include file="MenuTop.asp" -->
              <center>
                <font size="4"><b>GuLP Logins </b></font> 
                <hr>
                <font size="+1"> 
                <%
					set rst = myconn.execute("select login from logins where online=yes order by login")
					if rst.eof then
						response.write("<font size=0>{No One Online}</font>")
					end if
					dim Color
					color="#FFCC33"
					while not rst.eof
						if color = "#FFCC33" then
							color = "#CCFF22"
						else
							color="#FFCC33"
						end if
						response.write("<font color='" & color & "'>" & rst("login") & "</font><br>")
						rst.movenext
					wend
				%>
                </font> 
              </center>
              <!-- #include file="menuBottom.asp" -->
      </center>
    </td>
    <td colspan="3" height="810" align="left" valign="top"> 
      <% else %>
      <!-- #include file="palmheader.asp" -->
      <% end if %>
      <!--  End REAL File -->

      <!-- #1include file="footer.asp" -->
<center>
	  <font size=6><b><%=PageTitle%></b></font><br>
	  <font size=4><%=PageDescription%></font>
	  </center>
