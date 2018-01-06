#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool porownaj(int a, int b){
     if(a>b)return 1;
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
    int licznik=0, index=0;
    
    
    vector<int>::iterator iterator;
    
    // 1
    //------------------------------------------------------------------
    hr(licznik);
    //Utworzy� vector liczb typu int. Wype�ni� 10 liczbami wygenerowanymi losowo z zakresu
    //[0;100]. Wy�wietli� zawarto�� vector'a przy pomocy p�tli for, licznika pomocniczego i
    //operatora [], liczb� element�w jak i rozmiar zaalokowanej pami�ci.

    
    
    
    vector<int>  vec(10);
    
    for( int i=0; i<10; i++){
         vec[i] = rand()%101;
         }
    
    for( int i=0; i<10; i++){
         cout << vec[i] << endl;
         }
    // 2
    //------------------------------------------------------------------
    hr(licznik);
    //Doda� 8 liczb, wy�wietli� dane jak w poprzednim podpunkcie.
    
    
    
    
    for( int i=0; i<8;i++){
         vec.push_back(8);                                              // �semki �eby by�o je dobrze wida�
         }
    
    
    // 3
    //------------------------------------------------------------------
    hr(licznik);
    // Wy�wietli� zawarto�� vector'a przy pomocy iterator�w i p�tli for, u�y� metody at sk�adowej vector'a.
    
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    // 4
    //------------------------------------------------------------------
    hr(licznik);
    // Odwr�ci� kolejno�� sk�adnik�w vector'a, wy�wietli� liczby.
    
    
    reverse(vec.begin(), vec.end());
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    
    // 5
    //------------------------------------------------------------------
    hr(licznik);
    // Obliczy� sum� element�w w vectorze.
    
    
    int suma=0;
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         suma+=vec.at(index);
         
         }
    index=0;
    cout << " Suma: " << suma << endl; 
    
    // 6
    //------------------------------------------------------------------
    hr(licznik);
    // sprawdzi� czy liczba 18 znajduje si� w przedziale p�l [5;15] w vectorze.
    
    
    iterator = find(5 + vec.begin(), 15 + vec.end(),18);                          // jak 18 zmienimy na 8 to znajdzie w przedziale na bank
    
    if( iterator!=vec.end()+15){
        cout << " Znalazlem! " << endl;
        }
        else{
             cout << " Nie ma :( " << endl;     
             }
    
    // 7
    //------------------------------------------------------------------
    hr(licznik);
    // Poda� liczb� wyst�pie� warto�ci 25 w vectorze.
    
    
    suma=0;
    
    /*
    for( iterator = vec.begin(); iterator < vec.end(); iterator++){
         iterator = find(iterator, vec.end(),8);
         if( iterator!=vec.end()){
             suma++;
             }
         }
    */     
    suma = count(vec.begin(),vec.end(),8);                                        //zamiast 25 da�em 8 bo one s� na pewno
    cout << " Ilosc elementow \"8\" : " << suma << endl;
    
    
    // 8
    //------------------------------------------------------------------
    hr(licznik);
    // Doda� liczb� 56 do vectora a nast�pnie wyszuka� t� licz� i wy�wietli� (u�ywaj�c uzyskanego iteratora).
    
    
    
    vec[rand()%(vec.size()+1)] = 56;
    
    iterator = find(vec.begin(), vec.end(),56);
    
    cout << *iterator;
    
    // 9
    //------------------------------------------------------------------
    hr(licznik);
    // Doda� do vectora warto�� elementu na 3, 5 i 9 pozycji.
    
    
    vec.insert(vec.begin() + 3, 1);
	vec.insert(vec.begin() + 5, 2);
	vec.insert(vec.begin() + 9, 3);
    
    
    
    // 10
    //------------------------------------------------------------------
    hr(licznik);
    // Usun�� z wektora powtarzaj�ce si� elementy, wy�wietli� zawarto��.
    
    
    for( int i=0; i<101;i++){
         suma=0;
         suma = count(vec.begin(),vec.end(),i);      
         if( suma>1){
             replace( vec.begin(), vec.end(), i, 0 );        
             }   
         }
    
    
    index=0;
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    // 11
    //------------------------------------------------------------------
    hr(licznik);
    // Posortowa� zawarto�� vectora rosn�co i wy�wietli�.
    
    
    sort(vec.begin(), vec.end());
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    // 12
    //------------------------------------------------------------------
    hr(licznik);
    // Posortowa� zawarto�� vectora malej�co i wy�wietli�.
    
    
    
    index=0;
    sort(vec.begin(), vec.end(), porownaj);
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    
    index=0;
    // 13
    //------------------------------------------------------------------
    hr(licznik);
    // Doda� warto�� 8 na pozycj� nr 5.
    
    vec.insert(vec.begin()+5,8);
    
    
    // 14
    //------------------------------------------------------------------
    hr(licznik);
    // Wy�wietli� warto�� pierwszego elementu bez u�ycia operatora [] i metody at.
    
    cout << *(vec.begin())<<endl;
    
    
    // 15
    //------------------------------------------------------------------
    hr(licznik);


    vec.pop_back();
    index=0;
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }

    
    // 16
    //------------------------------------------------------------------
    hr(licznik);
    //Usun�� wszystkie elementy z vectora, sprawdzi� czy jest pusty, poda� liczb� element�w sk�adowych, poda� rozmiar zaalokowanej pami�ci.
    
    vec.clear();
    cout << " Ilosc elementow: " << vec.size() << endl;
    index=0;
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    
    
    
    hr(licznik);
    
    return EXIT_SUCCESS;
}
