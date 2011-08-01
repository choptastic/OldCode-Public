<%  if Session("Palm") = "" then Session("Palm")=false 
	Session("Palm")=not(Session("Palm"))
	response.redirect "PalmIndex.asp"
%>