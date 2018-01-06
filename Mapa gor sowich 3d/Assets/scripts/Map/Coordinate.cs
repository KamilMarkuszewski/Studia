using UnityEngine;
using System.Collections;

public class Coordinate {
	
	private int xDegree = 0;
	private int xMin = 0;
	
	private int yDegree = 0;
	private int yMin = 0;
	
	public Coordinate(int xD, int yD){
		xDegree = xD;
		yDegree = yD;
	}

	public Coordinate(int xD, int xM, int yD, int yM){
		xDegree = xD;
		yDegree = yD;
		xMin = xM;
		yMin = yM;
	}
	
	public string toString(){
		return xDegree + "*" + xMin + "'" + " : " + yDegree + "*" + yMin + "'";
	}

}
