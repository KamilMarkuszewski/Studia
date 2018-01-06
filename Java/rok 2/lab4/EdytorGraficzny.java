/* 
 *  Program Kolekcje
 *
 *  Autor:
 *   Data:
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;


abstract class Figura
{   private boolean zaznaczona = false;

    public boolean jestZaznaczona(){ return zaznaczona; }
    public void zaznacz(){ zaznaczona = true; };
    public void zaznacz(boolean z){ zaznaczona = z; }
    public void odznacz(){ zaznaczona = false; }
    public void zaznaczOdwrotnie(){ zaznaczona = !zaznaczona; }
   
    public abstract boolean jestWewnatrz(float px, float py);
    public boolean jestWewnatrz(int px, int py)
        { return jestWewnatrz((float)px, (float)py); }
   
    public abstract float pole();
    public abstract float obwod(); 
    public abstract void przesun(float dx, float dy);
    public abstract void skaluj(float s);
    
    protected void ustawKolor(Graphics g)    
    { if (zaznaczona) g.setColor(Color.RED); 
                 else g.setColor(Color.BLACK); 
    };

    public abstract void rysuj(Graphics g);
    
    protected String wlasciwosci()
    { String s = "  Pole: " + pole() + "  Obwod: " + obwod();
      if (jestZaznaczona()) s = s + "   [ZAZNACZONA]"; 
      return s;
    }
}


class Punkt extends Figura
{   protected float x, y;
    
    public Punkt(float px, float py){ x=px; y=py; }
    
    public boolean jestWewnatrz(float px, float py)
    { // by umozliwic zaznaczanie punktu myszka
      // miejsca odlegle nie wiecej niz 3 leza wewnatrz
      return (Math.sqrt((x-px)*(x-px) + (y-py)*(y-py))<=6);
    } 
    public float pole(){ return 0; };
    public float obwod(){ return 0; }; 
    public void przesun(float dx, float dy){ x+=dx; y+=dy; }
    public void skaluj(float s){ };
    
    protected String toStringXY(){ return "(" + x + " , " + y + ")"; }
    public String toString()
    { return "Punkt " + toStringXY() + wlasciwosci();   
    }
    public void rysuj(Graphics g)
    { ustawKolor(g);
      g.fillOval((int)(x-3),(int)(y-3), 6,6); 
    };
}


class Trojkat extends Figura
{   private Punkt punkt1, punkt2, punkt3;
    
    public Trojkat(Punkt p1, Punkt p2, Punkt p3)
    {    punkt1=p1; punkt2=p2; punkt3=p3;
    }
    
    public boolean jestWewnatrz(float px, float py)
    { float d1, d2, d3;
      d1 = px*(punkt1.y-punkt2.y) + py*(punkt2.x-punkt1.x) + 
           (punkt1.x*punkt2.y-punkt1.y*punkt2.x);
      d2 = px*(punkt2.y-punkt3.y) + py*(punkt3.x-punkt2.x) + 
           (punkt2.x*punkt3.y-punkt2.y*punkt3.x);
      d3 = px*(punkt3.y-punkt1.y) + py*(punkt1.x-punkt3.x) + 
           (punkt3.x*punkt1.y-punkt3.y*punkt1.x);
      return ((d1<=0)&&(d2<=0)&&(d3<=0)) || ((d1>=0)&&(d2>=0)&&(d3>=0));
    }
    
    public float pole()
    {   float a = (float)Math.sqrt( (punkt1.x-punkt2.x)*(punkt1.x-punkt2.x)+
                                    (punkt1.y-punkt2.y)*(punkt1.y-punkt2.y));
        float b = (float)Math.sqrt( (punkt2.x-punkt3.x)*(punkt2.x-punkt3.x)+
                                    (punkt2.y-punkt3.y)*(punkt2.y-punkt3.y));
        float c = (float)Math.sqrt( (punkt1.x-punkt3.x)*(punkt1.x-punkt3.x)+
                                    (punkt1.y-punkt3.y)*(punkt1.y-punkt3.y));
        float p=(a+b+c)/2;
        return (float)Math.sqrt(p*(p-a)*(p-b)*(p-c));
    }
    
    public float obwod()
    {   float a = (float)Math.sqrt( (punkt1.x-punkt2.x)*(punkt1.x-punkt2.x)+
                                    (punkt1.y-punkt2.y)*(punkt1.y-punkt2.y));
        float b = (float)Math.sqrt( (punkt2.x-punkt3.x)*(punkt2.x-punkt3.x)+
                                    (punkt2.y-punkt3.y)*(punkt2.y-punkt3.y));
        float c = (float)Math.sqrt( (punkt1.x-punkt3.x)*(punkt1.x-punkt3.x)+
                                    (punkt1.y-punkt3.y)*(punkt1.y-punkt3.y));
        return a+b+c;
    }
    
    public void przesun(float dx, float dy)
    {   punkt1.przesun(dx,dy);
        punkt2.przesun(dx,dy);
        punkt3.przesun(dx,dy);
    }
    
    public void skaluj(float s)
    {   Punkt sr1 = new Punkt((punkt1.x+punkt2.x+punkt3.x)/3,
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
    
    public String toString()
    { return "Trojkat {" + 
             punkt1.toStringXY() +
             punkt2.toStringXY() +
             punkt3.toStringXY() +
             "}" + wlasciwosci();
    }
    
    public void rysuj(Graphics g)
    {   ustawKolor(g);
        g.drawLine((int)punkt1.x, (int)punkt1.y, 
                   (int)punkt2.x, (int)punkt2.y);
        g.drawLine((int)punkt2.x, (int)punkt2.y, 
                   (int)punkt3.x, (int)punkt3.y);
        g.drawLine((int)punkt3.x, (int)punkt3.y, 
                   (int)punkt1.x, (int)punkt1.y);
    }
}





class Rysunek extends JPanel implements KeyListener, MouseListener
{   

	ArrayList<Figura> figury = new ArrayList();	


    private void dodajFigure(Figura fig)
    { for (Figura f : figury){ f.odznacz(); }      
      fig.zaznacz();
      figury.add(fig);
      repaint();
    }
    
    
    public void dodajPunkt()
    { float x, y;
      Random random = new Random();
      x = random.nextFloat()*getWidth();
      y = random.nextFloat()*getHeight();
      dodajFigure(new Punkt(x, y));
    }
    
        
    public void dodajTrojkat()
    { float x1, y1, x2, y2, x3, y3;
      Random random = new Random();
      x1 = random.nextFloat()*getWidth();
      y1 = random.nextFloat()*getHeight();
      x2 = random.nextFloat()*getWidth();
      y2 = random.nextFloat()*getHeight();
      x3 = random.nextFloat()*getWidth();
      y3 = random.nextFloat()*getHeight();
      dodajFigure(new Trojkat(new Punkt(x1,y1),new Punkt(x2,y2), new Punkt(x3,y3)));
    }
    
 
    void przesun(float dx, float dy)
    { for (Figura f : figury)
    	{ if (f.jestZaznaczona()) f.przesun(dx,dy); 
    	}
      repaint();
    }
 
    
    void skaluj(float s)
    { for (Figura f : figury)
    	{ if (f.jestZaznaczona()) f.skaluj(s); 
    	}
      repaint();
    }
    
    
    public String toString()
    { String s = "Rysunek{ ";
      for (Figura f : figury)
      	{ s += f.toString() + "\n         "; 
      	}
      s+="}";
      return s;
    }
    
    
    public void paintComponent(Graphics g)
    {   super.paintComponent(g);
        for (Figura f : figury) f.rysuj(g);
    }

     
     /***obs³uga zdarzeñ przez s³uchacza zdarzeñ  KeyListener ***/
     public void keyPressed (KeyEvent evt)
     //Virtual keys (arrow keys, function keys, etc) - handled with keyPressed() listener. 
     {  int krok;
        if (evt.isShiftDown()) krok = 10;
                          else krok = 1;
        switch (evt.getKeyCode()) 
         {  case KeyEvent.VK_LEFT : przesun(-krok, 0); break;
            case KeyEvent.VK_RIGHT: przesun( krok, 0); break;
            case KeyEvent.VK_UP   : przesun(0, -krok); break;
            case KeyEvent.VK_DOWN : przesun(0,  krok); break;
            case KeyEvent.VK_DELETE : 
            	Iterator<Figura> i = figury.iterator();
            	while(i.hasNext())
            		{ Figura f = i.next();
            	  	  if (f.jestZaznaczona()){ i.remove(); }
            		}
            	repaint();
                break; 
         }
     }
 
    public void keyReleased (KeyEvent evt)
    {  } 

    public void keyTyped (KeyEvent evt)
    //Characters (a, A, #, ...) - handled in the keyTyped() listener. 
    { 
      char znak=evt.getKeyChar(); //reakcja na przycisku na naciœniêcie klawisza
      switch(znak)
      { case 'p': dodajPunkt(); break;
        case 't': dodajTrojkat(); break;
      }
      int nr=(int)znak-48; // obsluga klawiszy '0'...'9'
      if ( nr>=0&& nr<figury.size() )
        { if (evt.isAltDown()==false) for(Figura f : figury ) f.odznacz(); 
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
 
    public void mouseEntered(MouseEvent e) 
    //Invoked when the mouse enters a component. 
    { }
 
    public void mouseExited(MouseEvent e) 
    //Invoked when the mouse exits a component. 
    { }
 
    public void mousePressed(MouseEvent e) 
    //Invoked when a mouse button has been pressed on a component. 
    { }
 
    public void mouseReleased(MouseEvent e) 
    //Invoked when a mouse button has been released on a component. 
    { }
}


public class EdytorGraficzny extends JFrame implements ActionListener 
{
    protected Rysunek rysunek;

    private JButton przyciskPunkt   = new JButton ("Punkt");
    private JButton przyciskTrojkat = new JButton("Trojkat");
      
    private JMenu[] menu = { new JMenu("Figury"), 
                             new JMenu("Edytuj") };
    private JMenuItem[] items = { new JMenuItem("Punkt"),  
                                  new JMenuItem("Trojkat"),
                                  new JMenuItem("Wypisz wszystkie"),
                                  new JMenuItem("Przesun w gore"),
                                  new JMenuItem("Przesun w dol"),
                                  new JMenuItem("Przesun w lewo"),
                                  new JMenuItem("Przesun w prawo") };
                               
  
    public EdytorGraficzny()
    { super ("Edytor graficzny");
      setSize(400,400);   
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
      for (int i = 0; i < items.length; i++)
      	items[i].addActionListener(this);
      menu[0].add(items[0]); 
      menu[0].add(items[1]);
      menu[0].addSeparator();
      menu[0].add(items[2]);
      menu[1].add(items[3]); 
      menu[1].add(items[4]);
      menu[1].add(items[5]);
      menu[1].add(items[6]); 

      JMenuBar menubar = new JMenuBar();
      for (int i = 0; i < menu.length; i++)
      	menubar.add(menu[i]);
      setJMenuBar(menubar); 

      rysunek=new Rysunek(); 
      rysunek.addKeyListener(rysunek);
      rysunek.setFocusable(true);   
      rysunek.addMouseListener(rysunek);
      rysunek.setLayout(new FlowLayout());
      przyciskPunkt.addActionListener(this);
      przyciskTrojkat.addActionListener(this);
      rysunek.add(przyciskPunkt);
      rysunek.add(przyciskTrojkat);
      setContentPane(rysunek);
      setVisible(true);
    } 

    public void actionPerformed (ActionEvent evt)
    { Object zrodlo = evt.getSource();
      if (zrodlo==przyciskPunkt) rysunek.dodajPunkt();
      if (zrodlo==przyciskTrojkat) rysunek.dodajTrojkat();
        
      if(zrodlo==items[0]) rysunek.dodajPunkt();
      if(zrodlo==items[1]) rysunek.dodajTrojkat();
      if(zrodlo==items[2]) JOptionPane.showMessageDialog(null, rysunek.toString());
        
      if(zrodlo==items[3]) rysunek.przesun(-10, 0);
      if(zrodlo==items[4]) rysunek.przesun( 10, 0);
      if(zrodlo==items[5]) rysunek.przesun( 0, -10);
      if(zrodlo==items[6]) rysunek.przesun( 0,  10);
        
      rysunek.requestFocus(); //przywrocenie ogniskowania w celu przywrocenia obslugi zadarezñ pd klawiatury
      repaint();
    }

    public static void main(String[] args) 
    { EdytorGraficzny edytor = new EdytorGraficzny();
    } 
      
}
                    