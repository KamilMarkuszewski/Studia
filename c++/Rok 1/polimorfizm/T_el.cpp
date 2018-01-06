

#include "T_el.h"



T_osoba::T_osoba( int d, int m, int r, char *im, char * nazw){
         set_data_ur(d,m,r);   
         set_imie(im);
         set_nazwisko(nazw);    
         }

T_osoba::T_osoba(const T_osoba & os){
         set_imie(os.imie);
         set_nazwisko(os.nazwisko);
         set_data_ur(os.data_ur.get_dzien(),os.data_ur.get_miesiac(),os.data_ur.get_rok());                          
         }



void T_osoba::set_data_ur(int d,int m,int r){
     data_ur.set_dzien(d);            
     data_ur.set_miesiac(m);            
     data_ur.set_rok(r); 
     }


void T_osoba::pokaz() const {
        cout << endl << endl << " -----------------------------"<< endl<<endl;
        cout << " Imie: " << imie << endl; 
        cout << " Nazwisko: " << nazwisko<< endl;
        cout << " Data urodzenia: " << data_ur.get_dzien() << "." << data_ur.get_miesiac() << "." << data_ur.get_rok() << endl;
        cout << endl << endl << " -----------------------------"<< endl<<endl;
        }

void T_osoba::wczytaj(){
     int temp;
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     cout << " Podaj imie: ";
     cin >> imie;
     cout << endl << " Podaj nazwisko: ";
     cin >> nazwisko;
     cout << endl << endl << " Data urodzenia: " << endl ;
     cout << " Dzien: " ;
     cin >> temp;
     data_ur.set_dzien(temp);
     cout << " Miesiac: " ;
     cin >> temp;
     data_ur.set_miesiac(temp);
     cout << " Rok: " ;
     cin >> temp;
     data_ur.set_rok(temp);
     
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     }












//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------      
//--------------------------------------------------------------------------------------------------------------------------------------------------




T_pracownik::T_pracownik( const T_pracownik & pr){
                          tel = pr.tel;
                          czas = pr.czas;
                          pensja = pr.pensja;
                          set_oddzial(pr.oddzial);
                          set_imie(pr.imie);
                          set_nazwisko(pr.nazwisko);
                          set_data_ur(pr.data_ur.get_dzien(),pr.data_ur.get_miesiac(),pr.data_ur.get_rok());                          
         
                          }


void T_pracownik::pokaz() const {
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     cout << " Imie: " << imie << endl; 
     cout << " Nazwisko: " << nazwisko<< endl;
     cout << " Data urodzenia: " << data_ur.get_dzien() << "." << data_ur.get_miesiac() << "." << data_ur.get_rok() << endl;
     cout << " Telefon: " << tel << endl;
     cout << " Czas pracy: " << czas << endl;
     cout << " Pensja: " << pensja << endl; 
     cout << " Oddzial: " << oddzial << endl;
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     }
     
     
void T_pracownik::wczytaj(){
     int temp;
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     cout << " Podaj imie: ";
     cin >> imie;
     cout << endl << " Podaj nazwisko: ";
     cin >> nazwisko;
     cout << endl << endl << " Data urodzenia: " << endl ;
     cout << " Dzien: " ;
     cin >> temp;
     data_ur.set_dzien(temp);
     cout << " Miesiac: " ;
     cin >> temp;
     data_ur.set_miesiac(temp);
     cout << " Rok: " ;
     cin >> temp;
     data_ur.set_rok(temp);
     cout << endl ;
     cout << endl << " Podaj telefon: ";
     cin >> tel;
     cout << endl << " Podaj czas pracy: ";
     cin >> czas;
     cout << endl << " Podaj pensje: ";
     cin >> pensja;
     cout << endl << " Podaj nazwe oddzialu: ";
     cin >> oddzial;
     
     cout << endl << endl << " -----------------------------"<< endl<<endl;
     }





