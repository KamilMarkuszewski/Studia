#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;
      
      
      
bool porownaj(double a, double b){
     if(a>b) return 1;
     return 0;
     }      


void hr(int &licznik){
     cout << endl << "-------------------------------------" << endl;
     cout << ++licznik;
     cout << endl << "-------------------------------------" << endl; 
     system("PAUSE");                                                           // DO WYKOMENTOWANIA POD LINUXA!
     }



int main(int argc, char *argv[])
{
    int licznik=0;
    
    hr(licznik);
    //---------------------------------------------------------------------
    //1
    
    
    list<double> lista;
    list<double>::iterator iterator;
    
    
    // dodaje 100 elementow mialo byc rand ale przy i pozniej wszystko lepiej widac
    for( int i=0; i<100; i++){
         lista.push_back(i);                                                    // przy losowych ciezko sie sprawdza czy dobrze dziala
         //lista.push_back(rand()%1001);    
         }
    
    hr(licznik);
    //---------------------------------------------------------------------
    //2
    
    // wyswietlam
    for( iterator = lista.begin(); iterator != lista.end(); iterator++){
         cout << *iterator << " \t " ;
         }
    
    hr(licznik);
    //---------------------------------------------------------------------
    //3
    
    
    //wyswietlam od konca
    for(iterator = lista.end();iterator != lista.begin();){
         cout << *(--iterator) << " \t " ;
         }
    
    
    hr(licznik);
    //---------------------------------------------------------------------
    //4
    
    //dodaje 5 losowych z przodu
    for( int i=0; i<5; i++){
         lista.push_front(rand()%1001);
         }
    
    hr(licznik);
    //---------------------------------------------------------------------
    //5
    
    //sortuje wiekszosc jest juz posortowana wiec zmiana widoczna bedzie tylko przy losowych 5 na poczatku
    lista.sort(porownaj);
    for( iterator = lista.begin(); iterator != lista.end(); iterator++){
         cout << *iterator << " \t " ;
         
         }
    
    
    hr(licznik);
    //---------------------------------------------------------------------
    //6
    
    // robie 2ga liste
    list<double> lista2;
    
    // dodaje 5 elementow do drugiej listy
    for( int i=0; i<5; i++){
         lista.push_front(10.89 + i);
         }
    
    //dodaje druga liste na poczatku pierwszej
    lista.splice(lista.begin(), lista2);
    
    
    // wyswietlam na koniec
    for( iterator = lista.begin(); iterator != lista.end(); iterator++){
         cout << *iterator << " \t " ;
         }
    
    
    
    hr(licznik);
    return EXIT_SUCCESS;
}
