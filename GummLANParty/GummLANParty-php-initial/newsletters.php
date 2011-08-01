<? 	$title = "Newsletters";
	$pagedesc = "Some swell news worthy of sending to everyone";
	require("header.php");

function fdate($d)
{
	return date("n/j/Y",$d);
}

$rst=mysql_query("Select * from newsletter order by day desc;");
$rows=mysql_num_rows($rst);
?>
<table align=center class=list cellpadding=5 cellspacing=0>
<?
	for($i=0;$i<$rows;$i++)
	{
		$row=mysql_fetch_array($rst);
?>
	 	<tr class="<? echo next_list_class();?>">
	 		<td width="15%">
	 			<? echo fdate(strtotime($row["day"])); ?>
	 		</td>
	 		<td>
	 			<a href="newsletter.php?newsletterid=<? echo $row['newsletterid'];?>"><? echo $row["newsletter"]; ?></a>
	 		</td>
	 	</tr>
<?
	}
?>
</table>

<? require("footer.php"); ?>