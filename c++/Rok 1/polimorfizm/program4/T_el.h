#ifndef T_el_h
#define T_el_h

#include <cstdlib>
#include <iostream>

using namespace std;






//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//Klasa data wykorzystywana w klasie osoba
//------------------------------------------------------------------------------

class T_data{
      private:
              int dzien;
              int miesiac;
              int rok;
      public:
             T_data():dzien(0),miesiac(0),rok(0){}                                          //konstr bezparametryczny
             T_data(int d, int m, int r):dzien(d),miesiac(m),rok(r){}                       // konstr z parametrami
             T_data( const T_data & d){ dzien = d.dzien; miesiac = d.miesiac; rok = d.rok;} // konstr kopiuj¹cy
             

             int get_dzien() const {return dzien;}      
             int get_miesiac() const {return miesiac;}      
             int get_rok() const {return rok;}    
             
             
             void set_dzien(int d){dzien = d;}  
             void set_miesiac(int m){miesiac = m;}  
             void set_rok(int r){rok = r;}  
      
             
      };
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
      
      
//------------------------------------------------------------------------------
//Interface kontener... funkcja bazowa klasy osoba i pracownik
//------------------------------------------------------------------------------


class T_kontener{
      public:
             virtual void pokaz() const {};
             virtual void wczytaj(){};                  
      };
      
      
      
      
      
      
      
      
      
      
      
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------


      
//------------------------------------------------------------------------------
// KLASA osoba
//------------------------------------------------------------------------------

class T_osoba: public T_kontener{
      protected:
                char imie[15];      
                char nazwisko[15];
                T_data data_ur;
      public:
             T_osoba(){set_data_ur(0,0,0);}
             T_osoba(int d, int m, int r, char *im, char * nazw);
             T_osoba(const T_osoba & os);
             virtual ~T_osoba(){};
             
             void set_data_ur(int d,int m,int r);
             void set_imie(const char * im){strcpy(imie, im);}
             void set_nazwisko(const char * nazw){strcpy(nazwisko, nazw);}
              
             const char * get_imie() const {return imie;}         
             const char * get_nazwisko() const {return nazwisko;}
             
             void pokaz() const ;
             void wczytaj();                  

      };







//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// KLASA pracownik
//------------------------------------------------------------------------------




class T_pracownik: public T_osoba {
      private: 
              char oddzial[15];
              int czas;
              int pensja;
              int tel;
      public:
             T_pracownik(): T_osoba(), tel(0), czas(0), pensja(0){};
             
             T_pracownik(int d, int m, int r, char *im, char * nazw, int cz, int pens, int t, char * odd):
                             T_osoba(d,m,r, im, nazw),
                             czas(cz),
                             pensja(pens), 
                             tel(t) {
                                    strcpy(oddzial, odd);        
                             }
                             
             T_pracownik(const T_pracownik & pr);
             
             virtual ~T_pracownik(){};             
             
             void set_czas(int c){czas=c;}
             void set_pensja(int p){pensja=p;}
             void set_tel(int t){tel=t;}             
             void set_oddzial(const char * odd){strcpy(oddzial, odd);}
              
             int get_czas() const {return czas;}
             int get_pensja() const {return pensja;}
             int get_tel() const {return tel;}
             const char * get_oddzial() const {return oddzial;}
             
             void pokaz() const ;
             void wczytaj();         
      };


//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------





// CLASS T_element!!!
class T_element{
      public:
             T_element(){};                                                                             //konstruktor domyslny
             T_element(T_kontener * kont) {kontener = kont; wsk_next=NULL;}                             //konstruktor z parametrem
             T_element(const T_element & cpy) { wsk_next = new T_element;  wsk_next = cpy.getwsk_next();}   //konstruktor kopiuj¹cy    
             ~T_element() {}                   //destruktor
     
             T_kontener *  getkontener() const {return kontener;}    //metody
             void setkontener( T_kontener * kont) {kontener = kont;}
             
             void setwsk_next(T_element *next) {wsk_next = next;}
             T_element *getwsk_next() const {return wsk_next;}
       
  
      protected:
                T_kontener *kontener;
      private:                        
                T_element *wsk_next;
                
                

      };






//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------

class T_element_dwu: public T_element{
      private:
              T_element_dwu * wsk_prev;
              T_element_dwu *wsk_next;
      public:  
              T_element_dwu(): T_element() {};
              T_element_dwu(T_kontener * kont): T_element(kont) {kontener = kont; wsk_next=NULL; wsk_prev=NULL;}
             ~T_element_dwu(){};
             
             void setwsk_prev(T_element_dwu * pre){wsk_prev = pre;}                 //  ustawia wsk_prev
             T_element_dwu *getwsk_prev() const { return wsk_prev;}
             
             void setwsk_next(T_element_dwu *next) {wsk_next = next;}
             T_element_dwu *getwsk_next() const {return wsk_next;}
             
            
             
            
      };


#endif
