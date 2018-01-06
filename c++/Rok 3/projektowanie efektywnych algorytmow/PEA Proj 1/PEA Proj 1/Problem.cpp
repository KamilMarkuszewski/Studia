#include "stdafx.h"
#include <iostream>
#include "Problem.h"
#include <math.h>

using namespace std;
void T_Problem::Tabu(int warunek, int L, int dl_listy){

	
	listaTabu= new int*[dl_listy];
	for(int i=0; i<dl_listy; i++){
		listaTabu[i] = new int[2];
		listaTabu[i][0] = 0;
		listaTabu[i][1] = 0;
	}


	losujPerm(best_perm);
	zapiszPerm(act_perm,best_perm);

	float next_kryt = 0;
	float delta;
	float x;
	
	int * next_perm = new int[N];
	zapiszPerm(next_perm,best_perm);
	
	int iter=0;//warunek zatrzymania!
	do{
		for (int k = 0; k<L; k++){
			TabuLosujSasiedniaPerm(next_perm,best_perm);
			next_kryt = kryterium(next_perm);
			
			if (next_kryt < kryterium(best_perm)){
				zapiszPerm(act_perm,next_perm); 
				iter=0;
				listaTabu[0][0] = 0;
				listaTabu[0][1] = 0;
			
			}
			else{
				iter++;
				listaTabu[0][0] = changed_a;
				listaTabu[0][1] = changed_b;
			
			} 	

			/*
			delta = next_kryt - kryterium(act_perm);
			
			if (delta<0){
				zapiszPerm(act_perm,next_perm);
			}
			
			else{
				x = losuj(0,1);
				if (x < exp((-1*delta)/Temp)){
					zapiszPerm(act_perm,next_perm);	
				}
			}
			*/
		}
		zapiszPerm(best_perm,act_perm); 
		
	}
	while (iter<warunek);
}




int T_Problem::TabuLosujSasiedniaPerm(int* next, int *act){
	bool ok = 1;
	cout << "do" << endl;
	zapiszPerm(next,act_perm);
	do{
		
		int p1 = rand()%N;
		int p2 = rand()%N;
		while(p1==p2){
			p2 = rand()%N;
		}
		
		
		int help = next[p1];
		next[p1] = next[p2];
		next[p2] = help;
		if(p1<p2){
			changed_a = next[p1];
			changed_b = next[p2];
		} else {
			changed_a = next[p2];
			changed_b = next[p1];
		}
		cout << p1 << " " << changed_a << " "<< p2 << " "  << changed_b << endl;
		ok = 1;
		for(int i=0; i<N;i++){
			if(listaTabu[0][0] == next[i] && next[i] != 0){
				cout << listaTabu[0][0] << " " << next[i];
				ok = 0;
				p1 = i;
				cout << "nie ok"<<endl;
				//break;
			}
			if(listaTabu[0][1] == next[i] && next[i] != 0){
				p2 = i;
				//break;
			}

		}
		help = next[p1];
		next[p1] = next[p2];
		next[p2] = help;
		
	
	}while(ok != 1);  //ok != 1


	return 0;
}
T_Problem::~T_Problem(void){
	delete []T_Procesy;
	delete []best_perm;
	delete [] act_perm;
}


T_Problem::T_Problem(int x){
	N=x;
	T_Procesy = new T_Proces[N];
	best_perm= new int[N];
	act_perm= new int[N];
}


float T_Problem::P(){
	int lT=0;
	for(int i =0; i < N; i++) lT += T_Procesy[i].p;

	return lT;
}


void T_Problem::ustawDane(vector<int> pj, vector<int> wj, vector<int> dj){
	for (int i = 0; i<N; i++){
		T_Procesy[i].p = pj.at(i);
		T_Procesy[i].w = wj.at(i);
		T_Procesy[i].d = dj.at(i);
		T_Procesy[i].index = i;        
		best_perm[i] = -1;
		act_perm[i] = -1;
	}
}

float T_Problem::losuj(float a, float b){ 
	return  ( rand()/(float)RAND_MAX ) * (b - a) + a; 
}

void T_Problem::SW(int Temp, double alpha, int epoka, int warunek){

	losujPerm(best_perm);
	zapiszPerm(act_perm,best_perm);
	float next_kryt = 0;
	float delta;
	float x;
	int L = epoka; //d³ugoœæ epoki
	int * next_perm = new int[N];
	zapiszPerm(next_perm,best_perm);
	
	int iter=0;//warunek zatrzymania!
	do{
		for (int k = 0; k<L; k++){
			losujSasiedniaPerm(next_perm,act_perm);
			next_kryt = kryterium(next_perm);
			
			if (next_kryt < kryterium(best_perm)){
				zapiszPerm(best_perm,next_perm); 
				iter=0;
			
			}
			else iter++;	

			delta = next_kryt - kryterium(act_perm);
			
			if (delta<0){
				zapiszPerm(act_perm,next_perm);
			}
			else{
				x = losuj(0,1);
				if (x < exp((-1*delta)/Temp)){
					zapiszPerm(act_perm,next_perm);	
				}
			}
		}

		Temp = alpha*Temp;
	}
	while (iter<warunek);
}

float T_Problem::longTask(int par, int * perm){     
	float T,opoz=0; 
    for (int i=0;i<=par;i++){ 
        opoz+=T_Procesy[perm[i]].p; 
    } 
	
    T=max(opoz,T_Procesy[perm[par]].d); 
    return T; 
}

float T_Problem::max(float a, float b){ 
    if(a-b>0)return a-b; 
    else return 0; 

}

void T_Problem::generuj(){

	for (int i = 0; i<N; i++){
		T_Procesy[i].p = rand()%100+1;
		T_Procesy[i].w = rand()%10+1;
		T_Procesy[i].index = i;        
		best_perm[i] = -1;
		act_perm[i] = -1;
	}
	for (int i = 0; i<N; i++){
		T_Procesy[i].d=losuj(P()*(1-0.2*(rand()%5+1)-0.2/2*(rand()%5+1)),P()*(1-0.2*(rand()%5+1)+0.2/2*(rand()%5+1)));//tak o! 
		cout<<T_Procesy[i].d<<" ";
	}
	cout<<" ";
}

float T_Problem::kryterium(int * perm){ 
    float wyn=0; 
	for (int i=0;i<N;i++){
		wyn+=T_Procesy[i].w*longTask(i, perm); 
	}   
    return wyn; 

}


void T_Problem::losujSasiedniaPerm(int* next, int *act){
	zapiszPerm(next,act);
	int p1 = rand()%N;
	int p2 = rand()%N;
	int help = next[p1];
	next[p1] = next[p2];
	next[p2] = help;
}


void T_Problem::losujPerm(int* perm){
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
int T_Problem::opoznione(int * perm){ 
    float wyn=0; 
	float opoz = 0;
        for (int i=0;i<N;i++) 
		{
			opoz += T_Procesy[perm[i]].p;
            if( opoz > T_Procesy[perm[i]].d )
				wyn++; 
		}
    return wyn; 
}
void T_Problem::zapiszPerm(int* into, int * from){
	for (int i = 0; i<N; i++)
	{
		into[i] = from[i];
	}
}


