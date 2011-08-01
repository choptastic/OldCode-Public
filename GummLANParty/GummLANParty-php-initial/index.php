<? 	$title = "News";
	$pagedesc = "All the news you'll ever need (relating to the LAN Party, anyway)";
	require("header.php");

function fdate($d)
{
	return date("l, F j, Y",$d);
}

$rst=mysql_query("Select * from lannews order by day desc;");
$rows=mysql_num_rows($rst);
?>
<table width="100%" align=center class=list cellspacing=0 cellpadding=4>
<?
	for($i=0;$i<$rows;$i++)
	{
		$row=mysql_fetch_array($rst);
?>
	 	<tr class=MenuCat>
	 		<td class=newssubject>
	 			<i><? echo fdate(strtotime($row["day"])); ?></i> : <b><? echo $row["subject"]; ?></b>
	 		</td>
	 	</tr>
	 	<tr class=<? echo next_list_class();?>>
	 		<td>
	 			<blockquote>
	 				<? echo parsetext($row["news"]); ?>
	 			</blockquote>
	 		</td>
	 	</tr>
<?
	}
?>
</table>

<? require("footer.php"); ?>