#include "stdafx.h"
#include "Problem.h"

#include <math.h>
#include <iostream>
using namespace std;

Problem::Problem(int x)
{
	N=x;
	procesy = new Proces[N];
	best_perm= new int[N];
	act_perm= new int[N];
	

}

Problem::~Problem(void)
{
	delete []procesy;
	delete []best_perm;
	delete [] act_perm;
}

void Problem::generuj()
{

	for (int i = 0; i<N; i++)
	{
		procesy[i].p = rand()%100+1;
		procesy[i].w = rand()%10+1;
		procesy[i].index = i;        
		best_perm[i] = -1;
		act_perm[i] = -1;
	}
	for (int i = 0; i<N; i++)
	{
		procesy[i].d=losuj(P()*(1-0.2*(rand()%5+1)-0.2/2*(rand()%5+1)),P()*(1-0.2*(rand()%5+1)+0.2/2*(rand()%5+1)));//tak o! 
		//procesy[i].d = rand()%100+1000;
		cout<<procesy[i].d<<" ";
	}
	cout<<" ";
}

void Problem::ustawDane(vector<int> pj, vector<int> wj, vector<int> dj)
{
	for (int i = 0; i<N; i++)
	{
		procesy[i].p = pj.at(i);
		procesy[i].w = wj.at(i);
		procesy[i].d = dj.at(i);
		procesy[i].index = i;        
		best_perm[i] = -1;
		act_perm[i] = -1;
	}
}

void Problem::SW(int Temp, double alpha, int epoka, int warunek) //Temp = temperatura
{

	losujPerm(best_perm);
	zapiszPerm(act_perm,best_perm);
	float next_kryt = 0;
	float delta;
	float x;
	int L = epoka; //d³ugoœæ epoki
	int * next_perm = new int[N];
	zapiszPerm(next_perm,best_perm);
	
	int iter=0;//warunek zatrzymania!
	do
	{
		for (int k = 0; k<L; k++)
		{
			losujSasiedniaPerm(next_perm,act_perm);
			next_kryt = kryterium(next_perm);
			
			if (next_kryt < kryterium(best_perm))
			{
				zapiszPerm(best_perm,next_perm); //CZY TO NAPEWNO TAK?
				iter=0;
				//moze cos jeszcze tu wbije
			
			}
			else iter++;	

			delta = next_kryt - kryterium(act_perm);
			
			if (delta<0)
			{
				zapiszPerm(act_perm,next_perm);
			}
			else
			{
				x = losuj(0,1);
				if (x < exp((-1*delta)/Temp))
				{
					zapiszPerm(act_perm,next_perm);	
				}
			}
		}

		Temp = alpha*Temp;
	}
	while (iter<warunek);//TODO WARUNEK ZATRZYMANIA
}

float Problem::losuj(float a, float b) 
{ 
    
/* 

RDD (RDD=0.2, 0.4, 0.6,0.8,1.0) and
a given average tardiness factor} TF
(TF=0.2, 0.4, 0.6,0.8,1.0), an integer due date d(j) for each job j
was randomly generated from the uniform distribution
[P(1-TF-RDD/2), P(1-TF+RDD/2)], where P = SUM{j=1,...,n}p(j).

*/	
	
	return  ( rand()/(float)RAND_MAX ) * (b - a) + a; 
      //jakubówka 
}

float Problem::max(float a, float b) 
{ 
    if(a-b>0)return a-b; 
    else return 0; 

}

float Problem::longTask(int par, int * perm) 
{     
	float T,opoz=0; 
    for (int i=0;i<=par;i++) 
    { 
        opoz+=procesy[perm[i]].p; 
    } 
	
    T=max(opoz,procesy[perm[par]].d); 
    return T; 
}

float Problem::kryterium(int * perm) 
{ 
    float wyn=0; 
        for (int i=0;i<N;i++) 
            wyn+=procesy[i].w*longTask(i, perm); 
    return wyn; 

}


void Problem::losujSasiedniaPerm(int* next, int *act)
{
	zapiszPerm(next,act);
	int p1 = rand()%N;
	int p2 = rand()%N;
	int help = next[p1];
	next[p1] = next[p2];
	next[p2] = help;
}


void Problem::losujPerm(int* perm)
{
	int random;
	for (int i =0; i<N; i++)
	{
		bool good;
		do
		{
			good = true;
			random = rand()%N;
			for (int j = 0; j<N; j++)
			{
				if (random == perm[i])
				{
					good = false;
					break;
				}
			}
		}
		while (!good);
		perm[i] = random;
	}
}

void Problem::zapiszPerm(int* into, int * from)
{
	for (int i = 0; i<N; i++)
	{
		into[i] = from[i];
	}
}

float Problem::P()
{
	int lT=0;
	for(int i =0; i < N; i++) lT += procesy[i].p;

	return lT;
}


int Problem::opoznione(int * perm) 
{ 
    float wyn=0; 
	float opoz = 0;
        for (int i=0;i<N;i++) 
		{
			opoz += procesy[perm[i]].p;
            if( opoz > procesy[perm[i]].d )
				wyn++; 
		}
    return wyn; 
}