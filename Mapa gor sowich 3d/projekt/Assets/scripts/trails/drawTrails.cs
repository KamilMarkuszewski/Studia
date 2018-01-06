using UnityEngine;
using System.Collections;

public class drawTrails{
	
	
	static Material lineMaterial;

	static ArrayList arr;
	
	public static Material red;
	public static Material green;
	public static Material blue;
	public static Material white;
	public static Material black;
	public static Material yellow;
	public static Material mag;
	

	private static string helpText ;
	
	
	static void CreateLineMaterial() {
	    if( !lineMaterial ) {
	        lineMaterial = new Material( "Shader \"Lines/Colored Blended\" {" +
	            "SubShader { Pass { " +
	            "    Blend SrcAlpha OneMinusSrcAlpha " +
	            "    ZWrite Off Cull Off Fog { Mode Off } " +
	            "    BindChannels {" +
	            "      Bind \"vertex\", vertex Bind \"color\", color }" +
	            "} } }" );
	        lineMaterial.hideFlags = HideFlags.HideAndDontSave;
	        lineMaterial.shader.hideFlags = HideFlags.HideAndDontSave;
			
		

	    }
	}
	
	
	public static void import(TextAsset helpTextAsset){
		arr = new ArrayList();
		
		string [] stringArray = helpTextAsset.text.Split(char.Parse("]"));
		ArrayList pars = new ArrayList();
		for(int i=0;i< stringArray.Length; i++){
			
			string [] simpleData =  stringArray[i].Split(char.Parse("\n"));
						
			str2 p = new str2();
			
			
			for(int j=0;j< simpleData.Length; j++){
	
				if( simpleData[j].Contains("Label") ){
					p.lab = simpleData[j];
				}
				if( simpleData[j].Contains("Data2") ){
					p.data = simpleData[j];
					break;
				}
				
			}

			if(p.data != null) pars.Add(p);
			simpleData = null;
		}
		stringArray = null;
		
		

		foreach(str2 p in pars){
			
			string [] points_col =  p.lab.Split(char.Parse("="));	
			for(int k=0;k< points_col.Length; k++){
				if( points_col[k].Contains("f") || points_col[k].Contains("0") ){
					p.lab = points_col[k];
				}
			}
			
			string [] points_try =  p.data.Split(char.Parse("="));
			for(int k=0;k< points_try.Length; k++){
				if( points_try[k].Contains(",") ){
					p.data = points_try[k];
				}
			}
			ArrayList pkty = new ArrayList();
			
			string [] points_tab =  p.data.Split(char.Parse(")"));
			
			for(int k=0;k< points_tab.Length; k++){
				string [] points_tab2 =  points_tab[k].Split(char.Parse("("));
				for(int l=0;l< points_tab2.Length; l++){
					if( points_tab2[l].Contains("5") ){
						pkty.Add(points_tab2[l]);
					}
					
				}

			}
			
			trail a = new trail();
			
			a.col = Color.gray; 
			a.mat = white;
		
			if(p.lab.Contains("ff00ff") ){
				a.col = Color.magenta; 
				a.mat = mag;
			}
			if(p.lab.Contains("ff0000") ){
				a.col = Color.red; 
				a.mat = red;
			}
			if(p.lab.Contains("00ff00") ){
				a.col = Color.green; 
				a.mat = green;
			}
			if(p.lab.Contains("ffff00") ){
				a.col = Color.yellow; 
				a.mat = yellow;
			}
			if(p.lab.Contains("0000ff") ){
				a.col = Color.blue; 
				a.mat = blue;
			}
			if(p.lab.Contains("000000") ){
				a.col = Color.black; 
				a.mat = black;
			}
			if(p.lab.Contains("ffffff") ){
				a.col = Color.white; 
				a.mat = white;
			}
			
			foreach(string pkt in pkty){
				
				
				string l=" ", r=" ";
				l = pkt.Substring(3,5);
				r = pkt.Substring(12,5);

				int li = System.Int32.Parse(l);
				int ri = System.Int32.Parse(r);
				
				li*=10;
				ri*=10;

				a.addP(ri, li);
			}
			arr.Add(a);
		}
		
		
	}

	
	public static void OnPostRender() {
		foreach(trail a in arr){
			a.draw();	
		}
	    
	}
	
	
}
