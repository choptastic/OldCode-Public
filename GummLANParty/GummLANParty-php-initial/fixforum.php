<?php
	require("codeheader.php");
	require("forum/includes/bbcode.php");
	$sql = "select * from phpbb_posts_text;";
	$rst = mysql_query($sql);
	$rows = mysql_num_rows($rst);
	for($i=0;$i<$rows;$i++)
	{
		$row = mysql_fetch_array($rst);
		$uid = make_bbcode_uid();
		$post_id = $row['post_id'];
		$text = $row['post_text'];
		$text = bbencode_first_pass($text, $uid);
		mysql_query("update phpbb_posts_text set post_text='".addslashes($text)."', bbcode_uid='$uid' where post_id=$post_id;");		
	}
?>
Done.