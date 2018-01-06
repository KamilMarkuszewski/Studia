import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;








//---------------------------------------------------------------------------------------------
//Figura
//---------------------------------------------------------------------------------------------

abstract class Figura{
	private boolean zaznaczona = false;
	
	public boolean jestZaznaczona(){return zaznaczona;}
	public void zaznacz(){zaznaczona=true;}
	public void zaznacz(boolean z){zaznaczona = z;}
	public void odznacz(){zaznaczona = false;}
	public void zaznaczOdwrotnie(){zaznaczona= !zaznaczona;}
	
	public abstract boolean jestWewnatrz(float px, float py);
	public boolean jestWewnatrz(int px, int py){return jestWewnatrz((float)px, (float)py);}
	
	public abstract float pole();
	public abstract float obwod();
	public abstract void przesun(int dx, int dy);
	
	public abstract void skaluj(float skala);
	
	public void ustawKolor(Graphics g){
		if(jestZaznaczona()){
			g.setColor(Color.RED);
			}
			else{
				g.setColor(Color.BLUE);
				}
		
		}
	public abstract void rysuj(Graphics g);
	
	protected String wlasciwosci(){
		String s = "Pole: " + pole() + " Obwod: " + obwod();
		return s;		
		}
	
	
	
	}

//---------------------------------------------------------------------------------------------
//Punkt
//---------------------------------------------------------------------------------------------

class Punkt extends Figura{
	float x, y;
	
	public Punkt(float dx, float dy){x=dx; y=dy;}
	
	public boolean jestWewnatrz(float px, float py){
		return ((((px-x)*(px-x)+(py-y)*(py-y)))<=8);
		}
		
	public float pole(){return 0;}
	 
	public float obwod(){return 0;}
	
	public void przesun(int dx, int dy){
		x-=dx;
		y-=dy;		
		}
	public void skaluj(float skala){}
	
	public String toString(){
		String s = "X: " + x + " Y: " + y + wlasciwosci();
		return s;
		}
		
	public void rysuj(Graphics g){
		ustawKolor(g);
		g.fillOval((int)(x-3), (int)(y-3), 6, 6);
		}
	
	
	
	
	}


//---------------------------------------------------------------------------------------------
//Okrag
//---------------------------------------------------------------------------------------------

class Okrag extends Figura{
	float x, y;
	float r;
	
	public Okrag(float dx, float dy, float r){x=dx; y=dy; this.r=r;}
	
	public boolean jestWewnatrz(float px, float py){
		return ((((px-x)*(px-x)+(py-y)*(py-y)))<=r*r);
		}
		
	public float pole(){return (float)(3.1*r*r);}
	 
	public float obwod(){return (float)(2*3.1*r);}
	
	public void przesun(int dx, int dy){
		x+=dx;
		y+=dy;		
		}
	public void skaluj(float skala){
		
		}
	public String toString(){
		String s = "X: " + x + " Y: " + y + wlasciwosci();
		return 	s;	
		}
	
	public void rysuj(Graphics g){
		ustawKolor(g);
		float rx = x - r;
		float ry = y - r;
		
		g.drawOval((int)rx,(int)ry,(int)(2*r),(int)(2*r));
		}
	}
	
	
	
	
	




//---------------------------------------------------------------------------------------------
//Rysunek
//---------------------------------------------------------------------------------------------

class Rysunek extends JPanel implements KeyListener, MouseListener, MouseMotionListener{
	
	ArrayList<Figura> figury= new ArrayList();
	
	float lastX, lastY;
	
	
	public void dodajFigure(Figura f){
		figury.add(f);
		repaint();		
		}
		
	public void dodajPunkt(){
		Random rand = new Random();
		float x = rand.nextFloat()*getWidth();
		
		float y = rand.nextFloat()*getHeight();
		
		dodajFigure(new Punkt(x,y));		
		}
	
	public void dodajOkrag(){
		Random rand = new Random();
		float x = rand.nextFloat()*getWidth();
		
		float y = rand.nextFloat()*getHeight();
		
		float r = rand.nextFloat()*50;
		
		dodajFigure(new Okrag(x,y, r));		
		}
	
	
	public void przesun(int dx,int  dy){
		for(Figura f: figury){
			if(f.jestZaznaczona()){
				f.przesun(dx,dy);
				}
			}
		
		}
	
	
	
	public void keyReleased(KeyEvent evt){
		
		}
	
	public void keyPressed(KeyEvent evt){
		
		
		switch(evt.getKeyCode()){
			
			case KeyEvent.VK_DOWN: przesun(0, 10);
			case KeyEvent.VK_LEFT: przesun(-10, 0);
			case KeyEvent.VK_RIGHT: przesun(10, 0);
			case KeyEvent.VK_UP: przesun(0, -10);
			
			}
		repaint();
		}

	public void keyTyped(KeyEvent evt){
		char znak = evt.getKeyChar();
		
		switch(znak){
			case 'p': dodajPunkt(); break;
			case 'P': dodajPunkt(); break;
			case 'O': dodajOkrag(); break;
			case 'o': dodajOkrag(); break;
			}	
		}



	public void mouseExited(MouseEvent evt){
		
		}
	
	public void mouseTyped(MouseEvent evt){
		
		}
	
	public void mouseReleased(MouseEvent evt){
		
		}
	
	public void mousePressed(MouseEvent evt){
		lastX=evt.getX();
		lastY=evt.getY();
		
		}
	
	public void mouseEntered(MouseEvent evt){
		
		}
	
	public void mouseClicked(MouseEvent evt){
		for(Figura f: figury){
			if(f.jestWewnatrz(evt.getX(), evt.getY())){
				f.zaznaczOdwrotnie();
				}
			}
		repaint();
		}
	
	public void mouseMoved(MouseEvent evt){
		
		}
	
	public void mouseDragged(MouseEvent evt){
		float x = evt.getX()-lastX;
		
		float y = evt.getY()-lastY;
		
		przesun((int)x,(int)y);
		
		lastX=evt.getX();
		lastY=evt.getY();
		repaint();
		}
	
	
	
	
	
	
	
	
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		for(Figura f:figury){
			f.rysuj(g);
			}
		
		}
	
	
	
	}




//---------------------------------------------------------------------------------------------
//Edytor
//---------------------------------------------------------------------------------------------


public class edytor extends JFrame implements ActionListener{
	
	Rysunek rys=new Rysunek();
	
	JButton punkt = new JButton("Punkt");
	
	JButton okrag = new JButton("Okr¹g");

	JMenu menu[]= {new JMenu("menu1"), new JMenu("menu2")};
	
	JMenuItem item[] = {new JMenuItem("Autor"), new JMenuItem("+")};
	
	JMenuBar bar = new JMenuBar();
	
	public edytor(){
		super("Edytor");
		setSize(400,400);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		rys.setFocusable(true);
		setVisible(true);
		rys.setVisible(true);
		menu[0].add(item[0]);
		menu[1].add(item[1]);
		
		
		punkt.addActionListener(this);
		okrag.addActionListener(this);
		
		rys.add(punkt);
		
		rys.add(okrag);
		rys.addMouseListener(rys);
		rys.addMouseMotionListener(rys);
		rys.addKeyListener(rys);
		
		for(int i=0;i<menu.length;i++){
			bar.add(menu[i]);
			}
		
		
		setJMenuBar(bar);
		setContentPane(rys);
		
		
		
		
		}
	
	
	public void actionPerformed(ActionEvent evt){
		
		Object source = evt.getSource();
		
		if(source==okrag){
			rys.dodajOkrag();
			}
		if(source==punkt){
			rys.dodajPunkt();
			}
		
		
		rys.requestFocus();
		}
	
	public static void main(String[] args){
		new edytor();
		
		}
	
	
	}