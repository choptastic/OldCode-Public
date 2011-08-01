<?	require("header.php");
$rst=mysql_query("Select * from lannews order by day desc;");
$rows=mysql_num_rows($rst);
?>
<center><A href="admin.php">Back to Administration Menu</a></center>
<br>
<center><a href='editnews.php?newsid=0'>Make new News</a><br>
<?
	for($i=0;$i<$rows;$i++)
	{
		$row=mysql_fetch_array($rst);
		printf("<a href='editnews.php?newsid=%s'>%s : %s</a><br>",$row["newsid"],$row["day"],$row["subject"]);
	} ?>
	</center>
<?	require("footer.php");?>