<? 	$title = "Awards";
	$pagedesc = "These awards get awarded at each LAN Party";
	require("header.php");

function fdate($d)
{
	return date("n/j/Y",$d);
}

$rst=mysql_query("Select * from lanparty where landate<'".date("Y-m-d",time())."' order by landate;");
$rows=mysql_num_rows($rst);
for($i=0;$i<$rows;$i++)
{	
	$row=mysql_fetch_array($rst);	?>
	<table align=center class=list cellpadding=2 cellspacing=0 width="90%">
		<tr class=MenuCat>
			<td colspan=3 align=center><? echo $row['lanparty']; ?></td>
		</tr>
		<tr class=MenuCat>
			<td>Award</td>
			<td>Who</td>
			<td>Why</td>
		</tr>
	<?	$sql = "select * from award where lanpartyid=".$row['lanpartyid'];
		$arst = mysql_query($sql);
		$arows = mysql_num_rows($arst);
		for($j=0;$j<$arows;$j++)
		{
			$arow = mysql_fetch_array($arst);	?>
		 	<tr class="<? echo next_list_class(); ?>">
		 		<td width="15%">
		 			<? echo $arow['award'];	?>
		 		</td>
		 		<td width="20%">
		 			<? echo $arow['who']; ?>
		 		</td>
				<td width="65%">
					<? echo $arow['why']; ?>
				</td>
		 	</tr>
	<?	}	?>
	</table><hr>	<?
}	?>
</table>

<? require("footer.php"); ?>