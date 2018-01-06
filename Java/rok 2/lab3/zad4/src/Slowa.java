/*
 * Jakub Sirek
 * 06.12.2009 (św. Mikołaj)
 */

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

/**
 *
 * @author swirus
 */
public class Slowa extends JFrame implements ActionListener
{

    JButton loadFileButt = new JButton("Wczytaj plik");

    //mapa alfabetyczna
    Map<String, Integer> alfMap = new TreeMap();

    WidokMapy viewAlf = new WidokMapy(300,200,"Słowa (alfabetycznie)");
    WidokMapy viewNr = new WidokMapy(300,200,"Słowa (ilosciowo)");

    final JFileChooser openF = new JFileChooser();

    public Slowa()
    {
        super("Licznik slow");
     	setSize(650,450);
     	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        loadFileButt.addActionListener(this);

        //wyglad
        setLayout(new GridBagLayout());

        GridBagConstraints c = new GridBagConstraints();

        c.gridx = 0;
        c.gridy = 0;
        loadFileButt.setMaximumSize(new Dimension(125,100));
        
        JPanel views = new JPanel();
        views.setLayout(new GridLayout(1,2));
        add(loadFileButt,c);
        views.add(viewAlf);
        views.add(viewNr);

        c.fill = GridBagConstraints.BOTH;
        c.gridy = 1;
        add(views,c);

        show();
    }

    public void actionPerformed (ActionEvent evt)
    {
        Object source = evt.getSource();

        if (source == loadFileButt)
        {
            int val = openF.showOpenDialog(this);
            if (val == JFileChooser.APPROVE_OPTION)
            {
                read(openF.getSelectedFile());

                Iterator it;
                String key;
                String value;

                viewAlf.clear();
                it = alfMap.keySet().iterator();
                while(it.hasNext())
                {
                    key=(String)it.next();
                    value = alfMap.get(key).toString();
                    viewAlf.addRow(key, value);
                }

                TreeSet<Integer> nrs = new TreeSet();
                nrs.addAll(alfMap.values());
                TreeSet<String> words = new TreeSet();
                words.addAll(alfMap.keySet());

                viewNr.clear();

                Iterator wIt;
                it = nrs.descendingIterator();
                String word;
                Integer nr;
                while(it.hasNext())
                {
                    wIt = words.iterator();
                    nr = (Integer) it.next();
                    while(wIt.hasNext())
                    {
                        word = wIt.next().toString();
                        if (alfMap.get(word) == nr)
                        {
                            viewNr.addRow(word, nr.toString());
                        }
                    }
                }
            }
        }
    }

    /**
     * Liczy wystapienia slow w danym pliku (zapisuje je do mapy)
     *
     * @param filePath sciezka do pliku
     */
    private void read(File file)
    {
        System.out.printf("HAHAH \n");
        try
        {
            System.out.printf("HAHAH\n");
            Scanner scn = new Scanner(file);
            System.out.printf("HAHAH\n");
            while (scn.hasNext())
            {
                System.out.printf("HAHAH\n");
                String word = scn.next();
                System.out.printf(word);
                if (alfMap.containsKey(word)) 
                {
                    Integer val = alfMap.get(word) +1;
                    alfMap.put(word,val);
                }
                else
                {
                    alfMap.put(word,1);
                }

            }
        }
        catch (FileNotFoundException ex)
        {
            JOptionPane.showMessageDialog(null,"Plik nie istnieje","Blad pliku", JOptionPane.ERROR_MESSAGE);
        }

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new Slowa();
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
      setMinimumSize(new Dimension(szerokosc, wysokosc));
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