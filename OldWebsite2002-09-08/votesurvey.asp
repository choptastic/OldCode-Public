<!-- #include file="header.asp" -->
	<%
	dim ip,d,aid
	sql="select * from surveys where now-[surveydatemonday] > 0 order by surveydatemonday;"
	set rst=myconn.execute(sql)
	qid=rst("SurveyID")
	ip=Request.ServerVariables("REMOTE_ADDR")
	d=fix(now)
	aid=request.form("survey")
	sql="Select * from Surveyresults where votedate=cdate(fix(now)) and voteip='" & ip & "';"
	set rst=myconn.execute(sql)
	if not rst.eof then
		response.write "Error: You may only vote once per day"
	elseif len(aid)>0 then
		sql="insert into SurveyResults(votedate,voteip,surveyid,answerid) values('" & d & "','" & ip & "'," & qid & "," & aid & ");"
		myconn.execute sql
		response.write "Thank you for voting"
	else
		response.write "You must specify an answer to participate in the Survey"
	end if
	%>

<!-- #include file="footer.asp" -->