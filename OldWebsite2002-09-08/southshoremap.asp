<!-- #include file="header.asp" -->
<center>
        <p>&nbsp;</p>
        </center>
	  <font size=4><b>
	  <%
	  	dim curd
		curd=0
	  	sql="Select * from SouthShoreMap order by picdate desc"
		set rst=myconn.execute(sql)
		while not rst.eof
			if rst("picdate") >< curd then
				curd=rst("picdate")
				response.write("<hr><center>" & curd & "<br><i><font size=3>" & rst("picdesc") & "</font></i></center>")
				'response.write("<hr>")
			end if
			response.write("<a href='southshoremappics\" & rst("pic") & "'><img border=0 src='southshoremappics\s_" & rst("pic") & "'></a> ")
			rst.movenext
		wend
		%>
		</b></font>
		
<!-- #include file="footer.asp" -->

