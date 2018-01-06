

#include "T_szablon.cpp"
#include "T_szablon.h"

void pause(){
     system("Pause");
     }

void clear(){
     system("cls");
     }



using namespace std;

int main(int argc, char *argv[])
{   
    bool koniec=0;
    int  menu=0, numer=0;
    
    
    // ------------------------------------ 
    // T_osoba mozna zamienic na int, double etc.
    
    //tablica<int> wektor;      
    //int tmp;
    
    
    
   tablica<T_osoba> wektor;      
    T_osoba tmp;
    // ------------------------------------ 
    
    
    
    
    
    
    
    
    
    
    
    while( !koniec){
           clear();
           cout << endl << " -----------------------------"<< endl;
           cout << " MENU" ;
           cout << endl << " -----------------------------"<< endl << endl;
           cout << " 0. Wyjscie! " <<endl;
           cout << " 1. Dopisz element na koncu - push_back " <<endl;
           cout << " 2. Wyswietl wszystkie elementy - wyswietl " <<endl;
           cout << " 3. Wyswietl element o podanym numerze - at " <<endl;
           cout << " 4. Zmien element o podanym numerze - zmien " <<endl;
           cout << " 5. Wywal to wszystko - kasuj " <<endl;
           cout << " 6. Sortuj - sort " <<endl;
           cout << endl << " -----------------------------"<< endl;
           
           cin >> menu;
           
           clear();
           switch(menu){
                        case 0: koniec = 1;
                                break;
                                
                        case 1: cin >> tmp; 
                                wektor.push_back(tmp);
                                clear();
                                break;
                                
                        case 2: wektor.wyswietl();
                                pause();
                                clear();
                                break;
                                
                        case 3: cout << " Podaj numer: "; 
                                cin >> numer;
                                wektor.at(numer);
                                pause();
                                clear();
                                break;
                                
                        case 4: cout << " Podaj numer: "; 
                                cin >> numer;
                                wektor.zmien(numer);
                                pause();
                                clear();
                                break;
                                
                        case 5: wektor.kasuj();
                                clear();
                                break;
                                
                        case 6: wektor.sort();
                                break;
                        
                        default: cout << " Zly wybor " << endl;
                                 pause();
                                 clear();
                                 break;
                        }
                   
           }
    
    

    
    pause();
    
    

    return EXIT_SUCCESS;
}
