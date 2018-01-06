/**
Politechnika Wroclawska
Struktury danych i zlozonosc obliczeniowa
Projekt

Kamil Markuszewski
171016
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


//------------------------------------------------------------------------------
//------------KONIEC NAG£ÓWKA---------------------------------------------------
//------------------------------------------------------------------------------

void testowanie();
bool symulacja();
bool symulacja2();
double bombelkowe(int x, short int przyp);
double shell(int x, short int przyp, int param);
double scalanie(int n, short int przyp);
double kopcowanie(int n, short int przyp);
double kubelkowe(int n, short int przyp, int zakres);
double quick(int n, short int przyp);

void wyswietlanie();
void wypelnij(int* tab,short int przyp, int n, int zakres);
void wypisz(int* tab, int n);
void wybor_czas();
time_t pobierz_czas();
double difft(time_t time_po, time_t time_przed);



bool wyswietl=0;                          // wyswtetlanie posortowanych liczb 
bool fczas=1;                             // wybor sposobu pomiaru czasu

//------------------------------------------------------------------------------
//------------MAIN JAKO MENU ---------------------------------------------------
//------------------------------------------------------------------------------


int main (){
    
    bool koniec = 0;                     // czy zakoñczyæ program
    short int menu = 0;                  // obs³uga menu

    
    
    do{
           system("cls");                // czysc ekran
           
           cout << "MENU:" << endl;
           cout << "0. Wyjdz" << endl;
           cout << "1. Przeprowadz symulacje" << endl;
           cout << "2. Wyswietlanie liczb (domyslnie 0)" << endl;
           cout << "3. Funkcja pomiaru czasu (domyslnie clock())" << endl;
           cout << "4. Testuj algorytmy" << endl;
           cout << "5. Przeprowadz symulacje bez zatrzymania" << endl;
           
           //koniec menu
           
           cout << endl << endl << endl;
           cout << "Wybor: ";
           cin >> menu;
           
           switch( menu){
                   case 0: koniec = 1; break;
                   case 1: symulacja(); break; 
                   case 2: wyswietlanie(); break;
                   case 3: wybor_czas(); break;
                   case 4: testowanie(); break;
                   case 5: symulacja2(); break; 
                   }
           cout << endl << endl;
           }while(koniec!=1);
    
    return 0;
    
    }
    
//------------------------------------------------------------------------------
//------------ZARZADZANIE SORTOWANIAMI------------------------------------------
//------------------------------------------------------------------------------

    
    
    
bool symulacja(){
     double sredni=0;
     short int menu;
     int zakres = 0;
     int h = 3;
     
     cout << "Ktory algorytm? "<<endl;
     cout << "1. sortowanie bombelkowe"<<endl;
     cout << "2. sortowanie Shella"<<endl;
     cout << "3. sortowanie przez scalanie"<<endl;
     cout << "4. sortowanie przez kopcowanie"<<endl;
     cout << "5. sortowanie kubelkowe"<<endl;
     cout << "6. sortowanie szybkie"<<endl;
     
     cout << endl << "wybor: ";
     cin >> menu;
     cout <<endl;
     cout << endl <<endl << "--------------------------------------------------"<< endl;
     
     
     
     switch(menu){
                  case 1: cout << "Sortowanie bombelkowe "<< endl; break;
                  case 2: cout << "Sortowanie Shella "<< endl;
                          cout << endl << "Wybierz parametr h: ";
                          cin >> h;
                          cout << endl;
                          break;
                  case 3: cout << "Sortowanie przez scalanie "<< endl; break;
                  case 4: cout << "Sortowanie przez kopcowanie "<< endl; break;
                  case 5: cout << "Sortowanie kubelkowe "<< endl; 
                          cout << endl << "Wybierz zakres elementow: "  << endl;
                          cin >> zakres;
                          cout << endl;
                          break;
                  
                  case 6: cout << "Sortowanie szybkie "<< endl; break;
                  default: cout << "zly wybor. "; system("Pause"); return 1;
                  }     
     
     
     for( int a=0; a<=2; a++){
          
          if(a==0){
                   cout <<" posortowane "<< endl;
                   }
                   else{
                        if(a==1){
                                 cout <<" losowo "<< endl;
                                 }
                                 else{
                                      cout <<" wspak "<< endl;
                                      }
                        }
          
          
          
          cout << endl <<endl << "--------------------------------------------------"<< endl;
     
          
     
     
     
          for( int j=0, l=4096; j<13;j++){
               l *=2;
               cout << " Elementy: " << l;
               cout << "\t\t\t\t\t" << " czasy: " ;
               for( int i=0; i<10; i++){
               
                    switch(menu){
                                 case 1: sredni += bombelkowe(l, a); break;
                                 case 2: sredni += shell(l, a, h); break;
                                 case 3: sredni += scalanie(l, a); break;
                                 case 4: sredni += kopcowanie(l, a); break;
                                 case 5: sredni += kubelkowe(l, a, zakres); break;
                                 case 6: sredni += quick(l, a); break;
                                 }   
                    
                    cout << " ; ";

                    }
               
               sredni /= 10;
               cout << endl << "Sredni czas: " << sredni;
          
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
          system("Pause");     
          }


     
     
     return 0;
     
     }
     
          
     
     
bool symulacja2(){
     double sredni=0;
     short int menu;
     int zakres = 0;
     int h = 3;
     for(menu=6; menu>=1; menu--){
     
     
     switch(menu){
                  case 1: cout << "Sortowanie bombelkowe "<< endl; break;
                  case 2: cout << "Sortowanie Shella "<< endl;
                          cout << "h = " << 3;
                          h = 3;
                          break;
                  case 3: cout << "Sortowanie przez scalanie "<< endl; break;
                  case 4: cout << "Sortowanie przez kopcowanie "<< endl; break;
                  case 5: cout << "Sortowanie kubelkowe "<< endl; 
                          cout << endl << "liczba elementow: " << " 10000 " << endl;
                          zakres = 10000;
                          cout << endl;
                          break;
                  
                  case 6: cout << "Sortowanie szybkie "<< endl; break;
                  default: cout << "zly wybor. "; system("Pause"); return 1;
                  }     
     
     
     for( int a=0; a<=2; a++){
          
          if(a==0){
                   cout <<" posortowane "<< endl;
                   }
                   else{
                        if(a==1){
                                 cout <<" losowo "<< endl;
                                 }
                                 else{
                                      cout <<" wspak "<< endl;
                                      }
                        }
          
          
          
          cout << endl <<endl << "--------------------------------------------------"<< endl;
     
          
     
     
     
          for( int j=0, l=4096; j<13;j++){
               l *=2;
               cout << " Elementy: " << l;
               cout << "\t\t\t\t\t" << " czasy: " ;
               for( int i=0; i<10; i++){
               
                    switch(menu){
                                 case 1: sredni += bombelkowe(l, a); break;
                                 case 2: sredni += shell(l, a, h); break;
                                 case 3: sredni += scalanie(l, a); break;
                                 case 4: sredni += kopcowanie(l, a); break;
                                 case 5: sredni += kubelkowe(l, a, zakres); break;
                                 case 6: sredni += quick(l, a); break;
                                 }   
                    
                    cout << " ; ";

                    }
               
               sredni /= 10;
               cout << endl << "Sredni czas: " << sredni;
          
               cout << endl << "----------------"<< endl;
               sredni = 0;
               }
               
          }


          }
     
     return 0;
     
     }
     
     
     
     
     
void testowanie(){
     
     wyswietl=1;  
     cout <<endl<< "Bombelkowe: "<<endl;
     
     bombelkowe(10, 1);

     cout <<endl<< "Shella: "<<endl;
     
     shell(10, 1, 3);

     cout <<endl<< "Scalanie: "<<endl;
     
     scalanie(10, 1);

     cout <<endl<< "Kopcowanie: "<<endl;
     
     kopcowanie(10, 1);
     
     cout <<endl<< "Kubelkowe: "<<endl;
     
     kubelkowe(10, 1, 15);

     cout <<endl<< "QuickSort: "<<endl;
     
     quick(10, 1);
     
     
     wyswietl=0;  
     cout <<endl<<endl<< "Wyswietlanie zmienione na 0"<< endl;
     system("Pause"); 
     }
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
//------------------------------------------------------------------------------
//------------SORTOWANIE KUBELKOWE ---------------------------------------------
//------------------------------------------------------------------------------

/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
  
    
    
double kubelkowe(int n, short int przyp, int zakres){
     
     int *tab, *liczniki;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                  // pomiar czasu prz sortowaniem
     clock_t time_po;                     // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime



     liczniki = new int [zakres+1];   
     tab = new int [n];                    
     wypelnij(tab, przyp, n, zakres);             // wype³nianie tablicy liczbami z zakresu 0 - 1000
     
     
     wypisz(tab, n);                      // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
   

     for( int i = 0; i <= zakres;){
          liczniki[i] = 0;                 // zerowanie licznikow
          i++;
          }

              
     for( int i = 0; i < n; i++){                           // zliczamy wystapienia wartosci i zwiêkszamy liczznik o 1
          liczniki[tab[i]] = liczniki[tab[i]] + 1;
          } 

     for( int i = 0, j = 0; i <= zakres; i++){              // wpisujemy index tyle razy ile wystapil
          for( ;liczniki[i]-- != 0;){
               tab[j++] = i; 
               } 
          } 






          
         
    time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



    wypisz(tab, n);                            // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
    delete [] tab;
  
  
    
    time_roznica = difft(time_po, time_przed);
    cout << time_roznica;
    return time_roznica;
    }
    
     
     
     

//------------------------------------------------------------------------------
//------------SORTOWANIE SZYBKIE -----------------------------------------------
//------------------------------------------------------------------------------

/**
Wywo³ywana rekurencyjnie funkcja szybkiego sortowania 
tab - sortowana tablica
index_pierwszego elementu :)
index_ostatniego elementu :)
*/


void quick_alg(int index_pierwszego, int index_ostatniego, int* tab){
  
     int i, i2, tmp, srodek;

     i = (index_pierwszego + index_ostatniego) / 2;
  
     srodek = tab[i];
     tab[i] = tab[index_ostatniego];
  
     for( i2 = index_pierwszego, i = index_pierwszego ; i < index_ostatniego; i++){
          if( tab[i] < srodek){
              tmp = tab[i];
              tab[i] = tab[i2];
              tab[i2] = tmp;
              i2++;
              }
          }
      
     tab[index_ostatniego] = tab[i2];
     tab[i2] = srodek;
  
     if( (i2 + 1) < index_ostatniego){
         quick_alg(i2 + 1, index_ostatniego, tab);    //rekurencyjne wykonanie quicksorta dla prawej partycji
         }  
  
     if( index_pierwszego < (i2 - 1)){
         quick_alg(index_pierwszego, (i2 - 1), tab);  //rekurencyjne wykonanie quicksorta dla lewej partycji
         }
     }



/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
  
    
    
double quick(int n, short int przyp){
     
     int *tab;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                  // pomiar czasu prz sortowaniem
     clock_t time_po;                     // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime


 
     tab = new int [n];
     
                 
     wypelnij(tab, przyp, n, 0);             // wype³nianie tablicy
     
     
     wypisz(tab, n);                       // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
    
     quick_alg(0,n-1, tab);               // quicksort
          
         
     time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



     wypisz(tab, n);                            // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     delete [] tab;
  

     time_roznica = difft(time_po, time_przed);
     cout << time_roznica;
     return time_roznica;
     }
    
     

     
     

//------------------------------------------------------------------------------
//------------SORTOWANIE PRZEZ SCALANIE ----------------------------------------
//------------------------------------------------------------------------------

/**
Wywo³ywana rekurencyjnie funkcja sortowania przez scalanie
tab - sortowana tablica
pom - tablica pomocnicza
index_pierwszego elementu :)
index_ostatniego elementu :)
*/

void scalanie_alg(int index_pierwszego, int index_ostatniego, int* tab, int* pom){
     
     int podzial;
     int j,k,i;

     podzial = (1 + index_pierwszego + index_ostatniego) / 2;                     // przygotowanie podzialu zbioru na 2 czesci
     
     
            
     if( index_ostatniego - podzial > 0){                                         // sortowanie rekurencyjne podzbioru drugiego
         scalanie_alg(podzial, index_ostatniego, tab, pom);
         }
     
     if( podzial - index_pierwszego > 1){                                         // sortowanie rekurencyjne podzbioru pierwszego
         scalanie_alg(index_pierwszego, podzial - 1, tab, pom);
         }

          
     j = index_pierwszego;
     k = podzial;
     
     for( i = index_pierwszego; i <= index_ostatniego; i++){                      // scalanie
          if(((index_ostatniego >= k) && (tab[k] < tab[j])) || ( j == podzial)){  // jezeli index pierwszego elementu z pierwszego zbioru jest rowny podzial tzn ze jestesmy
               pom[i] = tab[k];                                                   // na najnizszym poziomie rekurencji
               k++;                                                              
               }else{
                     pom[i] = tab[j];
                     j++;
                     }
          }
     
     for( i = index_pierwszego; i <= index_ostatniego; i++){                      // przepisywanie z tablicy pomocniczej do tab juz po scaleniu
          tab[i] = pom[i];
          } 
          
     }



/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
  
    
    
double scalanie(int n, short int przyp){
     
     int *tab;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                  // pomiar czasu prz sortowaniem
     clock_t time_po;                     // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     

     int *pom;                            // tablica pomocnicza

 
     tab = new int [n];
     
     pom = new int [n];
                 
     wypelnij(tab, przyp, n, 0);             // wype³nianie tablicy
     
     
     wypisz(tab, n);                       // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
    
    scalanie_alg(0,n-1, tab, pom);
          
         
    time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



    wypisz(tab, n);                            // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
    delete [] tab;
  

    time_roznica = difft(time_po, time_przed);
    cout << time_roznica;
    return time_roznica;
    }
    
     


     
     
     
     
     
     
     
//------------------------------------------------------------------------------
//------------SORTOWANIE PRZEZ KOPCOWANIE --------------------------------------
//------------------------------------------------------------------------------

/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
  
    
    
double kopcowanie(int n, short int przyp){
     
     int *tab;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                  // pomiar czasu prz sortowaniem
     clock_t time_po;                     // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     int a,b,tmp2,tmp;




     
     
     
     tab = new int [n];                    
     wypelnij(tab, przyp, n, 0);          // wype³nianie tablicy
     
     
     wypisz(tab, n);                      // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
  
  

                                          // Kopcowanie

     for( int i=2; i<=(n-1);i++){
          a=i; 
          tmp=tab[i];
          b=a/2;

          while( (tmp>tab[b]) && (b>0)){
                 tab[a]=tab[b];
                 a=b; 
                 b=a/2;
                 }
          tab[a]=tmp;
          }


     wypisz(tab, n);                      // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
                                          //Odkopcowanie

     for( int i = (n-1); i>1; i--){

          
          tmp2 = tab[1];
          tab[1] = tab[i];
          tab[i] = tmp2;

          a=1; 
          b=2;

          while( b<i){

                 if( (b+1<i) &&(tab[b]<tab[b+1]) ){
                     tmp = 1 + b;
                     }
                     else{
                          tmp = b;
                          } 

                 if( !( tab[tmp] > tab[a] ) ){
                     break;
                     }

                 tmp2 = tab[a];
                 tab[a] = tab[tmp];
                 tab[tmp] = tmp2;
                 
                 a=tmp;
                 b=2*a;
                 } 
          }



          

        
         
    time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



    wypisz(tab, n);                            // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
    delete [] tab;
  
  
    
    time_roznica = difft(time_po, time_przed);
    cout << time_roznica;
    return time_roznica;
    }
    
     
     
     
     
     
//------------------------------------------------------------------------------
//------------SORTOWANIE SHELL -------------------------------------------------
//------------------------------------------------------------------------------

/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
  
    
    
double shell(int n, short int przyp, int param){
     
     int *tab;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                  // pomiar czasu prz sortowaniem
     clock_t time_po;                     // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     int h,i,licz,a;                         // h -odleg³oœæ




     
     
     
     tab = new int [n];                    
     wypelnij(tab, przyp, n, 0);             // wype³nianie tablicy
     
     
     wypisz(tab, n);                      // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
    
     h = 1;                               //ustawianie parametru h 
     
     while( h < n){
            h=1 + param*h;
            }
                
     h = h/9;
    
     if(!h) h++;                           // istotne jedynie dla bardzo ma³ych tablic


     while( h){
            for( licz = n - 1 - h; !(licz < 0); licz--){
                 i = licz + h;
                 a = tab[licz];


                 for( ;(n > i) && (tab[i] < a);){     //sortowanie przez wstawianie
                      tab[i - h] = tab[i];
                      i += h;
                      }
                        
                 tab[i - h] = a;
                 }
            h = h/3;
            }







          
         
    time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



    wypisz(tab, n);                            // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
    delete [] tab;
  
  
    
    time_roznica = difft(time_po, time_przed);
    cout << time_roznica;
    return time_roznica;
    }
    
     

     
    
//------------------------------------------------------------------------------
//------------SORTOWANIE BOMBELKOWE---------------------------------------------
//------------------------------------------------------------------------------

   
/**
Funkcja zwraca wartoœæ double, jest to czas wykonania operacji
Argument n jest iloœci¹ elementów w tablicy
Argument przyp jest przypadkiem ulozenia elementow 0-posortowane 1-losowo 2-posortowane wspak
*/
    
    
    
double bombelkowe(int n, short int przyp){
     
     int *tab;                            // tablica na której bêdzie wykonywany algorytm
     
     clock_t time_przed;                   // pomiar czasu prz sortowaniem
     clock_t time_po;                      // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime

     
     
     
     
     
     tab = new int [n];                    
     wypelnij(tab, przyp, n, 0);             // wype³nianie tablicy
     
     
     wypisz(tab, n);                       // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
     
     
     time_przed = pobierz_czas();         // pomiar czasu przed sortowaniem 
                   
    
    
    

    
    for( int i=0; i<n-1; ++i){            // przegladanie tablicy
         bool end = true;                 // sprawdzanie czy zakonczyc

         for( int j=0; j<(n-i-1);j++){

              if( tab[j+1]<tab[j]){
                  int przenies;           // zmienna pomocnicza
                  przenies = tab[j+1];    // zamiana wartoœci
                  tab[j+1] = tab[j];
                  tab[j] = przenies;
                  end = false;            // coœ zosta³o zmienione, nie koñcz
                  }

              }                             
        if( end){                   // jeœli nic nie zosta³o zmienione zakoñcz
                  break;
                  }
          }
          
          
    time_po = pobierz_czas();                  // pomiar czasu po sortowaniu     



    wypisz(tab, n);                       // ewentualne wyswietlanie elementow tablicy dla sprawdzenia poprawnosci sortowania
    delete [] tab;
  
  
    
    time_roznica = difft(time_po, time_przed);
    cout << time_roznica;
    
    return time_roznica;
    }
    
     
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
//------------------------------------------------------------------------------
//------------MALE MNIEJ WAZNE FUNKCJE------------------------------------------
//------------------------------------------------------------------------------

/*
Ustawia wyswietlanie elementow posortowanej tablicy
*/
                                                                                
                                                                                
void wyswietlanie(){
     int pomocnicza;
         cout << "Czy wyswietlac liczby? (0/1)" <<endl;
         cin >> pomocnicza;
         switch(pomocnicza){
                            case 0: wyswietl = 0; cout << "wyswietlanie: nie" <<endl; break;
                            case 1: wyswietl = 1; cout << "wyswietlanie: tak" <<endl; break;          
                            default: cout << "zly wybor, nic nie zmienione" <<endl; break;
                            } 
         system("Pause");
         }
    
    
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





     
//---------------------------------------
//------------WYPELNIANIE TABLICY--------
//---------------------------------------

 
     
void wypelnij(int* tab,short int przyp, int n, int zakres){
     
     switch(przyp){
             // posortowane
             case 0: 
                     for( int i=0; i<n;i++){
                          if(zakres!=0){
                                     tab[i]= i%zakres;
                                     }
                                     else{
                                          tab[i]= i;
                                          }
                          }
                     break;
                     
             // losowo
             case 1:
                     for( int i=0; i<n;i++){
                          if(zakres!=0){
                                     tab[i]= rand()%zakres;
                                     }
                                     else{
                                          tab[i]= rand();
                                          }
                          }
                     break;
                     
             // wspak
             case 2: 
                     for( int i=0; i<n;i++){
                          if(zakres!=0){
                                     tab[i]= (n-i)%zakres;
                                     }
                                     else{
                                          tab[i]= (n-i);
                                          }
                          }
                     break;                   
             } 
     }    
     

//----------------------------------------------------
//------------WYPISYWANIE POSORTOWANEJ TABLICY--------
//----------------------------------------------------
 
/**
Funkcja wypisujaca elementy posortowanej tablicy, spam do testowania poprawnosci sortowania
n -liczba elementow
tab - nasza tablica
*/



void wypisz(int* tab, int n){
     
    if( wyswietl==1){
        cout << endl << endl <<endl;
        for( int i=0;i<n;i++){
             cout<<tab[i];
             if( (i%8)==0){
                 cout << "\n";        
                 }
                 else{
                      cout << "\t";
                      }
             } 
        cout << "czas: ";                
        }
     }
     
     
     
     
     
     
     
     
     
     
     
