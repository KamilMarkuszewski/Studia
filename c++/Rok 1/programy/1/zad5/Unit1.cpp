//---------------------------------------------------------------------------
#include <ctype.h>
#include <vcl.h>
#include <iostream.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop
#include <iomanip>

//---------------------------------------------------------------------------

#pragma argsused



int F_ile(){
                // wprowadzenie ilosci liczb
                int ile=0;
                do{
                cout << "podaj ilosc(max 1000) wczytywanych liczb: ";
                cin >> ile;
                cout << endl << endl;
                   }while(ile>1000);
                return ile;
             }




void hr(){
                // podzia³
                cout  << endl << endl << "________________________________________________________________________" << endl << endl;
         }




void wczytaj(float *tab, int ile){
                                // wczytywanie liczb do tablicy
                                          for(int i=0;i<ile;i++) {
                                                                    cout  << "Podaj liczbe: ";
                                                                    cin >> tab[i];
                                                                  }
                                }



float dec2oct(int x,int t);
float dec2oct(int x,int t){
//zamiana z systemu 10-tkowego na 8-kowy
        static int y = 0;
        static int z = 0;
        static int i=0;

        if(t==0){z = 0; y = 0; i=0; t++;} //zerowanie zmiennej pomocniczej z


        if (!x) return 0; //je¿eli x=0

        y+= floor(x/8);
        x-=y*8;

        z += x*pow(10,i); //doliczanie do zmiennej pomocniczej z
        i++;


        if(y>8){          // je¿eli x>8 rekurencja
            x = y;
        y = 0;
        dec2oct(x,t);
                }
        else{            // ostatnie wykonanie ju¿ bez rekurencji

           z += y*pow(10,i);
        i=0;


        }
        return z;

}

void przypisz(char *z, int x, int i){

      if(x>9||x==0){

        switch(x){
                case 10: z[i]='A'; break;
                case 11: z[i]='B'; break;
                case 12: z[i]='C'; break;
                case 13: z[i]='D'; break;
                case 14: z[i]='E'; break;
                case 15: z[i]='F'; break;
                case 16: z[i]='G'; break;
                case 0: break;




                  }

                 }
                 else{
                 z[i]=x+'0';
                 }



}



void dec2hex(int x, int t);
void dec2hex(int x, int t){
//zamiana z systemu 10-tkowego na 16-kowy
//upgradowana kopia poprzedniej funkcji
        static int y = 0;
        static char z[50];
        static int i=0;
        if(t==0){ y=0; i=0;}
        for(int j=0; j<49; j++){
        z[j]=0;}

        if (!x) {cout << "0"; exit;}

        y+= floor(x/16);
        x-=y*16;


        przypisz(z, x, i);




        if(y>16){
        x = y;
        y = 0;
        i++;
        dec2hex(x,1);
                }
        else{

                i++;
                x = y;
                y = 0;
                przypisz(z, x, i);

        }


     for(;i>-1; i--){
     cout << z[i];
     }

        exit;

}







int main(int argc, char* argv[]){
int ile = 0;
float *liczby; // wsk na poczatek dynamicznej tablicy
int precyzja;


cout << "Program wczytujacy liczby do tablicy" << endl << endl;

// wprowadzenie ilosci liczb
ile = F_ile();


liczby = new float[ile];


hr();
// okreslenie precyzji


cout << "Podaj z jaka precyzja maja byc wypisane liczby: ";
cin >>   precyzja ;



hr();
// wczytanie liczb

cout << "Program wczyta " << ile << " liczb rzeczywistych. " << endl <<  "Liczby niecalkowite nalezy zapisywac w postaci dziesietnej z uzyciem kropki." << endl << endl;


wczytaj(liczby, ile);


hr();







// wyswietlenie liczb

for(int i=0;i<ile;i++){


                        cout << setprecision(precyzja) << endl  ;
                        cout.width(25);
                        cout.setf(ios::right);
                        cout.setf(ios::showbase);
                        cout << fixed << liczby[i];
                        cout.width(10);
                        cout << setprecision(0) << dec2oct(liczby[i],0);                           // cout << oct<< liczby[i];
                        cout.width(10);
                        dec2hex(liczby[i],0);                           // cout << hex << liczby[i];




                       }




hr();

        system("Pause");
        delete []liczby;
        return 0;
}
//---------------------------------------------------------------------------



