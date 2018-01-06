/*
 * Jakub Sirek 171121
 *
 * 06.12.2009 (św. Mikołaja)
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 *
 * @author swirus
 */
public class Skarby extends JFrame implements ActionListener
{

    private JLabel nameL = new JLabel("Nazwa skarbu");
    private JTextField nameField = new JTextField(10);
    private JButton addAButt = new JButton("Dodaj do A");
    private JButton addBButt = new JButton("Dodaj do B");
    private JButton delAButt = new JButton("Usun z A");
    private JButton delBButt = new JButton("Usun z B");
    private JButton showButt = new JButton("Pokaz");
    JCheckBox showAuto = new JCheckBox("(Automatycznie)");

    TreeSet<String> setA = new TreeSet();
    TreeSet<String> setB = new TreeSet();

    WidokKolekcji viewA = new WidokKolekcji(150,200,"A");
    WidokKolekcji viewB = new WidokKolekcji(150,200,"B");
    WidokKolekcji viewSum = new WidokKolekcji(150,200,"Suma (A + B)");
    WidokKolekcji viewIlocz = new WidokKolekcji(150,200,"Iloczyn (A i B)");
    WidokKolekcji viewRoz = new WidokKolekcji(150,200,"Roznica (A - B)");
    WidokKolekcji viewRozSym = new WidokKolekcji(150,200,"Roznica sym. ()");

    /**
     * konstruktor
     */
    public Skarby()
    {
        super("Skarby");
     	setSize(650,450);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     	JPanel panel= new JPanel();

        JPanel sets = new JPanel();
        sets.setLayout(new GridLayout(1,2));
        sets.add(viewA);
        sets.add(viewB);
        panel.add(sets);

        JPanel buttons = new JPanel();
        buttons.setLayout(new GridLayout(4,2));
        buttons.add(nameL);
        buttons.add(nameField);
     	addAButt.addActionListener(this);
        buttons.add(addAButt);
     	addBButt.addActionListener(this);
        buttons.add(addBButt);
     	delAButt.addActionListener(this);
        buttons.add(delAButt);
     	delBButt.addActionListener(this);
        buttons.add(delBButt);
     	showButt.addActionListener(this);
        buttons.add(showButt);
     	showAuto.addActionListener(this);
        buttons.add(showAuto);
        panel.add(buttons);

        JPanel operations = new JPanel();
        operations.setLayout(new GridLayout(1,4));
        operations.add(viewSum);
        operations.add(viewIlocz);
        operations.add(viewRoz);
        operations.add(viewRozSym);
        panel.add(operations);

        setContentPane(panel);
        show();
    }

    public void liczSume()
    {
        TreeSet<String> sum = new TreeSet();
        sum.addAll(setA);
        sum.addAll(setB);
        viewSum.clear();
        viewSum.addItems(sum);
    }

    public void liczIloczyn()
    {
        TreeSet<String> ilocz = new TreeSet();
        ilocz.addAll(setA);
        ilocz.retainAll(setB);
        viewIlocz.clear();
        viewIlocz.addItems(ilocz);
    }

    public void liczRoznice()
    {
        TreeSet<String> roz = new TreeSet();
        roz.addAll(setA);
        roz.removeAll(setB);
        viewRoz.clear();
        viewRoz.addItems(roz);
    }

    public void liczRozniceSym()
    {
        TreeSet<String> sum = new TreeSet();
        TreeSet<String> ilocz = new TreeSet();
        sum.addAll(setA);
        sum.addAll(setB);
        ilocz.addAll(setA);
        ilocz.retainAll(setB);

        TreeSet<String> sym = new TreeSet();
        sym.addAll(sum);
        sym.removeAll(ilocz);

        viewRozSym.clear();
        viewRozSym.addItems(sym);

        
    }

    public void actionPerformed (ActionEvent evt)
    {
      Object zrodlo = evt.getSource();


      if (zrodlo == addAButt)
      {
          setA.add(nameField.getText());
      }

      if (zrodlo == addBButt)
      {
          setB.add(nameField.getText());
      }

      if (zrodlo == delAButt)
      {
          setA.remove(nameField.getText());
      }

      if (zrodlo == delBButt)
      {
          setB.remove(nameField.getText());
      }

      if (zrodlo == showButt || showAuto.isSelected())
      {
          viewA.clear();
          viewA.addItems(setA);

          viewB.clear();
          viewB.addItems(setB);
          
          liczSume();
          liczIloczyn();
          liczRoznice();
          liczRozniceSym();
      }

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        // TODO code application logic here
        new Skarby();
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

    void addItems(TreeSet<String> set)
    {
        Iterator it = set.iterator();
        while (it.hasNext())
        {
            modelListy.addElement(it.next());
        }
    }
}

