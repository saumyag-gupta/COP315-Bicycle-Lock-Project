<?php
	class User{
		public $user_id;
		public $entry_no;
		public $balance;
		public $password;
		public $email_id;
		
		
		public function __construct($id,$entry_no,$balance,$email){
		$this->user_id=$id;
		$this->entry_no=$entry_no;
		$this->balance=$balance;
		$this->email_id=$email;
		//$this->password=$password;
		}
	}
	
	class Lock{
		public $id;	
		public $imei;
		public $cycle_id;	//identify the cycle associated	
		public $status;		//1-lock/0-unlock
		public $latitude;
		public $longitude;
		public static $device_code="OM";
		public $faulty;		//boolean
		public $battery_level;
		public $ride=0;		//0 if not currently on 
		public $d_id;		//docking id
		
		public function __construct($id,$im,$s,$lat,$long,$f,$batt,$r,$d){
		$this->id=$id;
		$this->imei=$im;
		$this->status=$s;
		$this->longitude=$long;
		$this->latitude=$lat;
		$this->faulty=$f;
		$this->battery_level=$batt;
		$this->ride=$r;
		$this->d_id=$d;
		}
	}
	
	class Ride{
		public $user_id;
		public $lock_id;
		public $latitude;
		public $longitude;
		public $start_point;	//pickup_point-dock-id
		public $start_time;
		public $duration;		//duration of ride
		public $riding_status;	//halt or riding or stopped 0->halt,1->riding,2->stopped
		public function __construct($uid,$lid,$start_pt,$st_tm,$rid_stat){
		$this->user_id=$uid;
		$this->lock_id=$lid;
		
		$this->start_point=$start_pt;
		$this->start_time=$st_tm;
		$this->riding_status=$rid_stat;
		}
	}
class Docks{
		public $id;	
		public $no_of_cycle;	//no of cycles in this stand
		public $latitude;
		public $longitude;
		
		public function __construct($id,$no,$lat,$long){
		$this->id=$id;
		$this->longitude=$long;
		$this->latitude=$lat;
		$this->no_of_cycle=$no;
		}
		
	}
?>
