<? 	$title = "Statistics";
	$pagedesc = "I collect Computer info at each LAN and it gets collaborated here.";
	require("header.php");

function fdate($d)
{
	return date("n/j/Y",$d);
}

$ops = array("Sum","Avg","Max");
for($i=0;$i<sizeof($ops);$i++)
{	
	$op = $ops[$i];	?>
	<table align=center class=list cellpadding=2 cellspacing=0 width="50%">
		<tr class=MenuCat>
			<td colspan=5 align=center>Computer Statistics : <? echo $op; ?></td>
		</tr>
		<tr class=MenuCat align=center>
			<td align=left nowrap>LAN Party(# Comps)</td>
			<td>CPU (MHz)</td>
			<td>RAM (MBs)</td>
			<td>Disk Space (GBs)</td>
			<td>Video (MBs)</td>
		</tr>
	<?	$sql = "select lanparty, count(computerid) as comps, %s(cpu) as c, %s(mem) as m, %s(hd) as h, %s(vid) as v from lanparty inner join computer on computer.lanpartyid=lanparty.lanpartyid group by lanparty order by landate;";
		$sql = sprintf($sql,$op,$op,$op,$op);
		$arst = mysql_query($sql);
		$arows = mysql_num_rows($arst);
		for($j=0;$j<$arows;$j++)
		{
			$arow = mysql_fetch_array($arst);	?>
		 	<tr class="<? echo next_list_class(); ?>" align=center>
		 		<td width="40%" align=left>
		 			<? echo $arow['lanparty'];	?>(<? echo $arow['comps']; ?>)
		 		</td>
		 		<td width="15%">
		 			<? echo intval($arow['c']);	?>
		 		</td>
				<td width="15%">
		 			<? echo intval($arow['m']);	?>
		 		</td>
				<td width="15%">
		 			<? echo intval($arow['h']);	?>
		 		</td>
				<td width="15%">
		 			<? echo intval($arow['v']);	?>
		 		</td>
		 	</tr>
	<?	}	?>
	</table><hr>	<?
}	?>
</table>

<? require("footer.php"); ?>