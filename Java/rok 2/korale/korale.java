/* 
 *  Koraliki 
 *
 *  Autor: Kamil Markuszewski
 *   Data: 10 stycznia 2010 r.
 */





/**
 *
 * Koraliki s¹ w miare pos³uszne
 *
 * czasami nie wiem czemu zdarzy siê ze reapint() siê nie wywo³uje...
 *
 * zdarza³o siê ze koralik szybki ci¹gnie za sob¹ wolniejszy.. kwestia warunku wyprzedzania.. juz siê chyba nie zdarza
 *
 * zdarza siê przy du¿ej iloœci koralików i du¿ych prêdkoœciach, ¿e nie maj¹ siê gdzie pomieœciæ i t³ocz¹ tak bardzo ¿e 
 * zaczynaj¹ siê wyprzedzaæ lub maj¹ zbiorowego crasha i stoj¹ du¿¹ grupk¹ na jednym polu 
 *
 */


import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.event.*;






//=============================================================================
// Koralik
//=============================================================================






class T_Koralik extends Thread{


	private rysunek P_Main;

	private int number;
	private int kat;
	private int speed;
	private Punkt pkt;
	private boolean blisko = false;

	private boolean koniec = false;


	/**
	 * Takitam ma³y konstruktorek
	 */

	public T_Koralik(int number, rysunek p, int speed, int kat){ 
		this.speed = speed;
		this.number = number;
		P_Main=p;
		this.kat = kat;

		}
	
	
	/**
	 * Oblicza na jakiej pozycji w zal od k¹ta i prêdkosci powinien byc koralik zwraca pkt oznaczaj¹cy jego œrodek
	 */
	
	public Punkt pozycja(int kat){
		float x;
		float y;
		float rad = (float)Math.toRadians((double)kat);
		x = (float)400 - (float)300 * (float)Math.cos(rad);
		y = (float)400 - (float)300 * (float)Math.sin(rad);
		return new Punkt(x,y);
		}
	
	/**
	 * Zmienia prêdkosc koralika
	 */
	
	public void zmien_speed(int speed){
		this.speed = speed;
		}
	
	
	
	
	/**
	 * Start w¹tku 
	 */
	
	
	public void run(){ 
	
			
		while(!koniec){
			
			P_Main.repaint();
        	if(kat>=360){
        		kat-=360;
        		}
			try { 
				blisko=false;
				for(T_Koralik f : korale.tablica){

					if(f.number==number){
						continue;
						}
        			if(  ((f.kat - kat) < 20) &&((f.kat - kat)>0)){
        				blisko=true;
        				}
        		

        			
        			}
        		}catch (Exception e) { }
        	
        	if(blisko==false){
        		kat+=speed;
        		}
        		
        	blisko=false;
			if(kat>=360){
        		kat-=360;
        		}  
        			
        			
        			
        			
        			
			
			
			
			pkt = pozycja(kat);

			P_Main.figury.get(number).ustaw(pkt.x, pkt.y);
			

			try {
				sleep((int)(100));
				} 
				catch (InterruptedException e) { }

			
			}
		}
		
		
		/**
		 * akcesor, ustawia koniec na true
		 */
	public void koniec(){
		koniec = true;
		}	
		
	}










//=============================================================================
// Figury
//=============================================================================




/**
 * Klasa wykorzystywana przy klasie ko³o
 */



class Punkt{   
	
	protected float x, y;

	public Punkt(){}

    public Punkt(float px, float py){ x=px; y=py;}
    

    public void przesun(float dx, float dy){ x+=dx; y+=dy; }

    public void ustaw(float dx, float dy){ x=dx; y=dy; }
    
    public void rysuj(Graphics g){ 
    	
    	g.setColor(Color.BLUE); 
      	g.fillOval((int)(x-3),(int)(y-3), 6,6); 
    	}
}










class Kolo{
	
	/**
	 * punkt1 - srodek okrêgu
	 */
	private Punkt punkt1;
	
	/**
	 * r -promien
	 */
	 
    private float r;


    /**
     * Konstruktor parametryczny
     * @param p1 punkt srodek
     * @param srednica
     * @param kolor
     * @param nr numer ko³a
     */
    
    public Kolo(Punkt p1, float srednica){    
    	punkt1=p1; 
    	r=srednica/2;
    	}


    /**
     * Przesuwa o zadan¹ pozycjê 
     */
    public void przesun(float dx, float dy){   
    	punkt1.przesun(dx,dy);
    	}


	/**
	 * Ustawia na zadanej pozycji
	 */
    public void ustaw(float dx, float dy){   
    	punkt1.ustaw(dx,dy);
    	}

    /**
     * rysuje ko³o pierw kopiuj¹c punkt w srodku okrêgu i przesuwaj¹c w lewy górny róg 
     */ 
    
    public void rysuj(Graphics g){   
    	Punkt rog = new Punkt(punkt1.x, punkt1.y);
       	rog.przesun(-r, -r);
       	g.fillOval((int)rog.x, (int)rog.y, (int)(2*r), (int)(2*r));
       	
    	}
    	
    	/**
    	 * rysuje okr¹g tak jak wy¿ej
    	 */
    	
    public void rysujPusty(Graphics g){   
    	Punkt rog = new Punkt(punkt1.x, punkt1.y);
       	rog.przesun(-r, -r);
       	g.drawOval((int)rog.x, (int)rog.y, (int)(2*r), (int)(2*r));
       	
    	}
    	
    	
    	/**
    	 * sprawdza czy to ten g³ówny kolralik
    	 */
    	
    public boolean is_main(){
    	if(r==300){
    		return true;
    		}
    		else{
    			return false;
    			}
    	
    	}
    	
}











//=============================================================================
// Tu rysujemy :) 
//=============================================================================






class rysunek extends JPanel {
	

	ArrayList<Kolo> figury = new ArrayList();
	Kolo main = new Kolo(new Punkt(400,400),600);
		
	 /**
	 * Dodaje Figurê do Listy - zaporzyczone z wczesniejszego programu.. jak z reszt¹ spora czêœæ kodu rysuj¹cego 
	 */
	 private void dodajFigure(Kolo fig){ 
     	figury.add(fig);
    	repaint();
    	}
	
	
	
	/**
	 * dodaje rysunek koralika
	 */
	
	
    public void dodajKoralik(Punkt a){
    	
    	float sr = 20;
    	dodajFigure(new Kolo(new Punkt(a.x,a.y),sr));
    	}
	
	
	
	/**
	 * to do repainta
	 */
	
	
	public void paintComponent(Graphics g){   
    	
    	super.paintComponent(g);
    	main.rysujPusty(g);

		for(Kolo f : figury){
        	g.setColor(Color.BLUE);
        	
        	f.rysuj(g);
	
        	}

        	
        	
    	}
	
	
	
	
	}




//=============================================================================
// Ustawienia
//=============================================================================


/**
 * JSlidery do zarz¹dzania (ale to profesjonalnie brzmi) prêdkoœci¹ koralików
 */





class ustawienia extends JFrame implements ChangeListener{
	private int ile;
	ArrayList<JSlider> Slider = new ArrayList();
	
	
	/**
	 * Konstruktor okienka
	 */
	
	ustawienia(int ile){
		super("Ustawienia");
		setSize(400,400);
     	setVisible(true);
     	setLayout(null);
     	this.ile=ile;
     	
     	
     	for(int i=0; i<ile;i++){
     		
     		Slider.add(new JSlider(JSlider.HORIZONTAL, 0, 10, 1+i));//^
     		
     		
     		Slider.get(i).setBounds(10,10+(i*30),380,20);  //^
		
			Slider.get(i).setMajorTickSpacing(10);
			Slider.get(i).setMinorTickSpacing(1);
			Slider.get(i).setPaintTicks(true);
			Slider.get(i).addChangeListener(this);
			
     		
     		
     		add(Slider.get(i));
     		
     		}
     	
		

		
		
		repaint();
		}
		
		
	/**
	 * Listener... hmm nauczy³em siê czegos ciekawego :D
	 */
		
	public void stateChanged(ChangeEvent evt){
		JSlider e = (JSlider)evt.getSource();
		
		for(int i=0; i<ile;i++){
			if(e==Slider.get(i)){
				int speed = (int)e.getValue();
				korale.zmien_speed(i,speed);
				}
			}
		
		}
		
		
		
		
		
	
	}









//=============================================================================
// MAIN
//=============================================================================


public class korale extends JFrame{
	
	rysunek P_Main;
	int speed = 1;
	static ArrayList<T_Koralik> tablica = new ArrayList();	
		
	static ustawienia set;

	/**
	 * Oblicza na jakiej pozycji powinien byc koralik... z reszt¹... by³o wy¿ej 
	 */


	public Punkt pozycja(int kat){
		float x=0;
		float y=0;
		float rad = (float)Math.toRadians((double)kat);
		x = (float)400 - (float)300 * (float)Math.cos(rad);
		y = (float)400 - (float)300 * (float)Math.sin(rad);
		return new Punkt(x,y);
		}
	
	/**
	 * Konstruktor okienka
	 */
	
	korale(int ile){
		super("Koraliki");
		setSize(800,800);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	setVisible(true);
     	setLayout(null);
     	
		System.out.print("1");
		
		P_Main = new rysunek();
		P_Main.setVisible(true);
		
		
		for(int i=0; (i<36)&&(i<ile); i++){
			speed += 1;
			P_Main.dodajKoralik(pozycja(i*10));
			tablica.add(new T_Koralik(i, P_Main, speed, i*10));
      		tablica.get(i).start();
			}
		
		      
		System.out.print("2");
		
		
	
	
		setContentPane(P_Main);
		
		set = new ustawienia(ile);
		System.out.print("3");
		


		repaint();

		
		}


	/**
	 * Akcesor zmieniaj¹cy prêdkosc konkretnego koralika
	 * 
	 * z tej f. korzysta okienko ustawienia
	 */



	static public void zmien_speed(int nr, int speed){
		tablica.get(nr).zmien_speed(speed);
		
		}









	public static void main(String[] args){
		int ile=5;
		
		do{
			try{
				ile = Integer.parseInt(JOptionPane.showInputDialog("Ile koralików?(max 10 bo tak sobie ustali³em dla czytelnosci)"));
				}
				catch(Exception ex){
					JOptionPane.showMessageDialog(null,"Z³y typ danych! Wype³nij wszystkie pola!");
					ile = Integer.parseInt(JOptionPane.showInputDialog("Ile koralików?"));
				}	
			
			}while((ile>10)||(ile<0));
		
		
		// zmieniaj¹c maxymaln¹ liczbê koralików trzeba edytowaæ linijkê w klasie ustawienia oznaczon¹ ^
		
		korale aplikacja = new korale(ile);
		
		}
	
	
	
	
	}


