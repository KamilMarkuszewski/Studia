// plecaki.cpp : Defines the entry point for the console application.
//
/*
Struktury danych i z³o¿onoœæ obliczeniowa - Projekt
Kamil Markuszewski 171016
Cezary Ruszkiewicz, 171154  
*/

#include <fstream.h> 
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
//--KLASA--Elementu----------------------------------------
class CElement{
private:
	int a; //waga etc elementu
	int w; //wartosc elementu
public:
	CElement();
	CElement(bool recznie);
	~CElement(){}
	int daj_a();
	int daj_w();
};CElement * E;
CElement::CElement(){
	this->a = 0;
	this->w = 0;
};
CElement::CElement(bool recznie){
	if(recznie){
		cout<<"\nPodaj wage\n";
		cin>>this->a;
		cout<<"Podaj wartosc\n";
		cin>>this->w;
	 cout<<endl;
	}
	else{
	a = rand();
	w = rand();
	}

}
int CElement::daj_a(){
	return a;
}
int CElement::daj_w(){
	return w;
}
//--KLASA--Plecak------------------------------------------
class CPlecak{
private:
	int B; //max pojemnosc;
	int A; //aktualna pojemnosc
public:
	CPlecak(){};
	CPlecak(int rozmiar);
	~CPlecak(){};
	int daj_B();
	int daj_A();
	void ustaw_A(int x);
}Plecak;
CPlecak::CPlecak(int rozmiar){
	this->A = 0;
	this->B = rozmiar;
}


int CPlecak::daj_B(){
	return this->B;
}
int CPlecak::daj_A(){
	return this->A;
}
void CPlecak::ustaw_A(int x){
	this->A = x;
}

//--KLASA--Œrodowisko--------------------------------------
class CSrodowisko{
private:
	CElement * E; //wskaznik na elementy
	CPlecak P; //plecak
	int n; //ilosc elementow
	int ** wynik; //tablica wynikow
	int * rozw; //tablica do ktorej wrzucam elementy
	int licznik; //licznik ilosci elementow
	int i; //uniwerslany iterator
public:
	CSrodowisko(){};
	~CSrodowisko();
	CSrodowisko(bool reczny, int ilosc_elementow, int rozmiar_plecaka);
	void upakuj();
	double mierz();
};
CSrodowisko::CSrodowisko(bool reczny, int ilosc_elementow, int rozmiar_plecaka){
	this->P = CPlecak(rozmiar_plecaka);
	this->licznik = 0;
	this->n = ilosc_elementow;
	this->E = new  CElement[n+1];
	if(reczny){
		for(i = 1; i<=n; ++i){
			cout<<"Element "<<i<<"\n";
			this->E[i] = CElement(reczny);
			system("cls");
		}
	}
	else{
		for(i = 1; i<=n; ++i){
			this->E[i] = CElement(reczny);
		}
	}
	
	this->rozw = new int[n];
	this->wynik = new int * [n+1];
	for (i = 0; i<=n; ++i){
		wynik[i] = new int [rozmiar_plecaka+1];
	}
}
CSrodowisko::~CSrodowisko(){
	if(wynik != NULL){
		if(wynik[0] != NULL) {for(i = 0; i<=n; ++i)delete [] wynik[i];}
		delete [] wynik;
	}
	if(E != NULL)delete [] E;
    if(rozw != NULL)delete [] rozw; 
}	

/* prezentacja tekstowa algorytmu na konsoli do testowania poprawnosci, stosowac dla malyc liczb   */

void CSrodowisko::upakuj(){
	P.ustaw_A(P.daj_B());
	cout<<"Pojemnosc plecaka to "<<P.daj_B()<<"\n";
	cout<<"Wyswietlanie elementow\n";
	cout<<"Lp.\twaga\twartosc\n";
	for(i = 1; i<=n; ++i)cout<<i<<"\t"<<E[i].daj_a()<<"\t"<<E[i].daj_w()<<"\n";
	cout<<"\n";
	cout<<"Tabela"<<endl<<endl;
    for(i = 0; i<=n; ++i) wynik[i][0] = 0; //napisanie zer na krawedziach
	for(i = 0; i<=P.daj_B(); ++i){
		wynik[0][i] = 0;
		cout<<wynik[0][i]<<"\t";
	}
	cout<<"\n";
	//wyswietlanie wlasciwe
		for (i = 1; i<=n; ++i){
		for (int j = 0; j<=P.daj_B(); ++j){
			if(E[i].daj_a() > j){
				wynik[i][j] = wynik[i-1][j];
				cout<<wynik[i][j]<<"\t";
			}
			else{
				wynik[i][j] = std::max(wynik[i-1][j-E[i].daj_a()]+E[i].daj_w(),wynik[i-1][j]);
				cout<<wynik[i][j]<<"\t";
			}
			if(j==P.daj_B()) cout<<"\n";
		}
	}
	//backtracking
	for(i = n; i>=1; --i){
		if(P.daj_A()>0){
			if(wynik[i][P.daj_A()]!=wynik[i-1][P.daj_A()]){
				P.ustaw_A(P.daj_A()-E[i].daj_a());
				rozw[licznik]=i;
				++licznik;
			}
		}
	}
	cout<<endl<<"Elementy to: ";
	for(i = 0; i<licznik; ++i)cout<<rozw[i]<<" ";
	cout<<endl;

}


/*
Pobiera czas metoda zalezna od globalnej flagi
*/

time_t pobierz_czas(){
       return clock ();  
       }

/*
Oblicza czas wykonywania sie algorytmu dla metod clock() i time()
*/

double difft(time_t time_po, time_t time_przed){   
       return (difftime(time_po, time_przed) / CLOCKS_PER_SEC);
       }
/* badanie efektywnosci algorytmu   */
double CSrodowisko::mierz(){
	     
     clock_t time_przed;                   // pomiar czasu prz sortowaniem
     clock_t time_po;                      // pomiar czasu po sortowaniu
     double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
	
	 P.ustaw_A(P.daj_B());
     for(i = 0; i<=n; ++i) wynik[i][0] = 0; //napisanie zer na krawedziach
	 for(i = 0; i<=P.daj_B(); ++i){
		   wynik[0][i] = 0;
	}

     time_przed = pobierz_czas();         // pomiar czasu przed 
	//algorytm
		for (i = 1; i<=n; ++i){
		for (int j = 0; j<=P.daj_B(); ++j){
			if(E[i].daj_a() > j){
				wynik[i][j] = wynik[i-1][j];
			}
			else{
				wynik[i][j] = std::max(wynik[i-1][j-E[i].daj_a()]+E[i].daj_w(),wynik[i-1][j]);
			}
		}
	}

	//backtracking
	for(i = n; i>=1; --i){
		if(P.daj_A()>0){
			if(wynik[i][P.daj_A()]!=wynik[i-1][P.daj_A()]){
				P.ustaw_A(P.daj_A()-E[i].daj_a());
				rozw[licznik]=i;
				++licznik;
			}
		}
	}
    time_po = pobierz_czas();                  // pomiar czasu po
    time_roznica = difft(time_po, time_przed);    
	return time_roznica;
}

/* funkja testuj¹ca poprawnosc */
void test(){
     cout << "testuj plecak: \n";
     bool pytanie = true;
     int B,n;
     cout<<"\nPodaj ilosc elementow\n";
     cin>>n;
     cout<<"\nPodaj wielkosc plecaka\n";
     cin>>B;
     system("cls");
     CSrodowisko Srodowisko(pytanie,n,B);
     system("cls");
     Srodowisko.upakuj();
     cout<<endl;
     system("pause");
     }

/* funkja licz¹ca wyniki */
void pomiar(){
     bool pytanie = false;
     int B,n;
     ofstream zapis("zapis.txt"); 

     for(B=2000; B<=10000; B+=2000){
             zapis << "\n-----------------\n Rozmiar plecaka: " << B << endl ;
             for(n=5000; n<=50000; n+=5000){
                     zapis << " Ilosc elementow: " << n;
                     double srednia = 0;
                     for(int k=0; k<10;k++){
                             CSrodowisko Srodowisko(pytanie,n,B);
                             srednia += Srodowisko.mierz();
                             }
                     srednia = srednia/10;
                     zapis << " Pomiar: " << srednia << endl;
                     }
             }
             
     for(B=2000; B<=6000; B+=2000){
             zapis << "\n-----------------\n Rozmiar plecaka: " << B << endl ;
             for(n=55000; n<=80000; n+=5000){
                     zapis << " Ilosc elementow: " << n;
                     double srednia = 0;
                     for(int k=0; k<10;k++){
                             CSrodowisko Srodowisko(pytanie,n,B);
                             srednia += Srodowisko.mierz();
                             }
                     srednia = srednia/10;
                     zapis << " Pomiar: " << srednia << endl;
                     }
             }
     
     zapis.close(); 
     system("pause");
     }


//-----MAIN------------------------------------------------
int main()
{

    do{
        int menu = 0;
        system("cls");
        cout << "MENU: \n";
        cout << "1. Testowanie poprawnosci \n";
        cout << "2. Pomiary \n";
        cout << "0. Wyjscie \n\n";
        srand((unsigned)time(NULL));
        cin >> menu;
        
        if(menu==0){return 0;}                   
        if(menu==1){test();}  
        if(menu==2){pomiar();}
                    
                
   	}while(1);                  
}    
	              
	              
	              
