<script>

if (!document.layers&&!document.all&&!document.getElementById)
	event="test"

function showtip(current,e,text)
{
	if (document.all || document.getElementById)
	{
			thetitle=text.split('<br>')
		if (thetitle.length>1)
		{
			thetitles=''
			for (i=0;i<thetitle.length;i++)
				thetitles+=thetitle[i]
			current.title=thetitles
		}
		else
			current.title=text
	}

	else if (document.layers)
	{
		document.tooltip.document.write('<layer bgColor="white" style="border:1px solid black;font-size:12px;">'+text+'</layer>')
		document.tooltip.document.close()
		document.tooltip.left=e.pageX+5
		document.tooltip.top=e.pageY+5
		document.tooltip.visibility="show"
	}
}

function hidetip()
{
	if (document.layers)
		document.tooltip.visibility="hidden"
}

</script>
<div id="tooltip" style="position:absolute;visibility:hidden"></div>


<script>

var ns6=document.getElementById&&!document.all
var ie=document.all

function showtext(text, whichdiv)
{
	if (ie) eval("document.all."+whichdiv).innerHTML=text
	else if (ns6) document.getElementById(whichdiv).innerHTML=text
}

function reset(whichdiv)
{
	if (ie) eval("document.all."+whichdiv).innerHTML=' '
	else if (ns6) document.getElementById(whichdiv).innerHTML=' '
}


function showhide(what)
{
	if (what.style.display=='none')
	{
		what.style.display='';
	}
	else
	{
		what.style.display='none'
	}
}


</script>

<!-- show_text(index# of linktext[] to show, ID of div to write to) -->