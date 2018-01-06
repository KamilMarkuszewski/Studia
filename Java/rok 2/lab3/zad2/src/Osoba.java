/*
 *
 * Autor Jakub Sirek
 * Wersja: 06.12.2009r (św. Mikołaja)
 */

import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

/**
 * 
 * @author Jakub Sirek
 * @version  06.12.2009r (św. Mikołaja)
 */
public class Osoba implements Comparable
{
    private String name;
    private String surname;

    public Osoba()
    {
        name = "";
        surname = "";
    }

    public Osoba(String _name, String _surname)
    {
        name = _name;
        surname = _surname;
    }

    public String toString()
    {
        return name + " " +surname;
    }

    public boolean equals(Object os)
    {
        if (name.equals(Osoba.class.cast(os).name) && surname.equals(Osoba.class.cast(os).surname))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public int hashCode()
    {
        return toString().hashCode();
        //taki kod wydaje sie lepszy niż np. name.hashCode()*surname.hashCode()
        //dlatego ze mozna znalesc rozne pary liczb, ktore mnozone przez siebie dadza ten sam wynik
        // tak wiedz zamiast polegac na pomnożeniu dwuch hashCode'ów String'a
        //polegam tylko na jednym, co (o ile jest on w miarę dobrze zaimplementowany w String'u) powinno dac lepsze wyniki
    }

    public int compareTo(Object os)
    {
        int res = surname.compareTo(Osoba.class.cast(os).surname);
        if (res!=0)
        {
            return res;
        }
        else
        {
            res = name.compareTo(Osoba.class.cast(os).name);
            return res;
        }
    }

    public static void main(String[] args)
    {
        new Okienko();
    }

}


class Okienko extends JFrame implements ActionListener
{
    JLabel nameLab= new JLabel ("Podaj imie:");
    JTextField nameField = new JTextField(10);

    JLabel surnameLab= new JLabel ("Podaj nazwisko:");
    JTextField surnameField = new JTextField(10);

    JButton zapisz=new JButton("Zapisz");
    JButton usun=new JButton("Usun");
    JButton wyczysc=new JButton("Wyczysc");
    JCheckBox wyswietlAuto = new JCheckBox("Wyswietl automatycznie");
    JButton wyswietl=new JButton("Wyswietl");


    Vector<Osoba> vector = new Vector();
    ArrayList<Osoba> arrList = new ArrayList();
    LinkedList<Osoba> lkdList = new LinkedList();
    HashSet<Osoba> hshSet = new HashSet();
    TreeSet<Osoba> trSet = new TreeSet();


    WidokKolekcji widokVector;
    WidokKolekcji widokArrList;
    WidokKolekcji widokLkdList;
    WidokKolekcji widokHshSet;
    WidokKolekcji widokTrSet;


    Okienko()
    {
        super("MOJE KOLEKCJE");
     	setSize(550,380);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	JPanel panel= new JPanel();
     	panel.add(nameLab);
     	panel.add(nameField);
     	panel.add(surnameLab);
     	panel.add(surnameField);
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
      Osoba os;
      Object zrodlo = evt.getSource();

      if (zrodlo==zapisz)
        {
          os = new Osoba(nameField.getText(), surnameField.getText());
          if (!os.equals(new Osoba()))
       	    {
              vector.add(os);
              arrList.add(os);
              lkdList.add(os);
              hshSet.add(os);
              trSet.add(os);
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

          os = new Osoba(nameField.getText(), surnameField.getText());

          vector.remove(os);
          vector.trimToSize();

          arrList.remove(os);
          arrList.trimToSize();

          lkdList.remove(os);

          hshSet.remove(os);

          trSet.remove(os);
        }

      if((zrodlo==wyswietl) || (wyswietlAuto.isSelected()) )
        {
          Iterator iterator;

          widokVector.clear();
          iterator = vector.iterator();
          while(iterator.hasNext())
          {
              os=(Osoba)iterator.next();
              widokVector.addItem(os);
          }

          widokArrList.clear();
          iterator = arrList.iterator();
          while(iterator.hasNext())
          {
              os=(Osoba)iterator.next();
              widokArrList.addItem(os);
          }

          widokLkdList.clear();
          iterator = lkdList.iterator();
          while(iterator.hasNext())
          {
              os=(Osoba)iterator.next();
              widokLkdList.addItem(os);
          }

          widokHshSet.clear();
          iterator = hshSet.iterator();
          while(iterator.hasNext())
          {
              os=(Osoba)iterator.next();
              widokHshSet.addItem(os);
          }

          widokTrSet.clear();
          iterator = trSet.iterator();
          while(iterator.hasNext())
          {
              os=(Osoba)iterator.next();
              widokTrSet.addItem(os);
          }


        }
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
