<%
	sub SendMail(ToEmail,FromEmail,Subject,Body)
	
		set objNewMail = server.createObject("CDONTS.NewMail")
		
		objNewMail.To = ToEmail
		objNewMail.Subject = Subject
		objNewMail.From = FromEmail
		objNewMail.Body = Body
		objNewMail.send
	end sub
%>