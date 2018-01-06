/* 
 *  Problem producenta i konsumenta
 *
 *  Autor: Kamil Markuszewski
 *   Data: 23 grudnia 2009 r.
 */

import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;





/**
 * Klasa producent
 */


class Producent extends Thread{
	static char item = 'A';
	/**
	 * JPanel do rysowania
	 */
	Rysunek P_Main;
	Bufor buf;
	/**
	 * Numer elementu 
	 */
	int number;
	
	/**
	 * Sprawdza czy zakonczyc 
	 */
	private boolean koniec = false;
	/**
	 * Konstruktor 
	 * @param c bufor 
	 * @param number numer producenta
	 * @param p referencja do rysunku (panel)
	 */
	public Producent(Bufor c, int number, Rysunek p){ 
		buf = c;
		this.number = number;
		P_Main=p;
		}
	
	public void run(){ 
		char c;
		while(!koniec){
			c = item++;
			buf.put(number, c, P_Main);

			try {
				sleep((int)(2000));
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
	
	/**
 	* Klasa konsument ;>
 	*/


	
class Konsument extends Thread{
	
	Bufor buf;
	
	/**
	 * Numer elementu 
	 */
    int number;
    
	/**
	 * Sprawdza czy zakonczyc 
	 */
    
    boolean koniec = false;
    
    /**
	 * JPanel do rysowania
	 */
    
	Rysunek P_Main;
	/**
	 * Konstruktor 
	 * @param c bufor 
	 * @param number numer producenta
	 * @param p referencja do rysunku (panel)
	 */
	public Konsument(Bufor c, int number, Rysunek p){ 
		buf = c;
		this.number = number;
		P_Main=p;
		}
	
	public void run(){ 
		while(!koniec){ 
			buf.get(number, P_Main);

			try {
				sleep((int)(2000));
				} catch (InterruptedException e) { }

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
// BUFOR
//=============================================================================



class Bufor{	

	/**
	 * Rozmiar bufora
	 */

	private int rozmiar;
	
	/**
	 * OpóŸnienie akcji
	 */
	private int  delay;
	/**
	 * Wektor znaków ASCII
	 */
	
	Vector<Character> contents = new Vector();
	/**
	 * Referencja do JTextArea
	 */
	TextArea kon;
	
	/**
	 * Referencja Rysunku dziedzicz¹cego po JPanel
	 */
	Rysunek P_Main;
	JLabel L_Buf = new JLabel();
	public synchronized int get(int kons, Rysunek P){
		char tmp;
		P_Main=P;
		P_Main.przesunKonsumenta(kons);
		P_Main.repaint();		
		kon.append("Konsument #" + kons + " chce zabrac \n");
		//System.out.println("Konsument #" + kons + " chce zabrac");
		while (contents.size()<=0){
			try{ 
				kon.append("Konsument #" + kons + "   bufor pusty - czekam \n");
				//System.out.println("Konsument #" + kons + "   bufor pusty - czekam");

				wait();
				} 
				catch (InterruptedException e) { }
			}

		notifyAll();
		tmp = contents.lastElement();
		contents.remove(contents.size()-1);  
		contents.trimToSize();
		try{
			Thread.sleep(delay);
			}
			catch (InterruptedException e) { }

		
		String a="";
		
		for(int i=0;i<contents.size();i++){
			a = a + " " + contents.elementAt(i);
			}
		L_Buf.setText(a);
		L_Buf.setBounds(390,30,150,20);
		P_Main.add(L_Buf);
		P_Main.przesunKonsumentaback(kons);
		P_Main.repaint();
		kon.append("Konsument #" + kons + "      zabral: " + tmp + "\n");
		//System.out.println("Konsument #" + kons + "      zabral: " + tmp);
		
		return tmp;

		}



	public synchronized void put(int prod, char value, Rysunek P){
		P_Main=P;
		kon.append("Producent #" + prod + "  chce oddac: " + value + "\n");
		//System.out.println("Producent #" + prod + "  chce oddac: " + value);
		P_Main.przesunProducenta(prod);
		P_Main.repaint();
		
		while (contents.size()>=rozmiar){

			
			try{ 
				kon.append("Producent #" + prod + "   bufor zajety - czekam \n");
				//System.out.println();
				

				wait();
				} 
				catch (InterruptedException e) { }
			}
		contents.add(value);
		try{
			Thread.sleep(delay);
			}
			catch (InterruptedException e) { }

		String a="";
		
		for(int i=0;i<contents.size();i++){
			a = a + " " + contents.elementAt(i);
			}
		L_Buf.setText(a);
		L_Buf.setBounds(390,30,150,20);
		P_Main.add(L_Buf);
		
		P_Main.przesunProducentaback(prod);
		P_Main.repaint();
		kon.append("Producent #" + prod + "       oddal: " + value + "\n");
		//System.out.println("Producent #" + prod + "       oddal: " + value);
		

		notifyAll();
		}
	
	public void setRozmiar(int r){
		rozmiar = r;
		}
	
	public void setDelay(int d){
		delay = d;
		}	
	
	public void setKon(TextArea k){
		kon = k;
		}	
	
	}




//=============================================================================
// KSZTA£TY
//=============================================================================



/**
 * Klasa wykorzystywana przy klasie ko³o
 */



class Punkt{   
	
	protected float x, y;

	public Punkt(){}

    public Punkt(float px, float py){ x=px; y=py;}
    

    public void przesun(float dx, float dy){ x+=dx; y+=dy; }

    
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
    public int kolor;
    public int nr;
    
    /**
     * Konstruktor parametryczny
     * @param p1 punkt srodek
     * @param srednica
     * @param kolor
     * @param nr numer ko³a
     */
    
    public Kolo(Punkt p1, float srednica, int kolor, int nr){    
    	punkt1=p1; 
    	r=srednica/2;
		this.kolor=kolor;	
		this.nr=nr;	
    	}


    
    public void przesun(float dx, float dy){   
    	punkt1.przesun(dx,dy);
    	}


    /**
     * rysuje okr¹g pierw kopiuj¹c punkt w srodku okrêgu i przesuwaj¹c w lewy górny róg 
     */ 
    
    public void rysuj(Graphics g){   
    	Punkt rog = new Punkt(punkt1.x, punkt1.y);
       	rog.przesun(-r, -r);
       	g.fillOval((int)rog.x, (int)rog.y, (int)(2*r), (int)(2*r));
       	
    	}
    	
}






//=============================================================================
// Rysunek
//=============================================================================




class Rysunek extends JPanel{   


	ArrayList<Kolo> figury = new ArrayList();	
	
    /**
	 * Dodaje Figurê do Listy 
	 */
	 private void dodajFigure(Kolo fig){ 
     	figury.add(fig);
    	repaint();
    	}
    



    

	
	/**
	 * Dodaje ko³o producenta do listy
	 */
	
    public void dodajProducenta(int nr){
    	
    	float x1 = 100;
    	float y1 = 100+(100*(nr));
    	float sr = 50;
    	int kolor=0;
    	dodajFigure(new Kolo(new Punkt(x1,y1),sr, kolor,nr));
    	}
	
	/**
	 * Dodaje ko³o konsumenta do listy
	 */
	

    public void dodajKonsumenta(int nr){
    	
    	float x1 = 700;
    	float y1 = 100+(100*(nr));
    	float sr = 50;
    	int kolor=1;
    	dodajFigure(new Kolo(new Punkt(x1,y1),sr, kolor, nr));
    	}
    	
    	
    
 	/**
	 * przesuwa ko³o producenta 
	 */
	 
    void przesunProducenta(int nr){
		for(Kolo f : figury){
			if(f.kolor==0){
				if(f.nr==nr){
					f.przesun(290,0);
					repaint();
					}
				}
			}
		
      	repaint();
    	}
 
 	/**
	 * przesuwa ko³o producenta spowrotem
	 */
  
    void przesunProducentaback(int nr){
		for(Kolo f : figury){
			if(f.kolor==0){
				if(f.nr==nr){
					f.przesun(-290,0);
					repaint();
					}
				}
			}
		
      	repaint();
    	}
    	
 	 /**
	 * przesuwa ko³o konsumenta
	 */
 
    void przesunKonsumenta(int nr){ 
		for(Kolo f : figury){
			if(f.kolor==1){
				if(f.nr==nr){
					f.przesun(-290,0);
					repaint();
					}
				}
			}
		
      	repaint();
    	}
    	
 	 /**
	 * przesuwa ko³o konsumenta spowrotem
	 */

    void przesunKonsumentaback(int nr){ 
		for(Kolo f : figury){
			if(f.kolor==1){
				if(f.nr==nr){
					f.przesun(290,0);
					repaint();
					}
				}
			}
		
      	repaint();
    	}



    public void paintComponent(Graphics g){   
    	
    	super.paintComponent(g);
        for(Kolo f : figury){
        	if(f.kolor==0){
        		g.setColor(Color.BLUE);
        		}else{
        			g.setColor(Color.GREEN);
        			}
        	
        	f.rysuj(g);
        	}
    	}

    
    
	}














//=============================================================================
// Wizualizacja
//=============================================================================



class Wizualizacja extends JFrame implements ActionListener {
	
	
	Producent [] producenci;
	Konsument [] konsumenci;
	Rysunek P_Main;
	Bufor b;
	JLabel L_pro, L_ko, L_buf;
	
	

    	
    	
 
	
	
	Wizualizacja(int poj, int pro, int ko, int delay, TextArea kon){
		
		
		super("Okno akcji");
		setSize(800,600);
     	//setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	//setVisible(true);
     	//setLayout(null);
		
		
		
		b = new Bufor();
		b.setRozmiar(poj);
		b.setDelay(delay);
		b.setKon(kon);
		
		
		Rysunek P_Main = new Rysunek();
		P_Main.setLayout(null);
		L_pro = new JLabel("Producenci");
		L_ko = new JLabel("Konsumenci");
		L_buf = new JLabel("Bufor");
		
		
		L_pro.setBounds(70,0,120,20);
			
		L_ko.setBounds(670,0,120,20);	
			
		L_buf.setBounds(390,0,120,20);	
			
		P_Main.add(L_pro);
		P_Main.add(L_ko);
		P_Main.add(L_buf);

		
			
		producenci = new Producent[pro];
		konsumenci = new Konsument[ko];
		
		for(int i=0; i<pro; i++){
			producenci[i] = new Producent(b, i, P_Main);
			P_Main.dodajProducenta(i);
			}
			
		for(int i=0; i<ko; i++){
			konsumenci[i] = new Konsument(b, i, P_Main);
			P_Main.dodajKonsumenta(i);
			}
			
		for(int i=0; i<pro; i++){
			producenci[i].start();
			}
				
		for(int i=0; i<ko; i++){
			konsumenci[i].start();
			}
		
		
		
		
		
		
		
		setContentPane(P_Main);
		setVisible(true);
		repaint();
		
		
		
		}
		
		
	
	public void actionPerformed(ActionEvent evt){
		
		
		}
		
		
	/**
	 * konczy dzialanie w¹tków
	 */ 
	
	public void stop(int pro, int ko){
		
		for(int i=0; i<pro; i++){
			producenci[i].koniec();
			}
				
		for(int i=0; i<ko; i++){
			konsumenci[i].koniec();
			}
			
		b=null;
		}

	}


//=============================================================================
// MAIN
//=============================================================================


public class ProducentKonsument extends JFrame implements ActionListener{
	/**
 	* G£Ówny Panel zawieraj¹cy P_p1 i P_p2
 	*/
	JPanel P_Main;
	
	
	JLabel L_poj, L_pr, L_ko, L_de;
	JTextField TF_poj, TF_pr, TF_ko, TF_de;
	
	JButton B_start, B_stop;
	
	
	
	JPanel P_p1, P_p2;
	
	
	/**
	 * TextArea w roli konsolki
	 */
	
	TextArea TA_konsola;

	/**
	 * Konstruktor g³ównej klasy Tworzy GUI
	 */
	 
	 Wizualizacja w;
	 
	
	ProducentKonsument(){
		
		super("Main Window");
		setSize(300,700);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	setVisible(true);
     	setLayout(null);
     	

		// LABELE
		
		L_poj = new JLabel("Pojemnoœæ bufora: ");
		L_poj.setBounds(10,10,150,20);
		add(L_poj);
		
		
		L_pr = new JLabel("Iloœæ producentów: ");
		L_pr.setBounds(10,40,150,20);
		add(L_pr);
		
		
		L_ko = new JLabel("Iloœæ konsumentów: ");
		L_ko.setBounds(10,70,150,20);
		add(L_ko);
		
		
		L_de = new JLabel("OpóŸnienie: ");
		L_de.setBounds(10,100,150,20);
		add(L_de);
		
		// Text Fields
		
		
		TF_poj = new JTextField ("5");
		TF_poj.setBounds(170,10,100,20);
		add(TF_poj);
		
		
		TF_pr = new JTextField ("5");
		TF_pr.setBounds(170,40,100,20);
		add(TF_pr);
		
		TF_ko = new JTextField ("3");
		TF_ko.setBounds(170,70,100,20);
		add(TF_ko);
		
	
		TF_de = new JTextField ("9000");
		TF_de.setBounds(170,100,100,20);
		add(TF_de);
		
		// Button
		
		B_start = new JButton("Start");
		B_start.setBounds(40,640, 100, 20);
		B_start.addActionListener(this);
		add(B_start);
		
		B_stop = new JButton("Stop");
		B_stop.setBounds(160,640, 100, 20);
		B_stop.addActionListener(this);
		B_stop.setEnabled(false); 
		add(B_stop);
		
		
		TA_konsola = new TextArea();
		TA_konsola.setBounds(5,150,280,450);

		add(TA_konsola);
 

		repaint();
		}


	/**
	 * Obs³uga przycisków
	 */


	public void actionPerformed(ActionEvent evt){
		
		Object e = evt.getSource();
		
		if(e==B_start){
			w = null;
			TA_konsola.append("\n\n --------------------------- \n\n");
			int poj = Integer.parseInt(TF_poj.getText());
			int pr = Integer.parseInt(TF_pr.getText());
			int ko = Integer.parseInt(TF_ko.getText());
			int de = Integer.parseInt(TF_de.getText());
			B_start.setEnabled(false); 
			B_stop.setEnabled(true); 	
			TF_poj.setEnabled(false); 	
			TF_pr.setEnabled(false); 	
			TF_ko.setEnabled(false); 	
			TF_de.setEnabled(false); 
				
			w = new Wizualizacja(poj,pr,ko,de, TA_konsola);	
			
				
			}
		
		if(e==B_stop){
			int pr = Integer.parseInt(TF_pr.getText());
			int ko = Integer.parseInt(TF_ko.getText());
			
	
			TF_poj.setEnabled(true); 	
			TF_pr.setEnabled(true); 	
			TF_ko.setEnabled(true); 	
			TF_de.setEnabled(true); 
			B_start.setEnabled(true); 
			B_stop.setEnabled(false); 
			w.stop(pr, ko);
			w.setVisible(false);
			
			
				
			}
		
		
		}






	public static void main(String[] args){
		ProducentKonsument okno = new ProducentKonsument();

		try { Thread.sleep( 5000 );
			} catch (InterruptedException e) { }
		//System.exit(0);
	}
}


