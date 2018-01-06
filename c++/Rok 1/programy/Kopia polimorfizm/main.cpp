#include "T_el.h"
#include "T_listy.h"
























T_kontener * tworz(){
           int typ;
           T_kontener * kontener;
           do{
              cout << " Wybierz typ kontenera: 1 - osoba, 0 - pracownik: ";
              cin >> typ;
              cout << endl;
              }while(typ!=0 && typ!=1);
           
           if( typ==1){
               kontener = new T_osoba;       
               }
               else{
                    kontener = new T_pracownik;
                    }
           kontener->wczytaj();
           return kontener;           
           }





//------------------------------------------------------------------------------
// PROGRAM!
//------------------------------------------------------------------------------



int main(int argc, char *argv[])
{   
    
    
    lista_dwu dwu;
    lista jedno;
    int koniec=1, ktora, wybor, nr;
    
    while( koniec !=0){
           cout << " 0. zakoncz" << endl;
           cout << " 1. zarzadzaj lista jednokierunkowa. " << endl;
           cout << " 2. zarzadzaj lista dwukierunkowa. " << endl;
           cin >> ktora;
           cout << endl << endl << endl;
           switch( ktora){
                   case 1: cout << " 1. Dodaj element na koncu listy. " << endl;
                           cout << " 2. Dodaj element w wybranym miejscu. " << endl;
                           cout << " 3. Wyswietl element o wybranym numerze. " << endl;
                           cout << " 4. Wyswietl cala liste. " << endl;
                           cout << " 5. Usun ostatni element. " << endl;
                           cout << " 6. Usun element o wybranym numerze. " << endl;
                           cout << " 7. Wyczysc liste. " << endl;
                           cout << " 8. Podaj ilosc elementow. " << endl;
                           cout << " Default Back. " << endl;
                           cin >> wybor;
                           cout << endl << endl << endl;
                           switch( wybor){
                                   case 1: jedno.dodaj(tworz()); break;
                                   case 2: cout << " Podaj nr: "; cin >> nr; jedno.numer_dodaj(tworz(),nr); break;
                                   case 3: cout << " Podaj nr: "; cin >> nr; jedno.pokaz_numer(nr); break;
                                   case 4: jedno.pokaz(); break;
                                   case 5: jedno.usun(); break;
                                   case 6: cout << " Podaj nr: "; cin >> nr; jedno.usun_nr(nr); break;
                                   case 7: jedno.kasuj_all(); break;
                                   case 8: cout << jedno.ile(); break;

                                   }
                   
                           break;
                           
                           
                           
                   case 2: cout << " 1. Dodaj element na koncu listy. " << endl;
                           cout << " 2. Dodaj element w wybranym miejscu. " << endl;
                           cout << " 3. Podaj ilosc elementow. " << endl;
                           cout << " 4. Wyswietl cala liste. " << endl;
                           cout << " 5. Usun ostatni element. " << endl;
                           cout << " 6. Usun element o wybranym numerze. " << endl;
                           cout << " 7. Wyczysc liste. " << endl;

                           cout << " Default Back. " << endl;
                           cin >> wybor;
                           cout << endl << endl << endl;
                           switch( wybor){
                                   case 1: dwu.dodaj(tworz()); break;
                                   case 2: cout << " Podaj nr: "; cin >> nr; dwu.numer_dodaj(tworz(),nr); break;
                                   case 4: dwu.lista::pokaz(); break;
                                   case 5: dwu.usun(); break;
                                   case 6: cout << " Podaj nr: "; cin >> nr; dwu.usun_nr(nr); break;
                                   case 7: dwu.kasuj_all(); break;
                                   case 3: cout << dwu.ile(); break;

                                   }
                           break;
                   case 0: koniec = 0;
                           break;
                   
                   default: cout << " zly wybor" << endl ;
                         
                   }
           
                 
                 
                 
           }
  

    
    
    
    
    
    system("PAUSE");
    return 0;
}
