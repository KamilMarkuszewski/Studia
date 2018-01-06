/* 
 *  Autor: Kamil Markuszewski 171016
 *   Data: 23 stycznia 2010 r.
 */
 


import javax.swing.*;
import java.net.*;
import java.awt.*;

import java.io.*;
import java.awt.event.*;


//------------------------------------------------------------------------
// Komunikator sieciowy... Klient
//------------------------------------------------------------------------






class Klient extends JFrame implements ActionListener, Runnable{
	
	
	JPanel panel = new JPanel();
	JLabel JL_napisz = new JLabel("Napisz:");
	private JLabel JL_rozmowa = new JLabel("Rozmowa:");
	
	
	private JTextField TF_wiadomosc = new JTextField(30);
	private JTextArea  konsola  = new JTextArea(18,30);
	
	static final int SERVER_PORT = 6600;
	private String nick;
	private String host;
	private Socket socket;
	private ObjectOutputStream output;
	private ObjectInputStream input;
	
	Klient(String n){ 
		
		super("Klient: " + n);
		nick = n;
		setSize(400,400);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	  
	  
		konsola.setLineWrap(true);
		konsola.setWrapStyleWord(true);
	  
		panel.add(JL_napisz);
		panel.add(TF_wiadomosc);
	  
		TF_wiadomosc.addActionListener(this);
		panel.add(JL_rozmowa);
		
		JScrollPane scroll_bars = new JScrollPane(
	  		konsola,
	  		ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
			ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
			
	  	panel.add(scroll_bars);
	  	setContentPane(panel);
	  
	  
	  
	  	Thread t = new Thread(this);
	  	t.start();
	  	setVisible(true);
	  
		}
	
	
	
	
	/**
	 * Odbieranie wiadomosci
	 */
	
	
	public void run(){
		try{
			
			host = InetAddress.getLocalHost().getHostName();
	  		socket = new Socket(host, SERVER_PORT);
	  		input = new ObjectInputStream(socket.getInputStream());
	  		output = new ObjectOutputStream(socket.getOutputStream());
	  		output.writeObject(nick);
	  		
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
		 		String message = (String)input.readObject();
		 		konsola.setText(">> " + message + "\n");
		 		
		 		if(message.equals("/quit")){
		 			
	  		 		setVisible(false);
	  		 		output.close();		
		 			input.close();
	  		 		socket.close();
	  		 		return;
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
				
		//nick = JOptionPane.showInputDialog("Jaki chcesz mieæ nick?: ");
		nick = "kajt";
		if(nick != null ){
			new Klient(nick);
		}
	}




	/**
	 * Action listener reaguj¹cy na enter na polu TF_wiadomosc
	 * 
	 */

	public void actionPerformed(ActionEvent evt){ 
		
		String message;
	  	if (TF_wiadomosc==evt.getSource()){
	  		
	  		try{
	  			message = TF_wiadomosc.getText();
	  			
	  			output.writeObject(message);
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
	  			catch(IOException ex){ 
	  				System.out.println("Wyj¹tek w Action evencie klienta, po³¹czenie zakoñczone");
	  				}
	  		}
	  		repaint();
		}
	
















}
