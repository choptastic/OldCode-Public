<?	$title = "Contact List";
	$pagedesc = "I Send out newsletters ocasionally, and here is how you get em";
	require("codeheader.php");
	
	if($_POST['submit'])
	{
		extract($_POST);
		
		$sql="Insert into contact(contact, email, howfound) values('%s','%s','%s')";
		$sql=sprintf($sql,$contact, $email, $howfound);
		mysql_query($sql);
		$title = "Thank you for Signing up for the newsletter";
		$pagedesc = "Kickass.";
		require_once("layoutheader.php");
	}
	else
	{
	require_once("layoutheader.php");
	$count = mysql_op("count","contact","contactid","");
?>
	<form action="<? echo $SCRIPT_NAME ?>" method="POST">
	<center>Number of people currently on Contact List: <b><? echo $count; ?></b></center>
	<table>
		<tr>
			<td>Your Name: </td>
			<td><input type="text" value="" name="alias" size=50></td>
		</tr>
		<tr>
			<td>Email Address: </td>
			<td><input type="text" value="" name="email" size=50></td>
		</tr>
		<tr>
			<td>How did you find this website?</td>
			<td><textarea name="howfound" cols=50 rows=4></textarea></td>
		</tr>
	</table>
	<center>
		<input name="submit" type="submit" value="Submit" class=button
	</center>
	</form>
<?	}	?>
	<?	require("footer.php"); ?>		