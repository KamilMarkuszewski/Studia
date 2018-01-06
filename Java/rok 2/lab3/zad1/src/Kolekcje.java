/**
 *  Program Kolekcje
 *
 *  Autor: Jakub Sirek
 *   Data: 6.12.2009 (św, Mikołaja)
 */

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

class Kolekcje extends JFrame implements ActionListener
{
    JLabel etykieta= new JLabel ("Podaj tytul:");
    JTextField wiersz = new JTextField(10);
    JButton zapisz=new JButton("Zapisz");
    JButton usun=new JButton("Usun");
    JButton wyczysc=new JButton("Wyczysc");
    JCheckBox wyswietlAuto = new JCheckBox("Wyswietl automatycznie");
    JButton wyswietl=new JButton("Wyswietl");


    Vector<String> vector = new Vector();
    ArrayList<String> arrList = new ArrayList();
    LinkedList<String> lkdList = new LinkedList();
    HashSet<String> hshSet = new HashSet();
    TreeSet<String> trSet = new TreeSet();


    WidokKolekcji widokVector;
    WidokKolekcji widokArrList;
    WidokKolekcji widokLkdList;
    WidokKolekcji widokHshSet;
    WidokKolekcji widokTrSet;


    Kolekcje()
    {
        super("MOJE KOLEKCJE");
     	setSize(550,380);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	JPanel panel= new JPanel();
     	panel.add(etykieta);
     	panel.add(wiersz);
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

        widokVector = new WidokKolekcji(125, 150, "vector:");
        panel.add(widokVector);

        widokArrList = new WidokKolekcji(125, 150, "arrey list:");
        panel.add(widokArrList);

        widokLkdList = new WidokKolekcji(125, 150, "linked list:");
        panel.add(widokLkdList);

        widokHshSet = new WidokKolekcji(125, 150, "hash set:");
        panel.add(widokHshSet);

        widokTrSet = new WidokKolekcji(125, 150, "tree set:");
        panel.add(widokTrSet);


     	setContentPane(panel);
     	setVisible(true);
    }

 public void actionPerformed (ActionEvent evt)
    {
      String s;
      Object zrodlo = evt.getSource();

      if (zrodlo==zapisz)
        {
          s=wiersz.getText();
          if (!s.equals(""))
       	    {
              vector.add(s);
              arrList.add(s);
              lkdList.add(s);
              hshSet.add(s);
              trSet.add(s);
            }
        }
      else  if (zrodlo==wyczysc)
       {
          vector.clear();
          arrList.clear();
          lkdList.clear();
          hshSet.clear();
          trSet.clear();

       }
      else  if (zrodlo==usun)
        {
          s=wiersz.getText();
          
          vector.remove(s);
          vector.trimToSize();

          arrList.remove(s);
          arrList.trimToSize();
          
          lkdList.remove(s);

          hshSet.remove(s);

          trSet.remove(s);
        }

      if((zrodlo==wyswietl) || (wyswietlAuto.isSelected()) )
        {
          Iterator iterator;

          widokVector.clear();
          iterator = vector.iterator();
          while(iterator.hasNext())
          {
              s=(String)iterator.next();
              widokVector.addItem(s);
          }

          widokArrList.clear();
          iterator = arrList.iterator();
          while(iterator.hasNext())
          {
              s=(String)iterator.next();
              widokArrList.addItem(s);
          }

          widokLkdList.clear();
          iterator = lkdList.iterator();
          while(iterator.hasNext())
          {
              s=(String)iterator.next();
              widokLkdList.addItem(s);
          }

          widokHshSet.clear();
          iterator = hshSet.iterator();
          while(iterator.hasNext())
          {
              s=(String)iterator.next();
              widokHshSet.addItem(s);
          }

          widokTrSet.clear();
          iterator = trSet.iterator();
          while(iterator.hasNext())
          {
              s=(String)iterator.next();
              widokTrSet.addItem(s);
          }


        }
    }

    static  public void main(String arg[])
    { new  Kolekcje();
    }
 }



class WidokKolekcji extends JScrollPane
{
    private JList lista;
    private DefaultListModel modelListy;

    WidokKolekcji(int szerokosc, int wysokosc, String opis)
    {
       super();
      modelListy = new DefaultListModel();
      lista = new JList(modelListy);
      setViewportView(lista);
      setPreferredSize(new Dimension(szerokosc, wysokosc));
      setBorder(BorderFactory.createTitledBorder(opis));
    }

    void clear()
    {
        modelListy.clear();
    }

    void addItem(Object obj)
    {
        modelListy.addElement(obj);
    }
}

