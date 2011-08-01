<%
	function ReplaceChar(Str,Find,ReplaceWith)
		dim i, strs, x
		strs=split(str,find)
		if instr(1,str,find) then
			replacechar=strs(0)
			for x = 1 to ubound(strs)
				replacechar = replacechar & ReplaceWith & strs(x)
			next
		else
			ReplaceChar=Str
		end if
	end function
%>