#ifndef T_listy_h
#define T_listy_h
#include "T_el.h"


class lista{
      public:
             lista();                                                                                        // konstruktor
             lista(T_kontener * kontener);                                                                   
             virtual ~lista(); 
             int ile() const  ;                                                                               // ilosc emelentow
             void dodaj(T_kontener * kontener);                                                              // dodaje element na koncu
             void numer_dodaj(T_kontener * kontener, int numer);                                             // odoaje element we wskazanym miejscu
             void usun();                                                                                    // usuwa element z konca
             void usun_nr(int numer);                                                                        // usuwa element ze wskazanego miejsca
             T_kontener * pobierz_wsk(int numer);                                                            // pobiera wsk do elementu o wskazanym numerze
             T_kontener * pokaz_numer(int numer);                                                            // wyswietla osobe o wskazanym numerze
             void kasuj_all();                                                                               //kasuje zawartosc calej listy
        
             void pokaz();                                                                                   //wyswietla cala liste
             
      protected:
                int ilosc_elem;
                
      private:
              T_element *wsk_pierw, *wsk_aktualny;
      };




//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------


class lista_dwu: public lista{
      
      public:
             lista_dwu();                                                                                        // konstruktor
             lista_dwu(T_kontener * kontener);                                                                   
             virtual ~lista_dwu(); 
             void dodaj(T_kontener * kontener);
             void numer_dodaj(T_kontener * kontener, int numer);
             void usun();
             void usun_nr(int numer);
             T_kontener * pobierz_wsk(int numer);
             void pokaz();
             void kasuj_all();  
             
      private:
              T_element_dwu *wsk_pierw, *wsk_aktualny, *wsk_ost;
              int ilosc_elem;
      
      
      };



#endif
