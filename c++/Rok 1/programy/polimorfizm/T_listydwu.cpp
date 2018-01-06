

#include "T_listydwu.h"






lista_dwu::lista_dwu(){ 
                
    wsk_aktualny = NULL;
    wsk_pierw = NULL;  
    wsk_ost = NULL;             
    ilosc_elem = 0;
      
                }

lista_dwu::lista_dwu(T_kontener * kontener){ 

    wsk_aktualny = new T_element_dwu;
    wsk_pierw = wsk_aktualny;
    wsk_ost = wsk_aktualny;   
    wsk_aktualny->setkontener(kontener);                       
    wsk_aktualny->setwsk_next(NULL);                          
    ilosc_elem = 1; 
      
                }

lista_dwu::~lista_dwu(){
    T_element_dwu *wsk = wsk_pierw; 
    while( wsk != NULL ){
           wsk_aktualny = wsk->getwsk_next();
           delete wsk->getkontener();
           wsk->setkontener(NULL);
           delete wsk;       
                                       
           wsk = wsk_aktualny;                                 
           }          
    cout << " // Wywolano destruktor " << endl; 
    }


void lista_dwu::pokaz(){                                                 // wyswietla wszystkie elementy 
   
                                      
     
    if( ilosc_elem != 0){
        wsk_aktualny=wsk_pierw;
        
    
        for( int j=0 ;wsk_aktualny != NULL;j++  ){
             cout << " Element numer " << j;
             wsk_aktualny->getkontener()->pokaz();
	         wsk_aktualny = wsk_aktualny->getwsk_next();
             }                                 
        }
    }

void lista_dwu::dodaj(T_kontener * kontener){                              // dodaje element na koncu 
    
    
    
    if( ilosc_elem==0){ 
        wsk_aktualny = new T_element_dwu;
        wsk_pierw = wsk_aktualny;
        wsk_ost = wsk_aktualny;
        wsk_aktualny->setkontener(kontener);                       
        wsk_aktualny->setwsk_next(NULL);
        wsk_aktualny->setwsk_prev(NULL);              
        ilosc_elem++;
        }
    else{
    
         
         wsk_aktualny = new T_element_dwu;                                                                   
         wsk_ost->setwsk_next(wsk_aktualny);
         
         wsk_aktualny->setwsk_next(NULL);   
         wsk_aktualny->setwsk_prev(wsk_ost);                    
         wsk_aktualny->setkontener(kontener);
         wsk_ost = wsk_aktualny;
         ilosc_elem++;
         }
        
    
    
    cout << " // Dodano element na koncu " << endl;                           
    }




T_kontener * lista_dwu::pobierz_wsk(int numer){
           if( ilosc_elem >= numer){

            wsk_aktualny=wsk_pierw; 
            
       
            for( int i=0;(i < numer)&& ( wsk_aktualny->getwsk_next() != NULL );i++){
                 wsk_aktualny = wsk_aktualny->getwsk_next();                              
                 }
            return wsk_aktualny->getkontener();
            }
                                  
        else cout << " Element nie istnieje " << endl; 
        }


void lista_dwu::usun(){                                       //usuwa ostatni element listy
     
     if(wsk_ost!=NULL){
                       T_element_dwu *wsktmp = wsk_ost->getwsk_prev();
                       delete wsk_ost;
                       wsk_ost = wsktmp;
                       wsk_ost->setwsk_next(NULL);
                       --ilosc_elem;
                       }
     

     else cout << " Element nie istnieje " << endl ;
     
     
     
     }
     
     
     

void lista_dwu::usun_nr(int numer){                             //usuwa wybrany element
        
        if( ilosc_elem > numer){

            if( numer == 0){
                 
                 if(ilosc_elem==1){
                                   delete wsk_ost;
                                   wsk_ost=NULL;
                                   wsk_aktualny=NULL;
                                   wsk_pierw=NULL;
                                   }
                 else{
                      T_element_dwu *wsktmp = wsk_ost->getwsk_prev();
                      delete wsk_ost;
                      wsk_ost = wsktmp;
                      wsk_ost->setwsk_next(NULL);
                 
                      }
                    
                --ilosc_elem;     
                }
            else{
                 if((ilosc_elem-1)==numer){
                                         usun();
                                         }
                 else{
                      wsk_aktualny=wsk_pierw; 
       
                      for( int i=0;(i < numer) && (wsk_aktualny->getwsk_next() !=NULL)  ;i++){
                 
                           wsk_aktualny = wsk_aktualny->getwsk_next();                                
                           }
                       
                 
                       (wsk_aktualny->getwsk_next())->setwsk_prev(wsk_aktualny->getwsk_prev());
                       (wsk_aktualny->getwsk_prev())->setwsk_next(wsk_aktualny->getwsk_next());            
                       delete wsk_aktualny;            
                       wsk_aktualny = NULL;      
             
                
                       --ilosc_elem;
                      
                      }
                 
                 
                 
                 
                 }
            
        
            cout << " Wybrany element listy zostal usuniety " << endl;
            }
                                  
        else cout << " Element nie istnieje " << endl; 
        }


void lista_dwu::numer_dodaj(T_kontener * kontener, int numer){           // dodaje element na podanym miejscu jezeli podany nie istnieje, dodaje na koncu listy
    wsk_aktualny = wsk_pierw;
        
     if( ilosc_elem==0){
         wsk_aktualny = new T_element_dwu;
         wsk_pierw = wsk_aktualny;
         wsk_aktualny->setkontener(kontener);                       
         wsk_aktualny->setwsk_next(NULL);              
         }   
     else{
          if( numer==0){
              T_element_dwu *wsk = new T_element_dwu;
              wsk->setkontener(kontener);
              wsk->setwsk_next(wsk_pierw);
              wsk_pierw=wsk;         
              }
          else{
               for( int i = 1;(wsk_aktualny->getwsk_next() != NULL) && (i<numer);i++){
                    wsk_aktualny = wsk_aktualny->getwsk_next();
                    }                      
                 
               T_element_dwu *wsk = new T_element_dwu;
               wsk->setkontener(kontener);
               wsk->setwsk_next(wsk_aktualny->getwsk_next());
               wsk_aktualny->setwsk_next(wsk);
               wsk_aktualny = wsk; 
               }   
          }   
        
                                
    ilosc_elem++;                                
    cout << " // Dodano element pod tym numerem " << endl;                                 
    }


void lista_dwu::kasuj_all(){
     if( ilosc_elem!=0){
         wsk_aktualny = wsk_pierw;
     
         while( (wsk_aktualny->getwsk_next() != NULL) && (ilosc_elem > 1)){
                wsk_aktualny = wsk_aktualny->getwsk_next();
                delete wsk_pierw->getkontener();
                delete wsk_pierw;                           
                wsk_pierw = wsk_aktualny;                           
                }
         delete wsk_pierw->getkontener();
         delete wsk_pierw;
         wsk_aktualny = NULL;
         wsk_pierw = NULL;
         }
     
     }
