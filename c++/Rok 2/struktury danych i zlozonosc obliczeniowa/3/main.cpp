/*
Struktury danych i z³o¿onoœæ obliczeniowa - Projekt
Badanie efektywnoœci algorytmów grafowych

Kamil Markuszewski 171016
Cezary Ruszkiewicz, 171154  



*/

//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
#include <fstream.h> 
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;






//-------------------------------------------------------------------------------------------------------------------
// Deklaracje funkcji:
//-------------------------------------------------------------------------------------------------------------------






void generuj( int wie, float gestosc, bool wypisz, bool zapis);
void mk_macierz(int ile_wie);
void mk_lista(int ile_wie);
void rm_macierz(int ile_wie);
void rm_lista();
void wypisz_liste(int ile_wie);
void wypisz_macierz(int ile_wie);
void szer();
void testowanie();
void symulacja();
void symulacja2();
void wybor_czas();
time_t pobierz_czas();
double difft(time_t time_po, time_t time_przed);


double prim(bool typ, int ile_wie, float gestosc, bool wypisz);

double kruskal(bool typ, int ile_wie, float gestosc, bool wypisz);

double dij(bool typ, int ile_wie, float gestosc, bool wypisz, int ktory);

double ford(bool typ, int ile_wie, float gestosc, bool wypisz);




//-------------------------------------------------------------------------------------------------------------------
// Klasy
//-------------------------------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------
/**
klasa relacji wierzcholki - krawedz
*/
      
class T_krawedz{
      public:
      int w1, w2;
      int waga;
      
      T_krawedz(int wie1, int wie2, int waga){
                    w1 = wie1;
                    w2 = wie2;
                    waga = waga;
                    }
                    
      bool operator < ( const T_krawedz& w2) const{
           if( waga < w2.waga){
               return false;
               }
           return true;
           }

      bool operator > (const T_krawedz & w2) const{
           if( waga < w2.waga){
               return false;
               }
           return true;
           }

      bool operator == (const T_krawedz & w2) const{
           if( waga != w2.waga){
               return false;
               }
           return true;
           }
 
                    
      };




//-----------------------------------------------------------------------------
/**
listowa reprezentacja grafu
*/
      
class T_GrafLista{
      
      public:
      // iloœæ wierzcho³ków i krawêdzi
      int max_wierzcholkow;
      int ile_wie;
      
      
      list<int> **wierzcholki;
      int **wagi;
      
      // konstruktor i destruktor
      T_GrafLista(){
                    cout << "I znow zle wywolujesz konstruktor" << endl;
                    }
      
      T_GrafLista(int max_w){
                      
                      wierzcholki = new list<int> *[max_w];
                      wagi = new int *[max_w];
                      
                      for( int i = 0; i< max_w; i++){
                           wagi[i] = new int[max_w];
                           for( int i2 = 0; i2 < max_w; i2++){
                                wagi[i][i2] = 0;
                                }
                           }
                      for(int i = 0; i< max_w; i++){
                              wierzcholki[i] = NULL;
                              }
                      
                      ile_wie = 0;
                      max_wierzcholkow = max_w;
                      }
                      
      ~T_GrafLista(){
                     for( int i = 0; i<max_wierzcholkow; i++){
                          delete [] wagi[i];
                          wierzcholki[i]->clear();
                          }
                          
                     delete [] wagi;
                     delete [] wierzcholki;
                     }
      public:
      void wyswietl(){
           cout << " Graf zapisany w postaci listy: \n";
           for(int w = 0; w<max_wierzcholkow; w++){
                   cout << endl  << w << " laczy sie z: ";
                   if( wierzcholki[w] != NULL){
                       for( list<int>::iterator iter = wierzcholki[w]->begin(); iter != wierzcholki[w]->end(); iter++){
                            cout<<*iter<<" ; ";                    
                            }
                       }
                   }
           cout << endl;
           }

      
      // sprawdza czy relacja miedzy wierzcholkami w1 i w2 juz istnieje
      bool istnieje(int w1, int w2){
           if( wierzcholki[w1] != NULL){
               
               bool ex = false;
               for( list<int>::iterator iter = wierzcholki[w1]->begin(); iter != wierzcholki[w1]->end(); iter++){
                    if (w2 == (*iter))
                    return true;
                    }
               }
           return false;
           }
      
      
      
      // dodawanie wierzcho³ków oraz relacji wierzcho³ków 
      void nowa(int w1,int w2, int waga){
           
      // je¿eli krawêdŸ nie dotyczy tego samego wierzcho³ka, jeszcze nie istnieje oraz nr wierzcho³ka nie jest wiêkszy od maxymalnej wartosci
      if( w1!=w2 && w1 < max_wierzcholkow && w2 < max_wierzcholkow){
          ile_wie++;
          ile_wie++;
          
          wagi[w1][w2] = waga;
          wagi[w2][w1] = waga;
          
          if( wierzcholki[w1]==NULL){
              wierzcholki[w1] = new list<int>;
              }
          if( wierzcholki[w2]==NULL){
              wierzcholki[w2] = new list<int>;
              }
              
          wierzcholki[w1]->push_back(w2);
          wierzcholki[w2]->push_back(w1);

          }
      }

      
            
      };




//-------------------------------------------------------------------------------------------------------------------
// Zmienne globalne:
//-------------------------------------------------------------------------------------------------------------------

T_GrafLista *graf_lista;  
int **macierz, **ilosc;                                                                 // macierzowa reprezentacja grafu                                 

vector<list<int> > tab_list;                                              // wektor list - listowa reprezentacja grafu                                                   
/**
Pojedyncza lista reprezentuje wierzcho³ek
Dwa kolejne elementy listy odpowiadaj¹ jednemu odwzorowaniu dla wierzcho³ka. S¹ to: 
            1. Wierzcho³ek z którym ³¹czy go krawêdŸ
            2. Waga tej krawêdzi
*/


bool fczas=1;                             // wybor sposobu pomiaru czasu
int rodz = 0;








//-------------------------------------------------------------------------------------------------------------------
// Main:
//-------------------------------------------------------------------------------------------------------------------


int main(int argc, char *argv[]){
    
    
    
    bool koniec = 0;                     // czy zakoñczyæ program
    short int menu = 0;                  // obs³uga menum

    do{
           system("cls");                // czysc ekran
           
           cout << "MENU:" << endl;
           cout << "0. Wyjdz" << endl;
           cout << "1. Przeprowadz symulacje" << endl;
           cout << "2. Funkcja pomiaru czasu (domyslnie clock())" << endl;
           cout << "3. Testuj algorytmy" << endl;
           cout << "4. Symulacja nonestop" << endl; 
           cout << "5. Szeregowe/ rownolegle czy rownoleglo-szeregowe?" << endl;          
           //koniec menu
           
           cout << endl << endl << endl;
           cout << "Wybor: ";
           cin >> menu;
           
           switch( menu){
                   case 0: koniec = 1; break;
                   case 1: symulacja(); break; 
                   case 2: wybor_czas(); break;
                   case 3: testowanie(); break;
                   case 4: symulacja2(); break;
                   case 5: szer(); break;
                   }
           cout << endl << endl;
           }while(koniec!=1);
    
    
    return EXIT_SUCCESS;
    }













//-------------------------------------------------------------------------------------------------------------------
// Funkcje:
//-------------------------------------------------------------------------------------------------------------------

/**
Tworzy globalny wektor list w klasie T_GrafLista
*/
void mk_lista(int ile_wie){
     graf_lista = new T_GrafLista(ile_wie);    
     
     }



//-----------------------------------------------------------------------------
/**
Tworzy globaln¹ macierz
*/
void mk_macierz(int ile_wie){
     macierz = new int*[ile_wie];
     for(int i = 0; i <ile_wie; i++){
             macierz[i] = new int[ile_wie];
             for(int j=0; j<ile_wie; j++){
                     macierz[i][j] = 0;
                     }
             }             
     }

//-----------------------------------------------------------------------------
/**
Usuwa globalny wektor list
*/
void rm_lista(){
     delete graf_lista;    
     }




//-----------------------------------------------------------------------------
/**
Czysci globaln¹ macierz
*/
void rm_macierz(int ile_wie){
     for(int i = 0; i <ile_wie; i++){
             delete [] macierz[i];
             }
     delete [] macierz;
     }




//-----------------------------------------------------------------------------
/**
Funkcja generuj¹ca graf
ile_wie - liczba wierzcho³ków
gestosc - gêstoœæ grafu (0.1 minimalna wartoœæ ile_wie = ile_krawedzi) 
wypisz - flaga mówi¹ca o tym czy wypisywaæ wyniki
zapis - rodzaj zapisu grafu (macierz/lista)
**/
void generuj( int ile_wie, float gestosc, bool wypisz, bool zapis){
         //----------------------------
         // Zmienne:
                    
         int w1, w2,w3, waga, licznik;            // w1 -wierzcholek 1; w2 - wierzcholek 2; waga - waga krawêdzi; licznik - licznik do tablicy wierz
         int ile_krawedzi;
    
    
    
         int *wierz;                           // tablica zapamietujaca juz wylosowane wierzcholki
         wierz = new int [ile_wie];             
         
         
         ile_krawedzi = (int)(gestosc * 10 * ile_wie);
         int **graf;                           // tablica przechowuj¹ca caly graf
         graf = new int*[ile_krawedzi];
         
         for(int i = 0; i <ile_krawedzi; i++){
                 graf[i] = new int[3];
                 }
                 
         licznik = 0;
         
         //----------------------------
         // Algorytm:   
         
         if( rodz==0){
             // Pierwsza krawêdŸ          
             w1 = licznik;
             wierz[licznik] = w1;
             do{
                  licznik++;
                  w2 = licznik;
                  }while(w1==w2);
             wierz[licznik] = w2;  
             licznik++;
             waga = rand()%ile_wie;
             waga++;                      // by wyeliminowac wagê = 0
             graf[0][0] = w1;
             graf[0][1] = w2;
             graf[0][2] = waga;
             for(int i=1; i<ile_krawedzi; i++){ // Pozosta³e krawêdzie                 
                     w1 = wierz[rand()%licznik];
                     if(licznik < ile_wie){
                                w2 = licznik;
                                wierz[licznik] = w2;
                                licznik++;
                                }else{
                                      bool ok;
                                      do{
                                          ok=true; 
                                          w2 = wierz[rand()%licznik];
                                          if(w1==w2){ok = false;} 
                                          for(int j=0; j <= i ; j++){
                                                  
                                                  if(graf[j][0]==w1){
                                                                      if(graf[j][1]==w2){ok=false;break;}
                                                                      }
                                                  if(graf[j][0]==w2){
                                                                      if(graf[j][1]==w1){ok=false;break;}
                                                                      }                         
                                                  }  
                                          }while(!ok);
                                      }
                     waga = (rand()%ile_wie +1 )%30000;                                 // waga z zakresu 1-ile_wie przy czym 30 tys (oko³o 2^15) to max
                     graf[i][0] = w1;
                     graf[i][1] = w2;
                     graf[i][2] = waga;
                     }
         
             }
         if( rodz==1){
             
             int i=0;    
             for(;i< ile_wie-1;i++){
                     waga = (rand()%ile_wie +1 )%30000; 
                     graf[i][0] = i;
                     graf[i][1] = i+1;
                     graf[i][2] = waga;
                     }
                     
             for(;i< ile_krawedzi;i++ ){
                     graf[i][0] = 0;
                     graf[i][1] = 0;
                     graf[i][2] = 0;
                     }
             
             }
         if( rodz==2){
             
             int  j=0;
             w1 = rand()%ile_wie;
                
             
             do{
                w2 = rand()%ile_wie;
                }while(w2 == w1);
                  
                  for( int i = 0; (i<ile_wie) && (j<ile_krawedzi); i++){
                       if( (w1==i) || (w2==i)){
                           continue;
                           }
                         
                      w3 = i;
                      waga = rand()%ile_wie;
                         
                      if( j >= ile_krawedzi ) break;
                      
                      graf[j][0] = w1;
                      graf[j][1] = w3;
                      graf[j][2] = waga;
                      
                      j++;
                      if( j >= ile_krawedzi ) break;
                      
                      graf[j][0] = w2;
                      graf[j][1] = w3;
                      graf[j][2] = waga;
                      
                      j++;
                      if( j >= ile_krawedzi ) break;
                      }
                  for(;j< ile_krawedzi;j++ ){
                          graf[j][0] = 0;
                          graf[j][1] = 0;
                          graf[j][2] = 0;
                          }

             }
    
    
         
         // Ewentualne wypisanie wyników losowania. Postaæ: wierzcho³ek1, wierzcho³ek2, waga krawêdzi
         if(wypisz==1){cout << "\n Wylosowano: \n (w1 . w2 . waga) \n";}
         
         for(int i=0; i < ile_krawedzi && wypisz == 1; i++){
                 cout << graf[i][0] << " . " << graf[i][1] << " . " << graf[i][2] << endl;
                 }              
         
         
         
         
         /** Wchodzimy w if je¿eli arg zapis ma wartoœæ 1 tzn je¿eli potrzebujemy zapisu grafu przy pomocy list s¹siedztwa */
         if(zapis==1){
                      for(int i = 0; i< ile_krawedzi; i++){
                              graf_lista->nowa(graf[i][0],graf[i][1],graf[i][2]);
                              }

                      // ewentualne wypisanie listy
                      if(wypisz == 1){cout << "\n Wypisanie po losowaniu: \n"; wypisz_liste(ile_wie);}                      
                      }
         
         /** Wchodzimy w if je¿eli arg zapis ma wartoœæ 0 tzn je¿eli potrzebujemy zapisu grafu przy pomocy macierzy */
         if(zapis==0){
                      // ustawianie 1 w macierzowym zapisie grafu
                      for(int i = 0; i < ile_wie; i++){
                              
                              for(int j = 0; j<ile_krawedzi; j++){
                                      if(graf[j][0] == i){
                                                    macierz[i][graf[j][1]] = graf[j][2];
                                                    }
                                      if(graf[j][1] == i){
                                                    macierz[i][graf[j][0]] = graf[j][2];
                                                    }
                                      }        
                              }
                      // ewentualne wypisanie macierzy
                      if(wypisz == 1){cout << "\n Wypisanie po losowaniu: \n"; wypisz_macierz(ile_wie);}                                          
                      }


         // czyszczenie pamiêci 
         delete [] wierz;
         
         for(int i = 0;i<ile_krawedzi;i++){
                 delete [] graf[i];
                 }
         delete [] graf;
         }
             
             
//-----------------------------------------------------------------------------
/** 
Przeprowadzanie symulacji z menu wyboru co chcemy symolowaæ
*/

    
void symulacja(){
     double sredni=0;
     short int menu;
     ofstream zapis("zapis.txt") ; 
     
     cout << "Ktory algorytm? "<<endl;
     cout << "1. Prima - macierz"<<endl;
     cout << "2. Prima - lista"<<endl;
     cout << "3. Kruskala - macierz"<<endl;
     cout << "4. Kruskala - lista"<<endl;
     cout << "5. Djikstry - macierz"<<endl;
     cout << "6. Djikstry - lista"<<endl;
     cout << "7. Forda-Bellmana - macierz"<<endl;
     cout << "8. Forda-Bellmana - lista"<<endl;
     
     cout << endl << "wybor: ";
     cin >> menu;
     cout <<endl;
     cout << endl <<endl << "--------------------------------------------------"<< endl;
     
 
   
     
          
     cout << endl <<endl << "--------------------------------------------------"<< endl;
     
     int rodz_max_g = 10, rodz_min_g = 1;
          
     if(rodz == 1){
             rodz_max_g = 2;
             }
     if(rodz == 2){
             rodz_min_g = 10;
             rodz_max_g = 11;
             }
       
     
     for( int i=rodz_min_g; i < rodz_max_g; i++){
           
           float gestosc = (float)(0.1 * (float)i);
           cout << endl << "Gestosc: " << gestosc << endl;
           
           for( int j=0, l=0;j<9;j++){
                l = l+200;
                cout << " Ilosc wierzcholkow: " << l;
                cout << "\t" << " czasy: " ;
                
                for( int i=0; i<10; i++){
                    
                     switch(menu){
                                  case 1: sredni += prim(0,l,gestosc,0); break;
                                  case 2: sredni += prim(1,l,gestosc,0); break;
                                  case 3: sredni += kruskal(0,l,gestosc,0); break;
                                  case 4: sredni += kruskal(1,l,gestosc,0); break;
                                  case 5: sredni += dij(0,l,gestosc,0, 0); break;
                                  case 6: sredni += dij(1,l,gestosc,0, 0); break;
                                  case 7: sredni += ford(0,l,gestosc,0); break;
                                  case 8: sredni += ford(1,l,gestosc,0); break;
                                  
                                  }   
                    
                    cout << " ; ";

                    }
                                    switch(menu){
                                  case 1: 
                                       zapis<< "Prim macierz \n ";
                                        break;
                                  case 2:
                                       zapis << "Prim lista  \n";
                                       break;
                                  case 3:
                                       zapis << "Kruskal macierz  ";
                                       break;
                                  case 4:
                                       zapis << "Kruskal lista  ";
                                       break;  
                                  case 5:
                                       zapis << "Dij macierz  ";
                                       break;    
                                  case 6:
                                       zapis << "Dij lista  ";
                                       break;   
                                  case 7:
                                       zapis << "Ford macierz  ";
                                       break;  
                                  case 8:
                                       zapis << "Ford lista  ";
                                       break; 
                                  
                                  }   
               sredni /= 10;
               cout << endl << "Sredni czas: " << sredni;
               zapis << "Gestosc: " << gestosc << " ilosc: " << l << " czas: " << sredni << "\n"; 
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
           //system("Pause"); 
           }
     
     zapis.close() ; 

     
         
     }
     
     
          
//-----------------------------------------------------------------------------
/** 
Przeprowadzanie symulacji ciaglej
*/

    
void symulacja2(){
     double sredni=0;
     int ile_powt = 10;
     short int menu;
     
     
     ofstream szerrown("szer-rown.txt") ; 
     for(int menu=1; menu < 9; menu++){
          szerrown << endl << "\n------------------------------------------------\n"<< endl;
                     switch(menu){
                                  case 1: 
                                       szerrown<< "Prim macierz \n ";
                                        break;
                                  case 2:
                                       szerrown << "Prim lista  \n";
                                       break;
                                  case 3:
                                       szerrown << "Kruskal macierz  ";
                                       break;
                                  case 4:
                                       szerrown << "Kruskal lista  ";
                                       break;  
                                  case 5:
                                       szerrown << "Dij macierz  ";
                                       break;    
                                  case 6:
                                       szerrown << "Dij lista  ";
                                       break;   
                                  case 7:
                                       szerrown << "Ford macierz  ";
                                       break;  
                                  case 8:
                                       szerrown << "Ford lista  ";
                                       break; 
                                  
                                  }   
                    
     for( int i=1; i < 10; i++){
           
           float gestosc = (float)(0.1 * (float)i);
           cout << endl << "Gestosc: " << gestosc << endl;
           
           for( int j=0, l=0;j<9;j++){
                l = l+200;
                cout << " Ilosc wierzcholkow: " << l;
                cout << "\t" << " czasy: " ;
                
                for( int i=0; i<ile_powt; i++){
                    
                     switch(menu){
                                  case 1: sredni += prim(0,l,gestosc,0); break;
                                  case 2: sredni += prim(1,l,gestosc,0);break;
                                  case 3: sredni += kruskal(0,l,gestosc,0);break;
                                  case 4: sredni += kruskal(1,l,gestosc,0);break;
                                  case 5: sredni += dij(0,l,gestosc,0, 0);break;
                                  case 6: sredni += dij(1,l,gestosc,0, 0);break;
                                  case 7: sredni += ford(0,l,gestosc,0);break;
                                  case 8: sredni += ford(1,l,gestosc,0);break;

                                  
                                  }   
                    
                    cout << " ; ";

                    }
               
               sredni /= ile_powt;
               cout << endl << "Sredni czas: " << sredni;
               szerrown << "Gestosc: " << gestosc << " ilosc: " << l << " czas: " << sredni << "\n"; 
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
           //system("Pause"); 
           }
           szerrown << endl << "----------------"<< endl;
           }
     szerrown.close() ; 
     
     rodz = 1;
     
     
     ofstream szer("szer.txt") ; 
     for(int menu=1; menu < 9; menu++){
          szer << endl << "\n------------------------------------------------\n"<< endl;
                     switch(menu){
                                  case 1: 
                                       szer << "Prim macierz \n ";
                                        break;
                                  case 2:
                                       szer << "Prim lista  \n";
                                       break;
                                  case 3:
                                       szer << "Kruskal macierz  ";
                                       break;
                                  case 4:
                                       szer << "Kruskal lista  ";
                                       break;  
                                  case 5:
                                       szer << "Dij macierz  ";
                                       break;    
                                  case 6:
                                       szer << "Dij lista  ";
                                       break;   
                                  case 7:
                                       szer << "Ford macierz  ";
                                       break;  
                                  case 8:
                                       szer << "Ford lista  ";
                                       break; 
                                  
                                  }   
                    
     for( int i=1; i < 2; i++){
           
           float gestosc = (float)(0.1 * (float)i);
           cout << endl << "Gestosc: " << gestosc << endl;
           
           for( int j=0, l=0;j<9;j++){
                l = l+200;
                cout << " Ilosc wierzcholkow: " << l;
                cout << "\t" << " czasy: " ;
                
                for( int i=0; i<ile_powt; i++){
                    
                     switch(menu){
                                  case 1: sredni += prim(0,l,gestosc,0); break;
                                  case 2: sredni += prim(1,l,gestosc,0);break;
                                  case 3: sredni += kruskal(0,l,gestosc,0);break;
                                  case 4: sredni += kruskal(1,l,gestosc,0);break;
                                  case 5: sredni += dij(0,l,gestosc,0, 0);break;
                                  case 6: sredni += dij(1,l,gestosc,0, 0);break;
                                  case 7: sredni += ford(0,l,gestosc,0);break;
                                  case 8: sredni += ford(1,l,gestosc,0);break;

                                  
                                  }   
                    
                    cout << " ; ";

                    }
               
               sredni /= ile_powt;
               cout << endl << "Sredni czas: " << sredni;
               szer << "Gestosc: " << gestosc << " ilosc: " << l << " czas: " << sredni << "\n"; 
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
           //system("Pause"); 
           }
           szer << endl << "----------------"<< endl;
           }
     szer.close() ; 
     
     rodz = 2;
     
     
     
     
     ofstream zapis("rown.txt") ; 
     for(int menu=1; menu < 9; menu++){
             if(menu == 1 || menu == 3)continue;
             
          zapis << endl << "\n------------------------------------------------\n"<< endl;
                     switch(menu){
                                  case 1: 
                                       zapis << "Prim macierz \n ";
                                        break;
                                  case 2:
                                       zapis << "Prim lista  \n";
                                       break;
                                  case 3:
                                       zapis << "Kruskal macierz  ";
                                       break;
                                  case 4:
                                       zapis << "Kruskal lista  ";
                                       break;  
                                  case 5:
                                       zapis << "Dij macierz  ";
                                       break;    
                                  case 6:
                                       zapis << "Dij lista  ";
                                       break;   
                                  case 7:
                                       zapis << "Ford macierz  ";
                                       break;  
                                  case 8:
                                       zapis << "Ford lista  ";
                                       break; 
                                  
                                  }   
                    
     for( int i=1; i < 10; i++){
           
           float gestosc = (float)(0.1 * (float)i);
           cout << endl << "Gestosc: " << gestosc << endl;
           
           for( int j=0, l=0;j<9;j++){
                l = l+200;
                cout << " Ilosc wierzcholkow: " << l;
                cout << "\t" << " czasy: " ;
                
                for( int i=0; i<ile_powt; i++){
                    
                     switch(menu){
                                  case 1: sredni += prim(0,l,gestosc,0); break;
                                  case 2: sredni += prim(1,l,gestosc,0);break;
                                  case 3: sredni += kruskal(0,l,gestosc,0);break;
                                  case 4: sredni += kruskal(1,l,gestosc,0);break;
                                  case 5: sredni += dij(0,l,gestosc,0, 0);break;
                                  case 6: sredni += dij(1,l,gestosc,0, 0);break;
                                  case 7: sredni += ford(0,l,gestosc,0);break;
                                  case 8: sredni += ford(1,l,gestosc,0);break;

                                  
                                  }   
                    
                    cout << " ; ";

                    }
               
               sredni /= ile_powt;
               cout << endl << "Sredni czas: " << sredni;
               zapis << "Gestosc: " << gestosc << " ilosc: " << l << " czas: " << sredni << "\n"; 
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
           //system("Pause"); 
           }
           zapis << endl << "----------------"<< endl;
           }
     zapis.close() ; 
     
     
     
     
     
     
     

     
         
     }
//-----------------------------------------------------------------------------
/** 
Wywolanie jednokrotnie algorytmu z wypisywaniem wynikow dla sprawdzenia poprawnosci
*/ 
     
     
void testowanie(){
     float gestosc = 0.15;
     if(rodz == 1){
             gestosc = 0.1;
             }
     if(rodz == 2){
             gestosc = 0.3;
             }
     
     
     cout << endl << "------------------------------\n" << endl;
     cout << endl << "Prim: \n" << endl;
     prim(0, 8, gestosc, 1);
     prim(1, 8, gestosc, 1);
     cout << endl;
     system("Pause"); 
     
     cout << endl << "------------------------------\n" << endl;
     cout << endl << "Kruskal: \n" << endl;
     kruskal(0, 8, gestosc, 1);
     kruskal(1, 8, gestosc, 1);
     cout << endl;
     system("Pause"); 
     
     cout << endl << "------------------------------\n" << endl;
     cout << endl << "Dijkstra: \n" << endl;
     dij(0, 8,gestosc, 1, 0);
     dij(1, 8, gestosc, 1, 0);
     cout << endl;
     system("Pause");
     
     cout << endl << "------------------------------\n" << endl;
     cout << endl << "Ford-Bellman: \n" << endl;
     ford(0, 10, gestosc, 1);
     ford(1, 8, gestosc, 1);
     cout << endl;
     system("Pause");  
     
     
     }
     
     
     void stop(){
          system("Pause");
          cout << "\nstop()\n";
          }
     
     
     
     
//-----------------------------------------------------------------------------
/*
Ustawia metode pomiaru czasu
*/

void wybor_czas(){
     int pomocnicza;
         cout << "Uzywac time() czy clock()? 0/1" <<endl;
         cin >> pomocnicza;
         switch(pomocnicza){
                            case 0: fczas = 0; cout << "time()" <<endl; break;
                            case 1: fczas = 1; cout << "clock()" <<endl; break;          
                            default: cout << "zly wybor, nic nie zmienione" <<endl; break;
                            } 
         system("Pause");          
     }


//-----------------------------------------------------------------------------
/*
Pobiera czas metoda zalezna od globalnej flagi
*/

time_t pobierz_czas(){
       if( fczas==1){
           return clock ();
           }
           else{
                return time(NULL);
                }           
       }
       
       
//-----------------------------------------------------------------------------
/*
Oblicza czas wykonywania sie algorytmu dla metod clock() i time()
*/

double difft(time_t time_po, time_t time_przed){   
       if( fczas==1){
           return (difftime(time_po, time_przed) / CLOCKS_PER_SEC);
           }
           else{
                return difftime(time_po, time_przed);
                }   
       
       }

//-----------------------------------------------------------------------------
/*
Wypisuje macierz
*/

void wypisz_macierz(int ile_wie){
     cout << endl << " Postac macierzy sasiedztwa grafu \n";
     // ewentualne wypisanie macierzy
     for(int i = 0; i < ile_wie; i++){
             for(int j = 0; j < ile_wie; j++){
                     cout << macierz[i][j] << "\t";
                     }
             cout << endl;        
             }
     }
//-----------------------------------------------------------------------------
/*
Wypisuje liste
*/

void wypisz_liste(int ile_wie){
     
     graf_lista->wyswietl();
     cout << endl;
     }
     
     
//-----------------------------------------------------------------------------
/*
Szeregowe rownolegle czy rownoleglo szeregowe
*/
     
void szer(){
     int wybor;
     cout << " 0 - rownloleglo-szeregowe \n 1 - szeregowe \n 2 - rownolegle \n";
     cin >> wybor;
     
     switch(wybor){
                   case 0: rodz = 0; cout << "\n ustawiono na rownloleglo-szeregowe\n"; break;
                   case 1: rodz = 1; cout << "\n ustawiono na szeregowe \n"; break;
                   case 2: rodz = 2; cout << "\n ustawiono na  rownolegle\n"; break;
                   default: cout << "\n zly wybor \n"; break;
                   }
     system("Pause");
     }
     
     
     
//-----------------------------------------------------------------------------
/*
Sprawdzanie czy wierzcholki naleza do tego samego poddrzewa
*/
     
     
     
     int find(int szukana,int *wierzcholki){
	     if (wierzcholki[szukana]==szukana) return szukana; 
	
	     int fszukana = find(wierzcholki[szukana], wierzcholki);
	     wierzcholki[szukana] = fszukana; 
	     return fszukana;
         }

     
     bool unia(int a, int b,int *ilosc,int *wierzcholki ){
	      int a2;
	      int b2; 
 
          a2 = find(a, wierzcholki); 
          b2 = find(b, wierzcholki); 
	      if( a2==b2){
              return false;       
              } 
	         
          if( !(ilosc[a2] > ilosc[b2])){
		      ilosc[b2] = ilosc[b2] + ilosc[a2];
		      wierzcholki[a2] = b2;
	          }
          else{
		       ilosc[a2] = ilosc[a2]+ ilosc[b2];
		       wierzcholki[b2] = a2;
	           }
         return true;
         }

     
     
     







//-------------------------------------------------------------------------------------------------------------------
// Testowane algorytmy
//-------------------------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------
/*
Algorytm Prima. 
Arg: bool typ   0 - macierz 1-lista
arg: ile_wie - ilosc wierzcholkow
arg: gestosc - gestosc grafu (min 0.1 ... wtedy ile_wie = ile_krawedzi)
arg: wypisz - czy wypisaæ wyniki
*/

double prim(bool typ, int ile_wie, float gestosc, bool wypisz){

        

        clock_t time_przed;                  // pomiar czasu prz sortowaniem
        clock_t time_po;                     // pomiar czasu po sortowaniu
        double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     
        
        
       
        if( typ==0){
            mk_macierz(ile_wie);          
            generuj(ile_wie,gestosc,wypisz,typ);

            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem
            
            
            int **rozpinajace = new int*[ile_wie];
            for(int i=0; i<ile_wie; i++){
                    rozpinajace[i]=new int[ile_wie];
                    for(int j=0; j<ile_wie; j++){
                            rozpinajace[i][j] = 0;
                            }
                    }      
            
                    
            
            bool koniec = false;                 // czy wszystkie wierzcholki polaczone
            int w2= 0, w1 = 0, dodawana;                              // wierzcholek z ktorym aktualie lacze
            int w2_waga;
            
            bool *dodane = new bool[ile_wie];                                     // czy wierzcholek juz jest dodany do drzewa rozpinajacego
            for(int i=1;i<ile_wie;i++){
                    dodane[i] = 0;
                    }
            dodane[0] = 1;  
            
            
            while( !koniec){
                   dodawana = 0;
                   w2_waga = 62000;
                   for(int i=0; i<ile_wie;i++){
                           if( dodane[i]!=0 ){  // do dodanego juz wierzcholka dodaje inne
                               // lista graf_lista->wierzcholki[i] jest posortowana, sortuje siê przy dok³adaniu elementu
                               for( int j=0; j<ile_wie; j++){
                                    // patrze z jakimi laczy sie wierzcholek i
                                    w2 = j;
                                    // sprawdzam czy te z ktorymi sie laczy nie jest jeszcze dodany
                                    if(dodane[j]==0&&macierz[i][j]!=0){ 
                                                     // nie jest dodany wiec zaisuje jego wage i szukam czy jest max
                                                     if(macierz[i][j]<w2_waga){
                                                                                         w1 = i;
                                                                                         dodawana = w2;
                                                                                         w2_waga = macierz[w1][dodawana];      
                                                                                         }
                                                     }
                                    }      
                               }
                           }
                          
                   

                   rozpinajace[w1][dodawana] = w2_waga;      // dodaje krawedz do drzewa rozpinajacego
                   rozpinajace[dodawana][w1] = w2_waga;
                                          
                   dodane[dodawana] = 1;         // zaznaczam ze juz jest dodana

                   koniec = true;
                   for(int i=0; i<ile_wie;i++){
                           if( dodane[i]==0){
                               koniec = false;      
                               }
                           }
                   }
            
            rm_macierz(ile_wie);
            macierz = rozpinajace;  
            
            


            
            time_po = pobierz_czas(); 
                             // pomiar czasu po algorytmie
            if(wypisz == 1){cout << "\n Wypisanie po algorytmie: \n";wypisz_macierz(ile_wie); cout << "\n czas: " ;} 
            rm_macierz(ile_wie);
            
            delete [] dodane;
            
            }
                  
        if( typ==1){
            mk_lista(ile_wie);
            
            generuj(ile_wie,gestosc,wypisz,typ);
            
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem
            
            for(int w = 0; w<ile_wie;w++){
                    graf_lista->wierzcholki[w]->sort();
                    }
            
           
           
            bool koniec = false;                 // czy wszystkie wierzcholki polaczone
            int w2, w1, dodawana;                              // wierzcholek z ktorym aktualie lacze
            int w2_waga;
            T_GrafLista* rozpinajace = new T_GrafLista(ile_wie);                  // drzewo rozpinajace
            bool *dodane = new bool[ile_wie];                                     // czy wierzcholek juz jest dodany do drzewa rozpinajacego
            for(int i=1;i<ile_wie;i++){
                    dodane[i] = 0;
                    }
            dodane[0] = 1;        
            
            
            while( !koniec){
                   dodawana = 0;
                   w2_waga = 62000;
                   for(int i=0; i<ile_wie;i++){
                                     
                           if( dodane[i]!=0 ){  // do dodanego juz wierzcholka dodaje inne
                               // lista graf_lista->wierzcholki[i] jest posortowana, sortuje siê przy dok³adaniu elementu
                               for( list<int>::iterator iter = graf_lista->wierzcholki[i]->begin(); iter != graf_lista->wierzcholki[i]->end(); iter++){
                                    // patrze z jakimi laczy sie wierzcholek i
                                    w2 = *iter;

                                    
                                    // sprawdzam czy te z ktorymi sie laczy nie jest jeszcze dodany
                                    if(dodane[w2]==0){     
                                                     // nie jest dodany wiec zaisuje jego wage i szukam czy jest max
                                                     if(graf_lista->wagi[i][w2]<w2_waga){
                                                                                         //stop(); 
                                                                                         w1 = i;
                                                                                         dodawana = w2;
                                                                                         w2_waga = graf_lista->wagi[i][dodawana];
                                                                                         }
                                                     }
                                    }      
                               }
                           }
                   rozpinajace->nowa(w1,dodawana, w2_waga);                         // dodaje krawedz do drzewa rozpinajacego
                   dodane[dodawana] = 1;         // zaznaczam ze juz jest dodana

                   koniec = true;
                   for(int i=0; i<ile_wie;i++){
                           if( dodane[i]==0){
                               koniec = false;      
                               }
                           }
                   }
            rm_lista();    
            graf_lista = rozpinajace;        



            
           
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            
            if(wypisz == 1){cout << "\n Wypisanie po algorytmie: \n";wypisz_liste(ile_wie); cout << "\n czas: " ;} 
            
            rm_lista();
            delete [] dodane;
            }                 
       
       
       time_roznica = difft(time_po, time_przed);
       cout << time_roznica;
       return time_roznica;
       }


//-----------------------------------------------------------------------------
/*
Algorytm Kruskala. 
Arg: bool typ   0 - macierz 1-lista
arg: ile_wie - ilosc wierzcholkow
arg: gestosc - gestosc grafu (min 0.1 ... wtedy ile_wie = ile_krawedzi)
arg: wypisz - czy wypisaæ wyniki
*/

double kruskal(bool typ, int ile_wie, float gestosc, bool wypisz){

        

        clock_t time_przed;                  // pomiar czasu prz sortowaniem
        clock_t time_po;                     // pomiar czasu po sortowaniu
        double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
        
     
            

        
       
        if( typ==0){
            mk_macierz(ile_wie);          
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem

            bool koniec = false;                 // czy wszystkie wierzcholki polaczone
                        

            
            int **rozpinajace = new int*[ile_wie];
            for(int i=0; i<ile_wie; i++){
                    rozpinajace[i]=new int[ile_wie];
                    for(int j=0; j<ile_wie; j++){
                            rozpinajace[i][j] = 0;
                            }
                    }    
           

            // Tablica sprawdzajaca przynaleznosc wierzcholkow do podgrafow
            int *wierzcholki;
            wierzcholki = new int[ile_wie];
            int *ilosc;
            ilosc = new int[ile_wie];
            //int ile_krawedzi = ile_wie*ile_wie;
            
            for(int j = 0; j< ile_wie;j++){
                    wierzcholki[j] = j;
                    ilosc[j] = j;     
                    }

            // Algorytm dla grafu
            
            
            while( !koniec){
                   int w1, w2, waga_min=62000;
                   for(int i=0; i<ile_wie; i++){
                           for(int j=0; j<ile_wie;j++){
                                   if((macierz[i][j]<waga_min)&& (macierz[i][j]!=0) && (find(i,wierzcholki)!=find(j,wierzcholki))){
                                                              waga_min = macierz[i][j];
                                                              w1 = i;
                                                              w2 = j;
                                                              }
                                   }                         
                           }
                   unia(w1,w2,ilosc,wierzcholki);
                   rozpinajace[w1][w2] = waga_min;
                   rozpinajace[w2][w1] = waga_min;


                   koniec = true;
                   for(int i=0, j=1; j<ile_wie;i++, j++){
                           if( find(i,wierzcholki)!=find(j,wierzcholki)){
                               koniec = false; 
                               } 
                           }
                   }
            rm_macierz(ile_wie);
            macierz = rozpinajace;
            
            
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            if(wypisz == 1){cout << "\n Wypisanie po algorytmie: \n";wypisz_macierz(ile_wie); cout << "\n czas: " ;} 
            

            rm_macierz(ile_wie);
            }
                  
        if( typ==1){
            mk_lista(ile_wie);
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem
            for(int w = 0; w<ile_wie;w++){
                    graf_lista->wierzcholki[w]->sort();
                    }
            bool koniec = false;                 // czy wszystkie wierzcholki polaczone
            
            T_GrafLista* rozpinajace = new T_GrafLista(ile_wie);                  // drzewo rozpinajace  
           

            // Tablica sprawdzajaca przynaleznosc wierzcholkow do podgrafow
            int *wierzcholki;
            wierzcholki = new int[ile_wie];
            int *ilosc;
            ilosc = new int[ile_wie];
            int ile_krawedzi = ile_wie*ile_wie;
            
            for(int j = 0; j< ile_wie;j++){
                    wierzcholki[j] = j;
                    ilosc[j] = j;     
                    }

            // Algorytm dla grafu
            
            
            while( !koniec){
                   
                   int w1, w2,dodawana, waga_min=62000;
                   for(int i=0; i<ile_wie; i++){
                            
                           for( list<int>::iterator iter = graf_lista->wierzcholki[i]->begin(); iter != graf_lista->wierzcholki[i]->end(); iter++){
                                // patrze z jakimi laczy sie wierzcholek i
                                w2 = *iter;

                                    
                                // sprawdzam czy te z ktorymi sie laczy nie jest jeszcze dodany
                                if( find(i,wierzcholki)!=find(w2,wierzcholki) ){     
                                    // nie jest dodany wiec zaisuje jego wage i szukam czy jest max
                                    if(graf_lista->wagi[i][w2]<waga_min){
                                                                                         
                                                                                         w1 = i;
                                                                                         dodawana = w2;
                                                                                         waga_min = graf_lista->wagi[i][dodawana];
                                                                                         }
                                                     }
                                    }      
                           
                                                           
                           }
                   
                   //cout << "Unia :" << w1 << " " << 
                   unia(w1,dodawana,ilosc,wierzcholki);
                   rozpinajace->nowa(w1,dodawana, waga_min); 
                   
                   koniec = true;
                   
                   for(int i=0, j=1; j<ile_wie;i++, j++){
                           if( find(i,wierzcholki)!=find(j,wierzcholki)){
                               koniec = false; 
                               } 
                           }
                          
                   }
            
            rm_lista();
            graf_lista = rozpinajace; 
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            if(wypisz == 1){cout << "\n Wypisanie po algorytmie: \n";wypisz_liste(ile_wie); cout << "\n czas: " ;} 
            delete [] wierzcholki;
            delete [] ilosc;
            rm_lista();
            }                 
       
        
            time_roznica = difft(time_po, time_przed);
            cout << time_roznica;
            return time_roznica;
            }


//-----------------------------------------------------------------------------
/*
Algorytm Dijkstry 
Arg: bool typ   0 - macierz 1-lista
arg: ile_wie - ilosc wierzcholkow
arg: gestosc - gestosc grafu (min 0.1 ... wtedy ile_wie = ile_krawedzi)
arg: wypisz - czy wypisaæ wyniki
*/
class T_wierzcholek_dij{
      
      public:
             int w;
             int *d;
             
             T_wierzcholek_dij(int j, int *de){
                         w = j;
                         d = de;
                         }

            bool operator < ( const T_wierzcholek_dij & w2) const{
                 if( (*d) > (*(w2.d))){
                     return true;             
                     }
                 return false;
                 }
                 
            };









double dij(bool typ, int ile_wie, float gestosc, bool wypisz, int ktory){

        

        clock_t time_przed;                  // pomiar czasu prz sortowaniem
        clock_t time_po;                     // pomiar czasu po sortowaniu
        double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
        

        if( typ==0){
            mk_macierz(ile_wie);          
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem


            int *odl = new int[ile_wie];         // aktualna najmniejsza odleglosc
            for(int i = 0; i< ile_wie; i++){
                    odl[i] = 32768;
                    }
   
            odl[0] = 0;
            
            // wrzucamy wszystko do kolejki
            priority_queue<T_wierzcholek_dij> kolejka;
            for( int j=0; j<ile_wie; j++){
                 T_wierzcholek_dij *wierzch = new T_wierzcholek_dij(j,&odl[j]);
                 
                 kolejka.push(*wierzch);
                 } 
                 
           
                int w;
                while( !kolejka.empty()){
 
                       
                       w = kolejka.top().w;
                       
                       for(int i = 0; i < ile_wie; i++){
                                                
                           if( !(macierz[w][i]==0)){
                               
                               
                         
                               if( (macierz[w][i] + odl[w]) < odl[i]){
                                   odl[i] = macierz[w][i]+ odl[w];
                                   }
                               }
                           }
                          
                       kolejka.pop();
                       }  
             
            
           
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            if(wypisz == 1){
                      
                      cout << "\n Wypisanie po algorytmie: \n";
                      cout << "\n Najkrotsza droga z 0 do kolejnych wierzcholkow: \n";
                      
                      for(int i=0; i<ile_wie;i++){
                              cout << odl[i]<< "  ,  ";                     
                                                
                    
                              }  
            
                      cout << "\n czas: " ;
                      } 
            
            rm_macierz(ile_wie);
            
            }
                  
        if( typ==1){
            mk_lista(ile_wie);
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem
            
            int *odl = new int[ile_wie+8];         // aktualna najmniejsza odleglosc
            for(int i = 0; i< ile_wie; i++){
                    odl[i] = 32768;
                    }
   
            odl[0] = 0;
            
            // wrzucamy wszystko do kolejki
            priority_queue<T_wierzcholek_dij> kolejka;
            for( int j=0; j<ile_wie; j++){
                 T_wierzcholek_dij *wierzch = new T_wierzcholek_dij(j,&odl[j]);
                 
                 kolejka.push(*wierzch);
                 } 
                 
           
                int w;
                while( !kolejka.empty()){

                      
                       w = kolejka.top().w;
                       for(list<int>::iterator iter = graf_lista->wierzcholki[w]->begin(); iter != graf_lista->wierzcholki[w]->end(); iter++){                 
                              
                              
                  
                                               if( (odl[w] + graf_lista->wagi[w][*iter]) < odl[*iter]){
                                                   odl[*iter] = odl[w] + graf_lista->wagi[w][*iter];
                                                   }
                                               }


                          
                      kolejka.pop();
                      }  
             
            
           
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            if(wypisz == 1){
                      cout << "\n Wypisanie po algorytmie: \n";
                      
                      wypisz_liste(ile_wie); 
                      
                      
                      cout << "\n Najkrotsza droga z 0 do kolejnych wierzcholkow: \n";
                      
                      for(int i=0; i<ile_wie;i++){
                              cout << odl[i]<< "  ,  ";                     
                              }  
                      cout << endl;
                      cout << "\n czas: ";
                      }
  
            rm_lista();
            }                 
       
       
       time_roznica = difft(time_po, time_przed);
       cout << time_roznica;
       return time_roznica;
       }


//-----------------------------------------------------------------------------
/*
Algorytm Forda-Bellmana
Arg: bool typ   0 - macierz 1-lista
arg: ile_wie - ilosc wierzcholkow
arg: gestosc - gestosc grafu (min 0.1 ... wtedy ile_wie = ile_krawedzi)
arg: wypisz - czy wypisaæ wyniki
*/

double ford(bool typ, int ile_wie, float gestosc, bool wypisz){

        

        clock_t time_przed;                  // pomiar czasu prz sortowaniem
        clock_t time_po;                     // pomiar czasu po sortowaniu
        double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     

        
       
        if( typ==0){
            mk_macierz(ile_wie);          
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem

            int *odl = new int[ile_wie];         // aktualna najmniejsza odleglosc
            for(int i = 0; i< ile_wie; i++){
                    odl[i] = 32768;
                    }
   
            odl[0] = 0;
            

            for( int i = 1; i<ile_wie-1; i++){
                 for( int w1 = 0; w1<ile_wie; w1++){
                      for( int w2 = 0; w2 <ile_wie; w2++){                 
                           if( macierz[w1][w2]!=0){
                               int tmp = odl[w2] + macierz[w1][w2];
                               if( odl[w1] > tmp ){
                                   odl[w1] = tmp;
                                   }
                               }
                           }
             
                      }
                 }


            
           
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            if(wypisz == 1){
                      
                      cout << "\n Wypisanie po algorytmie: \n";
                      cout << "\n Najkrotsza droga z 0 do kolejnych wierzcholkow: \n";
                      
                      for(int i=0; i<ile_wie;i++){
                              cout << odl[i]<< "  ,  ";                     
                                                
                    
                              }  
            
                      cout << "\n czas: " ;
                      } 
            
            rm_macierz(ile_wie);
            delete [] odl;
            }
                  
        if( typ==1){
            mk_lista(ile_wie);
            generuj(ile_wie,gestosc,wypisz,typ);
            time_przed = pobierz_czas();         // pomiar czasu przed algorytmem
            
            for(int w = 0; w<ile_wie;w++){
                    graf_lista->wierzcholki[w]->sort();
                    }
            
            int *odl = new int[ile_wie];         // aktualna najmniejsza odleglosc
            for(int i = 0; i< ile_wie; i++){
                    odl[i] = 32768;
                    }
   
            odl[0] = 0;
            

            for( int i = 1; i<ile_wie-1; i++){
                 for( int w1 = 0; w1<ile_wie; w1++){
                      for(list<int>::iterator iter = graf_lista->wierzcholki[w1]->begin(); iter != graf_lista->wierzcholki[w1]->end(); iter++){                 
                           if( graf_lista->wagi[w1][*iter]!=0){
                               if( odl[w1] > odl[*iter] + graf_lista->wagi[w1][*iter]){
                                   odl[w1] = odl[*iter] + graf_lista->wagi[w1][*iter];
                                   }
                               }
                           }
             
                      }
                 }
            
           
            time_po = pobierz_czas();                  // pomiar czasu po algorytmie
            
            
            if(wypisz == 1){
                      
                      cout << "\n Wypisanie po algorytmie: \n";
                      cout << "\n Najkrotsza droga z 0 do kolejnych wierzcholkow: \n";
                      
                      for(int i=0; i<ile_wie;i++){
                              cout << odl[i]<< "  ,  ";                     
                                                
                    
                              }  
            
                      cout << "\n czas: " ;
                      } 
            
            
            
            
            
            
            
            rm_lista();
                   }                 
        
        
       time_roznica = difft(time_po, time_przed);
       cout << time_roznica;
       return time_roznica;
       }
