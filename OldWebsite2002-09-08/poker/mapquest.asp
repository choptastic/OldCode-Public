<!-- #include virtual="/StringFunctions.asp" -->
<%
	function MapQuestFix(S)
		MapQuestFix=ReplaceChar(S, " " , "+")
		MapQuestFix=ReplaceChar(MapQuestFix, "," , "%2C")
	end function

	function MapQuestDirections(byval AddressStart, byval CSZStart, byval AddressTo, byval CSZTo)
		Dim URL
		AddressStart=MapQuestFix(AddressStart)
		AddressTo=MapQuestFix(AddressTo)
		CSZStart=MapQuestFix(CSZStart)
		CSZTo=MapQuestFix(CSZTo)		
		
		URL="http://maps.yahoo.com/py/ddResults.py?Pyt=Tmap&tarname=&tardesc=&osd=&newname=&newdesc=&dsd=&newHash=&newTHash=&newErr=&newTErr=&newFL=Use+Address+Below&newaddr="
		URL=URL & AddressStart & "&newcsz=" & CSZStart
		URL=URL & "&newcountry=us&newTFL=Use+Address+Below&newtaddr="
		URL=URL & AddressTo & "&newtcsz=" & CSZTo
		URL=URL & "&newtcountry=us&Submit=Get+Directions"
		MapQuestDirections=URL
	end function
	
	%>