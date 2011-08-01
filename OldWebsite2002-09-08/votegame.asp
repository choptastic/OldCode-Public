<!-- #include file="header.asp" -->

<%
	dim gameid
	dim votedate
	
	gameid=request.form("gameid")
	ipaddress=Request.ServerVariables("REMOTE_ADDR")
	votedate=cdate(clng(now))
	
	dim rsv
	set rsv=myconn.execute("Select * from votes where voteip='" & ipaddress & "' AND votedate=Cdate('" & votedate & "');")
	'rsv.movefirst
	'response.write rsv.eof
	if rsv.eof then
		'response.write "Added"
		myconn.execute "Insert into votes(voteip,votedate,votegame) values('" & ipaddress & "','" & votedate & "'," & gameid & ");"
		response.redirect "games.asp"
	else
		response.write "Error: You may only vote once per day"
	end if
%>
	
<!-- #include file="footer.asp" -->