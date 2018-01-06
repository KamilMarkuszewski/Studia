/* 
 *  Autor: Kamil Markuszewski 171016
 *   Data: 23 stycznia 2010 r.
 */
 


import javax.swing.*;
import java.net.*;
import java.awt.*;
import java.util.*;
import java.io.*;
import java.awt.event.*;


//------------------------------------------------------------------------
// Komunikator sieciowy... Klient
//------------------------------------------------------------------------






class Klient extends JFrame implements ActionListener, Runnable{
	
	
	JPanel panel = new JPanel();
	JLabel JL_user = new JLabel("Odbiorca:");
	JLabel JL_napisz = new JLabel("Napisz:");
	private JLabel JL_rozmowa = new JLabel("Rozmowa:");
	
	private JTextField TF_wiadomosc = new JTextField(30);
	private JTextArea  konsola  = new JTextArea(18,30);
	private JTextField TF_odbiorca = new JTextField(30);
	
	static final int SERVER_PORT = 6600;
	private String nick;
	private String host;
	private Socket socket;
	private PrintWriter output;
	private Scanner input;
	
	Klient(String n){ 
		
		super("Klient: " + n);
		nick = n;
		setSize(400,420);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	    


	  
		konsola.setLineWrap(true);
		konsola.setWrapStyleWord(true);
	  
	  	
		panel.add(JL_napisz);
		panel.add(TF_wiadomosc);
	  	TF_odbiorca.addActionListener(this);
		TF_wiadomosc.addActionListener(this);
		panel.add(JL_rozmowa);
		
		JScrollPane scroll_bars = new JScrollPane(
	  		konsola,
	  		ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
			ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
			
	  	panel.add(scroll_bars);
	  	
	    panel.add(JL_user);
	    panel.add(TF_odbiorca);
	  	
	  	setContentPane(panel);
	  
	  
	  
	  	Thread watek = new Thread(this);
	  	watek.start();
	  	setVisible(true);
	  
		}
	
	
	
	
	/**
	 * Odbieranie wiadomosci
	 */
	
	
	public void run(){
		try{
			String odbiorca = (String)TF_odbiorca.getText();

			host = InetAddress.getLocalHost().getHostName();
	  		socket = new Socket(host, SERVER_PORT);
	  		input = new Scanner(socket.getInputStream());
	  		output = new PrintWriter(socket.getOutputStream(),true);
	  		output.println(nick);



	  		}
	  		
		catch(IOException ex){ 
			System.out.println(ex);
			JOptionPane.showMessageDialog(null, "Polaczenie sieciowe dla klienta nie moze byc utworzone");
			dispose(); 
			setVisible(false);
			return;
		
			}

		try{
		 	while(true){
		 		if(input.hasNext()){
		 			String n = (String)input.next();	
		 		
		 
		 			String message = (String)input.next();
		 			
		 				
		 				
		 			if(message.equals("/quit")){
		 			
	  		 			setVisible(false);
	  		 			output.close();		
		 				input.close();
	  		 			socket.close();
	  		 			return;
		 				}
		 			konsola.append(n+ ">> " + message.replace('_', ' ') + "\n");
		 			
		 			}	

		 				
		 			

		 			
		 		}

		 		
		 		

		 	}
		 	
		 	
		 	catch(Exception ex){
		   		JOptionPane.showMessageDialog(null, "Wyj¹tek w Action evencie klienta innego klienta, po³¹czenie zakoñczone");
		   		setVisible(false);
		   		dispose();
		 	}	
		}
	
	
	
	
	/**
	 * funkcja main 
	 */
	
	
	public static void main(String [] args)
		{
		String nick;		
				
		nick = JOptionPane.showInputDialog("Jaki chcesz mieæ nick? (bez spacji): ");

		if(nick != null ){
			new Klient(nick);
		}
	}




	/**
	 * Action listener reaguj¹cy na enter na polu TF_wiadomosc
	 * 
	 */

	public void actionPerformed(ActionEvent evt){ 
		String odbiorca;
		String message;
	  	if ((TF_wiadomosc==evt.getSource())||(TF_odbiorca==evt.getSource())){
	  		
	  		try{
	  			
	  			
	  			odbiorca = TF_odbiorca.getText();
	  			message = TF_wiadomosc.getText();
	  			if(odbiorca.equals("")||odbiorca.equals(" ")||message.equals("")||message.equals(" ")){
	  				JOptionPane.showMessageDialog(null,"Wype³nij pola odbiorca i wiadomosc!");
	  				
	  				}
	  			else{
	  			
	  			
	  				message=message.replace(' ', '_');
	  				output.println(odbiorca);
	  				output.println(message);
		 	 		konsola.append("<< " + message + "\n");
		 	 	
		 	 	
		 	 	
		 	 	/**
		 	 	 * Wyjœcie zaporzyczone z przyk³adowego programu
		 	 	 * Sk³adnia ircowa ;) 
		 	 	 */
		 	 	 
	  		 		if (message.equals("/quit")){

	  		 			setVisible(false);
	  		 			socket.close();
	  		 			output.close();
	  		 			input.close();


	  		 			return;
	  		 			}
	  		 		}
	  				}
	  			catch(IOException ex){ 
	  				System.out.println("Wyj¹tek w Action evencie klienta, po³¹czenie zakoñczone");
	  				}
	  		}
	  		repaint();
		}
	
















}
