<?
	function next_lan()
	{
		$sql = "Select * from lanparty where landate >= '".date("Y-m-d",time())."' order by landate;";
		$rst = mysql_query($sql);
		$row = mysql_fetch_array($rst);
		return $row;
	}
	
	function long_date($d)
    {
    	return date("l, F j, Y",$d);
    }
	
	function rsvp_list($lanpartyid)
	{
		$sql = sprintf("Select * from rsvp where lanpartyid=%s order by alias",$lanpartyid);
		$rst = mysql_query($sql);
		return $rst;
	}
	
	function rsvp_counts($lanpartyid)
	{
		$sql = "select count(rsvpid) as people ,sum(computers) as comps from rsvp where lanpartyid=$lanpartyid";
		$rst = mysql_query($sql);
		$row = mysql_fetch_array($rst);
		return $row;
	}
	
	function get_award_list($lanpartyid)
	{
		$sql = "select * from award where lanpartyid=$lanpartyid";
		$rst = mysql_query($sql);
	}
	
	
?>