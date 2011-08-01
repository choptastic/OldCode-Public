<? require_once("lanfunctions.php");	?>
<html><head>
<style type="text/css">
<!--
BODY 		{cursor: default;
			font-family: Arial;
			font-size: x-small;
			background: #006666;
			color: #CCFFCC;}
			
DIV.MenuCount	{color:#00FF00;}

TABLE.List	{cursor: default;
				border: inset;
				border-width: thin;}

TABLE.Menu	{cursor: default;
				width: 167;
				border: outset;
				font-weight: bold;
				border-width: thin;}
				
TABLE.ArticleMenu	{cursor: default;
				border: outset;
				border-width: thin;
				font-size: small;
				font-weight: bold;}
				
TABLE.Subject	{cursor: default;
				border: outset;
				border-width: thin;
				font-size: medium;
				font-weight: bold;
				background: #000000}

TABLE.Newsletter	{cursor: default;
				border: inset;
				font-size: small;
				border-width: thin;
				font-family: courier}
				
TABLE.About		{cursor: default;
				border: inset;
				font-size: small;
				border-width: thin;}

TR.AboutTitle	{cursor: default;
				font-size: medium;
				font-weight: bold;
				background: #009999;}

TR.AboutSubTitle{cursor: default;
				font-size: small;
				font-weight: bold;
				border-width: thin;}

TR.AboutText	{cursor: default;
				font-size: small;
				border-width: thin;}		


TR.list1	{cursor: default;
			font-size: small;
			background: #006363;}
			
TR.list2	{cursor: default;
			font-size: small;
			background: #007070;}

			
TR.MenuCat	{cursor: default;
			font-size: small;
			font-weight: bold;
			background: #009999;}
			
TR.MenuChoice	{cursor: default;
			font-size: small;
			background: #007777;}


TD.PostInfo		{cursor: default;
			font-size: small;
			background: #007777;
			width:150;}

TD.PostText		{cursor: default;
			font-size: small;
			background: #004444;}

TD.PostControls		{cursor: default;
			background: #009999;
			width:150;}
					

A:visited	{color: #DDDD00}
A:link		{color: #DDDD00}
A:active	{color: #FFFF55}
A:hover		{color: #FFFF55}

input.button {background: #005555;
			color: #DDDD00;}

//-->
</style>
<script language="Javascript1.2">
<!--
	function OpenProfileWindow(LoginID)
	{
		var settings='width=400,height=500,scrollbars=yes,location=no,directories=no,status=no,menubar=no,toolbar=no,resizable=yes';
		var filename='ShowProfile.asp?LoginID=' + LoginID;
		window.open(filename, '', settings);
	}
//-->
</script><title><? echo $title; ?></title></head>
<body text="#ccffcc" bgcolor="#006666" link="#dddd00">
<table width="100%" cellpadding="1" border="0"> 
	<tr valign="top">
        <td align="center" colspan="3">
			<table width="100%" border="0">
				<tr>
					<td width="282">
						<img src="logo.gif">
					</td>
					<td valign="top">
						<table style="border: thin outset ; background: rgb(0, 119, 119) none repeat scroll 0%; font-size: x-small; -moz-background-clip: initial; -moz-background-inline-policy: initial; -moz-background-origin: initial;" cellspacing="0" cellpadding="2" width="100%">
							<tr>
								<td align="center" bgcolor="#004444" rowspan="2" valign="center">
								<? 	$row = next_lan();	?>
									<font size="3"><b><? echo $row['lanparty'];?></b><br><? echo long_date(strtotime($row['landate'])); ?><br>5:00 PM</font><br><br>						
									<font size="2"><a href="http://www.poopinashoe.com/forum">[Go To Forum]</a></font>
								</td>
								<td valign="top">
								<?	$rsvp = rsvp_counts($row['lanpartyid']);	?>
									<font color="#00ff00"><? echo $rsvp['people'];?></font> People RSVPed for LAN<br>
									<font color="#00ff00"><? echo $rsvp['comps'];?></font> Computers RSVPed for LAN<br>
									<font color="#00ff00"><? echo mysql_op("count","contact","contactid","");?></font> People on Contact List<br>
									<!--
									<font color="#00ff00">4</font> Posts in 24 hours<br>
									<font color="#00ff00">73</font> Posts in 7 days<br>
									<font color="#00ff00">4823</font> Posts to date<br> -->
								</td>
								<td valign="top">
									<!--
									<b>Popular Threads</b><br>
        							<a href="">Thread</a><br>
        							<a href="">Thread</a><br>
        							<a href="">Thread</a><br>
									<a href="">Thread</a><br> -->
									Yeah! I know this bar is incomplete... It'll all be put up here soon....have patience.<br>
									&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
									&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
									
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td valign=top>
            <table class="Menu" cellpadding="1" cellspacing="0" width="167">
            	<tbody><tr class="MenuCat" align="center" onmouseover="this.style.background='#00AAAA'" onmouseout="this.style.background='#009999'" style="background: rgb(0, 153, 153) none repeat scroll 0%; -moz-background-clip: initial; -moz-background-inline-policy: initial; -moz-background-origin: initial;">
            		<td>Menu</td>
            	</tr>
            	<tr class="MenuChoice" align="left" onmouseover="this.style.background='#008888'" onmouseout="this.style.background='#007777'">
            		<td>
            			<li><a href="index.php">News</a></li>
            			<li><a href="about.php">History</a></li>
            			<li><a href="rsvp.php">RSVP for LAN</a></li>
            			<li><a href="newsletters.php">Newsletters</a></li>
            			<li><a href="http://www.poopinashoe.com/forum">Forum</a></li>
						<li><a href="stats.php">Statistics</a></li>
						<li><a href="awards.php">Awards</a></li>
						<li><a href="contacts.php">Contact List</a></li>
            		</td>
            	</tr>
            </table>
			<br>
            <table class="Menu" cellpadding="1" cellspacing="0" width="167">
            	<tr class="MenuCat" align="center" onmouseover="this.style.background='#00AAAA'" onmouseout="this.style.background='#009999'">
            		<td>
            			People RSVPed
            		</td>
            	</tr>
            	<tr class="MenuChoice" align="left" onmouseover="this.style.background='#008888'" onmouseout="this.style.background='#007777'">
            		<td>
					<?	$rsvp = rsvp_list($row['lanpartyid']);
						$rows = mysql_num_rows($rsvp);
						for($i=0;$i<$rows;$i++)
						{	
							$row = mysql_fetch_array($rsvp);	?>
                			<li><? echo $row['alias'];?></li>
					<?	}	?>
            		</td>
            	</tr>
            </table>
			<Br>
			<a href="http://www.poopinashoe.com"><img src="pias.jpg" border=0></a>
		</td>
		<td valign=top>
			<!--
			<center><font size="5">
				3114 Hours until the next LAN Party!
			</font></center>
			-->
			<table class="Subject" align="center" cellpadding="4" cellspacing="0" width="100%">
				<tr>
					<td align="center">
						<? echo $title; ?>
					</td>
				</tr>
				<tr bgcolor="#002222"><td align="center">
					<font size="2"><? echo $pagedesc; ?></font>
				</td></tr>			
			</table><br>
			<!-- Start Content Here -->