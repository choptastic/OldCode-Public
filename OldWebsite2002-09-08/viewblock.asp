<!-- #include file="header.asp" -->

<!-- #include file="functions.asp" -->
<center><a href="newforum.asp">[Forum Index]</a></center>
<% dim RootThread,ReplyTo,Editing
		Session("BlockStyle")=true
		Rootthread=request.querystring("C")
		ReplyTo=request.querystring("R")
		Editing=request.querystring("E")
		DisplayBlockThread rootthread, replyto, Editing
%>
<!-- #include file="footer.asp" -->