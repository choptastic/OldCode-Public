<?	require("codeheader.php");
	if($_POST['submit'])
	{
		extract($_POST);
		$day=date("Y-m-d",strtotime($day));
		if($newsid==0)
		{
			$sql="Insert into lannews(subject, day, news) values('%s','%s','%s')";
			$sql=sprintf($sql,$subject,$day,$news);
		}
		else
		{
			$sql="update lannews set subject='%s', day='%s', news='%s' where newsid=%s";
			$sql=sprintf($sql,$subject,$day,$news,$newsid);
		}
		mysql_query($sql);
		header("Location:adminnews.php");
	}
	else
	{
		$sql = sprintf("Select * from lannews where newsid=%s",$_GET['newsid']);
		$rst = mysql_query($sql);
		$rows = mysql_num_rows($rst);
		if($rows)
		{
			$row=mysql_fetch_array($rst);
			extract($row);
		}
	}
	require("layoutheader.php");
	if(strlen($day)==0)
		$day=date("m/d/Y",time());
	else	
		$day=date("m/d/Y",strtotime($day));
?>
	<form action="<? echo $SCRIPT_NAME ?>" method="POST">
	<Table align=center>
		<tr>
			<input type="hidden" name="newsid" value="<? echo $newsid;?>">
			<Td>Subject</td>
			<td><input type="text" name="subject" size=40 value="<? echo stripslashes($subject);?>"></td>
		</tr>
		<tr>
			<Td>Date</td>
			<Td><input type="text" name="day" value="<? echo stripslashes($day); ?>"></td>
		</tr>
		<tr>
			<td>News</td>
			<td><textarea name="news" rows="7" cols="40"><? echo stripslashes($news); ?></textarea></td>
		</tr>
	</table>
	<center>
		<input name="cancel" value="Cancel" type="button" onClick="javascript:document.location.href='adminnews.php'">
		<input name="submit" type="submit" value="Submit">
	</center>
	</form>
	<?	require("footer.php"); ?>		