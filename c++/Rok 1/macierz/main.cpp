#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <math.h>


using namespace std;

enum ERROR{
     ZLY_ROZMIAR,
     NIE_ISTNIEJE,
     NIE_KWADRATOWA,
     
           };     
int blad=0;




// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------


class macierz{                                                                   // pojedyncza macierz
      private:
             int il_kolumny, il_wersy;                                           // ilosc kolumn i wersów
             int **wsk_macierz;                                                  // wsk na macierz

 
              
                                                     
      
      public:
             macierz(){il_kolumny = 0; il_wersy = 0;wsk_macierz=NULL;} 
             macierz(int wer, int kol);                                          // tworzy tablice dwuwymiarowa 
             macierz(const macierz & matrix);                                    // kopiuj¹cy
             ~macierz();                                                         // destruktor
             
             
             int get_il_kolumny() const {return il_kolumny;}                     // zwraca ilosc kolumn
             int get_il_wersy() const {return il_wersy;}                         // zwraca ilosc wersow
             int **get_wsk_macierz() const {return wsk_macierz;}                 // zwraca wsk do tablicy
             void set_wsk_macierz(int **wsk){wsk_macierz = wsk;}                 // ustawia wskaŸnik
             void set_il_kolumny(int kol){il_kolumny = kol;}                     // ustawia ilosc kolumn
             void set_il_wersy(int wer){il_wersy = wer;}                         // ustawia ilosc wersow  
             
              
             void wyswietl() const;                                              // wyswietla zawartosc macierzy              
             void wypelnij();                                                    // wypelnianie macierzy
             void wypelnij_zerami();                                             // wypelnianie macierzy zerami
             void wypelnij_jednostkowa();                                        // wype³nia macierz cyframi 0 i 1 tworz¹c macierz jednostkow¹
             void transponowana();                                               // macierz transponowana
             void kasuj();                                                       // kasowanie macierzy bez kasowania obiektu
             void dodaj_wiersz_kolumna(bool w_or_k, int numer);                  // dodawanie wiersza lub kolumny w dowolnym miejscu
             void error(int err) const;                                          // b³êdy
             void zmien_rozmiar(int wer, int kol);                                       // zmiana rozmiaru
             
            
             macierz operator+(const macierz &mac);
             macierz operator*(const int liczba);
             macierz operator*(const macierz &mac);
             macierz operator-(const macierz &mac);
             macierz operator=(const macierz &mac);
             macierz operator+=(const macierz &mac);
             macierz operator-=(const macierz &mac);
             bool operator==(const macierz &mac);                                // sprawdza czy s¹ równe (zwraca 0 gdy którakolwiek nie istnieje)
             friend ostream &operator<<(ostream &wyjscie, const macierz &mac);
             
             };






// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------









// -----------------------------------------------------------------
// KONSTRUKTOR Z PARAMETREM

macierz::macierz(int wer, int kol){    
      if( kol > 0 && wer > 0){
          il_kolumny = kol;
          il_wersy = wer; 
          wsk_macierz = new int *[wer];
      
          for(int i=0; i < wer; i++){
                  wsk_macierz[i] = new int [kol];                                                          
                  }                   
          blad =0;                    
          }
      else{
           wsk_macierz = NULL;
           il_kolumny = 0;
           il_wersy = 0;
           blad = ZLY_ROZMIAR;
           }                       
                                                  
      }
// -----------------------------------------------------------------  
// KONSTRUKTOR Z KOPIUJACY

macierz::macierz(const macierz & matrix){    

        il_wersy = matrix.il_wersy;
        il_kolumny = matrix.il_kolumny;
        if(il_kolumny > 0 && il_wersy > 0){
          wsk_macierz = new int *[il_wersy];
      
           for(int i=0; i < il_wersy; i++){
                   wsk_macierz[i] = new int [il_kolumny];                                                          
                   }                   
                             
           for( int i = 0; i < il_wersy; i++){
                for( int j = 0; j < il_kolumny; j++){
                     wsk_macierz[i][j] = matrix.wsk_macierz[i][j];      
                     }    
                }
           blad =0;           
           }                          
        else{
           wsk_macierz = NULL;
           error(ZLY_ROZMIAR);
           blad = ZLY_ROZMIAR;
           }                       
                                          
}

                          
// -----------------------------------------------------------------                          
// DESTRUKTOR                          

macierz::~macierz(){
      if(wsk_macierz == NULL || il_kolumny == 0 || il_wersy == 0){ 
          wsk_macierz = NULL;                                               
                              }
                              
      else{
           for( int i=0; i < il_wersy; i++){
               delete [] wsk_macierz[i];
               wsk_macierz[i] = NULL; 
               }
      
           delete [] wsk_macierz;
           wsk_macierz = NULL;  
           }
                                                          
      }
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------

macierz macierz::operator+ (const macierz &mac){
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0 || mac.wsk_macierz==NULL){
                      error(NIE_ISTNIEJE);
                      return *this;
                      }
        if(il_kolumny != mac.il_kolumny || il_wersy != mac.il_wersy){
                      error(ZLY_ROZMIAR);
                      return *this;
                      }      
        else{
             macierz temp(il_wersy,il_kolumny);
             for(int i=0; i < il_wersy; i++){
                     for(int j=0; j < il_kolumny; j++){
                             temp.wsk_macierz[i][j] = wsk_macierz[i][j] + mac.wsk_macierz[i][j];
                             
                             }
             blad =0;
             }
             return temp;
             
             }
        }

// ----------------------------------------------------------------- 

macierz macierz::operator- (const macierz &mac){
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0 || mac.wsk_macierz==NULL){
                      error(NIE_ISTNIEJE);
                      return *this;
                      }
        if(il_kolumny != mac.il_kolumny || il_wersy != mac.il_wersy){
                      error(ZLY_ROZMIAR);
                      return *this;
                      }      
        else{
             macierz temp(il_wersy,il_kolumny);
             for(int i=0; i < il_wersy; i++){
                     for(int j=0; j < il_kolumny; j++){
                             temp.wsk_macierz[i][j] = wsk_macierz[i][j] - mac.wsk_macierz[i][j];
                             
                             }
                     }
             return temp;
             }
        }

// ----------------------------------------------------------------- 

macierz macierz::operator* (int liczba){
     
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL ){
                      error(NIE_ISTNIEJE);
                      return *this;
                      }
        macierz temp(il_wersy,il_kolumny);
        for(int i=0; i < il_wersy; i++){
                for(int j=0; j < il_kolumny; j++){
                        temp.wsk_macierz[i][j] = wsk_macierz[i][j] * liczba;
                             
                        }
                }
        return temp;

        }

// ----------------------------------------------------------------- 

macierz macierz::operator+= (const macierz &mac){
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0 || mac.wsk_macierz==NULL){
                      error(NIE_ISTNIEJE);
                      return *this;
                      }
        if(il_kolumny != mac.il_kolumny || il_wersy != mac.il_wersy){
                      error(ZLY_ROZMIAR);
                      return *this;
                      }      
        else{

             for(int i=0; i < il_wersy; i++){
                     for(int j=0; j < il_kolumny; j++){
                             wsk_macierz[i][j] = wsk_macierz[i][j] + mac.wsk_macierz[i][j];
                             
                             }
                     }
             return *this;
             }
        }

// ----------------------------------------------------------------- 

macierz macierz::operator-= (const macierz &mac){
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0 || mac.wsk_macierz==NULL){
                      error(NIE_ISTNIEJE);
                      return *this;
                      }
        if(il_kolumny != mac.il_kolumny || il_wersy != mac.il_wersy){
                      error(ZLY_ROZMIAR);
                      return *this;
                      }      
        else{

             for(int i=0; i < il_wersy; i++){
                     for(int j=0; j < il_kolumny; j++){
                             wsk_macierz[i][j] = wsk_macierz[i][j] - mac.wsk_macierz[i][j];
                             
                             }
                     }
             return *this;
             }
        }

// ----------------------------------------------------------------- 

bool macierz::operator== (const macierz &mac){
        if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0 || mac.wsk_macierz==NULL){
                      error(NIE_ISTNIEJE);
                      return 0;
                      }
        if(il_kolumny != mac.il_kolumny || il_wersy != mac.il_wersy){
                      
                      return 0;
                      }      
        else{

             for(int i=0; i < il_wersy; i++){
                     for(int j=0; j < il_kolumny; j++){
                             if( wsk_macierz[i][j] !=  mac.wsk_macierz[i][j]){
                                 return 0;
                                 }
                             
                             }
                     }
             return 1;
             }
        }

// ----------------------------------------------------------------- 


macierz macierz::operator= (const macierz &mac){
        if( mac.wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0){
            error(NIE_ISTNIEJE);
            return *this;
            }
        if( wsk_macierz!=NULL){
            for (int i=0; i < il_wersy; i++){
                 delete [] wsk_macierz[i];
                 wsk_macierz[i] = NULL; 
                 }
      
            delete [] wsk_macierz;
            wsk_macierz = NULL;                
        }
        
        il_wersy = mac.il_wersy;
        il_kolumny = mac.il_kolumny;
        
        wsk_macierz = new int *[il_wersy];
      
        for(int i=0; i < il_wersy; i++){
                wsk_macierz[i] = new int [il_kolumny];                                                          
                }                   
                             
                            

        for(int i=0; i < il_wersy; i++){
                for(int j=0; j < il_kolumny; j++){
                        wsk_macierz[i][j] =  mac.wsk_macierz[i][j];
                             
                        }
                }
        return *this;

        }

// ----------------------------------------------------------------- 

macierz macierz::operator* (const macierz &mac){
        if( mac.wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0){
            error(NIE_ISTNIEJE);
            return *this;
            }
        if( mac.il_wersy != il_kolumny){
            error(ZLY_ROZMIAR);
            return *this;
            }
       
        int **temp = new int *[il_wersy];
        for( int i=0;i<il_wersy; i++){
             temp[i] = new int [mac.il_kolumny];
             }
        
        
        
        for (int i = 0; i < il_wersy; i++){      
            for (int j = 0; j < mac.il_kolumny; j++) {
                temp[i][j]=0;
                for (int k = 0; k < il_kolumny; k++){
                    temp[i][j] += wsk_macierz[i][k] * mac.wsk_macierz[k][j];
                    }
                }
            }
        for( int i=0; i < il_wersy; i++){
             delete [] wsk_macierz[i];
             wsk_macierz[i] = NULL; 
             }     
        delete [] wsk_macierz;
        wsk_macierz = temp;
        il_kolumny = mac.il_kolumny;
      
               
                             
                            



        return *this;

        }

// ----------------------------------------------------------------- 


ostream &operator<<(ostream &wyjscie, const macierz &mac){
        if( mac.wsk_macierz==NULL || mac.il_kolumny == 0 || mac.il_wersy == 0){
             cout << " Macierz nie istnieje! " << endl ;
             return wyjscie;
             } 
        for( int i = 0;i< mac.il_wersy; i++){
             for( int j=0;j< mac.il_kolumny;j++){
                  wyjscie << "\t" << mac.wsk_macierz[i][j] ;
                  }
             wyjscie << endl;
             }
        return wyjscie; 
        }

// -----------------------------------------------------------------
















// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------
// KOMUNIKATY B£ÊDÓW

void macierz::error(int err) const {
     blad = err;              
     switch(err){
                    
                 case ZLY_ROZMIAR: cout << " Zly rozmiar macierzy! " << endl ;
                                   system("Pause");
                 break;
                 case NIE_ISTNIEJE: cout << " Macierz nie istnieje! " << endl ;
                                    system("Pause");
                 break;
                 case NIE_KWADRATOWA: cout << "Wymagana macierz kwadratowa! " << endl ;
                                      system("Pause");
                 break;
                    
                    
                 }      
                
    }

// ----------------------------------------------------------------- 
// WYSWIETLANIE MACIERZY

void macierz::wyswietl() const{
     if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz == NULL){
           error(NIE_ISTNIEJE);        
           return;       
                   }
     else{
          for(int i = 0; i< il_wersy; i++){
                  for(int j = 0; j< il_kolumny; j++){
                          cout << "\t" << wsk_macierz[i][j];
                          }
                  cout << endl;             
                  }    
          }
     cout << endl;          
     }


// -----------------------------------------------------------------
// WYPE£NIANIE MACIERZY PRZEZ USERA

void macierz::wypelnij(){
     if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz == NULL){               //sprawdza czy istnieje
           error(NIE_ISTNIEJE);        
           return;       
                }
           
     else{

          for(int i = 0; i < il_wersy; i++){
              for(int j = 0; j < il_kolumny; j++){
                   cout << "\t";
                   cout << " [" << i << "] [" << j << "] ";
                   cin >> wsk_macierz[i][j];   
                      
                      }
              cout << endl;       
  
                  }     
          } 
}   
// -----------------------------------------------------------------
// WYPE£NIANIE MACIERZY ZERAMI

void macierz::wypelnij_zerami(){
      if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz == NULL){               //sprawdza czy istnieje
           error(NIE_ISTNIEJE);        
           return;       
                }     
     else{

          for(int i = 0; i < il_wersy; i++){
              for(int j = 0; j < il_kolumny; j++){
                   wsk_macierz[i][j] = 0;                         
                      }
                  }     
          } 
}    


// -----------------------------------------------------------------
// KONSTRUKTOR Z KOPIUJACY

void macierz::wypelnij_jednostkowa(){
     if(il_kolumny == 0 || il_wersy == 0 || wsk_macierz == NULL){               //sprawdza czy istnieje
           error(NIE_ISTNIEJE);        
           return;       
                }
     if(il_kolumny != il_wersy){                                                //sprawdza czy kwadratowa
     error(NIE_KWADRATOWA);
     return;        
                   
                   }                     
     else{

          for(int i = 0, k = 0; i < il_wersy; i++, k++){
              for(int j = 0; j < il_kolumny; j++){
                   if(j==k){
                           wsk_macierz[i][j] = 1; 
                            }
                   else{
                        wsk_macierz[i][j] = 0;
                        }                         
                      }
                  }     
          }
     }
// -----------------------------------------------------------------
// TRANSPONOWANA

void macierz::transponowana(){
    if(il_wersy==0 || il_kolumny==0 || wsk_macierz == NULL ){
        error(NIE_ISTNIEJE); 
		return;
	}
     int **wsk_trans=NULL;                                                       // Tworzy tablice
     wsk_trans = new int *[il_kolumny];
     for(int i=0; i < il_kolumny; i++){
            wsk_trans[i] = new int [il_wersy]; 
            }  
     for(int i = 0; i < il_wersy; i++){                                          // Transpouje macierz zapisuj¹c w nowej tablicy
             for(int j = 0; j < il_kolumny; j++){
                     wsk_trans[j][i] = wsk_macierz[i][j] ;                    
                     }     
             }               
     for(int i=0; i < il_wersy; i++){                                            // zwalnia pamiêæ starej tablicy
             delete [] wsk_macierz[i];
             wsk_macierz[i] = NULL; 
                                             }     
    delete [] wsk_macierz;
    wsk_macierz = NULL;      
    int temp = il_wersy;                                                         // podmienia zmienne i wskaŸnik do tablicy
    il_wersy = il_kolumny;
    il_kolumny = temp;    
    wsk_macierz = wsk_trans;                                                     
     }
// -----------------------------------------------------------------
// KASOWANIE MACIERZY BEZ KASOWANIA OBIEKTU

void macierz::kasuj(){
     if(il_wersy==0 || il_kolumny==0 || wsk_macierz == NULL ){
        error(NIE_ISTNIEJE); 
		return;
	 }
     for(int i=0; i < il_wersy; i++){                                            
             delete [] wsk_macierz[i];
             wsk_macierz[i] = NULL; 
                                             }     
     delete [] wsk_macierz;
     wsk_macierz = NULL;    
     il_wersy = 0;
     il_kolumny = 0;
     
     }     
  


// -----------------------------------------------------------------

void macierz::dodaj_wiersz_kolumna(bool w_or_k, int numer){
     if( il_wersy==0 || il_kolumny==0 || wsk_macierz == NULL ){
         error(NIE_ISTNIEJE); 
		 return;
	     }
	     
     int **temp;
     temp = new int *[il_wersy];
     int zmienna; 
     for( int i=0; i < il_wersy; i++){
          temp[i] = new int [il_kolumny];                                                          
          } 
     for( int i=0; i<il_wersy; i++){
          for(int j=0; j < il_kolumny; j++){
                  temp[i][j] = wsk_macierz[i][j];
                  
                  } 
          }
     for( int i=0; i < il_wersy; i++){
          delete [] wsk_macierz[i];
          wsk_macierz[i] = NULL; 
          }
      
     delete [] wsk_macierz;
     wsk_macierz = NULL;
     
     if( w_or_k){
         il_wersy++;             
         }   
     else{   
         il_kolumny++; 
          }           
     wsk_macierz = new int *[il_wersy];
         for( int i=0; i < il_wersy; i++){
              wsk_macierz[i] = new int [il_kolumny];              
              } 
     if( w_or_k){
         for( int i=0; i<numer; i++){
              for( int j=0; j< il_kolumny; j++){
                   wsk_macierz[i][j] = temp[i][j];
                   }
              }
         for( int j=0; j<il_kolumny; j++){
              cout << " ["<< numer <<"] [" <<j<<"]: ";
              cin >> zmienna;              
              wsk_macierz[numer][j] = zmienna;
              } 
         for( int i=(numer+1) ; i< il_wersy; i++){
              for( int j=0; j< il_kolumny; j++){
                   wsk_macierz[i][j] = temp[i-1][j];                   
                   }
              }    
         for( int i=0; i < (il_wersy-1); i++){
              delete [] temp[i];
              temp[i] = NULL; 
              }
         }
     else{
          for( int j=0; j<numer; j++){
               for( int i=0; i<il_wersy; i++){
                    wsk_macierz[i][j] = temp[i][j];
                    }               
               }
          for( int i=0; i<il_wersy; i++){
               cout << " ["<< i <<"] [" <<numer<<"]: ";
               cin >> zmienna;
               wsk_macierz[i][numer] = zmienna;
               }
          for( int j=(numer+1); j<il_kolumny; j++){
               for( int i=0; i<il_wersy; i++){
                    wsk_macierz[i][j] = temp[i][j-1];
                    }
          for( int i=0; i < il_wersy; i++){
               delete [] temp[i];
               temp[i] = NULL; 
               }              
          }
     delete [] temp;
     temp = NULL;
     
     }
     }

// -----------------------------------------------------------------

void macierz::zmien_rozmiar(int wer, int kol){
     if(wsk_macierz == NULL || il_kolumny == 0 || il_wersy == 0){ 
          wsk_macierz = NULL;                                               
                              }
                              
      else{
           for (int i=0; i < il_wersy; i++){
               delete [] wsk_macierz[i];
               wsk_macierz[i] = NULL; 
                                             }
      
           delete [] wsk_macierz;
           wsk_macierz = NULL;  
           }
           
      if(kol > 0 && wer > 0){
          il_kolumny = kol;
          il_wersy = wer; 
          wsk_macierz = new int *[wer];
      
          for(int i=0; i < wer; i++){
                  wsk_macierz[i] = new int [kol];                                                          
                  }                   
         blad =0;                    
         }
      else{
           wsk_macierz = NULL;
           error(ZLY_ROZMIAR);
           }      
     
     
     
     }
// -----------------------------------------------------------------






// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------


void show_macierze(macierz &m1, macierz &m2, macierz &m3);
void men(int &menu);
void case1(macierz &m1, macierz &m2);
void case2(macierz &m1, macierz &m2);
void case3(macierz &m1, macierz &m2);
void case4(macierz &m1, macierz &m2);
void case5(macierz &m1, macierz &m2);
void case6(macierz &m1, macierz &m2);
void case7(macierz &m1, macierz &m2);
void case13(macierz &m1, macierz &m2, macierz &m3);
void case14(macierz &m1, macierz &m2, macierz &m3);
void case15(macierz &m1, macierz &m2, macierz &m3);


// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------




int main(int argc, char *argv[])
{   
    bool koniec = 1;                                                             // koniec, potwierdenie zakonczenia programu                                                              
    int menu;                                                          // zarzadzanie menu, w_or_k - wiersz lub kolumna
    macierz m1(0,0);
    macierz m2(0,0);
    macierz m3(0,0);
    cout << " Zostaly stworzone 3 obiekty typu macierz. " << endl;
    cout << " Sa one na razie puste nalezy zmienic ich rozmiar i wypelnic liczbami " << endl;
    
    
    
    while(koniec){   
                  show_macierze(m1, m2, m3);    
                  men(menu);

                  switch(menu){
                               case 1: 
                                       case1(m1,m2);     
                                       break;
                                       
                               case 2: 
                                       case2(m1,m2);                     
                                       break;
                                       
                               case 3: 
                                       case3(m1,m2);
                                       break; 
                                       
                               case 4: 
                                       case4(m1,m2);
                                       break;
                                       
                               case 5: 
                                       case5(m1,m2);
                                       break; 
                                       
                               case 6:  
                                       case6(m1,m2);
                                       break; 
                                        
                               case 7:  
                                       case7(m1,m2);
                                       break; 
                                
                               case 8: m3 = m1 + m2;  
                                       break;
                               
                               case 9: m3 = m1 - m2;  
                                       break;     
                               
                               case 10: m1 += m2;  
                                        break;
                               
                               case 11: m1 -= m2;  
                                        break;
                               
                               case 12: m3 = m1* m2;  
                                        break;
                               
                               case 13: 
                                        case13(m1, m2, m3);
                                        break;
                               
                               case 14: 
                                        case14(m1, m2, m3);
                                        break;
                               
                               case 15: 
                                        case15(m1, m2, m3);
                                        break;
                                        
                               case 0: koniec = 0;
                                       cout << " Czy na pewno chcesz zamknac program?  " << endl << endl;
                                       cout << " Wcisnij 1 by pozostac w programie, lub dowolny klawisz by wyjsc. " << endl; 
                                       cin >> koniec;
                                       break;     
                                 
                               default: cout << "Zly wybor! " << endl;
                           }

                  }

    return EXIT_SUCCESS;
}







// -----------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------



void men(int &menu){
     cout << endl << endl;    
     cout << "------------------------------------------------------" << endl; 
     cout <<" Menu" << endl;
     cout << "------------------------------------------------------" << endl;
     cout << endl << endl;
     cout << " 0. ZAKONCZ PROGRAM! " << endl << endl;
     cout << " 1. Zmien rozmiar macierzy." << endl;
     cout << " 2. Wypelnij macierz zerami." << endl; 
     cout << " 3. Wypelnij macierz liczbami." << endl;
     cout << " 4. Wypelnij macierz tworzac macierz jednostkowa." << endl;
     cout << " 5. Transponuj macierz." << endl;
     cout << " 6. Skasuj macierz. " << endl;
     cout << " 7. Dodaj wiersz lub kolumne. " << endl;
     cout << " 8. Dodaj macierze (m3=m1+m2). " << endl;
     cout << " 9. Odejmij macierze (m3=m1-m2). " << endl;
     cout << " 10. Dodaj macierze (m1+=m2). " << endl;
     cout << " 11. Odejmij macierze (m1-=m2). " << endl;    
     cout << " 12. Pomnoz macierze (m3 = m1* m2). " << endl;
     cout << " 13. Pomnoz macierz przez skalar. " << endl;    
     cout << " 14. Sprawdz czy macierze sa rowne. (m1==m2)" << endl;
     cout << " 15. Przypisz jedna macierz drugiej. " << endl;
                  
     cout << endl  << endl;

     cout << "------------------------------------------------------" << endl; 
     cout << " Wybor pozycji z menu: ";
     cin >> menu;
     cout << endl;
     cout << "------------------------------------------------------" << endl;

     }


// -----------------------------------------------------------------
void show_macierze(macierz &m1, macierz &m2, macierz &m3){
     system("CLS");
                  cout << "------------------------------------------------------" << endl;     
                  cout << " Twoje macierze:";
                  if( m1.get_wsk_macierz() != NULL && m1.get_il_kolumny() != 0 && m1.get_il_wersy() !=0){
                      cout << endl << " MACIERZ 1: "<< endl;
                      cout << m1;       
                      }
                  if( m2.get_wsk_macierz() != NULL && m2.get_il_kolumny() != 0 && m2.get_il_wersy() !=0){
                      cout << endl << " MACIERZ 2: "<< endl;
                      cout << m2;       
                      }
                  if( m3.get_wsk_macierz() != NULL && m3.get_il_kolumny() != 0 && m3.get_il_wersy() !=0){
                      cout << endl << " MACIERZ 3 (wyniki) : "<< endl;
                      cout << m3;       
                      } 

     }



// -----------------------------------------------------------------
void case1(macierz &m1, macierz &m2){
     int zmienna, kol, wer;
     do{ 
        cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
        cin >> zmienna;
        cout << endl<< " Podaj ilosc kolumn: ";
        cin >> kol;
        cout << endl << " Podaj ilosc wersow: ";
        cin >> wer;      
        }while(kol <= 0 || wer <= 0 || (zmienna != 1 && zmienna != 2));        
                                       
        switch(zmienna){
                        case 1: m1.zmien_rozmiar(wer, kol);
                        break;
                        case 2: m2.zmien_rozmiar(wer, kol); 
                        break;
                        }
        }

// -----------------------------------------------------------------

void case2(macierz &m1, macierz &m2){
     int zmienna;
     do{ 
         cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
         cin >> zmienna;
         }while(zmienna != 1 && zmienna != 2);
                                            
         switch(zmienna){
                         case 1: m1.wypelnij_zerami();
                         break;
                         case 2: m2.wypelnij_zerami(); 
                         break;
                         }
     }                                  
// -----------------------------------------------------------------

void case3(macierz &m1, macierz &m2){
     int zmienna;
     do{
        cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
        cin >> zmienna;
        }while(zmienna != 1 && zmienna != 2);
        switch(zmienna){
                        case 1: m1.wypelnij();
                        break;
                        case 2: m2.wypelnij(); 
                        break;
                        }
     }
     
// -----------------------------------------------------------------





void case4(macierz &m1, macierz &m2){
     int zmienna;
     do{
        cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
        cin >> zmienna;
        }while(zmienna != 1 && zmienna != 2);

        switch(zmienna){
                        case 1: m1.wypelnij_jednostkowa();
                        break;
                        case 2: m2.wypelnij_jednostkowa(); 
                        break;
                        }              
     }                                 

// -----------------------------------------------------------------


void case5(macierz &m1, macierz &m2){
     int zmienna;
     do{
        cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
        cin >> zmienna;
        }while(zmienna != 1 && zmienna != 2);

        switch(zmienna){
                        case 1: m1.transponowana();
                        break;
                        case 2: m2.transponowana(); 
                        break;
                        }
     
                  
     }    


// -----------------------------------------------------------------


void case6(macierz &m1, macierz &m2){
     int zmienna;
     do{
        cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
        cin >> zmienna;
        }while(zmienna != 1 && zmienna != 2);
        switch(zmienna){
                        case 1: m1.kasuj();
                        break;
                        case 2: m2.kasuj(); 
                        break;
                        }
          
     }    

// -----------------------------------------------------------------


void case7(macierz &m1, macierz &m2){
     int zmienna, zmienna2, w_or_k, numer;
     if( m1.get_wsk_macierz() == NULL && m2.get_wsk_macierz() == NULL){
         m1.error(NIE_ISTNIEJE);
         }
     else{
               do{
                  cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
                  cin >> zmienna;
                  cout <<endl<<  " Chcesz dodac wiersz czy kolumne? ( 0 - wiersz, 1 - kolumna ): ";
                  cin >> w_or_k;
                  cout <<endl<<  " Numer po ktorym dodasz wiersz lub kolumne";
                  cin >> numer;
                                          
                  switch(zmienna){
                                  case 1: switch(w_or_k){
                                                         case 0: zmienna2 = m1.get_il_wersy();
                                                         break;
                                                                                   
                                                         case 1: zmienna2 = m1.get_il_kolumny();
                                                         break;
                                                         }
                                                                 
                                  break;
                                  case 2: switch(w_or_k){
                                                         case 0: zmienna2 = m2.get_il_wersy();
                                                         break;
                                                                                   
                                                         case 1: zmienna2 = m2.get_il_kolumny();
                                                         break;
                                                         }        
                                 break;
                                 }                                          
                  }while((zmienna != 1 && zmienna != 2) || (w_or_k != 0 && w_or_k !=1) || (numer > zmienna2 || numer < 0) );
                  switch(zmienna){
                                  case 1: m1.dodaj_wiersz_kolumna(w_or_k,numer);
                                  break;
                                  case 2: m2.dodaj_wiersz_kolumna(w_or_k,numer); 
                                  break;
                                  }
                 }
                                    

                                             
          
     }   

// -----------------------------------------------------------------


void case13(macierz &m1, macierz &m2, macierz &m3){
     int zmienna, zmienna2;
     if( m1.get_wsk_macierz() == NULL && m2.get_wsk_macierz() == NULL){
                                            cout << " Macierz nie istnieje! " << endl;
                                            system("Pause");                  
                                            }
                                        else{
                                             do{
                                                cout << " Ktora macierz chcesz zmienic ( MACIERZ 1 lub MACIERZ 2): ";
                                                cin >> zmienna;                              
                                                cout << " Podaj liczbe, przez ktora chcesz pomnozyc. ";
                                                cin >> zmienna2;
                                                                                 
                                                }while(zmienna != 1 && zmienna != 2);
                                                
                                             if( zmienna==1){
                                                 m3 = m1 * zmienna2;           
                                                 }
                                             else{
                                                  m3 = m2 * zmienna2;
                                                  }
                                             }
    
     
     }


// -----------------------------------------------------------------

void case14(macierz &m1, macierz &m2, macierz &m3){

     if( m1.get_wsk_macierz() == NULL || m2.get_wsk_macierz() == NULL){
                                            cout << " Ktoras macierzy nie istnieje! " << endl;
                                            system("Pause");                  
                                            }
                                        else{
                                             if(m1==m2){
                                                        cout << " Macierze sa rowne " << endl;
                                                        system("Pause");
                                                        }
                                             else{
                                                  cout << " Macierze NIE sa rowne " << endl;
                                                  system("Pause");
                                                  }
                                             
                                             }
    
     
     }


// -----------------------------------------------------------------

void case15(macierz &m1, macierz &m2, macierz &m3){

     int zmienna2=0, zmienna, ;
                                        if(m1.get_wsk_macierz() == NULL) zmienna2++;
                                        if(m2.get_wsk_macierz() == NULL) zmienna2++;
                                        if(m3.get_wsk_macierz() == NULL) zmienna2++;
                                        if( zmienna2>1){
                                            cout << " Musza istniec przynajmniej 2 macierze " << endl;
                                            system("Pause");           
                                            }
                                        else{
                                             do{
                                                zmienna2=0;                       
                                                cout << " Jakie dzialanie chcesz wykonac? "<< endl;
                                                
                                                cout << " m1=m2 wcisnij 0 "<<endl;
                                                cout << " m1=m3 wcisnij 1 "<<endl;
                                                cout << " m2=m1 wcisnij 2 "<<endl;
                                                cout << " m2=m3 wcisnij 3 "<<endl;
                                                cout << endl<< " Gdy bedziesz chcial wykonac dzialanie " <<endl<< "na nie istniejacych macierzach program ponownie poprosi o wybor. "<<endl;
                                                cin >> zmienna;                                             
                                                
                                                
                                                if( zmienna==0||zmienna==1||zmienna==2){
                                                    if(m1.get_wsk_macierz() == NULL) zmienna2++;           
                                                    }
                                                if( zmienna==0||zmienna==2||zmienna==3){
                                                    if(m2.get_wsk_macierz() == NULL) zmienna2++;           
                                                    }
                                                if( zmienna==1||zmienna==3){
                                                    if(m3.get_wsk_macierz() == NULL) zmienna2++;           
                                                    }
                                                }while(zmienna2!=0 || zmienna<0 || zmienna > 3);
                                                
                                             
                                             switch(zmienna){
                                                             case 0: m1=m2; break;
                                                             case 1: m1=m3; break;
                                                             case 2: m2=m1; break;
                                                             case 3: m2=m3; break;
                                                             default: cout << endl <<" eee cos nie tak "; 
                                                             }
                                             }
     
     }


// -----------------------------------------------------------------





















