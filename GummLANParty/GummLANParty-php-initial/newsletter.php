<? 	require("codeheader.php");
	
function fdate($d)
{
	return date("n/j/Y",$d);
}

$rst=mysql_query("select * from newsletter where newsletterid=".$_GET['newsletterid']);
$row=mysql_fetch_array($rst);
extract($row);

$title = $newsletter;
$pagedesc = fdate(strtotime($day));

require("layoutheader.php");

?>
<table align=center class=newsletter cellpadding=5 width="90%">
	<tr>
	 	<td>
	 		<? echo nl2br($txt); ?>
	 	</td>
	 </tr>
</table>

<? require("footer.php"); ?>