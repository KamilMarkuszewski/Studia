// PEA_lab_1.cpp : Defines the entry point for the console application.
//
#include <fstream> 
#include <fstream.h> 
#include "stdafx.h"
#include <time.h>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

#include <iostream>
#include <conio.h>
using namespace std;
int wezly = 0;

long long int wezlyBB = 0;
// ----------------------------------------------------------------------------------
// STRUKTURA ZADANIE
// ----------------------------------------------------------------------------------

struct Zadanie{

	float aj;	//normalny czas wykonywania zadania
	float bj;	// liniowy wspl zuzycia

	float dj;	// pozadany termin wykonania zadania
	float gj;	//prog zuzycia zadania

	int uj;
	int cj;
	int index;

	// zadanie jest "wieksze" jesli pozadany termin wykonania jest wiekszy

	bool operator==(const Zadanie &operand){
		if (dj == operand.dj)return true; 
		return false;
	}
	bool operator>(const Zadanie &operand){
		if (dj > operand.dj)return true; 
		return false;
	}
	bool operator<(const Zadanie &operand){
		if (dj < operand.dj)return true; 
		return false;
	}

	void cpy(Zadanie cpy){
		aj = cpy.aj;
		bj = cpy.bj;
		dj = cpy.dj;
		gj = cpy.gj;
		index = cpy.index;
	}
	void wypisz(){
		cout << aj << "\t ";
		cout << bj << "\t ";
		cout << dj << "\t ";
		cout << gj << "\t ";
		cout << index << "\t ";
		cout << endl;
	}


};





// ----------------------------------------------------------------------------------
// STRUKTURA ROZWIAZANIE
// ----------------------------------------------------------------------------------

struct Rozwiazanie{
	int wart_k;

};

// ----------------------------------------------------------------------------------
// KLASA PROBLEM
// ----------------------------------------------------------------------------------


class Problem{

	private:
		int n;
		
		double wartosc;

	public:
		Zadanie * zad;
		Problem(int n);
		~Problem();

		double obliczCzasWykonania();	// oblicza pj czyli cza wykonania zadania dany funkcja niemalejaca zalezna od pozycji zadania

		void generujParametry();
		void randParam();
		void wypisz();
		int obliczUj();
		int obliczUj(int i);
		int obliczUj(int id, int dec_uj, double cj);
		int obliczUj(int id, int dec_uj, double cj, int i_do);
		double pj(int v);
		double pj_bez_b(int v);
		void f_edd(int index);
		void f_moore(bool funkcja, int index);
		void f_neh();

		Rozwiazanie * edd, moore, neh;

};

Problem::Problem(int tmp_n){
	n = tmp_n;
	wartosc = 0;
	zad = new Zadanie[n];
	randParam();
}





Problem::~Problem(){
	if(zad!=NULL) delete zad;
	zad = NULL;
}

double Problem::pj(int v){
	
	if(v>n || v<0) return 0;							// jesli poza zakresem tablicy
	float max = (float)v - 1 - zad[v].gj;				// pj(v) = aj+bj*max{v-1-qj,0}
	if(0.0>max) max = 0.0;
	return (zad[v].aj + zad[v].bj*max);					
}

double Problem::pj_bez_b(int v){
	return (zad[v].aj);					
}


int Problem::obliczUj(int id){
	double cj = 0;
	int u = 0;
	for(int i=0; i<id; i++){
		cj = cj + pj(i);
		if(zad[i].dj < cj) u++;
	}
	return u;
}

int Problem::obliczUj(int id, int dec_uj, double cj){
	cj = cj + pj(id);
	zad[id];
	if(zad[id].dj < cj) dec_uj++;
	return dec_uj;
}

int Problem::obliczUj(int id, int dec_uj, double cj, int i_do){
	cj = cj + pj(id);
	if(zad[id].dj < cj) dec_uj++;

	for(int i=id+1; i<i_do; i++){
		cj = cj + pj(i);
		if(zad[i].dj < cj) dec_uj++;
	}
	return dec_uj;
}

int Problem::obliczUj(){
	double cj = 0;
	int u = 0;
	for(int i=0; i<n; i++){
		cj = cj + pj(i);
		if(zad[i].dj < cj) u++;
	}
	return u;
}


void Problem::randParam(){
	// start losowania
	srand((unsigned)time(NULL));
	// losowanie podstawowych parametrów dla poszczegolnych zadan
	for(int i=0; i<n; i++){
		zad[i].index = i;
        zad[i].aj = (float)((float)rand()* (1.0/(RAND_MAX + 1.0)) * (20.0 - 10.0) + 10.0);
        zad[i].bj = (float)((float)rand()* (1.0/(RAND_MAX + 1.0)) * (10.0 - 1.0) + 1.0);
        zad[i].gj = (float)((float)rand()* (1.0/(RAND_MAX + 1.0)) * (0.5*n - 0.1*n) + 0.1*n);
	}
	
	// obliczanie parametru dj dla poszczegolnych zadan
	for(int i=0; i<n; i++){
		float suma = 0.0;	// suma potrzebna we wzorze na dj
		float suma2 = 0.0;	// suma potrzebna we wzorze na dj
		
		for(int j=0; j<n;j++){
			suma += zad[j].aj;
			suma2 += zad[j].aj + zad[j].bj * n; 
		}

		suma /=n;
		suma2 /= 4;
		zad[i].dj = (float)((float)rand()* (1.0/(RAND_MAX + 1.0)) * (suma2 - suma) + suma);
	}
}


void Problem::wypisz(){
	cout.precision(3);	
	for(int i = 0; i<n; i++){
		cout << endl << "index: " << zad[i].index << "\t aj: " << zad[i].aj << " \t bj: " << zad[i].bj << " \t gj: " << zad[i].gj << " \t dj: " << zad[i].dj<< " \t pj: " << pj(i)  ;
	
	
	}

	cout << endl;

}

// ----------------------------------------------------------------------------------
// CZAS
// ----------------------------------------------------------------------------------

/*
Oblicza czas wykonywania sie algorytmu dla metody clock()
*/

double difft(time_t time_po, time_t time_przed){   
	return (difftime(time_po*1000, time_przed*1000) / CLOCKS_PER_SEC);
}

// ----------------------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------------------









//------------------------------------------------------------------------------
//------------SORTOWANIE PRZEZ SCALANIE ----------------------------------------
//------------------------------------------------------------------------------

/**
Wywo³ywana rekurencyjnie funkcja sortowania przez scalanie
tab - sortowana tablica
pom - tablica pomocnicza
index_pierwszego elementu :)
index_ostatniego elementu :)
*/
void Permutacja::BruteForce(){
	int nr_perm = 0;
	int new_kryt = pr->obliczUj();
	if(new_kryt< min_kryt){
		min_kryt = new_kryt;
		poz_min_kryt = nr_perm;
	}
	while(!getEnd())
	{
		nr_perm++;
		Next();
		wezly++;
		int new_kryt = pr->obliczUj();
		if(new_kryt< min_kryt){
			int new_kryt = pr->obliczUj();
			//show();
			min_kryt = new_kryt;
			poz_min_kryt = nr_perm;
		}
	}
	first();
	while(!getEnd())
	{
		nr_perm++;
		Next();
		int new_kryt = pr->obliczUj();
		if(new_kryt< min_kryt){
			int new_kryt = pr->obliczUj();
			//show();
			min_kryt = new_kryt;
			poz_min_kryt = nr_perm;
		}
	}
	first();
	while(!getEnd())
	{
		nr_perm++;
		Next();
		int new_kryt = pr->obliczUj();
		if(new_kryt< min_kryt){
			int new_kryt = pr->obliczUj();
			//show();
			min_kryt = new_kryt;
			poz_min_kryt = nr_perm;
		}
	}

}

void scalanie_alg(int index_pierwszego, int index_ostatniego, Zadanie* tab, Zadanie* pom){
     
	int podzial;
	int j,k,i;
	podzial = (1 + index_pierwszego + index_ostatniego) / 2;                     // przygotowanie podzialu zbioru na 2 czesci
	if( index_ostatniego - podzial > 0){                                         // sortowanie rekurencyjne podzbioru drugiego
		scalanie_alg(podzial, index_ostatniego, tab, pom);
	}
	if( podzial - index_pierwszego > 1){                                         // sortowanie rekurencyjne podzbioru pierwszego
		scalanie_alg(index_pierwszego, podzial - 1, tab, pom);
	}
	j = index_pierwszego;
	k = podzial;
	for( i = index_pierwszego; i <= index_ostatniego; i++){                      // scalanie
		if(((index_ostatniego >= k) && (tab[k] < tab[j])) || ( j == podzial)){  // jezeli index pierwszego elementu z pierwszego zbioru jest rowny podzial tzn ze jestesmy
			pom[i].cpy(tab[k]);													// na najnizszym poziomie rekurencji
			//pom[i] = tab[k];                                                   
			k++;                                                              
		}else{
			pom[i].cpy(tab[j]);	// to jest dla klasy zadanie
			//pom[i] = tab[j];	// to by³o dla intów
			j++;
		}
	}
	for( i = index_pierwszego; i <= index_ostatniego; i++){                      // przepisywanie z tablicy pomocniczej do tab juz po scaleniu
		//tab[i] = pom[i];
		tab[i].cpy(pom[i]);
	}     
}


// algorytm EDD
// sortowanie przez scalanie (bo je lubie!) zadan rosnaco wedlug dj
void Problem::f_edd(int index = 0){
	Zadanie *pom;                            // tablica pomocnicza
    pom = new Zadanie[n];
	scalanie_alg(index,n-1, zad, pom);
	delete [] pom;
}

// algorytm NEH
// tu zostane jednak chyba przy tablicy a nie przy liscie
// co prawda musze co chwile wstawiac element w dziwne mejsce tablicy
// ale przy liscie i tak z takikm zadaniem trzeba przez cala przelatywac
// z reszta ten element jest wstawiany zawsze miejsce obok poprzedniego miejsca
// wiec wystarczy swapowac komorki
// po znalezieniu optymalnego polozenia trzeba wstawic w srodek, ale co za roznica czy bede swapowac od poczatku czy leciec iteratorem






/**
Przyspieszy³em algorytm z 3,4sek do 1,2sek wiêcej chyba nie wymyœlê. 
**/
void Problem::f_neh(){
	int pozycja_optymalna = 0;
	zad[0].uj = obliczUj(0);
	
	for(int i=1;i<n;i++){
		double tmp_cj = 0;
		if(pozycja_optymalna>0) tmp_cj = zad[pozycja_optymalna-1].cj;
		for(int k=pozycja_optymalna; k<i;k++){
			tmp_cj += pj(k);
			zad[k].cj =  (int)tmp_cj;
		}


		// sprawdzam jak dobry jest to wybor

		int min_kryterium = obliczUj(i,zad[i-1].uj,zad[i-1].cj);
		
		pozycja_optymalna = i;
		// szukam lepszego rozwiazania
		for(int j=i;j>1;j--){
		
			// cofam zadanie o 1 pozycje
			Zadanie swap_tmp = zad[j-1];
			zad[j-1] = zad[j];
			zad[j]= swap_tmp;

			// sprawdzam czy ten wybor jest lepszy
			
			int new_min = obliczUj(j-1,zad[j-2].uj,zad[j-2].cj,i);
			if(min_kryterium>new_min){
				min_kryterium = new_min;		// najlepsze znalezione kryterium
				pozycja_optymalna = j-1;			// pozycja na ktorym jest najlepsze kryterium
			} 
		}

		// cofam zadanie na 0 pozycje
		Zadanie swap_tmp = zad[0];
		zad[0] = zad[1];
		zad[1]= swap_tmp;

		int new_min = obliczUj(i);
		if(min_kryterium>new_min){
			min_kryterium = new_min;		// najlepsze znalezione kryterium
			pozycja_optymalna = 0;			// pozycja na ktorym jest najlepsze kryterium
		} 

		// dolecialem na sam poczatek tablicy a pozycja na kotrej powinno byc to zadanie jest przeciez pod pozycja_optymalna
		// musze wiec poswapowac to zadanie z pozycji 0 do optymalnej
		for(int j=0;j<pozycja_optymalna;j++){
			Zadanie swap_tmp = zad[j];
			zad[j] = zad[j+1];
			zad[j+1] = swap_tmp;
		}
	}
}




// algorytm moore'a
// zaimplementowane z pomoc¹ listy, poniewaz musimy przenosic element na koniec
// wiec w przypadku tablicy bylaby potrzeba przesuwania prawie calej tablicy w lewo przy kazdym przsunieciu na koniec
// tu wystarczy przelozyc wezel wiec wszystko idzie szybciej

void Problem::f_moore(bool funkcja = 0, int index = 0){
	clock_t time_przed;                  // pomiar czasu prz sortowaniem
	clock_t time_po;                     // pomiar czasu po sortowaniu
	double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
	list<Zadanie> lista;
	double suma_c = 0.00;
	int licznik = 0;
	// przepisuje z tablicy do listy
	for(int i=index; i<n;i++){
		lista.push_back(zad[i]);
	}
	if(funkcja != 0){
		f_edd(index);
	}
	time_przed = clock();			// pomiar czasu przed sortowaniem 
	for( list<Zadanie>::iterator iter=lista.begin(); iter != lista.end(); ++iter ){


		// suma_c - czas wykonania zadania, uwzgledniajacy zad wczesniejsze
		// dj - preferowany czas wykonania zadania
		if(funkcja == 0){
			suma_c = suma_c + pj(licznik);
		} else {
			suma_c = suma_c + zad[licznik].aj;
		}	

		if(suma_c>iter->dj){ 
			//cout << licznik << endl;
			// zdarzenie jest opoznione
			// wiec szukam zadania o najwiekszym czasie wykonywania (aj) bo przesunac go na koniec

				//cout <<endl << "opoznione: "<< iter->aj <<endl;			// do debugowania

				//cout << "IN"<< endl;
				//system("Pause");											// do debugowania


			float aj_max = 0.0;
			list<Zadanie>::iterator wsk_max;
			bool ok = false;
			
			for(list<Zadanie>::iterator iter_wewn=lista.begin(); iter_wewn!= iter; ++iter_wewn){
				if(iter_wewn->aj > aj_max){
					aj_max = iter_wewn->aj;
					wsk_max = iter_wewn;
					ok=true;
				} 
			}
			

			if(ok){
				Zadanie tmp = (*wsk_max);
				lista.erase(wsk_max);
				lista.push_back(tmp);
			}
		}
	
		
		licznik++;
		if(licznik>n-index) break;

	}
	time_po = clock();	            // pomiar czasu po sortowaniu  
    time_roznica = difft(time_po, time_przed);

	// przepisuje z listy do tablicy
	licznik = 0;
	for(list<Zadanie>::iterator iter=lista.begin(); iter != lista.end(); ++iter){
		zad[index + licznik] = *iter;
		licznik++;
	}
	lista.clear();
}





         
void obsluga_zad1(int i=0){

	clock_t time_przed;                  // pomiar czasu prz sortowaniem
	clock_t time_po;                     // pomiar czasu po sortowaniu
	double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
	double time_suma_edd = 0.00;						// suma czasow dla instancji
	double time_suma_moo = 0.00;
	double time_suma_neh = 0.00;
	int pyt;

	if(i==0){
		cout  <<endl << "Uwaga: czas podany jest w milisekundach!" <<endl <<endl; 

		cout << "Chcesz mierzyc czas dla 500 zadan(0) \nczy testowac poprawnosc (1) \nczy mierzyc czas dla 50 instancji po 500 zadan (2) \nczy mierzyc czasy i zapisac do pliku(3)?" <<endl; 
		cin >> pyt;
	} else{
		pyt =4;
	}
    

	if(pyt==0){
		system("cls"); 
		cout << endl <<" wybrales mierzenie czasu " <<endl;
		cout  << endl << "Zadania przed szeregowaniem:" << endl;
		Problem problem(500);
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//------------------------------------------------------------------------------
		time_przed = clock();			// pomiar czasu przed sortowaniem 
		problem.f_edd();
		time_po = clock();				// pomiar czasu po sortowaniu  
		time_roznica = difft(time_po, time_przed);
		cout << endl << "Zadania po EDD - earliest due date:" << endl;
		cout << endl << "Czas wykonywania: " << time_roznica;
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------

		problem.f_moore();
		cout << endl << "Czas wykonywania: " << time_roznica;
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------

		time_przed = clock();			// pomiar czasu przed sortowaniem 
		problem.f_neh();
		time_po = clock();				// pomiar czasu po sortowaniu  
		time_roznica = difft(time_po, time_przed);
	    

		cout  << endl << "Zadania po NEH:" << endl;
		cout << endl << "Czas wykonywania: " << time_roznica;
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------
		cout << endl;
		system("Pause"); 
	} 


	if(pyt==1){

		system("cls"); 
		cout << endl <<" wybrales sprawdzanie poprawnosci" <<endl;

		cout  << endl << "Zadania przed szeregowaniem:" << endl;
		Problem problem(10);
		problem.wypisz();
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		
		//-------------------------------------------------------------------------------

		problem.f_edd();



		cout << endl << "Zadania po EDD - earliest due date:" << endl;
		problem.wypisz();

		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------

		
		problem.f_moore();

		problem.wypisz();
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------

		problem.f_neh();

	    

		cout  << endl << "Zadania po NEH:" << endl;
		problem.wypisz();
		cout << endl << "Ilosc zadan opoznionych: " << problem.obliczUj();
		//-------------------------------------------------------------------------------
		cout << endl;
		system("Pause"); 
	}

	if(pyt==2){
		system("cls"); 
		cout << endl <<" wybrales mierzenie czasu dla 50 instancji" <<endl;
		/*
		for(int j=7; j<=15;j=j++){
			time_suma_edd = 0; 
			time_suma_neh = 0; 
			time_suma_moo = 0;
			for(int i=0; i<50;i++){
			

				Problem problem(j);

				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_edd();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_edd+=time_roznica;

				//-------------------------------------------------------------------------------

				
				problem.f_moore();
				time_suma_moo+=time_roznica;

				//-------------------------------------------------------------------------------

				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_neh();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_neh+=time_roznica;		
			}
			cout << endl << "Ilosc zadan: " << j <<endl;
			cout << endl << "Czas wykonywania edd: " << time_suma_edd/50.0 <<endl;
			cout << endl << "Czas wykonywania moore: " << time_suma_moo/50.0 <<endl;	
			cout << endl << "Czas wykonywania neh: " << time_suma_neh/50.0 <<endl;

			
		}
		*/

		for(int j=50; j<=1500;j=j+50){
			time_suma_edd = 0; 
			time_suma_neh = 0; 
			time_suma_moo = 0;
			for(int i=0; i<50;i++){
			

				Problem problem(j);

				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_edd();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_edd+=time_roznica;

				//-------------------------------------------------------------------------------

				
				problem.f_moore();
				time_suma_moo+=time_roznica;

				//-------------------------------------------------------------------------------

				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_neh();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_neh+=time_roznica;		
			}
			cout << endl << "Ilosc zadan: " << j <<endl;
			cout << endl << "Czas wykonywania edd: " << time_suma_edd/50.0 <<endl;
			cout << endl << "Czas wykonywania moore: " << time_suma_moo/50.0 <<endl;	
			cout << endl << "Czas wykonywania neh: " << time_suma_neh/50.0 <<endl;

			
		}

		cout << endl;
		system("Pause"); 
	} 
	if(pyt==3){
		
		FILE *pomiary; 
		system("cls"); 
		cout << endl <<" wybrales pomiar czasu z zapisem do pliku" <<endl;
		int ilosc = 0;
		pomiary=fopen("C://pomiary.txt", "w");
		if(pomiary==NULL)
		{
			cout << "B³¹d otwarcia pliku ";
			system("Pause");
			
		}
		//fprintf(pomiary, "%s", imie);


		for(int j=0;j<10;j++){
			ilosc += 50;
			time_suma_edd = 0; 
			time_suma_neh = 0; 
			time_suma_moo = 0;
			for(int i=0; i<1;i++){

				Problem problem(ilosc);
				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_edd();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_edd+=time_roznica;
				//-------------------------------------------------------------------------------
				problem.f_moore();
				time_suma_moo+=time_roznica;
				//-------------------------------------------------------------------------------
				time_przed = clock();			// pomiar czasu przed sortowaniem 
				problem.f_neh();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_neh+=time_roznica;
			}

			cout << endl << " --------------------------------- " << endl;
			cout << endl << "50 instancji problemu po " << ilosc << " zadan " <<endl;
			cout << endl << "Czas podany w ms! " <<endl;

			cout << endl << "Czas wykonywania 50 instancji edd: " << time_suma_edd <<endl;
			cout << endl << "Czas wykonywania 50 instancji moore: " << time_suma_moo <<endl;	
			cout << endl << "Czas wykonywania 50 instancji neh: " << time_suma_neh <<endl;

			cout << endl << "Czas wykonywania edd: " << time_suma_edd <<endl;	
			cout << endl << "Czas wykonywania moore: " << time_suma_moo <<endl;	
			cout << endl << "Czas wykonywania neh: " << time_suma_neh <<endl;

			fprintf(pomiary, "\n --------------------------------- \n");
			fprintf(pomiary, "\n 50 instancji problemu po %d zadan \n", ilosc  ); 
			fprintf(pomiary, "\n Czas podany w ms! \n"); 

			fprintf(pomiary, "\n Czas wykonywania 50 instancji edd: %f \n", time_suma_edd);
			fprintf(pomiary, "\n Czas wykonywania 50 instancji moore: %f \n", time_suma_moo);
			fprintf(pomiary, "\n Czas wykonywania 50 instancji neh: %f \n", time_suma_neh);

			fprintf(pomiary, "\n Czas wykonywania edd: %f \n", time_suma_edd/50.00);
			fprintf(pomiary, "\n Czas wykonywania moore: %f \n", time_suma_moo/50.00);
			fprintf(pomiary, "\n Czas wykonywania neh: %f \n", time_suma_neh/50.00);
		}


		fclose(pomiary);
		cout << endl;
		system("Pause"); 
	} 
}


          
	
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------Zad 2 ------------------------------------------------------------
//------------------------------------------------------------------------------


class Permutacja{
	private:
		int n;
		bool end;

	public:
		int min_kryt;
		int poz_min_kryt;
		Problem * pr;
		int *tab;
		bool getEnd(){return end;};
		Permutacja(int ile);
		void show();
		void first();
		void swap(int a, int b);
		int Next();
		void Moore_();
		void BruteForce();
		void BB();
		int lowerBound(int index);
		void sort(int poziom);


};

Permutacja::Permutacja(int ile){
	min_kryt = 0x7fff;
	poz_min_kryt = 0;
	end = false;
	pr = new Problem(ile);
	n = ile;
	tab = new int[ile];
	for(int j=0; j<n;){
		tab[j] = j++;
	}
	
}

void Permutacja::first(){
	end = false;
	int dl = (int)floor((float)n/2.0);
	for (int i = 0; i<dl; i++){ 
		swap(i, n-1-i); 
	}

}


void Permutacja::show(){
	for (int i = 0; i<n; i++){
		cout<<tab[i]<<"\t";
	}
	cout<<endl<<endl;
}

void Permutacja::swap(int a, int b){
	int tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
	Zadanie swap_tmp = pr->zad[a];
	pr->zad[a] = pr->zad[b];
	pr->zad[b]= swap_tmp;
}


     


int Permutacja::Next()
{
	int k = -1; 
	int j;
	for (int i = n-1; i>-1; i--){
		if (tab[i-1]<tab[i]){
			k = i-1;
			break;
		}
	}
	if (k == -1){
		end = true;
		return -1;
	}
	int min = tab[k+1];
	j = k+1;
	for(int i = k+1; i<n; i++){
		if (min >tab[i] && tab[i]>tab[k]){
			j = i;
			min = tab[i];
		}
	}
	swap(k,j);
	int dl = (int)floor((float)(n-k)/2.0);
	for (int i = 0; i<dl; i++){ 
		swap(k+1+i, n-1-i); 
	}
	return k;
	
}
void Permutacja::sort(int poziom){

			int h;                         // h -odleg³oœæ
			int param = 3;
			int i=0;
			int licz=0;
			Zadanie zad_a;
			int perm_a;
			h = 1;                               //ustawianie parametru h 
			while( h < n){
				h=1 + param*h;
            }
			h = h/9;
			if(!h) h++;                           // istotne jedynie dla bardzo ma³ych tablic
			while( h){
				for( licz = n - 1 - h +poziom+1 ; !(licz < poziom+1); licz--){
					i = licz + h;
					zad_a = pr->zad[licz];
					perm_a = tab[licz];



					for( ;(n > i) && (tab[i] > perm_a);){     //sortowanie przez wstawianie
						pr->zad[i - h] = pr->zad[i];
						tab[i - h] = tab[i];
						i += h;
						}
                        
					pr->zad[i - h] = zad_a;
					tab[i - h] = perm_a;

					}
					h = h/3;
            }
}



void Permutacja::BB(){
	Zadanie *najlepsze  = new Zadanie[n];
	bool odc = false;
	int poziom = 0;
	int nr_perm = 0;
    int lowerBoundValue = 0;
	int upperBoundValue = 0;
	Zadanie *tmpZ = new Zadanie[n];
	for(int i=0; i<n; i++){
		tmpZ[i] = pr->zad[i];
	}
	pr->f_edd();
	pr->f_moore();
	pr->f_neh();
    upperBoundValue = pr->obliczUj();
	for(int i=0; i<n; i++){
		najlepsze[i] = pr->zad[i];
	}
	for(int i=0; i<n; i++){
		pr->zad[i] = tmpZ[i];
	}
	delete tmpZ;
	int licznik = 0; 
	while(!getEnd()){
		//cout << "poziom: " << poziom << " UB: " << upperBoundValue << " LB: " << lowerBoundValue << endl;
		lowerBoundValue = lowerBound(poziom);
        if (lowerBoundValue < upperBoundValue){ 
			odc = false;
        } else {
            odc = true;	//odcinam
		}
		//cout << "poziom: " << poziom << " UB: " << upperBoundValue << " LB: " << lowerBoundValue << endl;
		//show();
		//system("Pause");


		if(odc==false && poziom <n){
			//cout << "nie odc"<<endl;
			if(poziom==n-2){
				lowerBoundValue = pr->obliczUj();
				if( lowerBoundValue < upperBoundValue){   
                    upperBoundValue = lowerBoundValue;
				//	cout << "best "<< endl;
					for (int i = 0; i < n; i++){
						najlepsze[i] = pr->zad[i];
					}
                }
				
				wezlyBB++;
				poziom = Next();
			} else {
				poziom++;
			}
		} else {
			//cout << "odc"<<endl;
			sort(poziom+1);
			poziom = Next();
			wezlyBB++;
		}
	}
	for (int i = 0; i < n; i++){
		pr->zad[i] = najlepsze[i];
	}
	
}

int Permutacja::lowerBound(int index){
	double cj = 0;
	int lowerBoundValue = 0;
	Zadanie *tmpZ = new Zadanie[n];
	for(int i=0; i<n; i++){
		tmpZ[i] = pr->zad[i];
	}
	//lowerBoundValue += pr->obliczUj(index);
	//cout << " LB do:" << lowerBoundValue << " ";
	for(int i=0; i<=index; i++){
		cj += pr->pj(i);
		if(pr->zad[i].dj < cj) lowerBoundValue++;
	}
	pr->f_moore(0,index+1);
	for(int i=index+1; i<n-1; ++i){
		cj += pr->zad[i].dj;
		if(pr->zad[i].dj < cj) lowerBoundValue++;
	}
	
	for(int i=0; i<n; i++){
		pr->zad[i] = tmpZ[i];
	}
	//cout << " LB po:" << lowerBoundValue << " ";
	//cout << " LB rl:" << pr->obliczUj() << " "<<endl;
    return lowerBoundValue;
}





// ------------------------------------------------------------------------------------
// ---------------------- OBS£UGA PROGRAMU---------------------------------------------
// ------------------------------------------------------------------------------------



void obsluga_zad2_BB(){
	int n = 10;
	Permutacja perm(n);
	perm.pr->wypisz();
	
	wezly=0;
	perm.BruteForce();
	cout << "odwiedzone wezly" << wezly <<endl;
	perm.pr->wypisz();
	perm.show();
	cout << "Brute Force Kryt: " << perm.min_kryt  << endl;
	
	system("Pause");
	perm.first();
	
	cout << "uszeregowane ";
	perm.show();
	wezlyBB=0;
	perm.BB();
	cout << "odwiedzone wezly" << wezlyBB <<endl;
	perm.min_kryt  = perm.pr->obliczUj();
	perm.show();
	perm.pr->wypisz();
	cout << " BB: " << perm.min_kryt  << endl;
	system("Pause");
	perm.show();
	perm.pr->f_moore();
	perm.min_kryt  = perm.pr->obliczUj();
	perm.show();
	perm.pr->wypisz();
	cout << " Moore Kryt: " << perm.min_kryt << endl;
	system("Pause");
	perm.pr->f_neh();
	perm.min_kryt  = perm.pr->obliczUj();
	perm.show();
	perm.pr->wypisz();
	cout << " Neh Kryt: " << perm.min_kryt  << endl;
	system("Pause");

}

void pomiary_zad2_BB(){
		clock_t time_przed;                  // pomiar czasu prz sortowaniem
		clock_t time_po;                     // pomiar czasu po sortowaniu
		double time_roznica;                 // ró¿nica czasu przed i po sortowaniu zwracana przez funkcjê difftime
		double time_suma_edd = 0.00;						// suma czasow dla instancji
		double time_suma_neh = 0.00;
		system("cls"); 
		cout << endl <<" wybrales pomiar czasu" <<endl;
		int ilosc = 0;

		for(int j=6;j<9;j++){
			time_suma_edd = 0.0; 
			time_suma_neh = 0.0; 
			wezly=0;
			wezlyBB=0;
			for(int i=0; i<50;i++){
				Permutacja perm(j);
				
				if(j<9){
					time_przed = clock();			// pomiar czasu przed sortowaniem 
					perm.BruteForce();
					time_po = clock();				// pomiar czasu po sortowaniu  
					time_roznica = difft(time_po, time_przed);
					time_suma_edd+=time_roznica;
					perm.first();
				}
				time_przed = clock();			// pomiar czasu przed sortowaniem 
				perm.BB();
				time_po = clock();				// pomiar czasu po sortowaniu  
				time_roznica = difft(time_po, time_przed);
				time_suma_neh+=time_roznica;
			}
			
			cout << endl << " --------------------------------- " << endl;
			cout << endl << "50 instancji problemu po " << j << " zadan " <<endl;
			cout << endl << "Czas podany w ms! " <<endl;
			cout << endl << "Czas wykonywania BF: " << time_suma_edd/50.0 <<endl;	
			cout << "odwiedzone wezly BF: " << wezly/50 <<endl <<endl;
			cout << endl << "Czas wykonywania BB: " << time_suma_neh/50.0 <<endl;
			//cout << "odwiedzone wezly BB: " << wezlyBB/50 <<endl <<endl;
			system("Pause");
		}
}


void obsluga_zad2_moore_bez(){
	Permutacja perm(10);
	perm.pr->wypisz();
	perm.show();
	system("Pause");
	perm.BruteForce();
	perm.show();
	perm.pr->wypisz();
	cout << "Brute Force Kryt: " << perm.min_kryt << endl << "Poz: " << perm.poz_min_kryt << endl;
	system("Pause");
	perm.pr->f_moore(1);
	perm.min_kryt  = perm.pr->obliczUj();
	perm.show();
	perm.pr->wypisz();
	cout << " Moore Kryt: " << perm.min_kryt << endl << "Poz: " << perm.poz_min_kryt << endl;
	system("Pause");
	perm.pr->f_neh();
	perm.min_kryt  = perm.pr->obliczUj();
	perm.show();
	perm.pr->wypisz();
	cout << " Neh Kryt: " << perm.min_kryt << endl << "Poz: " << perm.poz_min_kryt << endl;
	system("Pause");
}


void obsluga_zad2_bruteforce(){
	Permutacja perm(10);
	perm.pr->wypisz();
	perm.show();
	system("Pause");
	perm.BruteForce();
	perm.show();
	perm.pr->wypisz();
	cout << "Brute Force Kryt: " << perm.min_kryt << endl << "Poz: " << perm.poz_min_kryt << endl;
}

void obsluga_zad2_leksykograf(){
	int i = 4;
	cout<<"Proba dla "<<i<<" zadan"<<endl;
	Permutacja perm(i);
	perm.show();
	system("Pause");
	while(!perm.getEnd())
	{
		perm.Next();
		perm.show();
		//system("Pause");
	}
	perm.show();
	system("Pause");
}








int main(){
	srand(time(NULL));
	//obsluga_zad1();
	system("cls"); 
	//pomiary_zad2_BB();
	system("Pause");
	obsluga_zad2_BB();
	system("Pause");
	//pomiary_zad2_BB();
}