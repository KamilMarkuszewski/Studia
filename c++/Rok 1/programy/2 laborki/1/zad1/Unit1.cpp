//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
int ile = 0;
float *liczby; // wsk na poczatek dynamicznej tablicy
int precyzja;


cout << "Program wczytujacy liczby do tablicy" << endl << endl;

// wprowadzenie ilosci liczb
do{
        cout << "podaj ilosc(max 1000) wczytywanych liczb: ";
        cin >> ile;
        cout << endl << endl;
        }while(ile>1000);
liczby = new float[ile];




cout  << endl << endl << "__________________________________________" << endl << endl;
// wczytanie liczb

cout << "Program wczyta " << ile << " liczb rzeczywistych. Liczby niecalkowite nale�y zapisywac w postaci dziesietnej z uzyciem kropki." << endl << endl;


for(int i=0;i<ile;i++) {
                        cout << "Podaj liczbe: ";
                        cin >> liczby[i];
                        }


cout  << endl << endl << "__________________________________________" << endl << endl;
// wyswietlenie liczb

for(int i=0;i<ile;i++){
                        cout << "liczba nr " << i+1 << " to: " << liczby[i] << endl;
                       }




cout  << endl << endl << "__________________________________________" << endl << endl;

        system("Pause");
        delete []liczby;
        return 0;
}
//---------------------------------------------------------------------------
 