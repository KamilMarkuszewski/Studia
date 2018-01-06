using UnityEngine;
using System.Collections;


public class sliding : MonoBehaviour
{

	void Update ()
	{
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
		
		if (Input.touchCount == 2) {
			// ewentualny kod na przyblizanie mapy multitouch'em	
		}
	}

}
