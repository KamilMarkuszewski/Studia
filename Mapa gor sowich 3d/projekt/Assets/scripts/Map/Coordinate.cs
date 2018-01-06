using UnityEngine;
using System.Collections;

public class Coordinate {
	
	public static int xZero = 488351;
	public static int yZero = 674678;	
	
	
	public static double xRate = 12.40;
	public static double yRate = 7.18;	
	
	private int xDegree = 0;
	private int xLong = 0;
	
	private int yDegree = 0;
	private int yLong = 0;
	
	public Coordinate(int xD, int yD){
		xDegree = 16;
		yDegree = 50;
		xLong = xD;
		yLong = yD;
	}

	public Coordinate(int xD, int xM, int yD, int yM){
		xDegree = xD;
		yDegree = yD;
		xLong = xM;
		yLong = yM;
	}
	
	public string toString(){
		return xDegree + "*" + xLong + " : " + yDegree + "*" + yLong ;
	}

}
