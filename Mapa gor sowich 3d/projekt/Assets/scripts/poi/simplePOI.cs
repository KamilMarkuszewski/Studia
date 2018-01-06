using UnityEngine;
using System.Collections;

public class simplePOI : MonoBehaviour {
	
	public Texture2D txt1;
	public Texture2D txt2;
	public Texture2D txt3;
	public Texture2D txt4;
	public Texture2D txt5;
	public Texture2D txt6;
	public Texture2D txt7;
	public Texture2D txt8;
	public Texture2D txt9;
	
	int drawOn;
	static private Vector2 scrollViewVector = Vector2.zero;
	
	// Use this for initialization
	void Start () {
		drawOn = 0;
		options.isD = false;
	}
	
	public static GameObject GetClickedItem(Camera camera)
    {
		if (!camera.gameObject.active) return null;

		var mousePos = Input.mousePosition;

		if (!camera.pixelRect.Contains(mousePos)) return null;

        RaycastHit hit;
        Ray ray = camera.ScreenPointToRay(mousePos);

        if (Physics.Raycast(ray, out hit)) 
			return hit.collider.gameObject;

        return null; 
    }
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyUp(KeyCode.Escape)){
			if(options.isD){
				drawOn = 0;
				scrollViewVector = Vector2.zero;		
			}			
		}
		
        if (Input.GetMouseButtonDown(0))
        {
			GameObject gameObject = GetClickedItem(Camera.main);

            switch(gameObject.name)
            {
                case "p1" :
                    drawOn = 1;
                    break;
                case "p2" :
                    drawOn = 2;
                    break;
                case "p3" :
                    drawOn = 3;
                    break;
                case "p4" :
                    drawOn = 4;
                    break;
                case "p5" :
                    drawOn = 5;
                    break;
                case "p6" :
                    drawOn = 6;
                    break;
                case "p7" :
                    drawOn = 7;
                    break;
                case "p8" :
                    drawOn = 8;
                    break;
                case "p9" :
                    drawOn = 9;
                    break;
            }

        }
    }

	
	void OnGUI () {
		switch(drawOn){
		case 0: 
			break;
		case 1: 
			drawWind("Sokolec",
			         "Wies polozona malowniczo miedzy Wzgorzami Wyrebinskimi a Gorami Sowimi, w obnizeniu doliny Sowiego Potoku."
			         ,txt1);
			break;
		case 2: 
			drawWind("Rzeczka", " ", null);
			break;
		case 3: 
			drawWind("Wielka Sowa",
			         "Najwyzszy szczyt Gor Sowich w Sudetach Srodkowych.\n\nWysokosc: 1014,8 m n.p.m.\nWybitnosc: 485 m \n\nNa szczycie znajduje sie wysoka na 25 metrow kamienna wieza widokowa wybudowana w roku 1906."
			         ,txt3);
			break;
		case 4: 
			drawWind("Sowina", "Wies, obecnie stanowiaca poludniowa czesc Sokolca\n, przy czym jej dolne domy zaliczane bywaja w obreb Ludwikowic Klodzkich.\n\nZabudowania Sowiny leza na wysokosci okolo 530-580 m.\n\nSowina zachowala pierwotny uklad przestrzenny i dosc liczny zespol interesujacej, starej zabudowy. \n\nPrzy drodze stoja 2 murowane kapliczki z XIX w.", null);
			break;
		case 5: 
			drawWind(" ", " ", null);
			break;
		case 6: 
			drawWind("Walim", "Walim (do 1945 niem. Wüstewaltersdorf)\n\nWies w Polsce polozona w wojewodztwie dolnoslaskim,\nw powiecie walbrzyskim,\nw gminie Walim,\nw dolinie rzeki Walimki\n u zachodniego podnoza Gor Sowich.", txt6);
			break;
		case 7: 
			drawWind("Potoczek", "", txt7);
			break;
		case 8: 
			drawWind("Rosciszow", "Rosciszow (niem. Steinseifersdorf)\n\nOsiedle Pieszyc o charakterze sanatoryjno-letniskowym\npołozona malowniczo w Sudetach srodkowych w Gorach Sowich.\nRozciaga sie u podnoza Wielkiej Sowy\nwzdłuz Kotliny potoku Kłomnicy\ni drogi wojewodzkiej nr 383.", null);
			break;
		case 9: 
			drawWind("Kamioki", " ", txt9);
			break;
			
		}
		
	}
	
	void drawWind(string title, string desc1, Texture2D txt){
		options.isD = true;
		GUI.Box (new Rect (Screen.width / 2 - 100,Screen.height / 2 - 100,200,200), title);
		
		GUI.BeginGroup(new Rect (Screen.width / 2 - 100,Screen.height / 2 - 100,200,200));
		if(GUI.Button (new Rect (200 - 25,0,25,25), "X")){
			drawOn = 0;
			options.isD = false;
			scrollViewVector = Vector2.zero;
		}

		scrollViewVector = GUI.BeginScrollView(new Rect(10, 30, 190, 160), scrollViewVector, new Rect(0, 0, 160, 600));
		

		if(txt != null){
			GUI.DrawTexture(new Rect(10, 10, 160, 120), txt);
			GUI.Label(new Rect( 10, 30+120, 160, 300), desc1);
		}else{
			
			GUI.Label(new Rect( 10, 10, 160, 300), desc1);
		}
		

		
		
		GUI.EndScrollView();
		GUI.EndGroup();
		
	}
	
	
}
