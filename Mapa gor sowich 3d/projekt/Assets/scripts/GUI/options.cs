
using UnityEngine;
using System.Collections;


public static class options
{
	public static Transform tr_camera;
	public static bool optOn = false;
	public static bool isD;

	public static bool viewOn = false;
	public static bool camOn = false;
	public static bool autOn = false;
	public static bool gpsOn = false;
	public static bool poiOn = false;
	public static bool trailsOn = false;
	
	public static bool trailsDrawOn = false;
	public static bool poiDrawOn = false;
	public static bool gpsManOn = false;
	public static bool gpsFollowOn = false;
	
	public static bool coorOn = true;
	public static float light = 0.4f;
	
	public static GameObject poiObj;
	

	static string opt;  

	
	public static void drawOptions(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.options);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			optOn = false;
		}
		

		if(GUI.Button (new Rect (10,35,80,25), PL.view)){
			optOn = false;
			viewOn = true;
		}

		if(GUI.Button (new Rect (10 + 100,35,80,25), PL.cam)){
			optOn = false;
			camOn = true;
		}
		
		if(GUI.Button (new Rect (10, 35 +35 ,80,25), PL.gps)){
			optOn = false;
			gpsOn = true;
		}
		
		if(GUI.Button (new Rect (10 + 100, 35 +35 ,80,25), PL.poi)){
			optOn = false;
			poiOn = true;
		}
		
		
		if(GUI.Button (new Rect (10 , 35 +35+ 35 ,80,25), PL.trails)){
			optOn = false;
			trailsOn = true;
		}
		
		if(GUI.Button (new Rect (10 + 100,35 +35 + 35 ,80,25), PL.aut)){
			optOn = false;
			autOn = true;
		}

		
		GUI.EndGroup();
	}
	
	static void ChangeLight(float addL){
		
		light += addL;
		if(light<0.1f || light > 0.6f){
			light -= addL;
		}else{
			(GameObject.Find("lightA").GetComponent(typeof(Light)) as Light).intensity = light;
			(GameObject.Find("lightB").GetComponent(typeof(Light)) as Light).intensity = light;
			(GameObject.Find("lightC").GetComponent(typeof(Light)) as Light).intensity = light;
			(GameObject.Find("lightD").GetComponent(typeof(Light)) as Light).intensity = light;
			(GameObject.Find("lightCenter").GetComponent(typeof(Light)) as Light).intensity = light;
		}

	}
	
	static public void closeWindows(){
		autOn = false;
		viewOn = false;
		gpsOn = false;
		poiOn = false;
		trailsOn = false;
		camOn = false;
	}
	
	
	
	
	public static void drawAut(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.aut);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			autOn = false;
		}

		
		GUI.Label(new Rect( 10, 35, 180, 25), PL.aut1);
		GUI.Label(new Rect( 10, 35 + 25, 180, 25), PL.aut2);
		GUI.Label(new Rect( 10, 35 + 25 + 25, 180, 25), PL.aut3);
		GUI.Label(new Rect( 10, 35 + 25 + 25 + 25, 180, 25), PL.aut4);
		GUI.Label(new Rect( 10, 35 + 25 + 25 + 25 + 25, 180, 25), PL.aut5);
		
		GUI.EndGroup();
	}
	
	public static void drawView(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.view);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			viewOn = false;
		}
		
		
		if(coorOn){
			opt = PL.off;
		}else{
			opt = PL.on;
		}
		GUI.Label(new Rect( 10, 35, 80, 25), PL.dispCoor);
		
		if(GUI.Button (new Rect (10+ 100,35,80,25), opt)){
			coorOn = !coorOn;
		}
		
		GUI.Label(new Rect( 10, 45+25, 80, 25), PL.light + " " + light);
		
		if(GUI.Button (new Rect (10+ 100,45+25,25,25), "+")){
			ChangeLight(0.1f);
		}
		
		if(GUI.Button (new Rect (10+ 100 + 25 + 10,45+25,25,25), "-")){
			ChangeLight(-0.1f);
		}

		
		GUI.EndGroup();
	}
	
	public static void drawGps(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.gps);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			gpsOn = false;
		}
		
		if(gpsManOn){
			opt = PL.off;
		}else{
			opt = PL.on;
		}
		GUI.Label(new Rect( 10, 35, 80, 25), PL.gps);
		
		if(GUI.Button (new Rect (10+ 100,35,80,25), opt)){
			gpsManOn = !gpsManOn;
		}
		
		if(gpsManOn){
			if(gpsFollowOn){
				opt = PL.off;
			}else{
				opt = PL.on;
			}
			
			GUI.Label(new Rect( 10, 35 + 35, 80, 25), PL.follow);
			
			if(GUI.Button (new Rect (10+ 100,35 + 356,80,25), opt)){
				gpsFollowOn = !gpsFollowOn;
			}
		}

		GUI.EndGroup();
	}
	
	public static void drawPoi(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.poi);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			poiOn = false;
		}
		
		if(poiDrawOn){
			opt = PL.off;
		}else{
			opt = PL.on;
		}
		GUI.Label(new Rect( 10, 35, 80, 25), PL.poi);
		
		if(GUI.Button (new Rect (10+ 100,35,80,25), opt)){
			poiDrawOn = !poiDrawOn;
		}
		
		
		if(poiDrawOn){
			poiObj.SetActiveRecursively(false);
		}else{
			poiObj.SetActiveRecursively(true);
		}

		GUI.EndGroup();
	}
	
	public static void drawTrails(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.trails);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			trailsOn = false;
		}
		
		if(trailsDrawOn){
			opt = PL.off;
		}else{
			opt = PL.on;
		}
		GUI.Label(new Rect( 10, 35, 80, 25), PL.trails);
		
		if(GUI.Button (new Rect (10+ 100,35,80,25), opt)){
			trailsDrawOn = !trailsDrawOn;
		}
		
		


		GUI.EndGroup();
	}
	
	public static void drawCam(){
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160), PL.cam);
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 80,200,160));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			camOn = false;
		}
		
		

		GUI.Label(new Rect( 10, 35, 80, 25), PL.rotX + " ");
		
		if(GUI.Button (new Rect (10+ 100,35,25,25), "+")){
			rotX(-5.0f);
		}
		
		if(GUI.Button (new Rect (10+ 100 + 25 + 10,35,25,25), "-")){
			rotX(5.0f);
		}
		/*
		GUI.Label(new Rect( 10, 45+25, 80, 25), PL.rotY +  " ");
		
		if(GUI.Button (new Rect (10+ 100,45+25,25,25), "<")){
			rotY(-5.0f);
		}
		
		if(GUI.Button (new Rect (10+ 100 + 25 + 10,45+25,25,25), ">")){
			rotY(5.0f);
		}
		
		if(GUI.Button (new Rect (10,45+25+35,80,25), PL.res)){
			tr_camera.Rotate(new Vector3(-tr_camera.rotation.x, 0.0f, 0.0f));
			GameObject.Find("Camera").transform.Rotate(new Vector3(0.0f, -GameObject.Find("Camera").transform.rotation.y, 0.0f));
			Debug.Log(tr_camera.rotation + " " + GameObject.Find("Camera").transform.rotation);
		}
		 */
		
		GUI.EndGroup();

	}
	
	static bool rotX(float dx){
		
		if(tr_camera.rotation.x > 0.6f && dx > 0){
			return false;
		}
		if(tr_camera.rotation.x < 0.2f && dx < 0){
			return false;
		}
		
		tr_camera.Rotate(new Vector3(dx, 0.0f, 0.0f));
		return true;

	}
	/*
	static bool rotY(float dy){
		
		tr_camera.RotateAround(new Vector3(0.0f, 1.0f, 0.0f), dy);
		return true;

	}
	*/
	
}


