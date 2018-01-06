using UnityEngine;
using System.Collections;

public static class coordinatesCalc {

	
	
	/*
	 * TODO
	 * ma za zadanie zamieniac współrzędne terenu w app na współrzędne w stopniach npm
	 */
	public static Coordinate mapXZToCoordinates(float x, float z){
		
		
		
		Coordinate c = new Coordinate((int)x, (int)z);
		return c;
	}
	
	/*
	 * TODO
	 * ma za zadanie zamieniac wysokosc terenu w app na metry npm
	 * 
	 */
	public static int mapHeightToMeters(float h){
		
		
		
		return (int)h;
	}
}
