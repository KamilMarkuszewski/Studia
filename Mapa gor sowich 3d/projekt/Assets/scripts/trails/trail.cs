using UnityEngine;
using System.Collections;

public class trail {
	ArrayList points;
	public Color col;
	
	public Material mat;

	
	public trail(){
		points = new ArrayList ();
		col = Color.white;		
	}
	
	
	
	// podac tylko to co po przecinku w formie 6 cyfrowej np z 50.59204 podac 592040
	public void addP(int x, int y){
		Vector2 map = coordinatesCalc.coordinatesToMapXZ(x, y);
		float wys1 = (GameObject.Find("TerrainA").GetComponent(typeof(Terrain)) as Terrain).SampleHeight(new Vector3(map.x, 5000.0f , map.y));
		float wys2 = (GameObject.Find("TerrainB").GetComponent(typeof(Terrain)) as Terrain).SampleHeight(new Vector3(map.x, 5000.0f , map.y));
		float wys3 = (GameObject.Find("TerrainC").GetComponent(typeof(Terrain)) as Terrain).SampleHeight(new Vector3(map.x, 5000.0f , map.y));
		float wys4 = (GameObject.Find("TerrainD").GetComponent(typeof(Terrain)) as Terrain).SampleHeight(new Vector3(map.x, 5000.0f , map.y));
		
		/*
		wys1 -= (GameObject.Find("TerrainA").transform.position.y);
		wys2 -= (GameObject.Find("TerrainB").transform.position.y);
		wys3 -= (GameObject.Find("TerrainC").transform.position.y);
		wys4 -= (GameObject.Find("TerrainD").transform.position.y);
		
		wys1 -= 150.0f;
		wys2 -= 150.0f;
		wys3 -= 150.0f;
		wys4 -= 150.0f;
		*/
		float wys = 0.0f;
		if(wys1 > wys) wys = wys1;
		if(wys2 > wys) wys = wys2;
		if(wys3 > wys) wys = wys3;
		if(wys4 > wys) wys = wys4;

		
		if(wys>0)points.Add(new Vector3(map.x, wys , map.y));
	}
	
	public void draw(){
		
	    mat.SetPass(0);
		
		Vector3 last = Vector3.zero;
		foreach(Vector3 p in points){
			GL.Begin( GL.LINES);
			GL.Color( col );
			if(last.y != 0.0f){
				GL.Vertex3( last.x, last.y, last.z );
			}
			
			GL.Vertex3( p.x, p.y, p.z );
			last = p;
			GL.End();
		}
		
	}

}
