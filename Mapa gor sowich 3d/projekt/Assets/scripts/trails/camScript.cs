using UnityEngine;
using System.Collections;

public class camScript : MonoBehaviour {
	
	public TextAsset helpTextAsset;          //     Exposes a slot in the inspector
	public Material red;
	public Material green;
	public Material blue;
	public Material white;
	public Material black;
	public Material yellow;
	public Material mag;
	
	// Use this for initialization
	void Awake () {
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void Start(){
		drawTrails.red = red;
		drawTrails.green = green;
		drawTrails.blue = blue;
		drawTrails.white = white;
		drawTrails.black = black;
		drawTrails.yellow = yellow;
		drawTrails.mag = mag;
		
		
		
		drawTrails.import(helpTextAsset);
	}
	
	void OnPostRender() {
		if(options.trailsDrawOn){
			drawTrails.OnPostRender();
		}
	}
}
