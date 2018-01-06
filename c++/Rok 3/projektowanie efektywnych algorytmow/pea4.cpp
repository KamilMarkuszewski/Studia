// pea4.cpp : Defines the entry point for the console application.
/**
/* Kamil Markuszewski 171016
*/

#include "stdafx.h"
#include <iostream>


#include <time.h>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <fstream>



using namespace std;



/*
Oblicza czas wykonywania sie algorytmu dla metody clock()
*/

double difft(time_t time_po, time_t time_przed){   
	return (difftime(time_po*1000, time_przed*1000) / CLOCKS_PER_SEC);
}

double floatRand()
{
	return (float)((float)rand()* (1.0/(RAND_MAX + 1.0)) * (1.0 - 0.0) + 0.0);
}

inline bool czy_wiekszy(int x, int y){
	return x > y;
}

// PROBLEM -------------------------------------------------------------------------------------------------------------

class T_Problem{
public:
	int n_zad;
	int* czas_zadania;
	int* nr_maszyny;
	int czas_maszyny_1;
	int czas_maszyny_2;
	double blad;
	int ptas_k;
	int fptas_k;

	T_Problem();
	T_Problem(int n, double e, int max_p);
	~T_Problem();
	void od_nowa();
	bool nastepna(int _do);
	double sumuj(int _do);
	int kryterium();
	void FPTAS();
	void backTr(int** tab, int x);
	void Dynamiczna();
	void PTAS();
	void BruteForce(int _do);
	void save(int* tab_wyn, int* tab_now, int _do);



};

// PROBLEM FUNKCJE -----------------------------------------------------------------------------------------------------



T_Problem::T_Problem(){
	n_zad = 0;
	czas_zadania = 0;
	czas_maszyny_1 = 0;
	czas_maszyny_2 = 0;
	nr_maszyny = 0;
	blad = 0.0;
}

T_Problem::T_Problem(int n, double _blad, int max_p){
	n_zad = n;
	blad = _blad;
	czas_maszyny_1 = 0;
	czas_maszyny_2 = 0;
	czas_zadania = new int[n_zad];
	nr_maszyny = new int[n_zad];
	for(int i = 0; i < n_zad; i++){
		czas_zadania[i] = 1 + rand()%max_p;
		nr_maszyny[i] = 0;
	}
	sumuj(n_zad);
}

T_Problem::~T_Problem(){
	delete [] czas_zadania;
	delete [] nr_maszyny;
	czas_zadania = NULL;
	nr_maszyny = NULL;
}

int T_Problem::kryterium(){
	if(czas_maszyny_1 > czas_maszyny_2){
		return czas_maszyny_1;
	} else {
		return czas_maszyny_2;
	}
}



void T_Problem::FPTAS(){
	int suma = 0;
	for(int i = 0; i < n_zad; i++){
		suma += czas_zadania[i];
	}
	int fptas_k = int( ( blad * suma ) / (2 * n_zad) );
	int k = fptas_k;
	if(k <= 0){
		k = 1;
	}
	if(k > n_zad){
		k = n_zad;
	}
	ptas_k = k;
	int* wyn = new int[n_zad];
	save(wyn, czas_zadania, n_zad);
	for(int i = 0; i < n_zad; i++){
		czas_zadania[i] /= k;
	}
	Dynamiczna();
	save(czas_zadania, wyn, n_zad);
	sumuj(n_zad);
	delete [] wyn;
	wyn = 0;
}

void T_Problem::backTr(int** tab, int x){
	od_nowa();
	while( x > 0){
		for( int i = 1; i < 1 + n_zad ; i++){
			if(tab[i][x] == 1){
				nr_maszyny[i - 1] = 1;
				x -= czas_zadania[i - 1];
				break;
			}
			if( i == n_zad){
				x--;
			}
		}
	}
}

void T_Problem::Dynamiczna(){
	int suma_2 = 0;
	for(int i = 0; i < n_zad; i++){
		suma_2 += czas_zadania[i];
	}
	suma_2 = suma_2 / 2;
	int** tab = new int*[1+n_zad];
	for(int i = 0; i < 1+n_zad; i++){
		tab[i] = new int[1+suma_2];
		for(int j = 0; j < 1+suma_2; j++){
			tab[i][j] = 0;
		}
	}
	for(int i = 0; i < 1+n_zad; i++){
		tab[i][0] = 1;
	}
	for(int i = 1; i < 1+n_zad; i++){
		for(int j = 0; j < 1+suma_2 - czas_zadania[i - 1]; j++){
			if(tab[i - 1][j] == 1){
				for(int k = i; k < 1+n_zad; k++)	{
					tab[k][j + czas_zadania[i - 1]] = 1;
				}
			}
		}
	}
	backTr(tab, suma_2);
	sumuj(n_zad);
	for(int i = 0; i < 1+n_zad; i++){
		delete [] tab[i];
		tab[i] = 0;
	}
	delete [] tab;
	tab = 0;
}

void T_Problem::PTAS(){
	
	sort(czas_zadania, czas_zadania + n_zad, czy_wiekszy);
	int k = int(1 / blad) - 2;
	ptas_k = k;
	if(k > n_zad){
		k = n_zad;
	}
	if(k < 0){
		k = 0;
	}
	ptas_k = k;
	BruteForce(k);
	for(int i = k; i < n_zad; i++){
		if(czas_maszyny_1 < czas_maszyny_2){
			nr_maszyny[i] = 0;
			czas_maszyny_1 += czas_zadania[i];
		}
		else{
			nr_maszyny[i] = 1;
			czas_maszyny_2 += czas_zadania[i];
		}
	}
}


void T_Problem::BruteForce(int _do){
	od_nowa();
	int* wyn = new int[_do];
	save(wyn, nr_maszyny, _do);
	double najlepsze = sumuj(_do);
	double zm_temp;
	while( nastepna(_do) != true ){
		zm_temp = sumuj(_do);
		if( najlepsze > zm_temp){
			save(wyn, nr_maszyny, _do);
			najlepsze = zm_temp;
		}
	}
	save(nr_maszyny, wyn, _do);
	sumuj(_do);
	delete [] wyn;
	wyn = 0;
}

void T_Problem::save(int* tab_wyn, int* tab_now, int _do){
	if(_do > n_zad){
		_do = n_zad;
	}
	for(int i = 0; i < _do; i++){
		tab_wyn[i] = tab_now[i];
	}
}

bool T_Problem::nastepna(int _do){
	if(_do > n_zad){
		_do = n_zad;
	}
	for(int i = 0; i < _do; i++){
		if(nr_maszyny[i] == 1){
			nr_maszyny[i] = 0;
			continue;
		}
		if(nr_maszyny[i] == 0){
			nr_maszyny[i] = 1;
			return false;
		}
	}
	return true;
}

double T_Problem::sumuj(int _do){
	czas_maszyny_1 = 0;
	czas_maszyny_2 = 0;
	if(n_zad < _do){
		_do = n_zad;
	}
	for(int i = 0; i < _do; i++){
		if(nr_maszyny[i] == 1){
			czas_maszyny_2 += czas_zadania[i];
		}
		if(nr_maszyny[i] == 0){
			czas_maszyny_1 += czas_zadania[i];
		}
	}
	if(czas_maszyny_2 > czas_maszyny_1){
		return czas_maszyny_2;
	} else{
		return czas_maszyny_1;
	}
}

void T_Problem::od_nowa(){
	for(int i = 0; i < n_zad; i++){
		nr_maszyny[i] = 0;
	}
	sumuj(n_zad);
}



// MAIN ----------------------------------------------------------------------------------------------------------------
int main()
{
	srand(time(NULL));

	int n_il = 6;
	int* n = new int[n_il];
	n[0] = 10;
	n[1] = 25;
	n[2] = 50;
	n[3] = 100;
	n[4] = 250;
	n[5] = 500;

	int e_il = 5;
	double* e = new double[e_il];
	e[0] = 0.1;
	e[1] = 0.25;
	e[2] = 0.5;
	e[3] = 0.75;
	e[4] = 0.9;

	int czas_zad_il = 3;
	int* czas_zad = new int[czas_zad_il];
	czas_zad[0] = 10;
	czas_zad[1] = 20;
	czas_zad[2] = 30;

	double powtorzen = 50;

	time_t time_przed, time_po;

	double czas_ptas, czas_fptas, czas_md;
	double blad_PTAS, blad_FPTAS;
	double bledy[6][5][3][2] = {0};
	double wsp[6][5][3][2] = {0};
	int ptas_kryt, fptas_kryt, md_kryt;
	int ptas_k, fptas_k;
	ofstream plik("pomiar.txt");
	for(int i = 0; i < n_il; i++){
		for(int j = 0; j < e_il; j++){
			for(int k = 0; k < czas_zad_il; k++){

				czas_ptas = 0;
				czas_fptas = 0;
				czas_md = 0;

				blad_PTAS = 0;
				blad_FPTAS = 0;
				ptas_k = 0;
				fptas_k = 0;
				for(int l = 0; l < powtorzen; l++){

					T_Problem problem_tmp(n[i], e[j], czas_zad[k]);

					time_przed = clock();
					problem_tmp.PTAS();
					time_po = clock();
					ptas_kryt = problem_tmp.kryterium();
					czas_ptas += difft(time_po, time_przed);

					time_przed = clock();
					problem_tmp.FPTAS();
					time_po = clock();
					fptas_kryt = problem_tmp.kryterium();
					czas_fptas += difft(time_po, time_przed);

					time_przed = clock();
					problem_tmp.Dynamiczna();
					time_po = clock();
					md_kryt = problem_tmp.kryterium();
					czas_md += difft(time_po, time_przed);

					blad_PTAS += ( double(ptas_kryt) - double(md_kryt) ) / double(md_kryt);
					blad_FPTAS += ( double(fptas_kryt) - double(md_kryt) ) / double(md_kryt);

					ptas_k += problem_tmp.ptas_k;
					fptas_k += problem_tmp.fptas_k;
				}
				cout << endl<< endl<< "---------------" << endl<< endl;
				cout << "n: " << n[i] << " \te: " << e[j] << " \t max czas zad: " << czas_zad[k] << endl;
				cout << "Czas ptas_kryt ms: " <<  (czas_ptas / powtorzen) <<endl;
				cout << "Czas fptas_kryt ms: " << (czas_fptas / powtorzen) <<endl;
				cout << "Czas md_kryt: " << czas_md / powtorzen <<endl;
				cout << "Blad PTAS: " <<  blad_PTAS * 100.00 / powtorzen <<endl;
				cout << "Blad FPTAS: " << 100.00  * blad_FPTAS / powtorzen <<endl;
				cout << "Wspl k PTAS: " << double(ptas_k / powtorzen) <<endl;
				cout << "Wspl k FPTAS: " << double(fptas_k / powtorzen) <<endl;
				cout << endl<< endl<< "---------------" << endl<< endl;


				plik << endl<< endl<< "---------------" << endl<< endl;
				plik << "n: " << n[i] << " \te: " << e[j] << " \t max czas zad: " << czas_zad[k] << endl;
				plik << "Czas ptas_kryt: " <<  czas_ptas / powtorzen <<endl;
				plik << "Czas fptas_kryt: " << czas_fptas / powtorzen <<endl;
				plik << "Czas md_kryt: " << czas_md / powtorzen <<endl;
				plik << "Blad PTAS: " <<  blad_PTAS * 100.00 / powtorzen <<endl;
				plik << "Blad FPTAS: " << 100.00  * blad_FPTAS / powtorzen <<endl;
				plik << "Wspl k PTAS: " << double(ptas_k / powtorzen) <<endl;
				plik << "Wspl k FPTAS: " << double(fptas_k / powtorzen) <<endl;
				plik << endl<< endl<< "---------------" << endl<< endl;
			}
		}
	}
	plik.close();
	system("PAUSE");
	return 0;
}