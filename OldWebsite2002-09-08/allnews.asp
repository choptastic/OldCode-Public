<!-- #include file="header.asp" -->
      <!-- #include file="functions.asp" -->
      <p align="center"><font size="5"></font> 
        <%
Dim a, i,rsu
count = 0

sql="Select * from updates order by updatedate;"
set rsu= myconn.execute(sql)
while not(rsu.eof)
%>
      </p>
      <table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
        <tr> 
          <td bgcolor="#CC6600"> 
            <div align="left"><font face="Arial, Helvetica, sans-serif" size="3" color="#000000"><%= rsu("updatedate")%> 
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
      <br>
      <%
	rsu.movenext
wend
%>
      <!-- #include file="footer.asp" -->