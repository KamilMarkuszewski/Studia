#include <cstdlib>
#include <iostream>

using namespace std;




//---------------------------------------------------------------------------
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
//---------------------------------------------------------------------------





// CLASS LISTA!!!

class lista{
 public:
        lista();
        lista(int bitr);
        ~lista(); 
        int ile() const ;
        void dodaj(int br);
        void numer_dodaj(int br, int numer);
        void pokaz();
        void usun();
        void zmien_pierw(int wartosc);
        void zmien_ost(int wartosc);
        void zmien_elem(int wartosc,int numer);
        void usun_nr(int numer);
        void ustaw_pierwszy();
        void ustaw_ost();
        void ustaw_nr(int numer);
        void przypisz(int wartosc);
        int  czytaj();
        void przesun_numer(int numer);
        void usun_wsk();              
 private:
         int ilosc_elem;
         T_element *wsk_pierw, *wsk_aktualny;
      };


// FUNKCJE CLASSY


//konstruktory i destruktor

lista::lista(){ 
                
    wsk_aktualny = NULL;
    wsk_pierw = NULL;            
    ilosc_elem = 0;
    cout << " // Wywolano konstruktor " << endl;          
                }

lista::lista(int bitr){ 

    wsk_aktualny = NULL;
    wsk_pierw = NULL; 
    ilosc_elem = 0; 
    cout << " // Wywolano konstruktor " << endl;          
                }

lista::~lista(){
                

    T_element *wsk = wsk_pierw;
    
    for(;(*wsk).getwsk_next() != NULL ;){
                               
        wsk_aktualny = (*wsk).getwsk_next();
        delete wsk;                                    
        wsk = wsk_aktualny;                                 
                                         }          
    cout << " // Wywolano destruktor " << endl; 
                }
                
                
                
                
                
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------





// metody

void lista::ustaw_pierwszy(){                                                // ustawia wskaznik na poczatku
    wsk_aktualny = wsk_pierw;
    cout << " // Wskaznik zostal ustawiony na poczatku. " ;                        
                            }

int lista::czytaj(){
    if(wsk_aktualny != NULL){                                                 // czyta wartosc obiektu na ktory wskazuje wskaznik
    return (*wsk_aktualny).getbitrate();
                             }
    cout << " Wskaznik wskazuje na NULL! ";
    return 0;
                        }


void lista::ustaw_ost(){                                                       // utawia wskaznik na koniec
    lista::ustaw_pierwszy();                                                   // poniewaz wykorzystuje funkcje ustaw_pierwszy przy wywo³aniu wypisze " Wskaznik zostal ustawiony na poczatku. Wskaznik zostal ustawiony na koncu." 
    T_element *wsk = (*wsk_aktualny).getwsk_next(); 
    for(;wsk != NULL ;){
        wsk_aktualny = wsk;
        wsk = (*wsk).getwsk_next();                                      
                                             }
     cout << " Wskaznik zostal ustawiony na koncu. " ;                                                                
                       }



void lista::ustaw_nr(int numer){                                               // ustawia wskaznik na obiekcie, ktorego podamy numer
    if(numer>ilosc_elem){                                                      
        cout << " Halo, nie ma takiego numeru! " << endl;                 
                         }
    else{
        lista::ustaw_pierwszy();
        for(int i = 1; i < numer ; i++ ){
        wsk_aktualny = (*wsk_aktualny).getwsk_next();                         
                                         }
        cout << " // Wskaznik zostal ustawiony pod tym numerem. " << endl;                             
         } 
                                }
                                
                                
                                

void lista::przypisz(int wartosc){                                              // przypisuje wartosc zmiennej obiektu na ktory wskazuje wskaznik
    if(wsk_aktualny != NULL){
        (*wsk_aktualny).setbitrate(wartosc);
        cout << " // Wartosc przypisana " << endl;                 
                             }
    else cout << " Wskaznik wskazuje na NULL! " << endl;                              
                                  }




void lista::przesun_numer(int numer){                                             // przesuwa wskaznik o numer elementow w przod
     if(((numer <= 0) || (numer > ilosc_elem )) || (wsk_aktualny == NULL ) ){
         cout << " Wskaznik NIE zostal przesuniety, ale byc moze ma wartosc NULL " << endl;                 
                 }
     else{
          for(int i = 0;(i<numer)&&((*wsk_aktualny).getwsk_next() != NULL);i++){
              wsk_aktualny = (*wsk_aktualny).getwsk_next();                                  
                                                               }
          if((*wsk_aktualny).getwsk_next() == NULL){
              if(wsk_aktualny == NULL){
                   cout << " Blad: za malo elementow. Wskaznik nie zostal przesuniety ale !!ZA DARMO!! ustawilem go na NULL ;-) ";             
                              }
              else{
                   cout << " Wskaznik zostal przesuniety na koniec, a nie o n miejsc, poniewaz lista jest za krotka. "  << endl; 
                   }                
                        
                                   }                                                                      
          else{
              cout << " Wskaznik zostal przesuniety o " << numer << " elementow "  << endl;  
               }
          
          }
     
     
     
     
                              }



int lista::ile() const {                                                        // zwraca ilosc elementow listy (bez pierwszego elementu niewidocznego dla uzytkownika programu)
    return ilosc_elem;          
                        }



void lista::dodaj(int br){                              // dodaje element na koncu 
    
    if(ilosc_elem==0){
                      
        wsk_aktualny = new T_element;
        wsk_pierw = wsk_aktualny;
        (*wsk_aktualny).setbitrate(0);                       
        (*wsk_aktualny).setwsk_next(NULL);              
                      
                      }
    ilosc_elem++;
    wsk_aktualny = wsk_pierw;
    
    for(;(*wsk_aktualny).getwsk_next() != NULL;){
        wsk_aktualny = (*wsk_aktualny).getwsk_next();                               
                                                 }
    T_element *wsk = new T_element;                                                                   
    (*wsk_aktualny).setwsk_next(wsk);
    (*wsk).setwsk_next(NULL);                      
    (*wsk).setbitrate(br);
    cout << " // Dodano element na koncu " << endl;                           
                          
                          
                          }


void lista::numer_dodaj(int br, int numer){           // dodaje element na podanym miejscu jezeli podany nie istnieje, dodaje na koncu listy
    wsk_aktualny = wsk_pierw;
        
     if(ilosc_elem==0){
                      
        wsk_aktualny = new T_element;
        wsk_pierw = wsk_aktualny;
        (*wsk_aktualny).setbitrate(0);                       
        (*wsk_aktualny).setwsk_next(NULL);              
                      
                      }   
        
        
    for(int i = 0;((*wsk_aktualny).getwsk_next() != NULL) && (i<numer);i++){
    wsk_aktualny = (*wsk_aktualny).getwsk_next();
                     }                      
                                 
             
                             
    
                                                
                                    
    T_element *wsk = new T_element;
    (*wsk).setbitrate(br);
    (*wsk).setwsk_next((*wsk_aktualny).getwsk_next());
    (*wsk_aktualny).setwsk_next(wsk);
    wsk_aktualny = wsk;                                 
    ilosc_elem++;                                
    cout << " // Dodano element pod tym numerem " << endl;                                 
                                           }


void lista::pokaz(){                                   // wyswietla wszystkie elementy (bez pierwszego elementu niewidocznego dla uzytkownika programu)
   
                                      
     
    if(ilosc_elem != 0){
        wsk_aktualny=wsk_pierw;
        wsk_aktualny = (*wsk_aktualny).getwsk_next(); 
    
        for(int j=1 ;wsk_aktualny != NULL;j++  ){

            cout << " Element numer: " << j << " Wynosi: " << (*wsk_aktualny).getbitrate() <<endl;
	        wsk_aktualny = (*wsk_aktualny).getwsk_next();
                                             }                  
                        
                        
                        
                        }
                 
                                        

     
                    }



void lista::usun(){                                       //usuwa ostatni element listy
    if(ilosc_elem > 0){

        wsk_aktualny=wsk_pierw; 
        T_element *przed;
        przed = wsk_aktualny;
        wsk_aktualny = (*przed).getwsk_next();
        T_element *wsk;
        wsk = (*wsk_aktualny).getwsk_next();
    
    
        
        for(;wsk != NULL;){

            przed = wsk_aktualny;
            wsk_aktualny = wsk;               
            wsk = (*wsk).getwsk_next();                                      
                           }
        delete wsk_aktualny;            
        wsk_aktualny = NULL;           
        (*przed).setwsk_next(NULL);
        --ilosc_elem;
        cout << " Ostatni element listy zostal usuniety " << endl;
                        }

    else cout << " Element nie istnieje " << endl ;
  
                   
                   }
                   
                   
                   
void lista::zmien_pierw(int wartosc){                      // zmienia wartosc pierwszego elementu
    if(ilosc_elem > 0){    
        wsk_aktualny = (*wsk_pierw).getwsk_next();
        (*wsk_aktualny).setbitrate(wartosc);                                 
                       }
    else cout << " Element nie istnieje! " << endl;           
                                     }

void lista::zmien_ost(int wartosc){                        // zmienia wartosc ostatniego elementu
    if(ilosc_elem > 0){
        wsk_aktualny = wsk_pierw;
        T_element *wsk = NULL;

        for(;wsk_aktualny != NULL;){
            wsk = wsk_aktualny;
            wsk_aktualny = (*wsk_aktualny).getwsk_next();                        
                                    }
        (*wsk).setbitrate(wartosc);                              
                        }
        else cout << " Element nie istnieje! " << endl;                               
                                     }



void lista::zmien_elem(int wartosc,int numer){              // zmienia wartosc wybranego elementu
    
    if(ilosc_elem < numer){
        cout << " Element nie istnieje! " << endl;         
                           } 
    else{
         wsk_aktualny = wsk_pierw;
         for(int i = 0;(i<numer)&&(wsk_aktualny != NULL);i++){
             wsk_aktualny = (*wsk_aktualny).getwsk_next();                                                   
             cout << i;                  
                       }
         (*wsk_aktualny).setbitrate(wartosc);
         
         
         } 
     
                                              }


void lista::usun_nr(int numer){                             //usuwa wybrany element
        
        if(ilosc_elem >= numer){

            wsk_aktualny=wsk_pierw; 
            utwor *przed;
            przed = wsk_aktualny;
            wsk_aktualny = (*przed).getwsk_next();
       
            for(int i=1;i < numer ;i++){
                przed = wsk_aktualny;
                wsk_aktualny = (*wsk_aktualny).getwsk_next();                                
                                    }
                       
            utwor *wsk;
            wsk = (*wsk_aktualny).getwsk_next();
                               
            delete wsk_aktualny;            
            wsk_aktualny = NULL;      
             
            (*przed).setwsk_next(wsk);
            --ilosc_elem;
        
            cout << " Wybrany element listy zostal usuniety " << endl;
                                  }
                                  
        else cout << " Element nie istnieje " << endl; 
                   
                           }



void lista::usun_wsk(){                                                                      //usuwa element znajdujacy sie w miejscu wskazywanym przez aktualny wskaznik
     if((wsk_aktualny==NULL) || (wsk_aktualny == wsk_pierw) ){
         cout << " Nie mozna usunac tego elementu, lub wskaznik wskazuje na NULL " << endl  ;                                                 
                                                              }
     else{
          utwor *stop = wsk_aktualny;
          wsk_aktualny = wsk_pierw;
          
          for(;(*wsk_aktualny).getwsk_next() != stop;){
          wsk_aktualny = (*wsk_aktualny).getwsk_next();                                                                                
                                                       }
          if((*stop).getwsk_next() != NULL){
          (*wsk_aktualny).setwsk_next((*stop).getwsk_next());                                  
                                            }
          else{
          (*wsk_aktualny).setwsk_next(NULL);     
               }
           
          delete stop;
          stop = NULL; 
          
          }
     
     
     
     
                       }

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

 // znacznik <hr> :-)
void hr(){
    cout << endl << "------------------------------------------------------------------------------" << endl;
          }
      





      

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


  
  
  
  
  
  
  
  
  
  
  

//MAIN FUNCTION

int main(int argc, char *argv[]){
    
                   
    lista utwory; 
    int koniec = 0;   // zmienna kontrolujaca czy wybrano zamkniecie programu

                    
    while(koniec != 1){


      int menu, wartosc, numer;     // menu - zarzadza wyborem opcji, wartosc - przekazuje wartosc do listy, numer - numer obiektu na liscie 
      hr();
      cout << " MENU ";
      hr();
     
     
     
     
     
      cout << endl << " 1.  Dodaj obiekt na koncu listy. "; 
      cout << endl << " 2.  Dodaj obiekt w wybranym miejscu. ";
      cout << endl << " 3.  Pokaz ilosc elementow. ";
      cout << endl << " 4.  Pokaz elementy. "; 
      cout << endl << " 5.  Zmien warosc pierwszego elementu. "; 
      cout << endl << " 6.  Zmien warosc ostatniego elementu. ";  
      cout << endl << " 7.  Zmien warosc wybranego elementu. ";           
      cout << endl << " 8.  Usun ostatni element. "; 
      cout << endl << " 9.  Usun wybrany element. ";
      cout << endl << " 10. Ustaw wskaznik na poczatek. "; 
      cout << endl << " 11. Ustaw wskaznik na koniec. ";    
      cout << endl << " 12. Ustaw wskaznik na wybranym miejscu. "; 
      cout << endl << " 13. Zmien wartosc komorki na ktorej jest wskaznik. "; 
      cout << endl << " 14. Odczytaj wartosc elementu pod ktorym jest wskaznik. ";    
      cout << endl << " 15. Przesun wskaznik o numer elementow. ";    
      cout << endl << " 16. Usun element na ktory wskazuje wskaznik. ";                         
      cout << endl << " 0.  Zakoncz program! " << endl;
     
     
      hr();
     
      cout << endl << " Wybor: ";     
      cin >> menu;
      cout << endl;
     
     
     
      switch (menu){
            
            
            
            
            
            case 1: cout << " Dodawanie elementu na koncu listy." << endl << endl << " Podaj wartosc: ";
                    cin >> wartosc;
                    utwory.dodaj(wartosc);     
            break;
            
            case 2: cout << " Dodawanie elementu w wybranym miejscu. " << endl << endl;
                    cout << " W przypadku gdy bedziesz chcial dodac element za obiektem ktory nie istnieje" << endl << " zostanie on dodany na koncu listy " << endl << endl ;
                    cout << " Podaj numer elementu po ktorym chcesz dodac: ";
                    cin >> numer;
                    cout << endl << " Podaj wartosc: ";
                    cin >> wartosc;
                    utwory.numer_dodaj(wartosc, numer);
            break;
            
            case 3: cout << " Ilosc elementow wynosi: " << utwory.ile() << endl; 
            break;

            case 4: cout << " Wszystkie elementy: " << endl << endl;
                    utwory.pokaz();
                    cout << endl; 
            break;
            
            case 5: cout << " Zmiana wartosci pierwszego elementu. " << endl ;
                    cout << " W przypadku braku elementu funkcja nie zrobi nic. " << endl ;
                    cout << " Podaj wartosc: ";
                    cin >> wartosc;
                    utwory.zmien_pierw(wartosc);             
            break;

            case 6: cout << " Zmiana wartosci ostatniego elementu. " << endl ;
                    cout << " W przypadku braku elementu funkcja nie zrobi nic. " << endl ;
                    cout << " Podaj wartosc: ";
                    cin >> wartosc;
                    utwory.zmien_ost(wartosc);             
            break;            
            
            case 7: cout << " Zmiana wartosci wybranego elementu. " << endl ;
                    cout << " W przypadku braku elementu funkcja nie zrobi nic. " << endl ;
                    cout << " Podaj numer: ";
                    cin >> numer; 
                    cout << " Podaj wartosc: ";
                    cin >> wartosc;                   
                    utwory.zmien_elem(wartosc, numer);             
            break;
            
            case 8: utwory.usun();
            break;
            
            case 9: cout << " Podaj numer: " ;
                    cin >> numer; 
                    if(numer != 0)utwory.usun_nr(numer);
            break;
            
            case 10: utwory.ustaw_pierwszy();
            break;            
            
            case 11: utwory.ustaw_ost();
            break;             
            
            case 12: cout << " Podaj numer: ";
                     cin >> numer;
                     utwory.ustaw_nr(numer);
            break;           
            
            case 13: cout << " Podaj wartosc: ";
                     cin >> wartosc;
                     utwory.przypisz(wartosc);
            break;             
            
            case 14: cout << " Wartosc elementu pod ktorym jest wskaznik: " << utwory.czytaj();
            break; 
            
            case 15: cout << " Podaj numer: ";
                     cin >> numer;
                     utwory.przesun_numer(numer);
            break; 
            
            case 16: utwory.usun_wsk();
            break; 
                                                     
            case 0: koniec = 1;
            break;
            
            default: cout << " Zly wybor!" << endl ;
            break; 
            
            
            
            
            
            
            
            
                   }  
                   


     
                       }   

    

    return EXIT_SUCCESS;
                                 }
                                 
                                 
                                 
                                 
                                 
                                 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
                                 
            
                                 
