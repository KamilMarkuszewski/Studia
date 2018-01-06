using UnityEngine;
using System.Collections;

public static class moving {
	
	// wysokośc terenu w ostatnim położeniu kamery
	private static float lastH = 0.0f;
	
	// ogólna prędkośc przesuwania
	public static float speed = 1.0f;

	
	public static void move(float x, float y, float z){
		
		float actH = getHeigh();
		
		Vector3 dir = Vector3.zero;
		float ratio = (float)(GameObject.Find("Camera").transform.position.y / 50.0f) - 1.0f;
		if(ratio < 1.0f) ratio = 1.0f;
		dir.x = x * ratio * speed;
		dir.y = y * 50.0f * speed;
		dir.z = z * ratio * speed;
		dir.y += (actH - lastH);
		lastH = actH;
		

		float posX = GameObject.Find("Camera").transform.position.x;
		float posZ = GameObject.Find("Camera").transform.position.z;

		if(posX + dir.x < 4500.0f && posX + dir.x > -4000.0f ){
			if(posZ + dir.z < 3300.0f && posZ + dir.z > -5000.0f ){
				GameObject.Find("Camera").transform.Translate (dir);
			}
		}
	
	}
	
	public static void move(double x, double y, double z){
		move((float) x, (float) y, (float) z);
	}
	
	public static void move(int x, int y, int z){
		move((float) x, (float) y, (float) z);
	}
	
	/*
	 * Podczas włączania się sceny ustawia kamerę na właściwej wysokości
	 * w zależności od wysokości terenu w tym miejscu
	 * */
		
	public static void initHeight(float h){
		lastH = h;
		Vector3 dir = Vector3.zero;
		dir.y += h;
		GameObject.Find("Camera").transform.Translate (dir * speed);
	}
	
	public static float getHeigh(){
		float ha = (GameObject.Find("TerrainA").GetComponent(typeof(Terrain)) as Terrain ).SampleHeight(GameObject.Find("Camera").transform.position);
		float hb = (GameObject.Find("TerrainB").GetComponent(typeof(Terrain)) as Terrain ).SampleHeight(GameObject.Find("Camera").transform.position);
		float hc = (GameObject.Find("TerrainC").GetComponent(typeof(Terrain)) as Terrain ).SampleHeight(GameObject.Find("Camera").transform.position);
		float hd = (GameObject.Find("TerrainD").GetComponent(typeof(Terrain)) as Terrain ).SampleHeight(GameObject.Find("Camera").transform.position);
		
		float ret = 0.0f;
		if(ha > ret) ret = ha;
		if(hb > ret) ret = hb;
		if(hc > ret) ret = hc;
		if(hd > ret) ret = hd;
		return ret;
	}
	
	
	public static void moveUp(){
		float actH = getHeigh();
		float posY = GameObject.Find("Camera").transform.position.y;
		if(actH + 1500.0f > posY){
			moving.move(0.0f, 1.0f, 0.0f);
		}
	}
	
	
	public static void moveDown(){
		float actH = getHeigh();
		float posY = GameObject.Find("Camera").transform.position.y;
		if(actH + 500.0f < posY){
			moving.move(0.0f, -1.0f, 0.0f);
		}
	}
}
