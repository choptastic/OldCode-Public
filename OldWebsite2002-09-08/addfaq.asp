<!-- #include file="header.asp" -->
<!-- #include file="stringfunctions.asp" -->
 
        <%
			dim q
			q=trim(request.form("Q"))
			if q = "" then
				response.write "Error: Ask a question"
			else
				q = ReplaceChar(q,"'","&#39;")
				myconn.execute("insert into Faq(Q) values('" & q & "')")
				response.write("Thank you for your question")
			end if
		%>
      <!-- #include file="footer.asp" -->