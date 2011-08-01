<!-- #include file="header.asp" -->
      <!-- #include file="functions.asp" -->     
	  <div align="center">
        <%
Dim a, i,count,rsu
count = 0

sql="Select * from updates order by updatedate desc;"
set rsu= myconn.execute(sql)
while not(rsu.eof) and count<10
%>
      </div>
      <table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
        <tr> 
          <td bgcolor="#CC6600"> 
            <div align="left"><font face="Arial, Helvetica, sans-serif" size="3" color="#00000"><%= rsu("updatedate")%> 
              - <b><%=rsu("updatetitle")%></b></font></div>
          </td>
        </tr>
      </table>
      <table width="60%" border="0" cellspacing="0" cellpadding="0" align="center">
        <tr> 
          <td> <font face="Courier New, Courier, mono" size="2"> 
            <%=FormattedStringValue(rsu("text"))%>
            </font></td>
        </tr>
      </table>
      <div align="right"><br>
        <%
	count = count + 1
	rsu.movenext
wend
%>
        <a href="allnews.asp">See All Past Updates </a> </div>
      <!-- #include file="footer.asp" -->