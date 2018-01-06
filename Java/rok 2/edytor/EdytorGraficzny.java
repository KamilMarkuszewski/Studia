/* 
 *  Program Kolekcje
 *
 *  Autor: Kamil Markuszewski 171016	
 *   Data: 20.10.2009
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;





//---------------------------------------------------------------------------
// FIGURA
//---------------------------------------------------------------------------

/**
 * Klasa abstrakcyjna Figura
 */


abstract class Figura{   
	/**
	 * Zmienna przechowuj¹ca kolor figury
	 */
	protected int c;
	private boolean zaznaczona = false;

    public boolean jestZaznaczona(){ return zaznaczona; }
    public void zaznacz(){ zaznaczona = true; };
    public void zaznacz(boolean z){ zaznaczona = z; }
    public void odznacz(){ zaznaczona = false; }
    public void zaznaczOdwrotnie(){ zaznaczona = !zaznaczona; }
   
    public abstract boolean jestWewnatrz(float px, float py);
    public boolean jestWewnatrz(int px, int py){ 
    	return jestWewnatrz((float)px, (float)py); 
    	}
   
    public abstract float pole();
    public abstract float obwod(); 
    public abstract void przesun(float dx, float dy);
    public abstract void skaluj(float s);
    
    /**
     * Ustawia kolor w zale¿nosci od zaznaczenia i zmiennej c
     */
    protected void ustawKolor(Graphics g){ 
    	if (zaznaczona) g.setColor(Color.RED); 
        	else{
        		if(c==0)g.setColor(Color.BLACK); 
        		if(c==1)g.setColor(Color.GREEN);
        		if(c==2)g.setColor(Color.BLUE);	
        		}
        		
        		 
    	};

    public abstract void rysuj(Graphics g);
    
    protected String wlasciwosci()
    { String s = "  Pole: " + pole() + "  Obwod: " + obwod();
      if (jestZaznaczona()) s = s + "   [ZAZNACZONA]"; 
      return s;
    }
}


//---------------------------------------------------------------------------
// PUNKT
//---------------------------------------------------------------------------

class Punkt extends Figura{   
	
	protected float x, y;
    /**
     * Konstruktor z dodatkowym  parametrem kolor
     */
    
    public Punkt(float px, float py, int kolor){ x=px; y=py; c=kolor;}
    
    /**
     * Konstruktor uzwany gdy nie obchodzi nas kolor
     */
    public Punkt(float px, float py){ x=px; y=py; }
    
    public boolean jestWewnatrz(float px, float py)
    { // by umozliwic zaznaczanie punktu myszka
      // miejsca odlegle nie wiecej niz 3 leza wewnatrz
      return (Math.sqrt((x-px)*(x-px) + (y-py)*(y-py))<=6);
    } 
    public float pole(){ return 0; };
    public float obwod(){ return 0; }; 
    public void przesun(float dx, float dy){ x+=dx; y+=dy; }
    public void skaluj(float s){}
    
    protected String toStringXY(){ return "(" + x + " , " + y + ")"; }
    public String toString()
    { return "Punkt " + toStringXY() + wlasciwosci();   
    }
    public void rysuj(Graphics g)
    { ustawKolor(g);
      g.fillOval((int)(x-3),(int)(y-3), 6,6); 
    };
}



//---------------------------------------------------------------------------
// TRÓJK¥T 
//---------------------------------------------------------------------------


class Trojkat extends Figura{   
	private Punkt punkt1, punkt2, punkt3;
	
    
    public Trojkat(Punkt p1, Punkt p2, Punkt p3, int kolor){    
    	punkt1=p1; punkt2=p2; punkt3=p3; c=kolor;
    	}
    
    public boolean jestWewnatrz(float px, float py){ 
    	float d1, d2, d3;
      	d1 = px*(punkt1.y-punkt2.y) + py*(punkt2.x-punkt1.x) + 
        	(punkt1.x*punkt2.y-punkt1.y*punkt2.x);
      	d2 = px*(punkt2.y-punkt3.y) + py*(punkt3.x-punkt2.x) + 
        	(punkt2.x*punkt3.y-punkt2.y*punkt3.x);
      	d3 = px*(punkt3.y-punkt1.y) + py*(punkt1.x-punkt3.x) + 
        	(punkt3.x*punkt1.y-punkt3.y*punkt1.x);
      	return ((d1<=0)&&(d2<=0)&&(d3<=0)) || ((d1>=0)&&(d2>=0)&&(d3>=0));
    	}
    
    public float pole(){   
    	float a = (float)Math.sqrt( (punkt1.x-punkt2.x)*(punkt1.x-punkt2.x)+
                                    (punkt1.y-punkt2.y)*(punkt1.y-punkt2.y));
        float b = (float)Math.sqrt( (punkt2.x-punkt3.x)*(punkt2.x-punkt3.x)+
                                    (punkt2.y-punkt3.y)*(punkt2.y-punkt3.y));
        float c = (float)Math.sqrt( (punkt1.x-punkt3.x)*(punkt1.x-punkt3.x)+
                                    (punkt1.y-punkt3.y)*(punkt1.y-punkt3.y));
        float p=(a+b+c)/2;
        return (float)Math.sqrt(p*(p-a)*(p-b)*(p-c));
    	}
    
    public float obwod(){   
    	float a = (float)Math.sqrt( (punkt1.x-punkt2.x)*(punkt1.x-punkt2.x)+
                                    (punkt1.y-punkt2.y)*(punkt1.y-punkt2.y));
        float b = (float)Math.sqrt( (punkt2.x-punkt3.x)*(punkt2.x-punkt3.x)+
                                    (punkt2.y-punkt3.y)*(punkt2.y-punkt3.y));
        float c = (float)Math.sqrt( (punkt1.x-punkt3.x)*(punkt1.x-punkt3.x)+
                                    (punkt1.y-punkt3.y)*(punkt1.y-punkt3.y));
        return a+b+c;
    	}
    
    public void przesun(float dx, float dy){   
    	punkt1.przesun(dx,dy);
        punkt2.przesun(dx,dy);
        punkt3.przesun(dx,dy);
    	}
    
    public void skaluj(float s){   
    	Punkt sr1 = new Punkt((punkt1.x+punkt2.x+punkt3.x)/3,
                              (punkt1.y+punkt2.y+punkt3.y)/3);
        punkt1.x*=s; punkt1.y*=s;
        punkt2.x*=s; punkt2.y*=s;
        punkt3.x*=s; punkt3.y*=s;
        Punkt sr2 = new Punkt((punkt1.x+punkt2.x+punkt3.x)/3,
                              (punkt1.y+punkt2.y+punkt3.y)/3);
        float dx=sr1.x-sr2.x;
        float dy=sr1.y-sr2.y;
        punkt1.przesun(dx,dy);
        punkt2.przesun(dx,dy);
        punkt3.przesun(dx,dy);
    	}
    
    public String toString() { 
    	return "Trojkat {" + 
             punkt1.toStringXY() +
             punkt2.toStringXY() +
             punkt3.toStringXY() +
             "}" + wlasciwosci();
    	}
    
    public void rysuj(Graphics g){   
    	ustawKolor(g);
        g.drawLine((int)punkt1.x, (int)punkt1.y, 
                   (int)punkt2.x, (int)punkt2.y);
        g.drawLine((int)punkt2.x, (int)punkt2.y, 
                   (int)punkt3.x, (int)punkt3.y);
        g.drawLine((int)punkt3.x, (int)punkt3.y, 
                   (int)punkt1.x, (int)punkt1.y);
    	}
}




//---------------------------------------------------------------------------
// Prostok¹t
//---------------------------------------------------------------------------
/**
 * Klasa prostok¹t dziedzicz¹ca po figurze
 */

class Prostokat extends Figura{
	/**
	 * Lewy górny i prawy dolny róg
	 */
	
	private Punkt punkt1, punkt2;
     
    /**
     * Konstruktor zawieraj¹cy dodatkowy parametr - kolor
     */
      
    public Prostokat(Punkt p1, Punkt p2, int kolor){    
    	punkt1=p1; 
    	punkt2=p2;
    	c=kolor;
    	}
    
    /**
     * Tu zdarza³o sie ¿e by³o coœ nie tak, na koniec dzia³a³o, ale pewnosci nie mam
     */ 
    
    public boolean jestWewnatrz(float px, float py){ 
      	boolean a = false;
      	if((py>=punkt1.y)&&(py<=punkt2.y)&&(px<=punkt2.x)&&(px>=punkt1.x)){
      		a = true;	
      		}
    	return a;
    	}
    
    public float pole(){   
    	float a = punkt2.x - punkt1.x;
    	float b = punkt2.y - punkt1.y;
    	a *= b;
        return a;
    	}
    
    public float obwod(){   
    	float a = punkt2.x - punkt1.x;
    	float b = punkt2.y - punkt1.y;
    	a = (2*a) + (2*b);
    	
        return a;
    	}
    
    public void przesun(float dx, float dy){   
    	punkt1.przesun(dx,dy);
        punkt2.przesun(dx,dy);
    	}
    
    public void skaluj(float s){  
    	
    	Punkt sr1 = new Punkt((punkt1.x+punkt2.x)/2,
                              (punkt1.y+punkt2.y)/2);
        punkt1.x*=s; punkt1.y*=s;
        punkt2.x*=s; punkt2.y*=s;
        
        Punkt sr2 = new Punkt((punkt1.x+punkt2.x)/2,
                              (punkt1.y+punkt2.y)/2);
        float dx=sr1.x-sr2.x;
        float dy=sr1.y-sr2.y;
        punkt1.przesun(dx,dy);
        punkt2.przesun(dx,dy);
    	
    }
    
    public String toString(){ 
    	return "Prostok¹t {" + 
             punkt1.toStringXY() +
             punkt2.toStringXY() +
             "}" + wlasciwosci();
    	}
    /**
     * Rysuje prostok¹t - 4 linie 
     */
    
    public void rysuj(Graphics g){   
    	ustawKolor(g);
        g.drawLine((int)punkt1.x, (int)punkt1.y, 
                   (int)punkt2.x, (int)punkt1.y);
                   
        g.drawLine((int)punkt2.x, (int)punkt1.y, 
                   (int)punkt2.x, (int)punkt2.y);
                   
        g.drawLine((int)punkt2.x, (int)punkt2.y, 
                   (int)punkt1.x, (int)punkt2.y);
                   
        g.drawLine((int)punkt1.x, (int)punkt2.y, 
                   (int)punkt1.x, (int)punkt1.y);
                   
    }
}







//---------------------------------------------------------------------------
// Okrag
//---------------------------------------------------------------------------


class Okrag extends Figura{
	/**
	 * punkt1 - srodek okrêgu
	 */
	private Punkt punkt1;
	/**
	 * r -promien
	 */
    private float r;
    
    public Okrag(Punkt p1, float srednica, int kolor){    
    	punkt1=p1; 
    	r=srednica/2;
    	c=kolor;
    	}
    /**
     * korzysta z tw pitagorasa, liczy odleg³osc od srodka
     */
    public boolean jestWewnatrz(float px, float py){ 
		 
		float x = px-punkt1.x;
		float y = py-punkt1.y;
		float z = (float)Math.sqrt(x*x+ y*y);
		
      	if(z<r){
      		return true;
      		}
      	
    	return false;
    	}
    
    public float pole(){   
    	float pole = (float)3.14 * r * r;
        return pole;
    	}
    
    public float obwod(){   
    	float ob = 2 * (float)3.14 * r;
        return ob;
    	}
    
    public void przesun(float dx, float dy){   
    	punkt1.przesun(dx,dy);
    	}
    
    public void skaluj(float s){ 

        r*=s;
    	}
    
    public String toString(){ 
    	return "Prostok¹t {" + 
             punkt1.toStringXY() +
             " r: " + r  +
             "}" + wlasciwosci();
    	}
    
    /**
     * rysuje okr¹g pierw kopiuj¹c punkt w srodku okrêgu i przesuwaj¹c w lewy górny róg 
     */ 
    
    public void rysuj(Graphics g){   
    	ustawKolor(g);
    	Punkt rog = new Punkt(punkt1.x, punkt1.y);
       	rog.przesun(-r, -r);
       	g.drawOval((int)rog.x, (int)rog.y, (int)(2*r), (int)(2*r));
    	}
    	
}
























//---------------------------------------------------------------------------
// KLASA RYSUNEK!
//---------------------------------------------------------------------------

class Rysunek extends JPanel implements KeyListener, MouseListener, MouseMotionListener
{   /**
	* ostatnie po³o¿enie kursora
	*/
	int lastX, lastY;
	/**
	 * kolor 
	 * 0 - black
	 * 1 - green
	 * 2 - blue 
	 */
	int kolor=0;
	
	public void setColor(int k){
		kolor = k;
		}

	ArrayList<Figura> figury = new ArrayList();	


    private void dodajFigure(Figura fig){ 
    	for (Figura f : figury){ f.odznacz(); }      
    	fig.zaznacz();
     	figury.add(fig);
    	repaint();
    	}
    
    
    public void dodajPunkt(int kolor){ 
    	float x, y;
    	Random random = new Random();
    	x = random.nextFloat()*getWidth();
    	y = random.nextFloat()*getHeight();
    	dodajFigure(new Punkt(x, y, kolor));
    	}
    
        
    public void dodajTrojkat(int kolor){ 
    	float x1, y1, x2, y2, x3, y3;
    	Random random = new Random();
    	x1 = random.nextFloat()*getWidth();
    	y1 = random.nextFloat()*getHeight();
    	x2 = random.nextFloat()*getWidth();
   		y2 = random.nextFloat()*getHeight();
    	x3 = random.nextFloat()*getWidth();
   		y3 = random.nextFloat()*getHeight();
    	dodajFigure(new Trojkat(new Punkt(x1,y1),new Punkt(x2,y2), new Punkt(x3,y3), kolor));
    	}
    
    
    public void dodajProstokat(int kolor){ 
    	float x1, y1, x2, y2;
    	Random random = new Random();
    	x1 = random.nextFloat()*getWidth();
    	y1 = random.nextFloat()*getHeight();
    	x2 = random.nextFloat()*getWidth();
   		y2 = random.nextFloat()*getHeight();
    	dodajFigure(new Prostokat(new Punkt(x1,y1),new Punkt(x2,y2), kolor));
    	}
    
    public void dodajOkrag(int kolor){ 
    	float x1, y1, sr;
    	Random random = new Random();
    	x1 = random.nextFloat()*getWidth();
    	y1 = random.nextFloat()*getHeight();
    	sr = random.nextFloat()*getHeight();

    	dodajFigure(new Okrag(new Punkt(x1,y1),sr, kolor));
    	}
    
    
 
    void przesun(float dx, float dy){ 
    	for (Figura f : figury){ 
    		if (f.jestZaznaczona()) f.przesun(dx,dy); 
    		}
      	repaint();
    	}
 
    
    void skaluj(float s){ 
    	for (Figura f : figury){ 
    		if (f.jestZaznaczona()) f.skaluj(s); 
    		}
      	repaint();
    	}
    
    
    public String toString(){ 
    	String s = "Rysunek{ ";
      	for (Figura f : figury){ 
      		s += f.toString() + "\n         "; 
      		}
      	s+="}";
      	return s;
    	}
    
    
    public void paintComponent(Graphics g){   
    	super.paintComponent(g);
        for (Figura f : figury) f.rysuj(g);
    	}

     //Virtual keys (arrow keys, function keys, etc) - handled with keyPressed() listener. 
     /***obs³uga zdarzeñ przez s³uchacza zdarzeñ  KeyListener ***/
     public void keyPressed (KeyEvent evt){  
     	int krok;
        if (evt.isShiftDown()) krok = 10;
                          else krok = 1;
        switch (evt.getKeyCode()){  
        	case KeyEvent.VK_LEFT : przesun(-krok, 0); break;
            case KeyEvent.VK_RIGHT: przesun( krok, 0); break;
            case KeyEvent.VK_UP   : przesun(0, -krok); break;
            case KeyEvent.VK_DOWN : przesun(0,  krok); break;
            case KeyEvent.VK_DELETE : 
            	Iterator<Figura> i = figury.iterator();
            	while(i.hasNext()){ 
            		Figura f = i.next();
            	  	if (f.jestZaznaczona()){ i.remove(); }
            		}
            	repaint();
                break; 
         	}
     	}
 
    public void keyReleased (KeyEvent evt)
    {  } 


	//Characters (a, A, #, ...) - handled in the keyTyped() listener. 
    public void keyTyped (KeyEvent evt){ 
    	char znak=evt.getKeyChar(); //reakcja na przycisku na naciœniêcie klawisza
    	switch(znak){ 
      		case 'p': dodajPunkt(kolor); break;
        	case 't': dodajTrojkat(kolor); break;
        	case 'r': dodajProstokat(kolor); break;
        	case 'o': dodajOkrag(kolor); break;
      		case '=': skaluj(1.1f); break;
      		case '-': skaluj(0.9f); break;
      		
      		}
    	int nr=(int)znak-48; // obsluga klawiszy '0'...'9'
    	if ( nr>=0&& nr<figury.size() ){ 
      		if (evt.isAltDown()==false) for(Figura f : figury ) f.odznacz(); 
        	figury.get(nr).zaznaczOdwrotnie(); 
        	repaint();
        	} 
    	}   

    /***obs³uga zdarzeñ przez s³uchacza zdarzeñ MouseListener***/
    public void mouseClicked(MouseEvent e) 
    // Invoked when the mouse button has been clicked (pressed and released) on a component. 
    { int px = e.getX();
      int py = e.getY();
      for (Figura f : figury)
        { if (e.isAltDown()==false) f.odznacz(); 
          if (f.jestWewnatrz(px,py)) f.zaznaczOdwrotnie(); 
        }      
      repaint();           
    }
    
    void arm(){
    	for (Figura f : figury){ 
          	if (f.jestWewnatrz(lastX,lastY)) f.zaznaczOdwrotnie(); 
        	}      
      repaint();
    	}
 
    public void mouseEntered(MouseEvent e) 
    //Invoked when the mouse enters a component. 
    { }
 
    public void mouseExited(MouseEvent e) 
    //Invoked when the mouse exits a component. 
    { }
 
    public void mousePressed(MouseEvent e){ 
    	lastX = e.getX();
    	lastY = e.getY();
    	}
 
    public void mouseReleased(MouseEvent e) 
    //Invoked when a mouse button has been released on a component. 
    { }
    
    public void mouseDragged(MouseEvent e){ 
    	
    	int x = e.getX() - lastX;
    	int y = e.getY() - lastY;
    	przesun(x,y);
    	lastX = e.getX();
    	lastY = e.getY();   	
    	}
    
    public void mouseMoved(MouseEvent e){ 
    	
    	
    	}
    
    
}


public class EdytorGraficzny extends JFrame implements ActionListener 
{
    protected Rysunek rysunek;
    /**
     * zmienna przechowuje kolor
     */
    
	int kolor = 0;
	
	/**
	 * sprawdza czy byl juz armageddon, by po nim nie sprawdzic wlasciwosci, to moze byc tragiczne w skutkach
	 */
	int arm=0;
	
	
	/**
	 * funkcja kompletnie bez sensu ale ciekawie dzia³a :D
	 */
	
	void armageddon(){
		for(int j=0;j<10;j++){
			
			for(int i=0; i<1000;i++){
				rysunek.dodajTrojkat(0);
				
				}
			}
		rysunek.arm();
        arm=1;	   
      	repaint();     
		}
	
	
    private JButton przyciskPunkt   = new JButton ("Punkt");
    private JButton przyciskTrojkat = new JButton("Trojkat");
    private JButton przyciskRect = new JButton("Prostok¹t");
    private JButton przyciskOkrag = new JButton("Okr¹g");
      
    private JMenu[] menu = { new JMenu("Figury"), 
                             new JMenu("Edytuj"),
                             new JMenu("Opis Programu"),
                             new JMenu("Kolor")	
                             	 };
    private JMenuItem[] items = { new JMenuItem("Punkt"),  
                                  new JMenuItem("Trojkat"),
                                  new JMenuItem("Prostokat"),
                                  new JMenuItem("Okrag"),
                                  new JMenuItem("Wypisz wszystkie"),
                                  new JMenuItem("Przesun w lewo"),
                                  new JMenuItem("Przesun w prawo"),
                                  new JMenuItem("Przesun w góre"),
                                  new JMenuItem("Przesun w dó³"),
                                  new JMenuItem("Powieksz(=)"),
                                  new JMenuItem("Pomniej(-)"),
                                  new JMenuItem("Help"),
                                  new JMenuItem("Autor"),
                                  new JMenuItem("Czarny"),
                                  new JMenuItem("Zielony"),
                                  new JMenuItem("Niebieski"),	
                                  new JMenuItem("Wywo³aj armageddon!")	
                                  	 };
                               
  
    public EdytorGraficzny()
    { super ("Edytor graficzny");
      setSize(400,400);   
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
      for (int i = 0; i < items.length; i++)
      	items[i].addActionListener(this);
      menu[0].add(items[0]); 
      menu[0].add(items[1]);
      menu[0].add(items[2]);
      menu[0].add(items[3]); 
      menu[0].addSeparator();
      menu[0].add(items[4]);
      menu[1].add(items[5]);
      menu[1].add(items[6]); 
      menu[1].add(items[7]);
      menu[1].add(items[8]);
      menu[1].addSeparator();
      menu[1].add(items[9]);
      menu[1].add(items[10]);
      menu[2].add(items[11]);
      menu[2].add(items[12]);
      menu[3].add(items[13]);
      menu[3].add(items[14]);
      menu[3].add(items[15]);
      menu[2].add(items[16]);

      JMenuBar menubar = new JMenuBar();
      for (int i = 0; i < menu.length; i++)
      	menubar.add(menu[i]);
      setJMenuBar(menubar); 

      rysunek=new Rysunek(); 
      rysunek.addKeyListener(rysunek);
      rysunek.setFocusable(true);   
      rysunek.addMouseListener(rysunek);
      rysunek.addMouseMotionListener(rysunek);
      rysunek.setLayout(new FlowLayout());
      przyciskPunkt.addActionListener(this);
      przyciskTrojkat.addActionListener(this);
      przyciskRect.addActionListener(this);
      przyciskOkrag.addActionListener(this);
      rysunek.add(przyciskPunkt);
      rysunek.add(przyciskTrojkat);
      rysunek.add(przyciskRect);
      rysunek.add(przyciskOkrag);
      setContentPane(rysunek);
      setVisible(true);
    } 

    public void actionPerformed (ActionEvent evt)
    { Object zrodlo = evt.getSource();
      if (zrodlo==przyciskPunkt) rysunek.dodajPunkt(kolor);
      if (zrodlo==przyciskTrojkat) rysunek.dodajTrojkat(kolor);
      if (zrodlo==przyciskRect) rysunek.dodajProstokat(kolor);   
      if (zrodlo==przyciskOkrag) rysunek.dodajOkrag(kolor);
        
      if(zrodlo==items[0]) rysunek.dodajPunkt(kolor);
      if(zrodlo==items[1]) rysunek.dodajTrojkat(kolor);
      if(zrodlo==items[2]) rysunek.dodajProstokat(kolor);
      if(zrodlo==items[3]) rysunek.dodajOkrag(kolor);
      if(zrodlo==items[4]) {
      	if(arm==0){
      		JOptionPane.showMessageDialog(null, rysunek.toString());
      		}else{
      			JOptionPane.showMessageDialog(null,"Ta opcja nie dziala po armageddonie bo jest zbyt pamiêcio¿erna");
      			}
      	}
        
      if(zrodlo==items[5]) rysunek.przesun(-10, 0);
      if(zrodlo==items[6]) rysunek.przesun( 10, 0);
      if(zrodlo==items[7]) rysunek.przesun( 0, -10);
      if(zrodlo==items[8]) rysunek.przesun( 0,  10);
      if(zrodlo==items[9]) rysunek.skaluj(1.1f);
      if(zrodlo==items[10]) rysunek.skaluj(0.9f);
      if(zrodlo==items[11]){
      	JOptionPane.showMessageDialog(null,"Klawisze: \n \n kursory   przesuwanie firgur \n shift+kursory  szybkie przesuwanie firgur \n = - powiekszanie, pomniejszanie \n DEL kasowanie \n p dodanie punktu \n 	 o dodanie okrêgu \n r dodanie prostok¹ta \n t dodanie trójk¹ta \n 1-9 zaznaczanie figury o numerze \n alt + 1-9 zmiana zaznaczenia  figury o numerze  "); 
      	JOptionPane.showMessageDialog(null,"Mysz: \n \n click zaznaczanie figur \n alt + click zmiana zaznaczenia figur \n przeci¹ganie przesuwanie figur ");
      	}
      if(zrodlo==items[12]) JOptionPane.showMessageDialog(null,"Kamil Markuszewski 171016"); 
      if(zrodlo==items[13]) {
      	kolor = 0;
      	rysunek.setColor(kolor);
      	}
      if(zrodlo==items[14]) {
      	kolor = 1;
      	rysunek.setColor(kolor);
      	}
      if(zrodlo==items[15]) {
      	kolor = 2;
      	rysunek.setColor(kolor);
      	}
      if(zrodlo==items[16]) armageddon();
      
      
      rysunek.requestFocus(); //przywrocenie ogniskowania w celu przywrocenia obslugi zadarezñ pd klawiatury
      repaint();
    }

    public static void main(String[] args) 
    { EdytorGraficzny edytor = new EdytorGraficzny();
    } 
      
}
                    