<?php
	include 'class.php';
	$user_obj=array();
	$ride_obj=array();
	$lock_obj=array();
	
	$user1=new User("246.104.222.116.52","2016ME106892105",100,9547621425,"abc@gmail.com");
	$user2=new User("204.74.120.137.119","2017MCS2105",100,9830050366,"sh@gmail.com");
	$user3=new User("112.49.190.43.212","2017MCS2082",100,9830050366,"sh@gmail.com");
	
	
	$lock1=new Lock(1,863158022988725,0,88.38,25.36,0,98,0,1);
	$lock2=new Lock(2,863725031194523,1,89.45,36.36,0,45,0,1);
	
	$dock1=new Docks(1,10,98.53,40.36);
	
	$ride1=new Ride("246.104.222.116.62",1,1,0,1);
	$ride2=new Ride("204.74.120.137.119",2,1,0,1);
	
	
	$user_obj[0]=$user1;
	$user_obj[1]=$user2;
	#$user_obj[2]=$user3;
	$ride_obj1[0]=$ride1;
	$ride_obj1[1]=$ride2;
	$lock_obj[0]=$lock1;
	$lock_obj[1]=$lock2;
	$dock_obj[0]=$dock1;
	
	
	
		
	///Parser
	define("LOCK_HEADER","CMDR");
	define("SERVER_HEADER","CMDS");
	define("Reserve data",0);
	
	
	
	
	//If SIGN Up
	if(isset($_GET["signup"]))
	{
		$id=$_GET["rfidsignup"];
		$entry=$_GET["usernamesignup"];
		$bal=100;
		$pass=$_GET["passwordsignup"];
		$em_id=$_GET["emailsignup"];
		$new_user=new User($id,$entry,$bal,$em_id);
		array_push($user_obj,$new_user);
		header("Location:../index.php");
		
	}
	
	//if LOGIN
	if(isset($_GET["login"]))
	{
		$entry=$_GET["username"];
		$crypt_password=$_GET["password"];
		foreach($user_obj as $u_o)
		{
			if($u_o->entry_no==$entry && $crypt_password==$u_o->password)
			{
				echo "Hi".$entry;
				echo "Your Balance:".$u_o->balance;
			}
		}
	}
	//$param_array=array("header","device_code","IMEI","time","cmd","uid","time","ride_time","end");
	//cmd_string=$_SERVER['QUERY_STRING'];		//if through get
	
	if(isset($_GET["command"]))
	{
	$cmd_string=$_GET["command"];
	$cmd_array=explode(',',$cmd_string);
	$len_data=count($cmd_array);
	
	
	//Stores the first 5 data -STX,CODE,IMEI,TIME,CMD
	$data=array();
	$response_arr=array();
	for($i=0;$i<5;$i++)
	{
	    $data[$i]=$cmd_array[$i];
	}
	
	//When user shows RFID first time R0
	if($data[4]=="R0")
	{
		//get the rest of data
	    for($i=5;$i<8;$i++)
	    $data[$i]=$cmd_array[$i];
		$uid=$data[6];		//get the user id of the lock
		foreach($user_obj as $u_o){
			//check credentials of this user
			//echo "user id=".$u_o->user_id;
			if($u_o->balance>0 && $uid==$u_o->user_id){
			
			//send command to unlock
			$j=0;
			$response_arr[$j++]=constant("SERVER_HEADER");
			$response_arr[$j++]=$data[1];       //copy device type
			$response_arr[$j++]=$data[2];       //copy imei number of device
			$response_arr[$j++]=date("Ymd").date("his");
			$response_arr[$j++]="L0";		//command code
			$response_arr[$j++]= 0 ;     		//Unlock
			$response_arr[$j++]= $u_o->user_id;     		
			$response_arr[$j++]= $data[7];		//TS    		
			$response_string="";
			foreach($response_arr as $r)
			$response_string.=$r.",";
			
			
			$response_string.="#<LF>";
			echo "Server's response:".$response_string;
					
			}
			
		}
	}
	
	//command is unlock
	else if($data[4]=="L0")
	{
		//get the rest 	of data
		$uid=$data[6];		//get the user id of the lock
	    for($i=5;$i<8;$i++)
	    $data[$i]=$cmd_array[$i];
		foreach($lock_obj as $l_o){	
		if($l_o->imei==$data[2])
		{
			if($l_o->ride==0)	//check if this is the unlock signal sent for the first time the user starts riding
			{
				$ride3=new Ride($uid,$l_o->id,$l_o->d_id,time(),1);
				array_push($ride_obj1,$ride3);
				$l_o->ride=1;
				$l_o->status=0;
				foreach($dock_obj as $d)
				{
					if($d->id==$l_o->d_id)
						$d->no_of_cycle-=1;		//reduce the no of cycle in this dock by 1
				}
			}
			else
			{	
				$l_o->status=0;
				
			}
			//prepare server response
	    $j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$data[1];       //copy device type
	    $response_arr[$j++]=$data[2];       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="Re";
	    $response_arr[$j++]="L0" ;       //command code
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		
		
		$response_string.="#<LF>";
		echo "Server's response to L0 command:".$response_string;
		}
	
		}
	}
	
	//if the command is lock
	if($data[4]=="L1")
	{
	    
	    //get the rest of data
	    for($i=5;$i<8;$i++)
	    $data[$i]=$cmd_array[$i];
	    
	    //DO SOMETHING
		$uid=$data[5];		//get the user id of the lock
		foreach($lock_obj as $l_o){	
		if($l_o->imei==$data[2])
		{
			//get the corresponding ride object
			foreach($ride_obj1 as $r_o)
			{
			if($r_o->user_id==$uid && $r_o->lock_id==$l_o->id)
				$ride_obj=$r_o;
			}
			if($l_o->ride==1 && $ride_obj->$riding_status==1)			//when ending the ride
			{	
				$ride_obj->duration=time()-$ride_obj->start_time;
				$charges=$ride_obj->duration*5;
				$l_o->ride=0;
				$l_o->status=1;
				$uid->balance-=$charges;
				unset($ride_obj);		//destroy the object after ride is over
				
			}
			
			//if halts
		else if($l_o->ride==1 && $ride_obj->$riding_status==0)
			{	
				
				
			}
			
			
		//prepare server response
	    $j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$data[1];       //copy device type
	    $response_arr[$j++]=$data[2];       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="Re";
	    $response_arr[$j++]="L1" ;       //command code
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		
		$response_string.="#<LF>";
		echo "Server's response:".$response_string;
		}
		break;
	    }
	    
	    
	}
	
	
	//Heartbeat command
	else if($data[4]=="H0")
	{
		//get the rest of data
	    for($i=5;$i<8;$i++)
	    $data[$i]=$cmd_array[$i];
		foreach($lock_obj as $l_o)
		{
			if($l_o->imei==$data[2])
			{
				$l_o->status=$data[5];
				$l_o->battery_level=$data[6];
			}
		}
	
	}
	
	//Gps info
	else if($data[4]=="D0")
	{
		//get the rest of data
	    
	    $data[5]=$cmd_array[5];		//reserve data
	    $data[6]=$cmd_array[6];		//UTC time from gps
	    $data[7]=$cmd_array[7];		//lat
	    $data[8]=$cmd_array[8];		//lng
		foreach($lock_obj as $l_o)
		{
			if($l_o->imei==$data[2])
			{
				$l_o->latitude=$data[7];
				$l_o->longitude=$data[8];	
			}
		}
		//prepare server response
	    $j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$data[1];       //copy device type
	    $response_arr[$j++]=$data[2];       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="Re";
	    $response_arr[$j++]="D0" ;       //command code
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		$response_string.="#<LF>";
		echo "Server's response to D0 command:".$response_string;
	
	}
	
	
	///SIGN IN COMMAND
	else if($data[4]=="Q0")
	{
		//get the rest of data
		$data[5]=$cmd_array[5];		//battery
	    
		//create a new lock object
		$new_lock=new Lock(3,$data[2],0,12346.5,215456.545,0,$data[5],0,1);
		array_push($lock_obj,$new_lock);
	
	}
	
	////reply of lock status to server
	else if($data[4]=="S5")
	{
		//get the rest of data
	    for($i=5;$i<10;$i++)
	    $data[$i]=$cmd_array[$i];
		foreach($lock_obj as $l_o)
		{
			if($l_o->imei==$data[2])
			{
				$l_o->battery_level=$data[5];
				$l_o->status=$data[8];
				
				//prepare server response
	    $j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$data[1];       //copy device type
	    $response_arr[$j++]=$data[2];       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="Re";
	    $response_arr[$j++]="S5" ;       //command code
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		
		$response_string.="#<LF>";
		echo "Server's response:".$response_string;
			}
		}
	
	}
	
	//Halt
	else if($data[4]=="L2")
	{
		//get the rest of data
	    for($i=5;$i<7;$i++)
	    $data[$i]=$cmd_array[$i];
		foreach($lock_obj as $l_o)
		{
			if($l_o->imei==$data[2])
			{
				
				//get the corresponding ride object
			foreach($ride_obj as $r_o)
			{
			if($r_o->user_id==$data[5] && $r_o->lock_id==$l_o->id)
				$r_o->riding_status=0;
			}
				
				//prepare server response
	    $j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$data[1];       //copy device type
	    $response_arr[$j++]=$data[2];       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="Re";
	    $response_arr[$j++]="L2" ;       //command code
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		
		$response_string.="#<LF>";
		echo "Server's response:".$response_string;
		break;
			}
			
		}
	
	}
	
	
	}
	
	/*
	//Get the gps data of all the locks currently on ride
	while(True){
		$flag=0;
	foreach($lock_obj as $l)
	{
		if($l->ride==1)
		{
			$flag=1;
			
			$j=0;
	    $request_gps_arr[$j++]=constant("SERVER_HEADER");
	    $request_gps_arr[$j++]=$l->device_code;       //copy device type
	    $request_gps_arr[$j++]=$l->imei;       //copy imei number of device
	    $request_gps_arr[$j++]=date("Ymd").date("his");
	    $request_gps_arr[$j++]="D0";
		
		$request_gps_string="";
		foreach($request_gps_arr as $r)
		$request_gps_string.=$r.",";
		
		$request_gps_string.=$request_gps_string."#<LF>";
		echo "Server's  D0 command:".$response_string;
		}
	}
	if($flag==0)	//no lock currently on ride
	break;
	
	////get the lock status of all locks
	foreach($lock_obj as $l)
	{
		$j=0;
	    $response_arr[$j++]=constant("SERVER_HEADER");
	    $response_arr[$j++]=$l->device_code;       //copy device type
	    $response_arr[$j++]=$l->imei;       //copy imei number of device
	    $response_arr[$j++]=date("Ymd").date("his");
	    $response_arr[$j++]="S5";
		
		$response_string="";
		foreach($response_arr as $r)
		$response_string.=$r.",";
		
		$response_string.=$response_string."#<LF>";
		
		echo "Server's  S5 command:".$response_string;
	}
	sleep(10);
	}*/
	
	
?>

<!DOCTYPE html>
<html>
<head>
	<title>Smart Bicycle App</title>
	<link rel="stylesheet" type="text/css" href="mypage.css">
</head>
<body>
<div class="contain">
<div class="hi"><p>Hi  <?php echo $_GET["username"];?></p></div>
<div class="balance"><p class="bal">Your Balance is 100 Rs.</p></div>
	
</div>
<!--
<form action="server.php" method="GET">
<input type="text" name="command">
</form>
-->
</body>

</html>		