<?
	function iff($val,$iftrue,$iffalse)
	{
		if($val)
			return($iftrue);
		else
			return($iffalse);
	}

	function parsetext($text)
	{
		$temp=$text;
		$temp=str_replace("\n","<br>",$temp);
		return $temp;
	}
	
	function checkbox($val)
	{
		if($val=="on")
			return 1;
		else
			return 0;
	}
	
	function make_pias($txt)
	{
		$redlink = "<font color='#FE0000'>";
		$greenlink = "<font color='#00FE00'>";
		$startstring = "[".strtoupper(substr($txt,0,1));
		$endstring = strtoupper(substr($txt,-1,1))."]";
		$midstring = strtolower(substr($txt,1,-1));
		echo $finalstring = $redlink.$startstring."</font>".$greenlink.$midstring."</font>".$redlink.$endstring."</font>";
	}
	
	function checked($val)
	{
		if((int)$val)
			return " checked ";
		else
			return " ";
	}
	
	$currlistclass="list1";
	function next_list_class()
	{
		global $currlistclass;
		if($currlistclass=="list1")
			return($currlistclass="list2");
		else
			return($currlistclass="list1");
	}
	
	function vertical_array($sql)
	{
		$rst = mysql_query($sql);
		$rows = mysql_num_rows($rst);
		for($i=0;$i<$rows;$i++)
		{
			$row = mysql_fetch_row($rst);
			$ret[$i] = $row[0];
		}
		return $ret;
	}
	
	function make_drop_down($name, $arrtxt, $arrvalue, $selected)
	{
		echo "<select name=$name>";
		echo "<option></option>";
		for($i=0;$i<sizeof($arrtxt);$i++)
		{
			printf("<option value=%s %s>%s</option>",$arrvalue[$i],iff($selected==$arrvalue[$i]," selected ",""),$arrtxt[$i]);
		}
		echo "</select>";
	}
	
	function make_jpeg_thumb($image, $dest, $newwidth)
	{
        $img_origem = imagecreatefromjpeg($image);
    
    	
        $width = imagesx($img_origem);
        $height = imagesy($img_origem);
    	
    	$ratio = $height/$width;
    	$height = $ratio*$newwidth;
    	$width = $newwidth;
        
        $img_destino = imagecreate($width,$height);
        imagecopyresized($img_destino,$img_origem,0,0,0,0,$width,$height,imagesx($img_origem),imagesy($img_origem));
        imagejpeg($img_destino,$dest);
	}
	
	function parse_quake_text($txt)
	{	
		$ret = str_replace("^0","<span style='color:#000000'>",$txt);
		$ret = str_replace("^1","<span style='color:#FE0000'>",$ret);
		$ret = str_replace("^2","<span style='color:#00FE00'>",$ret);
		$ret = str_replace("^3","<span style='color:#FEFE00'>",$ret);
		$ret = str_replace("^4","<span style='color:#0000FE'>",$ret);
		$ret = str_replace("^5","<span style='color:#00FEFE'>",$ret);
		$ret = str_replace("^6","<span style='color:#FE00FE'>",$ret);
		$ret = str_replace("^7","<span style='color:#FEFEFE'>",$ret);
		
		$num = substr_count($ret,"<span");
		$ret.=str_repeat("</span>",$num);
		return $ret;
	}
	
	function menu_text($txt, $href)
	{
		$redlink = "<a href='".$href."' style=\"color:#FE3919;\">";
		$greenlink = "<a href='".$href."' style=\"color:#45F100;\">";
		$startstring = "[".substr($txt,0,1);
		$endstring = substr($txt,-1,1)."]";
		$midstring = substr($txt,1,-1);
		echo $finalstring = $redlink.$startstring."</a>".$greenlink.$midstring."</a>".$redlink.$endstring."</a>";
	}
	
	
	function mysql_op($op, $table, $tosum, $where)
	{
		$sql=sprintf("select %s(%s) as tot from %s",$op,$tosum,$table);
		if(strlen($where) > 0)
			$sql.= " where " . $where;
		$rst = mysql_query($sql);
		$rows=mysql_num_rows($rst);
		if($rows==0)
			return null;
		$row = mysql_fetch_row($rst);
		return $row[0];
	}
	
	
	function mysql_get_value($table, $id, $field)
	{
		$sql = sprintf("select %s from %s where %sid=%s",$field,$table,$table,$id);
		$rst=mysql_query($sql);
		$rows=mysql_num_rows($rst);
		if($rows==0)
			return null;
		$row=mysql_fetch_row($rst);
		return $row[0];
	}
	
	function mysql_lookup($table,$retfield,$where)
	{
		$sql = sprintf("Select %s from %s where %s",$retfield,$table,$where);
		$rst = mysql_query($sql);
		$rows = mysql_num_rows($rst);
		if($rows==0)
			return 0;
		$row = mysql_fetch_row($rst);
		return $row[0];
	}
	
	
	
	function month($val)
	{
		return date("M",strtotime(sprintf("%u/1/2000",$val)));
	}
	
	function days_in_month($month, $year) 
	{
		$days = array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
		if($month != 2) 
			return $days[$month - 1];
		return (checkdate($month, 29, $year)) ? 29 : 28;
	}
	
	function day_of_week($d)
	{
		return date("l",strtotime($d));
	}
	
	function long_month($val)
	{
		return date("F",strtotime(sprintf("%u/1/2000",$val)));
	}

	mysql_connect("localhost", "gumm", "swuocnkg");
	mysql_select_db("pias");
	session_start();
?>