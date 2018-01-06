/* 
 *  Autor: Kamil Markuszewski 171016
 *   Data: 23 stycznia 2010 r.
 */
 

import java.util.*;
import javax.swing.*;
import java.net.*;
import java.awt.*;

import java.io.*;
import java.awt.event.*;




//------------------------------------------------------------------------
// Komunikator sieciowy... Sever
//------------------------------------------------------------------------










class T_Serwer extends JFrame implements  Runnable {
	
	
	private ArrayList<WatekKlienta> klienci = new ArrayList();
	
	private JTextArea  textArea  = new JTextArea(15,18);
	private JScrollPane scroll = new JScrollPane(textArea,
	  				ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
					ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	
	
	static final int SERVER_PORT = 6600;
	private String host;
	private ServerSocket serwer;

	
	T_Serwer(){ 
		super("SERWER");
	  	setSize(300,330);
	  	setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	  	JPanel panel = new JPanel();
	  	



	  	textArea.setLineWrap(true);
	  	textArea.setWrapStyleWord(true);
	  	textArea.setEditable(false);
	  	
	  	panel.add(scroll);
	  	setContentPane(panel);
	  	Thread watek = new Thread(this); 
	  	watek.start();                   
	  	setVisible(true);
		}
		
		

	synchronized void usunKl(WatekKlienta klient){
      	klienci.remove(klient);
		}
		
		
		
	
	synchronized public void wypiszOdebrane(WatekKlienta klient, String s){
		
			boolean poszlo=false;
		
 
			for(WatekKlienta k:klienci){
				if(k.getNick().equals(klient.getOdbiorca())){
					k.getOutput().println(klient.getNick());
	  				k.getOutput().println(s);
	  				poszlo=true;
					}
				}
			if(poszlo==false){
				
				klient.getOutput().println("ServerKomunikat");
				klient.getOutput().println("Nie_ma_takiego_usera");
				}
			


	  		if (s.equals("/quit")){
				usunKl(klient);
	  			}

			textArea.append(klient.getNick() + " >>> "+ klient.getOdbiorca() + " : " + s.replace('_', ' ') + "\n");
		
		
		
		}

	

	
	
	
	public void run(){
		Socket s;
	  	WatekKlienta klient;
		
	  	
	  	try{host = InetAddress.getLocalHost().getHostName();
	  	   	serwer = new ServerSocket(SERVER_PORT);
			} 
		catch(IOException e){ 	
		 	System.out.println(e);
		   	JOptionPane.showMessageDialog(null, "Gniazdko dla serwera nie mo¿e byæ utworzone"); 
		   	System.exit(0);
			}
			
		System.out.println("Serwer zosta³ uruchomiony na hoscie " + host);
	  	// koniec inicjalizacji po³¹czeñ sieciowych
	  
	  	while(true){
			try{ 
				s = serwer.accept();

				if (s!=null){
		  			klient = new WatekKlienta(this, s);
		  			klienci.add(klient);
		  			System.out.print(klienci.size());
		  			}
				}
			catch(IOException e){ 
				System.out.println("BLAD SERWERA: Nie mozna polaczyc sie z klientem ");
				}
			}
		}
	
	
	
	
	
	
	
	public static void main(String [] args){
		new T_Serwer();
		}
	
	}











class WatekKlienta implements Runnable {
	private Socket socket;
	private PrintWriter output;
	private Scanner input;
	private String odbiorca;
	
	private String nick;
	private T_Serwer okno;
	
	WatekKlienta(T_Serwer okno, Socket socket) throws IOException{ 
		this.okno = okno;
	  	this.socket = socket;
	  	
	  	Thread t = new Thread(this);  
	  	t.start();                    
	}
	
	
	public String toString(){ return nick; }
	
	public PrintWriter getOutput(){ return output; }
	
	public String getNick(){ return nick; }
	
	public String getOdbiorca(){ return odbiorca; }
	
	public void run(){  
		String message;
	
	   	try{
	   		output = new  PrintWriter(socket.getOutputStream(),true);
	  		input = new Scanner(socket.getInputStream());
	   		if(input.hasNext()){
	   			nick = (String)input.next();
	   			}
	   		
	   		
	   		




			while(true){
				
				if(input.hasNext()){
	   				odbiorca = (String)input.next();
	   				message = (String)input.next();
					okno.wypiszOdebrane(this,message);
					if (message.equals("/quit")){
						okno.usunKl(this);
						break;		
						}
					}
				
				
			

			}
			
			input.close();
			output.close();
			socket.close();
			socket = null;
			
	   	} catch(Exception e) {}
	}
}











