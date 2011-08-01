<!-- #include file="header.asp" -->
      <div align="center">
<% 	
	
	dim rsP,RSc
	SQL = "SELECT * FROM [qryComputers] order by ComputerID;"
	Set RSc = MyConn.Execute(SQL)
	while not rsc.eof
%>
	<%if Session("Palm")=true then response.write("<hr>") %>
  <table bgcolor="#990000" bordercolor="#FFFF00" width="425" border="1">
    <tr> 
      <td> 
        <center>
          <font size="5" color="#FFFF00"><b><%= rsc("ComputerName") %></b></font> 
        </center>
        
      </td>
    </tr>
    <%
		sql="select * From qryParts where ComputerID=" & rsc("computerid")
		set RSp = MyConn.Execute (SQL)
		rsp.movefirst
		'if rsp.recordcount > 0 then
%>
    <tr> 
      <td> 
        <table bgcolor="#FFFFFF" width="100%">
          <%
			while not rsp.eof
%>
          <tr> 
            <td width="133"><font size="+1" color="#990000"><%= rsp("PartTypeName") %>: </font></td>
            <td width="270"><font size="+1" color="#990000"><%= rsp("PartName") %></font></td>
          </tr>
	
          <%
				rsp.movenext
			wend
%>
        </table>
      </td>
    </tr>
    <tr> 
      <td> 
        <center>
          <b><font size="+1" color="#FFFF00">Price: $<%= cint(rsc("price")*1.11)%></font> 
          </b>
        </center>
		</td>
    </tr>
    <font size="+1"></font>
  </table>
  <%
		rsc.movenext
	wend
%>
</div>
<!-- #include file="footer.asp" -->
