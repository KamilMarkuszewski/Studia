using UnityEngine;
using System.Collections;

public class drawGUI : MonoBehaviour {
	gpsManager man;
	// Use this for initialization
	
	void Awake(){
		coordinatesCalc.Init();
	}
	
	
	void Start () {
		moving.moveUp();
		options.tr_camera = GameObject.Find("Main Camera").transform;
		options.poiObj = GameObject.Find("poi");
		man = GameObject.Find("gps").GetComponent(typeof(gpsManager)) as gpsManager;
	}
	

	
	
	// Update is called once per frame
	void OnGUI () {
		
	    if (GUI.Button (new Rect (10,10,25,25), "+")){
			moving.moveDown();
		}
	    if (GUI.Button (new Rect (10,45,25,25), "-")){
			moving.moveUp();
		}
	    if (GUI.Button (new Rect (10, Screen.height - 10 - 25,50,25), PL.options)){
			options.optOn = !options.optOn;
			options.closeWindows();
		}
		

		
		if(options.coorOn){
			if(options.gpsManOn)GUI.Label(new Rect( 10, Screen.height - 50 - 100, 170, 50), PL.gps + ": \n" + man.loc.longitude.ToString() +  " : " + man.loc.latitude.ToString());
			GUI.Label(new Rect( 10, Screen.height - 30 - 75, 125, 25), PL.coor + ": " );
			GUI.Label(new Rect( 10, Screen.height - 30 - 60, 170, 50), coordinatesCalc.PointCoordinates().toString());
			GUI.Label(new Rect( 10, Screen.height - 20 - 50, 125, 25), PL.height + ": " + coordinatesCalc.PointToMeters());
		}
		

		

		if(options.optOn){
			options.drawOptions();
		}
		if(options.autOn){
			options.drawAut();
		}
		if(options.viewOn){
			options.drawView();
		}
		if(options.camOn){
			options.drawCam();
		}
		if(options.gpsOn){
			options.drawGps();
		}
		if(options.poiOn){
			options.drawPoi();
		}
		if(options.trailsOn){
			options.drawTrails();
		}
	}

	
}
