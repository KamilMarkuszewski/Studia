

#include "T_osoba.h"



T_osoba::T_osoba( int d, int m, int r, char *im){
         set_data_ur(d,m,r);   
         set_imie(im);   
         }

T_osoba::T_osoba(const T_osoba & os){
         set_imie(os.imie);
         set_data_ur(os.data_ur.get_dzien(),os.data_ur.get_miesiac(),os.data_ur.get_rok());                          
         }



void T_osoba::set_data_ur(int d,int m,int r){
     data_ur.set_dzien(d);            
     data_ur.set_miesiac(m);            
     data_ur.set_rok(r); 
     }




T_osoba T_osoba::operator= (const T_osoba &os){
        set_imie(os.imie);
        set_data_ur(os.data_ur.get_dzien(),os.data_ur.get_miesiac(),os.data_ur.get_rok());       
        return *this;
        }
        
        
bool T_osoba::operator> (const T_osoba &os){
     int a = strcmp(this->imie, os.imie);
     if(a>0) return 1;
     else return 0;
     }  
     
bool T_osoba::operator< (const T_osoba &os){
     int a = strcmp(this->imie, os.imie);
     if(a<0) return 1;
     else return 0;
     }       
        

ostream &operator<<(ostream &wyjscie, const T_osoba &os){
        cout << endl << " -----------------------------"<< endl<<endl;
        wyjscie << " Imie : " << os.imie << endl;
        wyjscie << " Data urodzenia: " << os.data_ur.get_dzien() << "." << os.data_ur.get_miesiac() << "." << os.data_ur.get_rok() << endl;
        
        cout << endl << " -----------------------------"<< endl<<endl;
        return wyjscie; 
        }

istream &operator>>(istream &we, T_osoba &os){
        
        int temp;
        
        cout << endl << " -----------------------------"<< endl<<endl;
        cout << " Podaj imie: ";
        we >> os.imie;
        cout << endl << endl << " Data urodzenia: " << endl ;
        cout << " Dzien: " ;
        we >> temp;
        os.data_ur.set_dzien(temp);
        cout << " Miesiac: " ;
        we >> temp;
        os.data_ur.set_miesiac(temp);
        cout << " Rok: " ;
        we >> temp;
        os.data_ur.set_rok(temp);
     
        cout << endl << " -----------------------------"<< endl<<endl;
        
        return we;
        }


