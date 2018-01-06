// Zad3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Problem.h"
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

void stop()
{
	char ch = _getch();
	if (ch == 0)
		_getch();
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N[] =		{10,20,25,30};		int nMAX		= 4;
	float alpha[] =	{0.2,0.5,0.8};		int alphaMAX	= 3;
	float beta[] =	{0.02,0.05,0.1};	int betaMAX		= 3;
	int pjMax[] =	{10,20,30};			int pjMaxMAX	= 3;
	int instanceNr = 50;
	
	

	ofstream file;
	file.open("wyniki.txt");

	file<<"[N]\t[alpha]\t[beta]\t[pjMax]\t[inst]\t[time]\t[bench]\t[regeneration]"<<endl;

	//obliczenia
	for (int i_N = 0; i_N<nMAX; i_N++)
	{
		for (int i_al = 0; i_al<alphaMAX; i_al++)
		{
			for (int i_be = 0; i_be<betaMAX; i_be++)
			{
				for (int i_pj = 0; i_pj<pjMaxMAX; i_pj++)
				{
					for (int i_inst= 0; i_inst<instanceNr; i_inst++)
					{
						Problem prb( N[i_N] , alpha[i_al] , beta[i_be] , pjMax[i_pj]);
						Result res = prb.getResult();
						cout<<"N = "<<N[i_N]<<" alpha = "<<alpha[i_al]<<" beta = "<<beta[i_be]<<" max_pj = "<<pjMax[i_pj]<<" próbka nr "<<i_inst<<endl;						
						file<<""<<N[i_N]<<"\t"<<alpha[i_al]<<"\t"<<beta[i_be]<<"\t"<<pjMax[i_pj]<<"\t"<<i_inst;
						file<<"\t"<<res.time<<"\t"<<res.benchmark<<"\t"<<res.s<<""<<endl;
					}
					file<<endl<<endl<<endl;
				}
			}
		}
	}
	//obliczenia ----END----
	file.close();
	stop();
	return 0;
}

