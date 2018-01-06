using UnityEngine;
using System.Collections;

public static class moving {
	
	// wysokośc terenu w ostatnim położeniu kamery
	private static float lastH = 0.0f;
	
	// ogólna prędkośc przesuwania
	public static float speed = 1.0f;

	
	public static void move(float x, float y, float z){
		
		float actH = Terrain.activeTerrain.SampleHeight(GameObject.Find("Camera").transform.position);
		
		Vector3 dir = Vector3.zero;
		float ratio = (float)(GameObject.Find("Camera").transform.position.y / 50.0f) - 1.0f;
		if(ratio < 1.0f) ratio = 1.0f;
		dir.x = x * ratio * speed;
		dir.y = y * 50.0f * speed;
		dir.z = z * ratio * speed;
		dir.y += (actH - lastH);
		lastH = actH;
		
		GameObject.Find("Camera").transform.Translate (dir);
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
}
