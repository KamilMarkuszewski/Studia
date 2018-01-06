#include "T_szablon.h"

using namespace std;



template <class Typ>
tablica<Typ>::tablica(int nr){
                          nowa(nr);                       
                          }
                     
template <class Typ>
tablica<Typ>::tablica(const tablica & rhs){
                            ile = rhs.get_ile();    
                            element = new Typ[ile];
                            if( element==NULL){
                                throw brak_pamieci();
                                }
                            for(int i=0; i < ile; i++){
                                    element[i]= rhs.element[i];
                                   
                                    }
                            aktualnie = rhs.get_aktualnie();                  
                            }
                          



template <class Typ>                                                           // alokuje od nowa tablice
void tablica<Typ>::nowa(int rozmiar){
     ile = rozmiar;
     element = new Typ[rozmiar];
     aktualnie =0;
     if( element==NULL){
         throw brak_pamieci();
         }
     }
     
     
                         
template <class Typ>                                                              // dwukrotnie zwieksza rozmiar tablicy  
void tablica<Typ>::zwieksz(){
     if(ile>0){
               ile *=2; 
               Typ *wsk_tmp = new Typ[ile];
               if( wsk_tmp == NULL){
                   throw brak_pamieci();
                   }
               for( int i=0; i< aktualnie; i++){
                    wsk_tmp[i]= element[i];
                    }   
               delete [] element;   
               element = wsk_tmp;
               
               
               }
     else{
          ile=1;
          element = new Typ[ile];
          }
           
     }                      
                          




template <class Typ>                                                                 // dodaje element na koniec
void tablica<Typ>::push_back(Typ obiekt){
     if( aktualnie<ile){
         element[aktualnie] = obiekt; 
         aktualnie++;
         }  
     else{
          if(ile>0){
                    zwieksz();
                    element[aktualnie] = obiekt; 
                    aktualnie++;
                    }
          else{
               nowa(1);
               element[aktualnie] = obiekt; 
               aktualnie++;
               }
          
          }           
     }   

template <class Typ>                                                             // wyswietla wszystkie elementy
void tablica<Typ>::wyswietl(){
     for(int i=0; i<aktualnie; i++ ){
             
             cout <<   element[i] << endl;
             }            
     }   




template <class Typ>                                                               // kasuje cala tablice
void tablica<Typ>::kasuj(){
     delete [] element;
     element=NULL;
     aktualnie=0;
     ile=0;           
     }   

template <class Typ>                                                                // wyswietla obiekt znajdujacy sie pod podanym numerem
void tablica<Typ>::at(int n){
     if( (aktualnie==0) || (aktualnie <= n) ){
          throw zly_rozmiar();
          }
     cout << element[n] << endl;
     }   


template <class Typ>                                                                   // zmienia obiekt spod podanego numeru
void tablica<Typ>::zmien(int n){                                                    
     
     if( (aktualnie==0) || (aktualnie <= n)){
         throw zly_rozmiar();
         }
     cout << " Uzupelnij dane: ";
     cin >> element[n];
        
     }   

template <class Typ>                                                                   // sortowanie bombelkowe
void tablica<Typ>::sort(){                                                    
     bool zmiana=0;
     do{
        zmiana = 0; 
        Typ temp; 
        for( int i=0;i<aktualnie-1;i++){
             if( element[i]>element[i+1]){
                 temp = element[i];
                 element[i] = element[i+1];
                 element[i+1] = temp;
                 zmiana =  1; 
                 }
             }
        
        }while(zmiana==1);
        
     } 



