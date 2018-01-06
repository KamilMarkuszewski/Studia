#ifndef T_listydwu_h
#define T_listydwu_h
#include "T_listy.h"

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
