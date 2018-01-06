using System;
using UnityEngine;
using System.Collections;


public class pointer : MonoBehaviour
{
	Transform myPointer;
	gpsManager man;
	
	void Awake(){
		myPointer = GameObject.Find("pointer").GetComponent(typeof(Transform)) as Transform;
		man = GameObject.Find("gps").GetComponent(typeof(gpsManager)) as gpsManager;
	}
	
	
	void Update(){
		
		RaycastHit hitout = findCoor();
		myPointer.position = hitout.point;
		
		if(options.gpsFollowOn){
			
			string x = man.loc.longitude.ToString().Substring(3,5);
			string z = man.loc.latitude.ToString().Substring(3,5);
			
			float xi = (float)System.Int32.Parse(x)*10;
			float zi = (float)System.Int32.Parse(z)*10;
			
			Vector2 vec = coordinatesCalc.coordinatesToMapXZ(xi, zi);
			//TO DO
		}
		
	}
	
	
	RaycastHit findCoor(){
		Vector2 v = new Vector2(Screen.width / 2.0f, Screen.height / 2.0f);
		
		RaycastHit hitout = new RaycastHit();
		
		RaycastHit hita = new RaycastHit();
		RaycastHit hitb = new RaycastHit();
		RaycastHit hitc = new RaycastHit();
		RaycastHit hitd = new RaycastHit();
		
		Camera mainCamera = Camera.main;

		TerrainCollider cola = GameObject.Find("TerrainA").GetComponent(typeof(TerrainCollider)) as TerrainCollider;
		TerrainCollider colb = GameObject.Find("TerrainB").GetComponent(typeof(TerrainCollider)) as TerrainCollider;
		TerrainCollider colc = GameObject.Find("TerrainC").GetComponent(typeof(TerrainCollider)) as TerrainCollider;
		TerrainCollider cold = GameObject.Find("TerrainD").GetComponent(typeof(TerrainCollider)) as TerrainCollider;

		cola.Raycast(mainCamera.ScreenPointToRay(v),  out hita, 10000.0f);
		colb.Raycast(mainCamera.ScreenPointToRay(v),  out hitb, 10000.0f);
		colc.Raycast(mainCamera.ScreenPointToRay(v),  out hitc, 10000.0f);
		cold.Raycast(mainCamera.ScreenPointToRay(v),  out hitd, 10000.0f);
		
		if(hitout.point.y < hita.point.y){
			hitout = hita;
		}
		
		if(hitout.point.y < hitb.point.y){
			hitout = hitb;
		}
		
		if(hitout.point.y < hitc.point.y){
			hitout = hitc;
		}
		
		if(hitout.point.y < hitd.point.y){
			hitout = hitd;
		}

		return hitout;		
	}
	
	
}


