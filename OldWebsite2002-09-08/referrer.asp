<%
dim myconn,sql,rs,bs
Set MyConn = Server.CreateObject("ADODB.Connection")
MyConn.Open "DSN=Main"
response.write request.querystring("referrer")

'myconn.execute("insert into referrer(referrer) values('" & request.querystring("referrer") & "');"

'response.redirect(request.querystring("src"))

%>