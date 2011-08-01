<!-- #include file="connection.asp" -->

<%
	dim who, comment
	who = request.form("Who")
	comment = request.form("comment")
	
	if len(who)=0 or len(comment)=0 then
		response.write "Please Provide a Name And Comment"
	else
		dim rst
		set rst = Server.CreateObject("ADODB.Recordset")
		rst.activeconnection=myconn
		rst.open "Select * from Comments",,1,2,1
		rst.addnew
		rst("Who")=who
		rst("Comment")=comment
		rst.update
		response.redirect("index.asp")
	end if %>