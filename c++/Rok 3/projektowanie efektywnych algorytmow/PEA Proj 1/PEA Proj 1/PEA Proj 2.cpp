// SW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Problem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;
int zad1(){

	double alpha = 0.99;

	int warunek = 400;
	int N[] = {40,50,100};
	int Temp = 400;
	int t = Temp;
	int epoka = 100;
	do{
		t = alpha*t;
	//	warunek ++;
	} while (t > 0);


	ofstream file;
	ifstream dataFile;
	file.open("wyniki.txt");
	if (!file){
		cout<<"Nie ma pliku wynikow"<<endl;
		return 0;
	}

	for (int i = 0; i<3; i++){

		cout <<endl<<endl<<endl;
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<"N =  "<<N[i]<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"N =  "<<N[i]<<endl;
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;

		
		std::string name = "";
		switch (N[i]){
			case 40: name = "wt40.txt"; break;
			case 50: name = "wt50.txt"; break;
			case 100: name = "wt100.txt"; break;
		}
		dataFile.open(name.c_str());
		if (!dataFile){
			cout<<"Nie ma pliku danych: "<<name<<endl;
			system("Pause");
			return 0;
		}

		vector<int> wj[125];
		vector<int> dj[125];
		vector<int> pj[125];

		int helper;
		for (int j = 0; j<125; j++){
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				pj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				wj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				dj[j].push_back(helper);
			}
		}
		dataFile.close();


		double opoznienie[125];
		double times[125];
		double wyniki_kryt[125];

		for (int j = 0; j<125; j++){
			cout<<"Powtorzenie "<<j<<endl;
			T_Problem T_Problem(N[i]);
			T_Problem.ustawDane(pj[j],wj[j],dj[j]);
		
			double aTime = clock();
			T_Problem.SW(Temp,alpha,epoka,warunek);
			double bTime = clock();
			times[j] = bTime-aTime;
			wyniki_kryt[j] = T_Problem.kryterium(T_Problem.best_perm);
			opoznienie[j] = T_Problem.opoznione(T_Problem.best_perm);
			
		}

		double opoz_sr = 0;
		double kryt_sr = 0;
		double czas_sr = 0;
		//file<<"czas: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<times[j]<<endl;
			czas_sr += times[j];
			opoz_sr +=opoznienie[j];
			kryt_sr += wyniki_kryt[j];

		}
		//file<<"krytryterium: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<wyniki_kryt[j]<<endl;
		}
		//file<<"opoznienie: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<opoznienie[j]<<endl;
		}
		czas_sr = czas_sr / 125;
		opoz_sr = opoz_sr / 125;
		kryt_sr = kryt_sr / 125;
		file<< "alpha (wzrost temperatury): "<< alpha<<endl;
		file<<"________________________________________________________________"<<endl;
		file<<"Kryterium sredne: "<<kryt_sr<<endl;
		file<<"Czas sredni: "<<czas_sr<<endl;
		file<<"Opoznione sredne: "<<opoz_sr<<endl;
	}

	file.close();
	return 0;
}

int zad2(){

	int N[] = {40,50,100};
	ofstream file;
	ifstream dataFile;
	file.open("wyniki.txt");
	if (!file){
		cout<<"Nie ma pliku wynikow"<<endl;
		return 0;
	}


	for (int i = 0; i<3; i++){

		cout <<endl<<endl<<endl;
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<"N =  "<<N[i]<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"N =  "<<N[i]<<endl;
		cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;

		
		std::string name = "";
		switch (N[i]){
			case 40: name = "wt40.txt"; break;
			case 50: name = "wt50.txt"; break;
			case 100: name = "wt100.txt"; break;
		}
		dataFile.open(name.c_str());
		if (!dataFile){
			cout<<"Nie ma pliku danych: "<<name<<endl;
			system("Pause");
			return 0;
		}

		vector<int> wj[125];
		vector<int> dj[125];
		vector<int> pj[125];

		int helper;
		for (int j = 0; j<125; j++){
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				pj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				wj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++){
				dataFile>>helper;
				dj[j].push_back(helper);
			}
		}
		dataFile.close();


		double opoznienie[125];
		double times[125];
		double wyniki_kryt[125];

		for (int j = 0; j<125; j++){
			cout<<"Powtorzenie "<<j<<endl;
			T_Problem T_Problem(N[i]);
			T_Problem.ustawDane(pj[j],wj[j],dj[j]);
		
			double aTime = clock();

			//TU funkcja TABU SEARCH
			T_Problem.Tabu(400, 100, 4);
			//T_Problem.SW(Temp,alpha,epoka,warunek);


			double bTime = clock();
			times[j] = bTime-aTime;
			wyniki_kryt[j] = T_Problem.kryterium(T_Problem.best_perm);
			opoznienie[j] = T_Problem.opoznione(T_Problem.best_perm);
			
		}

		double opoz_sr = 0;
		double kryt_sr = 0;
		double czas_sr = 0;
		//file<<"czas: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<times[j]<<endl;
			czas_sr += times[j];
			opoz_sr +=opoznienie[j];
			kryt_sr += wyniki_kryt[j];

		}
		//file<<"krytryterium: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<wyniki_kryt[j]<<endl;
		}
		//file<<"opoznienie: "<<endl;
		for (int j = 0; j< 125; j++){
			//file<<opoznienie[j]<<endl;
		}
		czas_sr = czas_sr / 125;
		opoz_sr = opoz_sr / 125;
		kryt_sr = kryt_sr / 125;
		
		file<<"________________________________________________________________"<<endl;
		file<<"Kryterium sredne: "<<kryt_sr<<endl;
		file<<"Czas sredni: "<<czas_sr<<endl;
		file<<"Opoznione sredne: "<<opoz_sr<<endl;
	}

	file.close();



	return 0;
}


int _tmain(int argc, _TCHAR* argv[]){

	srand(time(NULL));
	zad2();
	system("Pause");
	return 0;
}

