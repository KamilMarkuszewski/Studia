using UnityEngine;
using System.Collections;

public static class coordinatesCalc {

	static Transform myPointer;
	
	public static void  Init(){
		myPointer = GameObject.Find("pointer").GetComponent(typeof(Transform)) as Transform;
		
	}
	
	public static Coordinate PointCoordinates(){
		return mapXZToCoordinates(myPointer.position.x, myPointer.position.z);
	}
	
	
	/*
	 * TODO
	 * ma za zadanie zamieniac współrzędne terenu w app na współrzędne w stopniach
	 */
	public static Vector2 coordinatesToMapXZ(float x, float z){
		
		x = (float) ((x - Coordinate.xZero) / Coordinate.xRate);
		z = (float) ((z - Coordinate.yZero) / Coordinate.yRate);
		Vector2 p = new Vector2(x, z);
		
		return p;
	}
	
	public static Coordinate mapXZToCoordinates(float x, float z){
		x = (float)(x * Coordinate.xRate + Coordinate.xZero);
		z = (float)(z * Coordinate.yRate + Coordinate.yZero);
		

		Coordinate c = new Coordinate((int)x, (int)z);
		return c;
	}
	
	
	public static int PointToMeters(){
		return mapHeightToMeters(myPointer.position.y);
	}
	
	/*
	 * TODO
	 * ma za zadanie zamieniac wysokosc terenu w app na metry npm
	 * 
	 */
	public static int mapHeightToMeters(float h){
		h = 840.0f - h;
		
		
		return (int) ( 913 - ((h * 5.0)/10.0f));
	}
}
