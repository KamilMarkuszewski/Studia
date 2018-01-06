#ifndef T_osoba_h
#define T_osoba_h

#include <cstdlib>
#include <iostream>

using namespace std;








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
      
      

      
//------------------------------------------------------------------------------
// KLASA osoba
//------------------------------------------------------------------------------

class T_osoba{
      
      protected:
                char imie[15];      
                T_data data_ur;
      public:
             T_osoba(){set_data_ur(0,0,0);}
             T_osoba(int d, int m, int r, char *im);
             T_osoba(const T_osoba & os);
             ~T_osoba(){};
             
             void set_data_ur(int d,int m,int r);
             void set_imie(const char * im){strcpy(imie, im);}
              
             const char * get_imie() const {return imie;}         
             
             void pokaz() const ;
             void wczytaj();  
             
             T_osoba operator= (const T_osoba &os);  
             bool operator> (const T_osoba &os);
             bool operator< (const T_osoba &os);
                           
             friend ostream &operator<<(ostream &wyjscie, const T_osoba &os);
             friend istream &operator>>(istream &we, T_osoba &os);
      };










#endif
