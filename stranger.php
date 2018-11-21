<html>
<head>
<title>-=STRANGER THINGS=- </title>

<?php

$CMD="";
if ($_SERVER["REQUEST_METHOD"]=="POST"){
	$CMD=test_input($_POST["CMD"]);
	}
function test_input($data){
	$data=trim($data);
	$data=stripslashes($data);
	$data=htmlspecialchars($data);
	return $data;
	}

?>

</head>
<body>


Enter your text here (32 char limit): 

<form name="form1"  method = "post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
<input type = "text" name="CMD" style="width:150px" value="" maxlength="32">
<input type ="submit" name="submit" value="execute">
</form>

<?php

if ($CMD!=""){

	if (!preg_match("/^[a-z A-z]*$/",$CMD)){
		echo "<br> Sorry, only letters and white space allowed.<br>";
	} else {
	echo "<pre>";
//	echo $CMD;
	$a=popen("/home/pi/strange/strangeScript.sh '".$CMD."'",'r');
//	$output=str_replace("-",chr(34),$output);
//	echo $output;

	while($b=fgets($a,32)){
	echo $b;
//		ob_end_flush()
		ob_flush();
		flush();
//		ob_start();
	}
	pclose($a);

	echo "</pre>\n";

	}
}

?>

</body>
</html>
