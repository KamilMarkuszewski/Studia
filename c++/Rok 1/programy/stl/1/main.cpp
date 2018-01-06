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
    //Utworzyæ vector liczb typu int. Wype³niæ 10 liczbami wygenerowanymi losowo z zakresu
    //[0;100]. Wyœwietliæ zawartoœæ vector'a przy pomocy pêtli for, licznika pomocniczego i
    //operatora [], liczbê elementów jak i rozmiar zaalokowanej pamiêci.

    
    
    
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
    //Dodaæ 8 liczb, wyœwietliæ dane jak w poprzednim podpunkcie.
    
    
    
    
    for( int i=0; i<8;i++){
         vec.push_back(8);                                              // ósemki ¿eby by³o je dobrze widaæ
         }
    
    
    // 3
    //------------------------------------------------------------------
    hr(licznik);
    // Wyœwietliæ zawartoœæ vector'a przy pomocy iteratorów i pêtli for, u¿yæ metody at sk³adowej vector'a.
    
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    // 4
    //------------------------------------------------------------------
    hr(licznik);
    // Odwróciæ kolejnoœæ sk³adników vector'a, wyœwietliæ liczby.
    
    
    reverse(vec.begin(), vec.end());
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    
    // 5
    //------------------------------------------------------------------
    hr(licznik);
    // Obliczyæ sumê elementów w vectorze.
    
    
    int suma=0;
    
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         suma+=vec.at(index);
         
         }
    index=0;
    cout << " Suma: " << suma << endl; 
    
    // 6
    //------------------------------------------------------------------
    hr(licznik);
    // sprawdziæ czy liczba 18 znajduje siê w przedziale pól [5;15] w vectorze.
    
    
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
    // Podaæ liczbê wyst¹pieñ wartoœci 25 w vectorze.
    
    
    suma=0;
    
    /*
    for( iterator = vec.begin(); iterator < vec.end(); iterator++){
         iterator = find(iterator, vec.end(),8);
         if( iterator!=vec.end()){
             suma++;
             }
         }
    */     
    suma = count(vec.begin(),vec.end(),8);                                        //zamiast 25 da³em 8 bo one s¹ na pewno
    cout << " Ilosc elementow \"8\" : " << suma << endl;
    
    
    // 8
    //------------------------------------------------------------------
    hr(licznik);
    // Dodaæ liczbê 56 do vectora a nastêpnie wyszukaæ t¹ liczê i wyœwietliæ (u¿ywaj¹c uzyskanego iteratora).
    
    
    
    vec[rand()%(vec.size()+1)] = 56;
    
    iterator = find(vec.begin(), vec.end(),56);
    
    cout << *iterator;
    
    // 9
    //------------------------------------------------------------------
    hr(licznik);
    // Dodaæ do vectora wartoœæ elementu na 3, 5 i 9 pozycji.
    
    
    vec.insert(vec.begin() + 3, 1);
	vec.insert(vec.begin() + 5, 2);
	vec.insert(vec.begin() + 9, 3);
    
    
    
    // 10
    //------------------------------------------------------------------
    hr(licznik);
    // Usun¹æ z wektora powtarzaj¹ce siê elementy, wyœwietliæ zawartoœæ.
    
    
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
    // Posortowaæ zawartoœæ vectora rosn¹co i wyœwietliæ.
    
    
    sort(vec.begin(), vec.end());
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    index=0;
    
    // 12
    //------------------------------------------------------------------
    hr(licznik);
    // Posortowaæ zawartoœæ vectora malej¹co i wyœwietliæ.
    
    
    
    index=0;
    sort(vec.begin(), vec.end(), porownaj);
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    
    index=0;
    // 13
    //------------------------------------------------------------------
    hr(licznik);
    // Dodaæ wartoœæ 8 na pozycjê nr 5.
    
    vec.insert(vec.begin()+5,8);
    
    
    // 14
    //------------------------------------------------------------------
    hr(licznik);
    // Wyœwietliæ wartoœæ pierwszego elementu bez u¿ycia operatora [] i metody at.
    
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
    //Usun¹æ wszystkie elementy z vectora, sprawdziæ czy jest pusty, podaæ liczbê elementów sk³adowych, podaæ rozmiar zaalokowanej pamiêci.
    
    vec.clear();
    cout << " Ilosc elementow: " << vec.size() << endl;
    index=0;
    for( iterator = vec.begin(); iterator < vec.end(); iterator++, index++){
         cout << vec.at(index) << endl;
         
         }
    
    
    
    hr(licznik);
    
    return EXIT_SUCCESS;
}
