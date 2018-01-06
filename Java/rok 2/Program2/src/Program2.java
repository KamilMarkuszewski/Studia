/**
 * @(#)Program2.java
 *
 * Program2 application
 *
 * @author Kamil Markuszewski 171016
 * @version 1.00 2009/10/31
 */
 
  import java.awt.*;
  import java.awt.event.*;
  import javax.swing.JOptionPane;
  import java.io.*;

 
 
 
 
  //--------------------------------------------------------------------------------
  // T_czas
  //--------------------------------------------------------------------------------
 
class T_czas{
	private int godz;
	private int min;
	private int sek;
		
	T_czas(){
		godz = 0;
		min = 0;
		sek = 0;
		}
		
	T_czas(int g, int m, int s){
		godz = g;
		min = m;
		sek = s;
		}
		
	// akcesory

	void set_czas(int g, int m, int s){
		godz = g;
		min = m;
		sek = s;	
		}

	int get_godz(){
		return godz;
		}
	
	int get_min(){
		return min;
		}
	
	int get_sek(){
		return sek;
		}
		
		
	String ToString(){
		return String.format(godz + " : " + min + " : " + sek);
		}
	}
  
  //--------------------------------------------------------------------------------
  // T_album
  //--------------------------------------------------------------------------------
  
  
  
  
  
  
class T_album {
 	
 	private String nazwa;
 	
 	private String artist;
 	
 	private String genre;
 	
 	private int tracks;
 	
 	private T_czas time;  	
 		
 		
 	T_album(){
		nazwa = "wprowadz_dane";
		
		artist = "wprowadz_dane";
			
		genre = "wprowadz_dane"; 
			
		tracks = 0;
		
		time = new T_czas(0,0,0); 	
 		}
 		
 	T_album(T_album cpy){
 		nazwa = cpy.nazwa;
 		artist = cpy.artist;
 		genre = cpy.genre;
 		tracks = cpy.tracks;
 		time = cpy.time;
 		}
 			
 		
 	T_album(String temp_nazwa, String temp_artist, String temp_genre, int temp_tracks, int temp_g, int temp_m, int temp_s){
 		
 		nazwa = temp_nazwa;
 		
 		artist = temp_artist;
 			
 		genre = temp_genre;
 		
 		tracks = temp_tracks;
 		
 		time = new T_czas(temp_g, temp_m, temp_s); 		
 		}

	// akcesory
	
	String get_nazwa(){
		return nazwa;
		}	
			
	String get_artist(){
		return artist;
		}
	
	String get_genre(){
		return genre;
		}
	
	int get_tracks(){
		return tracks;
		}
		
	T_czas get_time(){
		return time;
		}	
		
		
	void set_nazwa(String temp_nazwa){
		nazwa = temp_nazwa;
		}
		
	void set_artist(String temp_artist){
		artist = temp_artist;
		}
		
	void set_genre(String temp_genre){
		genre = temp_genre;
		}	
		
	void set_tracks(int temp_tracks){
		tracks = temp_tracks;
		}
		
	void set_time(int g, int m, int s){
		time.set_czas(g,m,s);
		}
		
	public String ToString(){
		
		return String.format("\n Nazwa albumu: " + nazwa + "\n Artysta: " + artist + "\n Gatunek: "+ genre + "\n Iloœæ utworów: " + tracks + "\n Czas trwania: " + time.ToString() + "\n\n");
		
		}

 	
 	}
  
  //--------------------------------------------------------------------------------
  // Tablica
  //--------------------------------------------------------------------------------
  
  
class T_Tablica{
	private int rozmiar = 2;
   
	private int ile;
   
	T_album [] tablica;
   
	T_album [] temp_tablica;
   
	T_Tablica(){
   		tablica = new T_album[rozmiar];
   		ile=0;
		}
   
   int get_ile(){
   		return ile;
   		}
   
	void add_album(String n, String a, String ge, int t, int g, int m, int s){
   		if(ile == rozmiar){
   			
   			rozmiar *=2;
   			temp_tablica = new T_album[ile];
   			
   			for(int i=0;i<ile;i++){
   				temp_tablica[i] = tablica[i];
   				}
			tablica = null;
   			tablica = new T_album[rozmiar];
   			
   			for(int i=0;i<ile;i++){
   				tablica[i] = temp_tablica[i];
   				}
   			temp_tablica = null;
   			
   			}else{
   				tablica[ile] = new T_album(n, a, ge, t, g, m, s);
   				ile++;
   				}
   		
		}
   	
   }
   
   
   
   
   
  //--------------------------------------------------------------------------------
  // main
  //--------------------------------------------------------------------------------
  
 
public class Program2 extends Frame implements ActionListener{
    
    static T_Tablica baza = new T_Tablica();
    String pomocnicza, name, artist, genre;
    int tracks, g, m, s;
    
    // Góra - dodaj nowy element
	Button B_dodaj;
	Label Label_nowy, Label_nazwa, Label_artist, Label_genre, Label_tracks, Label_time;
	TextField TField_nazwa, TField_artist, TField_genre, TField_tracks, TField_godz, TField_min, TField_sek;
    TextArea TArea_konsola;
    //
    
    
    //Konstruktor
    
    public Program2(){
    	super("Program 2");
    	setSize(890,768);
    	setVisible(true);
    	setLayout(null);
    	
    	
    	
    	
    	 // Góra - dodaj nowy element
    	 
    	 
    	Label_nowy = new Label("Dodaj nowy album muzyczny:");
    	Label_nowy.setBounds(10, 40, 210, 20);
    	add(Label_nowy);
		
    	Label_nazwa = new Label("Nazwa Albumu: ");
    	Label_nazwa.setBounds(10, 70, 100, 20);
    	add(Label_nazwa);		

		TField_nazwa = new TextField();
    	TField_nazwa.setBounds(110, 70, 200, 20);
    	add(TField_nazwa);

    	Label_artist = new Label("Artysta: ");
    	Label_artist.setBounds(10, 90, 100, 20);
    	add(Label_artist);
    	
    	TField_artist = new TextField();
    	TField_artist.setBounds(110, 90, 200, 20);
    	add(TField_artist);

    			
    	Label_genre = new Label("Gatunek: ");
    	Label_genre.setBounds(10, 110, 100, 20);
    	add(Label_genre);	
    		
    	TField_genre = new TextField();
    	TField_genre.setBounds(110, 110, 200, 20);
    	add(TField_genre);
	
    	Label_tracks = new Label("Iloœæ utworów: ");
    	Label_tracks.setBounds(10, 130, 100, 20);
    	add(Label_tracks);

    	TField_tracks = new TextField();
    	TField_tracks.setBounds(110, 130, 200, 20);
    	add(TField_tracks);		
		
    	Label_time = new Label("Czas trwania: ");
    	Label_time.setBounds(10, 150, 100, 20);
    	add(Label_time);

    	TField_godz = new TextField();
    	TField_godz.setBounds(110, 150, 66, 20);
    	add(TField_godz);

    	TField_min = new TextField();
    	TField_min.setBounds(176, 150, 66, 20);
    	add(TField_min);
    	
    	TField_sek = new TextField();
    	TField_sek.setBounds(242, 150, 67, 20);
    	add(TField_sek);

		B_dodaj = new Button("Dodaj");
		B_dodaj.setBounds(125,180,100,20);
		B_dodaj.addActionListener(this);
		add(B_dodaj);
		
		TArea_konsola = new TextArea();
		TArea_konsola.setBounds(350, 40, 500, 160 );
		add(TArea_konsola);

    	
    	// Wyswietlanie elementow
    	
    	repaint();
    	}
    
    	public void actionPerformed(ActionEvent e){

		if(e.getSource() == B_dodaj){ 
			try{
				name = TField_nazwa.getText();
				
				artist = TField_artist.getText();
				
				genre = TField_genre.getText();
				
				pomocnicza = TField_tracks.getText();
				tracks = Integer.parseInt(pomocnicza);
				
				pomocnicza = TField_godz.getText();
				g = Integer.parseInt(pomocnicza);
				
				pomocnicza = TField_min.getText();
				m = Integer.parseInt(pomocnicza);
				
				pomocnicza = TField_sek.getText();
				s = Integer.parseInt(pomocnicza);		
				
				baza.add_album(name,artist,genre,tracks,g,m,s);
				TArea_konsola.append("Dodano: " + baza.tablica[baza.get_ile()-1].ToString());    				  			
				}
				
			catch(Exception ex){
				JOptionPane.showMessageDialog(null,"Z³y typ danych!");
				}

			}
		}
    
    
    
    
    public static void main(String[] args) {

    	new Program2();
    	
    	
    	
    	}
    
   
    
}
