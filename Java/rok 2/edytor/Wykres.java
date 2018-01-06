/**
 * @(#)Program2.java
 *
 * Program2 application
 *
 * @author Kamil Markuszewski 171016
 * @version  2009/12/20
 *
 * Robiony wieczorem w poniedzia³ek wiêc nie dokoñczony
 */
 
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.awt.geom.*;



//Nie rysuje mi wykresu, a rysowa³o tylko coœ popsu³em.


class T_Rysunek extends JPanel {
		public Vector<Integer> wektor2 =  new Vector();
	
		public void paint(Graphics arg){
		Graphics2D grafika = (Graphics2D) arg;
		int sumaIntow = 0;
		int licznik = 0;
		int tempback = 0;	
		int temp = 0;
		
		System.out.println(wektor2.size());
		
		for(int i : wektor2){
			sumaIntow = sumaIntow + i;	
			}
		
		
		
		grafika.clearRect(10, 10, 300, 300);
		
		for(int part = 0; part < wektor2.size(); part++){
			temp = (int)((360*wektor2.elementAt(part))/sumaIntow); 

   			
			switch(licznik%4){
				case 0: grafika.setPaint(Color.blue); break;
				case 1: grafika.setPaint(Color.red); break;
				case 2: grafika.setPaint(Color.green); break;
				case 3: grafika.setPaint(Color.black); break;
				}
  				

  			licznik++;	
  			grafika.fill(new Arc2D.Double(10, 10, 300, 300, tempback, temp, Arc2D.PIE));
			tempback = tempback + temp;
			tempback = tempback%360;
			
			}
		}
	
	void add(int arg){
		wektor2.add(arg);
		repaint();
		}
	
	
	
	}

  
  
  
 
public class Wykres extends JFrame implements ActionListener {
	private T_Rysunek rysunek = new T_Rysunek();
	private JPanel panel = new JPanel();
	private JPanel panel2 = new JPanel();
	private JButton B_dodaj = new JButton("Dodaj");
	private JButton B_usun = new JButton("Usuñ");
	private JTextField TF_data = new JTextField("1",10);
	private JButton B_edytuj = new JButton("Edytuj");	
	public Vector<Integer> wektor =  new Vector();
	private WidokKolekcji widok;



	
	public Wykres(){
		super ("Edytor graficzny");
      	setSize(450,650);   
      		
      	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      	
      	
		TF_data.addActionListener(this);
		
		panel2.add(TF_data);
      	
		
		//B_dodaj.setBounds(10,310,100,20);
		B_dodaj.addActionListener(this);
		
		panel2.add(B_dodaj);
		
		
		//B_usun.setBounds(10,340,100,20);
		B_usun.addActionListener(this);
		
		panel2.add(B_usun);
		
		
		
		//B_edytuj.setBounds(10,370,100,20);
		B_edytuj.addActionListener(this);
		
		panel2.add(B_edytuj);		
		widok = new WidokKolekcji(100, 200, "Dane");
    	panel2.add(widok);
		rysunek.setLayout(new GridLayout());
		
		
		
		panel.add(panel2);
		panel.add(rysunek);

			
			
		      			
		//TF_data.setBounds(10,280,100,20);

		
				
			
		
	//	rysunek.setLayout(new FlowLayout());
		
		setContentPane(panel);
      	setVisible(true);	
      		
		
		}
		
		
	
	public void actionPerformed (ActionEvent e){
		
		if (e.getSource() == B_dodaj && TF_data.getText()!= null){
			wektor.add(Integer.parseInt(TF_data.getText()));
			rysunek.add(Integer.parseInt(TF_data.getText()));
			}
		
		
		
		widok.clear();
		
		Iterator iterator = wektor.iterator();
        while(iterator.hasNext()){ 
        	widok.addItem((Integer)iterator.next()); 
        	}	
		
		}
	
	
	
		//bazuj¹c na znalezionym w internecie kodzie
	
	
	
	
	
	
	    
    public static void main(String[] args) {
    	Wykres a = new Wykres();    	
    	}
    
	
	}
    
    
    /**
     * Z poprzedniego programu 
     */
    
class WidokKolekcji extends JScrollPane{
    private JList lista;
    private DefaultListModel modelListy;

    WidokKolekcji(int szerokosc, int wysokosc, String opis){
    	super();
    	modelListy = new DefaultListModel();
    	lista = new JList(modelListy);
    	setViewportView(lista);
   		setPreferredSize(new Dimension(szerokosc, wysokosc));
    	setBorder(BorderFactory.createTitledBorder(opis));
    	}

    void clear(){
        modelListy.clear();
    	}

    void addItem(Object obj){
        modelListy.addElement(obj);
    	}
	}
