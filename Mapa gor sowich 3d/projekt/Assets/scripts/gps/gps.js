var gpsPos : LocationInfo;
var maxWait : int = 20;
var check_t :float = 0.0f;

function Start() {
	

	// Start service before querying location
	iPhoneSettings.StartLocationServiceUpdates();
	
	// Wait until service initializes
	
	while (iPhoneSettings.locationServiceStatus ==	LocationServiceStatus.Initializing && maxWait > 0) {
		yield WaitForSeconds(2);
		maxWait--;
	}
	
	// Service didn’t initialize in 20 seconds
	if (maxWait < 1) {
		maxWait = 150;
		return;
	}
	
	// User denied access to device location
	if (iPhoneSettings.locationServiceStatus == LocationServiceStatus.Failed) {
		maxWait = 250;
		return;
	}
	// Access granted and location value could be retrieved
	else {
		maxWait = 350;
	
	}
	
	// Initialize our empty LocationInfo object
	gpsPos = new LocationInfo();
}

function Update() {
	
	// Update the LocationInfo object with the last information we got from the Location Service
	if(check_t + 30.0f > Time.time){
		gpsPos = iPhoneInput.lastLocation;
		GameObject.Find("gps").SendMessage("setloc", gpsPos);
	}
	check_t = Time.time;
}

