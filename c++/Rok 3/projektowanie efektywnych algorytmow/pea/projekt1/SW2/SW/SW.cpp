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

int _tmain(int argc, _TCHAR* argv[])
{
	int N[] = {40,50,100};
	int Temp = 400;
	double alpha = 0.89;
	int epoka = 100;
	int warunek = 400;
	int t = Temp;
	do
	{
		t = alpha*t;
	//	warunek ++;
	}while (t > 0);


	ofstream file;
	ifstream dataFile;
	file.open("wyniki.txt");
	if (!file) 
	{
		cout<<"Nie ma pliku wynikow"<<endl;
		return 0;
	}

	for (int i = 0; i<3; i++)
	{
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<"N =  "<<N[i]<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"N =  "<<N[i]<<endl;
		file<<"--------------------------------------------------------------------------"<<endl;

		//WCZYTYWANIE DANYCH Z PLIKU
		std::string name = "";
		switch (N[i])
		{
			case 40: name = "wt40.txt"; break;
			case 50: name = "wt50.txt"; break;
			case 100: name = "wt100.txt"; break;
		}
		dataFile.open(name.c_str());
		if (!dataFile) 
		{
			cout<<"Nie ma pliku danych: "<<name<<endl;
			system("Pause");
			return 0;
		}
		vector<int> pj[125];
		vector<int> wj[125];
		vector<int> dj[125];
		int helper;
		for (int j = 0; j<125; j++)
		{
			for (int k = 0; k<N[i]; k++)//pj
			{
				dataFile>>helper;
				pj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++)//wj
			{
				dataFile>>helper;
				wj[j].push_back(helper);
			}
			for (int k = 0; k<N[i]; k++)//dj
			{
				dataFile>>helper;
				dj[j].push_back(helper);
			}
		}
		dataFile.close();
		//KONIEC WCZYTYWANIA DANYCH Z PLIKU


		double times[125];
		double wyniki_kryt[125];
		double opoznienie[125];//opoznieneie?
		for (int j = 0; j<125; j++)
		{
			cout<<"Powtórzenie "<<j<<endl;
			Problem problem(N[i]);
			problem.ustawDane(pj[j],wj[j],dj[j]);
			//problem.generuj();
		
			double aTime = clock();
			problem.SW(Temp,alpha,epoka,warunek);
			double bTime = clock();
			times[j] = bTime-aTime;
			wyniki_kryt[j] = problem.kryterium(problem.best_perm);
			opoznienie[j] = problem.opoznione(problem.best_perm);
			
		}
		double kryt_sr = 0;
		double czas_sr = 0;
		double opoz_sr = 0;
		file<<"czas: "<<endl;
		for (int j = 0; j< 125; j++)
		{
			file<<j<<" "<<times[j]<<endl;
			kryt_sr += wyniki_kryt[j];
			czas_sr += times[j];
			opoz_sr +=opoznienie[j];
		}
		file<<"kryt: "<<endl;
		for (int j = 0; j< 125; j++)
			file<<j<<" "<<wyniki_kryt[j]<<endl;
		file<<"opoz: "<<endl;
		for (int j = 0; j< 125; j++)
			file<<j<<" "<<opoznienie[j]<<endl;
		kryt_sr = kryt_sr / 125;
		czas_sr = czas_sr / 125;
		opoz_sr = opoz_sr / 125;
		file<<"--------------------------------------------------------------------------"<<endl;
		file<<"Czas œredni: "<<czas_sr<<endl;
		file<<"Kryterium œredne: "<<kryt_sr<<endl;
		file<<"Opoznione œredne: "<<opoz_sr<<endl;
	}

	file.close();
	return 0;
}

