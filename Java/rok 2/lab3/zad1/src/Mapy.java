/* 
 *  Program Mapy
 *
 *  Autor: Jakub Sirek 171121
 *   Data: 6.12.2009 (św. Miłokaja)
 */
import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;
 
class Mapy extends JFrame implements ActionListener                        
{
    JLabel etykietaK= new JLabel ("Podaj klucz:");
    JTextField wierszK = new JTextField(10);
    JLabel etykietaV = new JLabel ("Podaj wartosc:");
    JTextField wierszV = new JTextField(10);
    JButton zapisz=new JButton("Zapisz");
    JButton usun=new JButton("Usun");
    JButton wyczysc=new JButton("Wyczysc");
    JCheckBox wyswietlAuto = new JCheckBox("Wyswietl automatycznie");
    JButton wyswietl=new JButton("Wyswietl");
   
    
    HashMap <String,String> hashMap = new HashMap();
    TreeMap <String,String> treeMap = new TreeMap();
    
    WidokMapy widokTreeMap;
    WidokMapy widokHashMap;
    
    
    Mapy()
    {	super("MOJE MAPY");
     	setSize(550,250);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	JPanel panel= new JPanel();
     	panel.add(etykietaK);        			
     	panel.add(wierszK);
        panel.add(etykietaV);                    
        panel.add(wierszV); 
     	zapisz.addActionListener(this);     	
     	panel.add(zapisz);
     	usun.addActionListener(this);     	
     	panel.add(usun);
     	wyczysc.addActionListener(this);    
     	panel.add(wyczysc);
        wyswietlAuto.addActionListener(this);    
        panel.add(wyswietlAuto);
     	wyswietl.addActionListener(this);    
     	panel.add(wyswietl);
     	
        widokHashMap = new WidokMapy(150, 150, "hashMap:");
        panel.add(widokHashMap);

        widokTreeMap = new WidokMapy(150, 150, "treeMap:");
        panel.add(widokTreeMap);
        
     	setContentPane(panel);  
     	setVisible(true);
    }
 
 public void actionPerformed (ActionEvent evt)
    { String sk,sv;
      Object zrodlo = evt.getSource();
 
      if (zrodlo==zapisz)
        { sk=wierszK.getText();
          sv=wierszV.getText();
          if (!sk.equals(""))
       	    {
              hashMap.put(sk, sv);
              treeMap.put(sk, sv);
            }       
        } else
      if (zrodlo==wyczysc)
        { 
          hashMap.clear();
          treeMap.clear();
        } else
      if (zrodlo==usun)  
        {
          sk=wierszK.getText();
          hashMap.remove(sk);
          treeMap.remove(sk);
        }
            
      if((zrodlo==wyswietl) || (wyswietlAuto.isSelected()) )   
        { Iterator iterator;
            
          widokHashMap.clear();
          iterator = hashMap.keySet().iterator();
          while(iterator.hasNext())
            { sk=(String)iterator.next();
              sv = hashMap.get(sk);
              widokHashMap.addRow(sk, sv); 
            }

          widokTreeMap.clear();
          iterator = treeMap.keySet().iterator();
          while(iterator.hasNext())
            { sk=(String)iterator.next();
              sv = treeMap.get(sk);
              widokTreeMap.addRow(sk, sv);
            }
            
        }     
    }
   
    static  public void main(String arg[])
    { new  Mapy();      
    } 
 }
  

class WidokMapy extends JScrollPane
{
    private JTable tabela;
    private DefaultTableModel modelTabeli;
    
    WidokMapy(int szerokosc, int wysokosc, String opis)
    { super();
      String [] kolumny = {"klucz", "wartosc"};
      modelTabeli = new DefaultTableModel(kolumny, 0);
      tabela = new JTable(modelTabeli);
      setViewportView(tabela);
      setPreferredSize(new Dimension(szerokosc, wysokosc));
      setBorder(BorderFactory.createTitledBorder(opis));
    }
    
    void clear()
    { modelTabeli.setRowCount(0);
    }
    
    void addRow(String sk, String sv)
    { Object[] rowData = new Object[2];
      rowData[0] = sk;
      rowData[1] = sv;
      modelTabeli.addRow(rowData);
    }
}