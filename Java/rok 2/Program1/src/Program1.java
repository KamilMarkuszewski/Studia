		/**
  *
  * Jakiœ txt dokumentacji 
  * @author Kamil M
  *
  *
  */
 
 
 import java.awt.*;
 import java.io.*;
 import javax.swing.JOptionPane;
 import java.awt.event.*;













 
 //---------------------------------------------------------------
 // MAIN!
 //---------------------------------------------------------------
 
 
 /*
  * G³ówna klasa programu
  * Menu etc. etc.
  **/
 
 
public class Program1 extends Frame implements ActionListener{
    
    List lista_menu;
    Button przycisk1;
    TextArea pole_tekstowe;
    
    public Program1(){


          
          



		//Tego nie umiem, w³aœnie siê uczê ;> 
				
		
		super("Program 1"); 


		String pom = "";
		String a = " aaa bbb ccc dd z";
		int b = a.length();
		System.out.println(b);
		for(int i=0;i<b;i++){
			
			if(a.charAt(i)== '\u0020'){
				//wrzucam do listy
				System.out.println(pom);
				pom = "";
				}else{
					pom = pom + a.charAt(i);
					}
			
			}
		
		

		
				setSize(800,600); 

		setVisible(true); 
		setLayout(null); // przez to sie sporo namêczy³em :<

		
		
	
		przycisk1 = new Button("Ok");
		przycisk1.setBounds(10, 200, 100, 20);
		przycisk1.addActionListener(this);
		add(przycisk1);
						
				
				
				

		
		pole_tekstowe = new TextArea();
		pole_tekstowe.setBounds(140, 50, 600, 500 );
		add(pole_tekstowe);
	
		
		lista_menu = new List();
		lista_menu.setBounds(10, 50, 100, 130); 
		lista_menu.add("Zadanie 1");
		lista_menu.add("Zadanie 2");
		lista_menu.add("Zadanie 3");
		lista_menu.add("Zadanie 4");
		lista_menu.add("Zadanie 5");
		lista_menu.add("Zadanie 6");
		lista_menu.add("Zadanie 7");
		lista_menu.add("Zadanie 8");
		lista_menu.add("Zadanie 9");
		lista_menu.add("Wyjscie");
		add(lista_menu);
		

		repaint(); // odœwie¿enie widoku
		
		
		}
		
		
    // akcje pozycji listy
    
    
	public void actionPerformed(ActionEvent e){

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 0){ 
			zad1.zad1metoda(pole_tekstowe); 
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 1){
			zad2.zad2metoda(pole_tekstowe);
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 2){
			zad3.zad3metoda(pole_tekstowe);
			}
			
		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 3){ 
			zad4.zad4metoda(pole_tekstowe); 
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 4){
			zad5.zad5metoda(pole_tekstowe);
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 5){
			zad6.zad6metoda(pole_tekstowe);
			}
			
		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 6){
			zad7.zad7metoda(pole_tekstowe);
			}
			
		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 7){
			zad8.zad8metoda(pole_tekstowe);
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 8){
			zad9.zad9metoda(pole_tekstowe);
			}

		if(e.getSource() == przycisk1 && lista_menu.getSelectedIndex() == 9){
			System.exit(0);
			}


		}
    
    
    // wygl¹da na to ¿e siê nauczy³em ;> 
    // ale nie mogê powiedzieæ, ¿e sam z pamiêci bez pomocy internetu napisa³bym takie okienko
    
    
    
    
    

    
    
    
    public static void main(String[] args) {
    	
    	new Program1();
 


    	
    	
/*	
 		//stare menu
 		
 		String pomocnicza;
    	int menu;
    	
    	while(1>0){   
    		
    		System.out.println("\n \n Wybór programu: \n \n 1 - Zad 1 \t 2 - Zad 2 \t 3 - Zad 3 \n 4 - Zad 4 \t 5 - Zad 5 \t 6 - Zad 6 \n 7 - Zad 7 \t 8 - Zad 8 \t 9 - Zad 9 \n  0 - wyjscie \n \n");

    		pomocnicza = JOptionPane.showInputDialog(null,"Wybór programu: ");
    		menu = Integer.parseInt(pomocnicza);
    		
    				
    		switch(menu) {
    		
    		case 1: zad1.zad1metoda();
    				break;
 			case 2: zad2.zad2metoda();
    				break;
  			case 3: zad3.zad3metoda();
    				break;
  			case 4: zad4.zad4metoda();
    				break; 
  			case 5: zad5.zad5metoda();
    				break; 
  			case 6: zad6.zad6metoda();
    				break; 
  		
  		
  			case 7: zad7.zad7metoda();
    				break; 
  			case 8: zad8.zad8metoda();
  					break; 
  			
  			
    				
   			case 9: zad9.zad9metoda();
    				break; 

    						   			   			    			    			    					
    					
 
 
 			case 0: System.exit(0);
 
    		default: System.exit(0);
    		}
    		
    		
    	}
  */  
  	
    }
}




























 //---------------------------------------------------------------
 // ZADANIE 1
 //---------------------------------------------------------------
 

 
 
 
 
 
abstract class zad1{

	zad1(){}

	static String pomocnicza;
	static String imie;
	static String nazwisko;
	static int wiek;
	static float srednia_ocena;
	
	static void zad1metoda(TextArea pole_tekstowe ){
		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 1!  \n \n \n");
		System.out.println(" Wczytuje on i wyswietla dane o osobie \n \n \n");
		
		pole_tekstowe.setText("\n \n WYBRANO PROGRAM 1!  \n \n \n Wczytuje on i wyswietla dane o osobie \n \n \n");
		
		imie = JOptionPane.showInputDialog(null," Podaj imiê: ");
		nazwisko = JOptionPane.showInputDialog(null," Podaj nazwisko: ");	
		pomocnicza = JOptionPane.showInputDialog(null," Podaj wiek: ");
		wiek = Integer.parseInt(pomocnicza);
		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (ulamek z kropk¹) sredni¹ ocenê: ");
		srednia_ocena = Float.parseFloat(pomocnicza);
		
		JOptionPane.showMessageDialog(null, imie + " " + nazwisko + " \n wiek: " + wiek + " lat \n" + " Œrednia ocena: " + srednia_ocena);
		pole_tekstowe.append( imie + " " + nazwisko + " \n wiek: " + wiek + " lat \n" + " Œrednia ocena: " + srednia_ocena);
		}	
	}
 
 
 //---------------------------------------------------------------
 // ZADANIE 2
 //---------------------------------------------------------------
 
 
abstract class zad2{
 	static float a, b, c;
 	static double delta, x1, x2;
	static String pomocnicza;

	
	static void zad2metoda(TextArea pole_tekstowe){
		
		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 2!  \n \n ");
		System.out.println(" Oblicza on pierwiastki trójmianu kwadratowego \n");
		System.out.println(" Podaj 3 liczby typu float  \n");
		System.out.println(" Warunek a!=0  \n \n \n");
		pole_tekstowe.setText("\n \n WYBRANO PROGRAM 2!  \n \n Oblicza on pierwiastki trójmianu kwadratowego \n Podaj 3 liczby typu float  \n Warunek a!=0  \n \n \n");
		//pêtla wymaga by a!=0
		do{
			
			pomocnicza = JOptionPane.showInputDialog(null," Podaj a");
			a = Float.parseFloat(pomocnicza);
			pomocnicza = JOptionPane.showInputDialog(null," Podaj b");
			b = Float.parseFloat(pomocnicza);
			pomocnicza = JOptionPane.showInputDialog(null," Podaj c");
			c = Float.parseFloat(pomocnicza);
				
					
			}while(a==0);
		
		delta = (b*b) - (4*a*c);
		
		System.out.println("Delta = " + delta + "\n\n\n");
		
		if( delta<0){
			JOptionPane.showMessageDialog(null, " Delta < 0! \n Brak pierwiastków! ");
			pole_tekstowe.append(" Delta < 0! \n Brak pierwiastków! ");
			}
			else{
				 if(delta==0){
				 	x1 = (-b) / (2 * a) ;
				 	JOptionPane.showMessageDialog(null, " Delta = 0 \n Jeden pierwiastek \n x0 = " + x1);
				 	pole_tekstowe.append(" Delta = 0 \n Jeden pierwiastek \n x0 = " + x1);
				 	}
				 	else{
				 		x1 = ((-b) - Math.sqrt(delta)) / 2*a ;
				 		x2 = ((-b) + Math.sqrt(delta)) / 2*a ;
				 		JOptionPane.showMessageDialog(null, " Delta > 0 \n Dwa pierwiastki \n x1 = " + x1 + " \n x2 = " + x2);
				 		pole_tekstowe.append(" Delta > 0 \n Dwa pierwiastki \n x1 = " + x1 + " \n x2 = " + x2);
				 		}
				}		
		}
 	
 	}
 
  
 //---------------------------------------------------------------
 // ZADANIE 3
 //---------------------------------------------------------------
 
 
abstract class zad3{
 	static char znak;
 	static int newline;
 			
 		
 	static void zad3metoda(TextArea pole_tekstowe){
 		znak = 32;
 		newline=0;
 		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 3!  \n \n ");
		System.out.println(" Wypisuje on tabele znaków ASCII \n");
		pole_tekstowe.setText("\n \n WYBRANO PROGRAM 3!  \n \n Wypisuje on tabele znaków ASCII \n ");

      	while (znak <= 251){
         	System.out.print((int)znak + ":" + znak + "\t");
         	pole_tekstowe.append((int)znak + ":" + znak + "\t");
         	znak++;
         	newline++;
         	if(newline==10){
         		System.out.print("\n");
         		pole_tekstowe.append("\n");
         		newline=0;
         		}
      		}	
 		} 		
 	}
 
 
 //---------------------------------------------------------------
 // ZADANIE 4
 //---------------------------------------------------------------
 
abstract class zad4{
 	static String pomocnicza;
 	static int kol, wier, licz;
 	
 	static void zad4metoda(TextArea pole_tekstowe){
 		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 4!  \n \n ");
		System.out.println(" Tworzy on tabliczkê mno¿enia \n");
		pole_tekstowe.setText("\n \n WYBRANO PROGRAM 4!  \n \n Tworzy on tabliczkê mno¿enia \n");

 		pomocnicza = JOptionPane.showInputDialog(null," Podaj liczbê kolumn: ");
 		kol = Integer.parseInt(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null," Podaj liczbê wierszy");
 		wier = Integer.parseInt(pomocnicza);
 		
 		
 		for( int i=1; i <= wier; i++){
 			licz = i;
 			System.out.print("\n");
 			pole_tekstowe.append("\n");
 			for( int j=1; j <= kol; j++){
 				System.out.print(licz*j + "\t"); 	
 				pole_tekstowe.append(licz*j + "\t");							
 				}
 			}
 		}
	}
  
  
  
  
 //---------------------------------------------------------------
 // ZADANIE 5
 //---------------------------------------------------------------
 
abstract class zad5{
 	static String pomocnicza;
 	static Float a,b,c,d,x,w;
 	
	static void zad5metoda(TextArea pole_tekstowe){
 		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 5!  \n \n ");
		System.out.println(" Oblicza on wartoœæ wielomianu stopnia 3  \n");
 		System.out.println(" Za pomoc¹ wzoru Kronera  \n");
 		pole_tekstowe.setText(" \n \n WYBRANO PROGRAM 5!  \n \n Oblicza on wartoœæ wielomianu stopnia 3  \n Za pomoc¹ wzoru Kronera  \n");
 		
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (Float z kropk¹) a: ");
 		a = Float.parseFloat(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (Float z kropk¹) b: ");
 		b = Float.parseFloat(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (Float z kropk¹) c: ");
 		c = Float.parseFloat(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (Float z kropk¹) d: ");
 		d = Float.parseFloat(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (Float z kropk¹) x: ");
 		x = Float.parseFloat(pomocnicza);
 		
 		w = a * x + b;
 		w = w * x + c;
 		w = w * x + d;
 		
 		JOptionPane.showMessageDialog(null," Wynik: " + w); 		
 		pole_tekstowe.append(" Wynik: " + w);
 		
 		}
	}
 
 
  
 //---------------------------------------------------------------
 // ZADANIE 6
 //---------------------------------------------------------------
 
 
abstract class zad6{
 	static String pomocnicza;
 	static int a,b,nwd,nww;
 	
 	static void zad6metoda(TextArea pole_tekstowe){
 		
 		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 6!  \n \n ");
		System.out.println(" Oblicza on nwd i nww  \n");
		System.out.println(" nwd = 0 lub nwd = 1 oznacza brak NWD  \n");
 		pole_tekstowe.setText(" \n \n WYBRANO PROGRAM 6!  \n \n Oblicza on nwd i nww  \n nwd = 0 lub nwd = 1 oznacza brak NWD  \n");
 		
 		
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (int) a: ");
 		a = Integer.parseInt(pomocnicza);
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (int) b: ");
 		b = Integer.parseInt(pomocnicza);
 		
 		// OBLICZANIE NWD 
 		if(a>b){
 			nwd = b;
 			}else{
 				nwd = a;
 				}
 		while(nwd > 1){
 			if((a%nwd==0)&&(b%nwd==0)){
 				break;
 				}
 			nwd--;
 			}
 			
 		
 		// OBLICZANIE NWW		
 		if(a>b){
 			nww = a;
 			}else{
 				nww = b;
 				}
 				
 		while(1>0){
 			if((nww%a==0)&&(nww%b==0)){
 				break;
 				}
 			
 			nww++;
 			}
 		
 		// Gdy NWD = 0 oraz NWD = 1 przyj¹³em brak NWD
 		if(nwd>1){
 			JOptionPane.showMessageDialog(null," Najwiêkszy wspólny dzielnik: " + nwd + " \n Najmniejsza wspólna wielokrotnoœæ: " + nww);
 			pole_tekstowe.append(" Najwiêkszy wspólny dzielnik: " + nwd + " \n Najmniejsza wspólna wielokrotnoœæ: " + nww);
 			}else{
 				JOptionPane.showMessageDialog(null, "Brak nwd"  +  "\n Najmniejsza wspólna wielokrotnoœæ: " + nww);
 				pole_tekstowe.append("Brak nwd"  +  "\n Najmniejsza wspólna wielokrotnoœæ: " + nww);
 				}

 		
 		
 		}
	}
 
 
 
  
 //---------------------------------------------------------------
 // ZADANIE 7
 //---------------------------------------------------------------
 
abstract class zad7{
 	static double eps;
 	static double s1, s2, silnia, stop;
 	static String pomocnicza;

 	
 	static void zad7metoda(TextArea pole_tekstowe){
 		
 		pole_tekstowe.setText(" \n \n WYBRANO PROGRAM 7!  \n \n Obliczanie przybli¿onej wartoœci liczb pi oraz e  \n");	
 		pomocnicza = JOptionPane.showInputDialog(null, " Podaj wartoœæ przybli¿enia (float z kropk¹) eps: ");
 		eps = Float.parseFloat(pomocnicza);
 		s1 = 0.00;
 		s2 = 1.00;
 		silnia = 1;
 		stop = 1.00;
 		
 		
 		for(int i=0; eps < stop; i++){
 			stop = (1.00 /(2.00*i + 1.00));
 			s1 += stop * ( Math.pow(-1.00, i) ) ;
 			} 	
 					
 		stop = 1.00;
 		for(int i=1; eps < stop ; i++){
 			silnia *= i;
 			stop = 1.00/ silnia;
 			s2 += stop;
 			}
 		 			
 		
 		s1 *=4;
 		pole_tekstowe.append("S1 = Pi = " + s1 + "\n");	
 		pole_tekstowe.append("S2 = e = " + s2);
 		
 		}
	}
 
 
 
 
 
 //---------------------------------------------------------------
 // ZADANIE 8
 //---------------------------------------------------------------
 
  
abstract class zad8{
	
	static int n, f, silnia;
	static String pomocnicza;
 	
 	static void zad8metoda(TextArea pole_tekstowe){
 		
 		pole_tekstowe.setText(" \n \n WYBRANO PROGRAM 8!  \n \n Obliczanie ilosci liczb pierwszych mniejszych lub równych n \n ");	
 			
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (int wiêkszy od 3) n: ");
 		n = Integer.parseInt(pomocnicza);
 		
 		f = -1;
 		silnia = 1;
 		for(int j =3; j <= n; j++){
 			silnia *= j-2; 
 			f += silnia - j* Math.floor(silnia/j);
 			}
 		pole_tekstowe.append("\n Liczb pierwszych mniejszych lub równych " + n + " jest: " + f);
 		
 		
 		
 		}
 	}
 
 
  
 //---------------------------------------------------------------
 // ZADANIE 9
 //---------------------------------------------------------------
 
 
 
 
abstract class zad9{
 	static int n, n1, licznik, parzystosc;
 	static String pomocnicza; 	
 	
 	static void zad9metoda(TextArea pole_tekstowe){
 		System.out.println(" \n \n \n \n \n \n WYBRANO PROGRAM 9!  \n \n ");
		System.out.println(" Algorytm Hofstadter'a  \n");	
		pole_tekstowe.setText(" \n \n WYBRANO PROGRAM 9!  \n \n Algorytm Hofstadter'a  \n");	
			
			
 		pomocnicza = JOptionPane.showInputDialog(null,"Podaj (int) n0: ");
 		n = Integer.parseInt(pomocnicza);
 		licznik = 1;
 		do{
 			if(n%2==0){
 				parzystosc=1;
 				n1 = n/2 ;
 				}else{
 					parzystosc=0;
 					n1 = 3*n + 1;
 					}
 					
 			if(parzystosc==1){
 				System.out.println(licznik + "\t" + n + "\t" + "parzyste" + "\t" + n1);
 				pole_tekstowe.append(licznik + "\t" + n + "\t" + "parzyste" + "\t\t" + n1 + "\n");
 				}else{
 					System.out.println(licznik + "\t" + n + "\t" + "nieparzyste" + "\t" + n1 );
 					pole_tekstowe.append(licznik + "\t" + n + "\t" + "nieparzyste" + "\t" + n1 + "\n");
 					}
 					
 			
 			licznik++;
 			
 			n=n1; 			
 			
 			}while(n!=1);
 		
 		
 		
 		}
 	}
 
 
 
 