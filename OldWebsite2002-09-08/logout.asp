<% Session("LoginName")=""
	response.Cookies("LoginName").expires=now
	page=request.QueryString("P")
	if page= "" or page="/editprofile.asp" or page="/profile.asp" then
		page="main.asp"
	end if
	response.redirect(page & "?" & Session("QS"))
%>