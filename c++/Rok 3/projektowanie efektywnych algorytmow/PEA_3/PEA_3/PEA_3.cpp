// PEA_3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <climits>
using namespace std;


struct Zadanie{
	int p;		// czas wykonywania
	int c;		
	float w;	// waga
	float p_w;
};


struct Wyniki{
	double czas;
	int *permutacja;
	float pomiar;
	int s;
};


float randF(float min, float max){
	return ( rand()/(float)RAND_MAX ) * (max - min) + min;
}



class Problem{
public:
	Zadanie *Zadania;
	int T;		// krytyczny moment zakoñczenia wyonywania czynnoœci regeneracyjnej (maintenance deadline) 
	int t;		// czas trwania czynnoœci regeneracyjnej 
	int n;		// iloœæ zadañ
	int pj_max;

	Problem(int n, int pj_max, float alpha, float beta);
	~Problem();
	Wyniki getWyniki();
	void quickSort(int left,int right, int *permutacja);
	int sumapj();
};



Problem::Problem(int t_n, int t_pj_max, float alpha, float beta){
	n = t_n;
	pj_max = t_pj_max;
	Zadania = new Zadanie[n];
	for (int i = 0; i < n; i++){
		Zadania[i].w = randF(1,10);
		Zadania[i].p = rand() % (pj_max + 1);
		Zadania[i].p_w = (float)Zadania[i].p/Zadania[i].w;
	}

	int suma = sumapj();
	t = (int)(suma * beta);
	T = (int)(suma * alpha);
}

Problem::~Problem(){
	delete []Zadania;
}

int Problem::sumapj(){
	int suma = 0;
	for (int i = 0; i < n; i++){
		suma = suma + Zadania[i].p;
	}
	return suma;
}

void Problem::quickSort(int lewy, int prawy, int *permutacja){
	int sr,a;
	int piwot;
	sr = ( prawy + lewy ) / 2; 
    piwot = permutacja[sr];     
    permutacja[sr] = permutacja[prawy]; 
	a = lewy;
    for (int i=lewy; i < prawy; i++){
		a = lewy;
        if (Zadania[piwot].p_w > Zadania[permutacja[i]].p_w ){
		   int tmp = permutacja[i];
		   permutacja[i] = permutacja[a];
		   permutacja[a] = tmp;
           a++;
        }        
    }
    permutacja[prawy] = permutacja[a];
    permutacja[a] = piwot; 
	if(a > lewy ){
		quickSort(lewy, a-1, permutacja);
	} 
	if(a+1 < prawy){
		quickSort(a+1, prawy, permutacja);
	}
}


Wyniki Problem::getWyniki(){
	Wyniki w;
	int pj_suma = sumapj();
	w.permutacja = new int[n];
	for( int i = 0; i < n; i++){
		w.permutacja[i] = i;
	}
	w.pomiar = (float)INT_MAX;
	double Tprzed = clock();
	// sortowanie wg pj/wj niemalejaco
	quickSort(0,n-1,w.permutacja);



	for (int s = 0; s < T-t+1; s++){
		// alokowanie tablicy 3d
		float ***fs;
		fs = new float**[n+1];
		for (int i = 0; i < n+1; i++){
			fs[i] = new float*[s+1];
			for (int j = 0; j < s+1; j++){
				fs[i][j] = new float[T+pj_suma];
			}
		}
		
		for (int i=0; i <= s; i++){
			for (int j = 0; j < pj_suma + T; j++){
				fs[n][i][j] = 0;
			}
		}

		for (int k = n-1; k >= 0; k--){
			for (int i = 0; i < s+1; i++){
				for (int j = 0; j < pj_suma + T; j++){
					if (j+Zadania[w.permutacja[k]].p < pj_suma + T){
						if (i+Zadania[w.permutacja[k]].p <= s){

							float zm1 = (i+Zadania[w.permutacja[k]].p)*Zadania[w.permutacja[k]].w + fs[ k+1][i+Zadania[w.permutacja[k]].p][j];
							float zm2 = (j+Zadania[w.permutacja[k]].p)*Zadania[w.permutacja[k]].w + fs[ k+1][i][j+Zadania[w.permutacja[k]].p];
							float mniejsza = zm2;
							if( zm1 < zm2){
								mniejsza = zm1;
							}
							fs[k][i][j] = mniejsza;
						}
						else{
							fs[k][i][j] = (j+Zadania[w.permutacja[k]].p)*Zadania[w.permutacja[k]].w + fs[ k+1][i][j+Zadania[w.permutacja[k]].p];
						}
					}
					else{
						fs[k][i][j] = (j+Zadania[w.permutacja[k]].p)*Zadania[w.permutacja[k]].w;
					}
				}
			}
		}
		

		float znaleziona_optymalna = fs[1][0][s+t];
		if (znaleziona_optymalna < w.pomiar)	{
			w.pomiar = znaleziona_optymalna;
			w.s = s;
		}
		for (int i = 0; i<n+1; i++){
			for (int j = 0; j<s+1; j++)	{
				delete [] fs[i][j];
			}
			delete [] fs[i];
		}
		delete [] fs;

	}

	double Tpo = clock();
	w.czas = (Tpo-Tprzed)/CLOCKS_PER_SEC; 	

	return w;
}

void pomiary(){
	ofstream plik;
	plik.open("wyniki.txt");

	plik<<"ilosc \t alpha \t beta \t pj_max \t inst \t time \t wynik \t regeneracja"<<endl;

	int ilosc_dl	= 4;
	int alpha_dl	= 3;
	int beta_dl		= 3;
	int pj_max_dl	= 3;

	int * ilosc = new int[ilosc_dl];
	ilosc[0]= 10;
	ilosc[1]= 20;
	ilosc[2]= 25;
	ilosc[3]= 30;

	double * alpha = new double[alpha_dl];
	alpha[0]= 0.2;
	alpha[1]= 0.5;
	alpha[2]= 0.8;

	double * beta = new double[beta_dl];
	beta[0]= 0.02;
	beta[1]= 0.05;
	beta[2]= 0.1;

	int * pj_max = new int[pj_max_dl];
	pj_max[0]= 10;
	pj_max[1]= 20;
	pj_max[2]= 30;
	int ile_instancji = 50;
	for (int in = 0; in<ilosc_dl; in++){
		for (int ialpha = 0; ialpha<alpha_dl; ialpha++){
			for (int ibeta = 0; ibeta<beta_dl; ibeta++){
				for (int ipj = 0; ipj<pj_max_dl; ipj++){
					double sr_czas = 0.0;
					int sr_pomiar = 0;
					int sr_s = 0;
					cout <<"\t ilosc = "<< ilosc[in] <<"\t alpha = "<< alpha[ialpha] <<"\t beta = "<< beta[ibeta] <<"\t max_pj = "<< pj_max[ipj] << endl;	
					for (int iinst= 0; iinst<ile_instancji; iinst++){

						Problem problem1( ilosc[in], pj_max[ipj] , (float)alpha[ialpha] , (float)beta[ibeta] );
						Wyniki wynik = problem1.getWyniki();

						cout <<" nr "<< iinst << endl;						
						plik <<" "<< ilosc[in] <<" \t "<< alpha[ialpha] <<" \t "<< beta[ibeta] <<" \t "<< pj_max[ipj] <<" \t \t "<< iinst ;
						plik <<"\t"<< wynik.czas <<"\t"<< wynik.pomiar <<"\t"<< wynik.s <<""<< endl;
						sr_czas += wynik.czas;
						sr_pomiar += wynik.pomiar;
						sr_s += wynik.s;

					}

					sr_czas = sr_czas/ile_instancji;
					sr_pomiar = sr_pomiar/ile_instancji;
					sr_s = sr_s/ile_instancji;
					plik << "wart srednie: " << sr_czas << "\t" << sr_pomiar << "\t" << sr_s << "\t" << endl;
					cout << endl <<"-----------------------"<< endl;
					plik << endl <<"-----------------------"<< endl;
				}
			cout << endl <<"-----------------------"<< endl;
			plik << endl <<"-----------------------"<< endl;
			}
		cout << endl <<"-----------------------"<< endl;
		plik << endl <<"-----------------------"<< endl;
		}
	cout << endl <<"-----------------------"<< endl;
	plik << endl <<"-----------------------"<< endl;
	}

	plik.close();

}









//---------------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[]){
	
	pomiary();
	system("Pause");
	return 0;
}

