#ifndef T_szablon
#define T_szablon

#include "T_osoba.h"
template <class Typ>
class tablica{
      public:
             tablica(){ile=0; element=NULL; aktualnie =0;};
             tablica(int nr);
             tablica(const tablica & rhs);
             ~tablica(){ delete element; element=NULL;}
             void nowa(int rozmiar);                                            // alokuje od nowa tablice
             int get_ile() const {return ile;}                                  // zwraca ilosc zaalokowanych miejsc
             int get_aktualnie() const {return aktualnie;}                      // zwraca ilosc aktualnie przechowywanych obiektow
             void zwieksz();                                                    // dwukrotnie zwieksza rozmiar tablicy  
             void wyswietl();                                                   // wyswietla wszystkie elementy
             void push_back(Typ obiekt);                                        // dodaje element na koniec
             void kasuj();                                                      // kasuje cala tablice
             void at(int n);                                                    // wyswietla obiekt znajdujacy sie pod podanym numerem
             void zmien(int n);                                                 // zmienia obiekt spod podanego numeru
             void sort();                                                       // sortowanie bombelkowe 
      private:
              Typ *element;
              int ile, aktualnie;   

      
      };







#endif
