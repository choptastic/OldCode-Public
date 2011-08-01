<?	$title = "RSVP for LAN";
	$pagedesc = "Here you can sign up for the next LAN Party";
	require("codeheader.php");
	
	if($_POST['submit'])
	{
		extract($_POST);
		require("lanfunctions.php");
		$lan = next_lan();
		
		$sql="Insert into rsvp(lanpartyid, alias, fullname, email, location, computers) values(%s,'%s','%s','%s','%s',%s)";
		$sql=sprintf($sql,$lan['lanpartyid'],$alias,$fullname,$email, $location, $computers);
		mysql_query($sql);
		$title = "Thank you for RSVPing";
		$pagedesc = "You rule.";
		require_once("layoutheader.php");
	}
	else
	{
	require_once("layoutheader.php");
	$lan = next_lan();
?>
	<form action="<? echo $SCRIPT_NAME ?>" method="POST">
	<table>
		<tr>
			<td>Alias: </td>
			<td><input type="text" value="" name="alias"></td>
		</tr>
		<tr>
			<td>Your Real Name: </td>
			<td><input type="text" value="" name="fullname"></td>
		</tr>
		<tr>
			<td>Email Address: </td>
			<td><input type="text" value="" name="email"></td>
		</tr>
		<tr>
			<td>Location: </td>
			<td><input type="text" value="" name="location"></td>
		</tr>
		<tr>
			<td>Number of Computers you're bringing: </td>
			<td>
				<select name="computers">
					<option value=0>0</option>
					<option value=1 selected>1</option>
					<option value=2>2</option>
					<option value=3>3</option>
					<option value=4>4</option>
				</select>
			</td>
		</tr>
	</table>
	<center>
		
		<input name="submit" type="submit" value="Submit" class=button>
	</center>
	</form>
<?	}	?>
	<?	require("footer.php"); ?>		