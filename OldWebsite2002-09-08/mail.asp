<% dim objnewmail
set objNewMail = server.createObject("CDONTS.NewMail")
	
	objNewMail.To = "jjlibby@uwm.edu"
	objNewMail.Subject = "test server"
	objNewMail.From = "GummLANParty.net<jgumm@wi.rr.com>"
	objNewMail.Body = "wang test"
	objNewMail.send
%>

Mail sent