<html>
<head>
<title>-= MORSE CODE WRITER=- </title>

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


<table align="center" border="0">
<tr>
<td>
<b> Morse Code Writer</b><br>
Enter your text here (64 char limit): 

<form name="form1"  method = "post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
<input type = "text" name="CMD" style="width:250px" value="" maxlength="64">
<input type ="submit" name="submit" value="execute">
</form>
</td>
</tr>
<tr>
<td> <?php

	if ($CMD!=""){

	if (!preg_match("/^[a-z A-z]*$/",$CMD)){
		echo "<br> Sorry, only letters and white space allowed.<br>";
	} else {
	echo "<pre> WORKING...<br>";
	$a=popen("/home/pi/morse/morseScript.sh '".$CMD."'","r");
	while ($b=fgets($a,32)){
		echo $b;
		ob_flush();flush();
		}
	pclose($a);
	echo "<br>";
	echo "</pre>\n";
	}
	}
	?>
</td>
</tr>
</table>



</body>
</html>
