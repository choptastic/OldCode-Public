<!-- #include file="header.asp" -->
<!-- #include file="functions.asp" -->
<font size=6>
<%
	dim game,release,developer,developerweb,thumb,desc,submitter,email,demo,e
	e=false
	game=trim(request.form("gamename"))
	release=trim(request.form("release"))
	developer=trim(request.form("developer"))
	developerweb=trim(request.form("developerweb"))
	thumb=trim(request.form("thumb"))
	desc=trim(request.form("desc"))
	submitter=trim(request.form("submitter"))
	demo=trim(request.form("demo"))
	if game="" then
		e=true
		response.write("Error: Must specify Game Name<br>")
	end if
	if release="" then
		release="Not Known"
	end if
	if thumb="" then
		thumb="notknown.gif"
	end if
	
	if developer="" then
		e=true
		response.write("Error: Must specify Developer<br>")
	end if
	
	if developerweb="" then
		developerweb="#"
	end if
	
	if desc="" then
		e=true
		response.write("Error: Must supply a Description<br>")
	end if
	
	if submitter="" then
		e=true
		response.write("Error: Must specify your Name<br>")
	end if
	if email="" then
		email="Not specified"
	end if
	
	if demo="" then
		demo = "#"
	end if
	
	if e = false then
	
	sql="insert into games(gametitle,release,developer,website,gamethumb,gametextfile,submitter,download) " & _
		"values('" & game & "','" & release & "','" & developer & "','" & developerweb & "','" & thumb & "','" & _
		game & ".txt','" & submitter & "','" & demo & "');"
	makenewtextfile "d:\games\" & game & ".txt",desc
	myconn.execute sql
	response.redirect("games.asp")
	end if
%>
</font>
<!-- #include file="footer.asp" -->