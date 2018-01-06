#include <iostream>
#include <conio.h>
using namespace std;

char tab[3][3]={'a','b','c','d','e','f','g','h','i'};


/*
Funkcja sprawdzajaca czy znak ascii jest z zakresu (a,z)
Jesli nie, znaczy to ze nie jest mala litera
Duze pomijamy, bo nie ma ich w tej tablicy i tak
wzracana wartosc bool to flaga z 
arg char x to char x w f-cji zamien()

for przeszukuje tablice i sprawdza czy jest tam taka litera
*/
bool sprawdz_litere(char x){
     bool ok=0;
     if( (x<'a')||(x>'z')){
         cout << endl << "To nie jest litera! \n";
         return 0;
         }
         
              
     for( int i=0; i<3; i++){
          for( int j=0; j<3; j++){
               if( tab[i][j]==x) {
                   ok=1;
                   }
               }
          }
     if(ok){
            return 1;
            }
     cout << endl << "W tablicy nie ma takiej litery " << endl;
     
     return 0;
     }
/*
W ten sam sposob dla cyfr
*/

bool sprawdz_cyfre(char x){   
     if( (x<'0')||(x>'9')){
         cout << endl << "To nie jest cyfra! \n";      
         return 0;
         }

     return 1;
     }


bool istnieja(){
     bool ok = 0;
     for( int i=0; i<3; i++){
          for( int j=0; j<3; j++){
               if((tab[i][j]>='a')&&(tab[i][j]<='z')) {
                   ok=1;
                   }
               }
          }
     if(!ok){
             cout << endl << "W tablicy nie ma juz liter. Powymienialiscie wszystko :( Musimy konczyc. " << endl;
             system("Pause");
             return 0;
             }
    return 1;
     }




void wyswietl(){
     cout<<endl;
     for( int i=0; i<3; i++){
          for( int j=0; j<3; j++){
               cout<<tab[i][j]<<" ";
               }
          cout<<endl;
          }
     cout<<endl;
     }
     
     
void zamien(){
     char x,a;
     bool z=0;
     do{
        cout<<endl<<endl;
        
        do{
           cout<<"Podaj litere do zamiany"<<endl;
           cin>>x;
           z = sprawdz_litere(x);          
           }
           while(z==0);
        z=0;
        
        do{
           cout <<endl<<"Na jaka cyfre zamienic"<<endl;
           cin>>a;
           z = sprawdz_cyfre(a);          
           }
           while(z==0);
           
        z=0;
           
        for( int i=0; i<3; i++){
             for( int j=0; j<3; j++){
                  if( tab[i][j]==x) {
                      tab[i][j]=a; z=1;
                      }
                  }
             }
        if(z==0){cout<<"nie ma takiej litery"<<endl;system("PAUSE");}

        }
        while(z==0);

     }
 
 
 
int main(){
    char tmp;
    do{
         
       if( !istnieja()){
           return 0;     
           }  
       wyswietl();
       zamien();
       wyswietl();
       
       do{
          cout <<endl<< "Koniec? (0/1)"<< endl;
          cin >> tmp;       
          if(tmp=='0'){
                       cout << " Jeszcze raz :)" <<endl;
                       }
                       else{
                            if(tmp=='1'){
                                         cout << " Konczymy" <<endl;
                                         system("PAUSE");
                                         return 0;
                                         }
                            }
          
          }while((tmp!='0')&&(tmp!='1'));
     
       }
       while(1);  
         

    cin.get();
    system("PAUSE");
    return 0;  

    }    
    
