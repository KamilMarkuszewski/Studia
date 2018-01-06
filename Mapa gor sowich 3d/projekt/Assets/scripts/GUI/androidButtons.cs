using UnityEngine;
using System.Collections;

public class androidButtons : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	
	// Update is called once per frame
	void Update () {
		
		//Exit
		if (Input.GetKeyUp(KeyCode.Escape)){
			if(options.optOn){
				options.optOn = false;
			}
			else if(options.viewOn || options.trailsOn || options.poiOn || options.camOn || options.gpsOn ||options.autOn){
				options.closeWindows();
				options.optOn = true;
			}else if(options.isD){
				options.isD = false;
				// obsluzone w simplePOI
			}else{
				Application.Quit();
			}
		}

		
		//Menu
		if (Input.GetKeyUp(KeyCode.Menu)){
			options.optOn = !options.optOn;
			options.closeWindows();
		}
		
	}
	
	
}
