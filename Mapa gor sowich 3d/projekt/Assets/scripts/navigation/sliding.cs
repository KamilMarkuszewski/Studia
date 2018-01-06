using UnityEngine;
using System.Collections;


public class sliding : MonoBehaviour
{

	void Update ()
	{
		if(!options.optOn && !options.viewOn && !options.trailsOn && !options.poiOn && !options.camOn && !options.gpsOn && !options.autOn && !options.isD){
			
			if (Input.touchCount == 1) {
				// przesuwanie mapy 1 palcem
				foreach (Touch touch in Input.touches) {
					if (touch.phase == TouchPhase.Moved) {
						
						if(System.Math.Abs(touch.deltaPosition.x) + System.Math.Abs(touch.deltaPosition.y) > 5.0f ){
							// waruek zeby nie przesuwalo przy przyapdowym nacisnieciu
							moving.move(-touch.deltaPosition.x, 0.0, -touch.deltaPosition.y);
						}
					}
					//debug.text = " " + Terrain.activeTerrain.SampleHeight(transform.position);
				}
			}
			
			if (Input.GetKey (KeyCode.UpArrow) || Input.GetKey (KeyCode.LeftArrow) || Input.GetKey (KeyCode.DownArrow) || Input.GetKey (KeyCode.RightArrow)){
				if(Input.GetKey (KeyCode.UpArrow)){
					moving.move(-0.0f, 0.0f, 0.5f);
				}
				if(Input.GetKey (KeyCode.DownArrow)){
					moving.move(-0.0f, 0.0f, -0.5f);
				}
				if(Input.GetKey (KeyCode.LeftArrow)){
					moving.move(-0.5f, 0.0f, 0.0f);
				}
				if(Input.GetKey (KeyCode.RightArrow)){
					moving.move(0.5f, 0.0f, 0.0f);
				}
			}
			
			
			if (Input.touchCount == 2) {
				// ewentualny kod na przyblizanie mapy multitouch'em	
			}
			
			
			
		}

	}

}
