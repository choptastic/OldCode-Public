<!-- #include file="StringFunctions.asp" -->
<%	

function GetTableColor(num)
	GetTableColor="#" & num & num & "0000"
end function

dim AlternatingColor

function FindLastPoster(ID)
	dim rst
	set rst=myconn.execute("Select * from Forum where RootThread=" & ID & " order by ID Desc;")
	if rst.eof then
		FindLastPoster=""
	else
		FindLastPoster=rst("Name")
	end if
	rst.close
end function
	

function GetAlternatingTableColor()
	if AlternatingColor=GetTableColor(6) then
		AlternatingColor=GetTableColor(5)
	else
		AlternatingColor=GetTableColor(6)
	end if
	GetAlternatingTableColor=AlternatingColor
end function

function IsImageFile(filename)
	dim temp
	temp=lcase(filename)
	if right(temp,4)=".gif" or _
		right(temp,4)=".jpg" or _
		right(temp,5)=".jpeg" or _
		right(temp,4)=".jpe" then
			isimagefile=true
	else
		isimagefile = false
	end if
end function

function RootOfThread(threadID)
	dim rstm, TID, ID
	set rstm = myconn.execute("Select * from forum where ID=" & threadid)
	if rstm.eof then 
		RootOfThread=-1
	else
		TID=rstm("ThreadID")
		ID=rstm("ID")
		rstm.close
		if TID = 0 then
			RootOfThread=ID
		else
			RootOfThread=RootOfThread(TID)
		end if
	end if
end function

function FormattedStringValue(s)
	dim fs,a, strs, strs1, i, x, finished, size, ii
	s=server.htmlencode(s)
	'Start New Change
'	strs=Split(s,vbcrlf)
'	s=""
'	for x = 0 to ubound(strs)
'		strs1=Split(strs(x)," ")
'		for i=0 to ubound(strs1)
'			size=len(strs1(i))
'			finished=""
'			for ii=1 to size step 200
'				finished=finished & mid(strs1(i),ii,200)
'				if ii<size then
'					finished=finished & "- "
'				end if
'			next
'			strs1(i)=finished
'		next
'		for i=0 to ubound(strs1)
'			strs(x)=strs(x) & strs1(i) & " "
'		next
'		s=strs(x) & vbcrlf
'	next
				
	'End New Change
	
	strs=Split(s,vbcrlf)
	finished=""
	for x = 0 to ubound(strs)
		strs1=Split(strs(x)," ")
		strs(x)=""
		for i = 0 to ubound(strs1)
			if lcase(left(strs1(i),7)) = "http://" or lcase(left(strs1(i),6))= "ftp://" then
				if IsImageFile(strs1(i)) then
					strs1(i) = "<img src=" & strs1(i) & ">"
				else
					strs1(i) = "<a href=" & strs1(i) & ">" & strs1(i) & "</a>"
				end if
			end if
			strs(x)=strs(x) & strs1(i) & " "
		next
		finished=finished & strs(x)
		strs(x)=trim(strs(x))
		if ucase(right(strs(x),len("quote]")))><"QUOTE]" then
			if x < ubound(strs) then
				 finished =finished & "<br>"
			end if
		end if
	next
	
	
	finished=ReplaceChar(finished,"[QUOTE]","<blockquote><hr>")
	finished=ReplaceChar(finished,"[/QUOTE]","<hr></blockquote>")

	FormattedStringValue=finished
end function

sub PrintTextFileFormatting(filename, Formatting)
	dim fs,a, strs, i, x, finished
	Set fs = CreateObject("Scripting.FileSystemObject")
	set a = fs.OpenTextFile(filename)
			while not a.AtEndOfStream
				i=a.readline
				i=server.htmlencode(i)
				If Formatting then
					strs=Split(i," ")
					for x = lbound(strs) to ubound(strs)
						if lcase(left(strs(x),7)) = "http://" or lcase(left(strs(x),6))= "ftp://" then
							if IsImageFile(strs(x)) then
								strs(x) = "<img src=" & strs(x) & ">"
							else
								strs(x) = "<a href=" & strs(x) & ">" & strs(x) & "</a>"
							end if
						end if
						finished = finished & strs(x) & " "
					next
					response.write(finished & "<br>")
				else
					response.write(i)
				end if
				if not(a.AtEndOfStream) then
					response.write(vbcrlf)
				end if
				finished=""
			wend
	a.close 
end sub
	
	Sub PrintTextFile(filename)
		PrintTextFileFormatting filename, true
	end sub
	
	sub PrintNoFormatting(filename)
		PrintTextFileFormatting filename, false
	end sub
	
	sub MakeNewTextFile(filename,contents)
	dim fs, a
	Set fs = CreateObject("Scripting.FileSystemObject")
	Set a = fs.CreateTextFile(filename, True)
	a.WriteLine(contents)
	a.Close
	end sub

	sub PrintDrivingDirections(filename)
	dim fs,a
	Set fs = CreateObject("Scripting.FileSystemObject")
	set a = fs.OpenTextFile(filename)
			response.write("<ol>")
			while not a.AtEndOfStream
				i=a.readline
				response.write("<li>" & i & "</li>")
			wend
			response.write("</ol>")
	a.close 
	end sub
	

	function PostLevel(Login)
		dim rst, count
		set rst = myconn.execute("Select * from PostCounts inner join Logins on Logins.Login=PostCounts.Name where Login='" & Login & "' and Name='" & Login & "';")
		if not rst.eof then
			count=rst("CountOfID")
			rst.close
			set rst=myconn.execute("Select * from PostLevels where NumPosts<=" & count & " order by NumPosts DESC;")
			PostLevel="Post Count: " & count & "<BR><font color=#00FF00>Rank: " & rst("PostLevel") & "</font>"
		else
			PostLevel=""
		end if
		rst.close
	end function
	
	
	function GetCurrentLoginID()
		dim rst, ip
		set rst = myconn.execute("Select * from Logins where LastIP='" & Request.ServerVariables("REMOTE_ADDR") & "'")
		if rst.eof then
			getcurrentloginid= 0
		else
			getcurrentloginid=rst("LoginID")
		end if
	end function
	
	function GetLoginName(ID)
		dim rst
		set rst = myconn.execute("Select * from Logins where LoginID='" & ID & "'")
		if rst.eof then
			getloginname = "<Not Registered>"
		else
			getloginname = rst("First") & " " & rst("last")
		end if
	end function

	sub PrintMessage(ID, subject, pname, PDate, Links)
		dim msg
		if links then
			if now-(2/24) < pdate then 
				response.write("<font color='#ffffff'>")
			elseif now-1 < pdate then	
				response.write("<font color='#00ff00'>")
			elseif now-3 < pdate then
				response.write("<font color='#FF6699'>")
			end if
		end if
		'response.write(links)
		msg="<b>"
		if links then msg=msg & "<a href='displaymessage.asp?ID=" & id & "'>"
		msg=msg & subject
		if links then msg=msg & "</a>"
		msg= msg & "</b> - <i>" & pname & "</i> - " & pdate
		response.write(msg)
		'if now-3 < pdate then 
		response.write("</font>" & vbcrlf)
	end sub
	
	sub DisplayThread(ID, num, ShowRootThread, IDNotToDisplay)
		dim rst
		dim count, links
		count=0
		If ShowRootthread then
			response.write "<UL><LI>"
			set rst=myconn.execute("select * from forum where id=" & id)
			if cint(rst("id"))=cint(IDNotToDisplay) then
				links=false
			else
				links=true
			end if
			'response.write("<p>ThreadID=" & IDNotToDisplay & "<p>")
			PrintMessage rst("id"),rst("subject"),rst("name"),rst("Date"), links
			rst.close
		end if
		set rst=myconn.execute("select * from forum where threadid=" & id & " order by ID desc;")
		if not rst.eof then
			response.write "<UL>"
			while not rst.eof and count < num
				response.write("<li>")
				if cint(rst("id"))=cint(IDNotToDisplay) then
					links=false
				else
					links=true
				end if
				'response.write("<p>ThreadID=" & IDNotToDisplay & "<p>")
				PrintMessage rst("id"),rst("subject"),rst("name"),rst("Date"), links
				DisplayThread rst("ID"),32000, false, IDNotToDisplay
				response.write("</li>")
				rst.movenext
				count = count + 1
			wend
			if ShowRootthreads then	response.write("</li></UL>")
			response.write "</ul>"
		end if
		
		rst.close
	end sub
	
	sub DisplayBlockThreads()
		dim rst, curcolor
		curcolor="#555555"
		
		set rst=myconn.execute("Select * from forum inner join Threadsize on forum.rootthread=threadsize.rootthread where threadid=0 order by LastReply DESC")
		%>
	
		<table width="100%" align=center border=0 cellspacing=1>
			<tr bgcolor=#000000>
				
				
    <td width=51%><font color="#FFFFFF">Subject</font></td>
				
    <td width="14%"><font color="#FFFFFF">Poster:</font></td>
				
    <td width="5%"><font color="#FFFFFF">Replies:</font></td>
				
    <td width="30%"><font color="#FFFFFF">Last Reply:</font></td>
			</tr>
		<%
		while not rst.eof
			curColor=GetAlternatingTableColor
		%>
		<tr bgcolor=<%=curcolor%>>
		
			
    <td width="51%"><A href="viewblock.asp?C=<%=rst("ID")%>" color=#FFFFFF><%=rst("subject")%></a></td>
			
    <td width="14%"><%=rst("Name")%> 
    <td width="5%"><%=rst("CountofID")-1%></td>
			
    <td width="30%"><%=FindLastPoster(rst("ID"))%> @ <%=rst("LastReply")%></td>
		</tr>
		<%
			rst.movenext
		wend
		%>
		</table>
		
	
<% 
end sub

sub DisplayBlockThread(RootThread, ReplyTo, Editing)
	dim rst
	set rst = myconn.execute("Select * from forum where RootThread=" & RootThread & " order by date;")
	if rst.eof then
		response.redirect("viewblock.asp?C=" & RootOfThread(Rootthread))
	end if
%>
	
<table width=100% border=0 cellspacing=1>
  <tr bgcolor=#000000>
	<td width=30%><font color=#FFFFFF>Post Info:</font></td>
	<td colspan = 2><font color=#FFFFFF>Message:</font></td>
	</tr>
	<% while not rst.eof 
		dim PostText
		posttext=rst("text")%>
	<tr HEIGHT="15">
	<td rowspan=2 bgcolor=#660000 valign=top width=30%> <%=rst("Date")%><br>
		<b><%=rst("Name")%></b><br>
      <%=PostLevel(rst("Name"))%></td>
	<td bgcolor=#330000 height=15><font color=#FF0000><b><a name=<%=rst("ID")%>></a><%=rst("Subject")%></b></font></td>
    <td bgcolor=#330000 WIDTH=20%> 
      <P align=right> 
        <% if Session("LoginName")>< "" then %>
        <a href=viewblock.asp?C=<%=RootThread%>&R=<%=rst("ID")%>#<%=rst("ID")%>>[Reply]</a> 
        <% 	if ucase(Session("LoginName"))=ucase(rst("Name")) Or ucase(Session("LoginName"))="CHOPS" then %>
        <a href=viewblock.asp?C=<%=RootThread%>&E=<%=rst("ID")%>#<%=rst("ID")%>>[Edit]</a> 
        <% end if
	else %>
        <A href="#Login">[To Interact, Login]</a>
        <% end if %>
		<a href="newforum.asp">[Index]</a>
      </P>
    </td>
  <tr>
	<td bgcolor=#550000 colspan=2> 
      <% if CLng(Editing)=rst("ID") and len(Session("LoginName"))>0 then %>
      <form name="form1" method="post" action="editmessage.asp">
			<input type="hidden" name="ID" value="<%=rst("ID")%>">
			<input type="hidden" name="Name" value="<%=rst("Name")%>">
			<center><font size=4>Edit Message</font></center>
			
        <table width="100%" border="0" cellspacing="0" cellpadding="0" align="center" height="210">
         	<tr>
				
				<td width="13%">Subject:</td>
					
				
            <td width="87%"> 
              <input type="text" name="subject" size="50" maxlength="50" value='<%=rst("Subject")%>'>
				</td>
			</tr>
			<tr>
					<td width="13%">Text:</td>
					<td width="87%">
						<textarea name="text" cols="60" rows="10"><%=posttext%></textarea>
					</td>
			</tr>
		</table>
			<center>
			
          <input type="submit" name="Submit" value="Save Changes">
          <input type="reset" name="Submit2" value="Reset To Original">
        </center>
		</form>
      <% 
	  	else
			response.write(formattedStringValue(posttext))
		end if
	  if Clng(Replyto)=rst("ID") and len(Session("LoginName"))>0 then %>
	 	<form name="form1" method="post" action="addmessage.asp">
			<input type="hidden" name="threadID" value="<%=replyto%>">
			<input type="hidden" name="RootThread" value="<%=RootThread%>">
			<center><font size=4>Reply To Message</font></center>
			
			<table width="100%" border="0" cellspacing="0" cellpadding="0" align="center" height="210">
				<tr>
					
					<td width="13%">Subject:</td>
						
					<td width="87%"> 
					  <input type="text" name="subject" size="50" maxlength="50" value="<%if ucase(left(rst("Subject"),3)) >< "RE:" then response.write("Re: ") %> <%=rst("Subject")%>">
					</td>
				</tr>
				<tr>
					
            <td width="13%">Text:</td>
					<td width="87%">
					<textarea name="text" cols="60" rows="10">[QUOTE]<%=posttext%>[/QUOTE]</textarea>
					</td>
				</tr>
			</table>
			<center>
			<input type="submit" name="Submit" value="Submit">
          <input type="reset" name="Submit2" value="Reset"></center>
		</form>
		<% end if %>
    </td>
  </tr>
	<% rst.movenext
		wend %>
	</table>
	
<% end sub



%>
		
		

