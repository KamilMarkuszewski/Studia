#pragma once

#include "Proces.h"
#include <vector>
using namespace std;

class T_Problem{
	/* zmienne */
	int N;
	T_Proces* T_Procesy;
	int* act_perm;
	int** listaTabu;
	int changed_a;
	int changed_b;

	/* metody */
public:
	T_Problem(int N);

	void ustawDane(vector<int> pj, vector<int> wj, vector<int> dj);
	~T_Problem(void);
	int* best_perm;

	void SW(int Temp, double alpha, int epoka, int warunek); 
	void Tabu(int warunek, int L, int dl_listy); 

	void generuj();
	int opoznione(int * perm);
	float kryterium(int * perm);

private:
	
	float max(float a, float b); 

	void losujSasiedniaPerm(int* next, int *act);
	void zapiszPerm(int* into, int * from);
	float losuj(float a, float b);
	float longTask(int par,int * perm);
	void losujPerm(int* perm);
	float P();
	int TabuLosujSasiedniaPerm(int* next, int *act);
};
