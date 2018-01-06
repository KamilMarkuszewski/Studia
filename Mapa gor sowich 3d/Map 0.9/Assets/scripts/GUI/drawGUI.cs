using UnityEngine;
using System.Collections;

public class drawGUI : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void OnGUI () {
		
	    if (GUI.Button (new Rect (10,10,25,25), "+")){
			moving.move(0.0f, -1.0f, 0.0f);
		}
	    if (GUI.Button (new Rect (10,45,25,25), "-")){
			moving.move(0.0f, 1.0f, 0.0f);
		}
		
		GUI.Label(new Rect( 10, Screen.width - 65, 100, 25), "Wspolrzedne: " + coordinatesCalc.mapXZToCoordinates(transform.position.x, transform.position.z).toString());
		GUI.Label(new Rect( 10, Screen.width - 35, 100, 25), "Metry npm: " + coordinatesCalc.mapHeightToMeters( Terrain.activeTerrain.SampleHeight(transform.position)));
	}
}
