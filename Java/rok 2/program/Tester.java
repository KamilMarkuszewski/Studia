/* 
 *  Komunikator sieciowy
 *   - program uruchamiajacy serwer i dwóch klientów
 *
 *  Autor: Pawel Rogalinski
 *   Data: 1 stycznia 2010 r.
 */
 
 
import java.net.*;
import java.io.*;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;


class Tester {
	
	public static void main(String [] args){
		new Serwer();
		
		try{
			Thread.sleep(1000);
		} catch(Exception e){}
			
	  	new Klient("Ewa");
		
		new Klient("Adam");
	}
	
}


