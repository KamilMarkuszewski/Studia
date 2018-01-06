#pragma once

#include "Proces.h"
#include <vector>
using namespace std;

class Problem
{
	Proces* procesy;
	int* act_perm;
	int N;

public:
	Problem(int N);
	~Problem(void);
	
	int* best_perm;

	void SW(int Temp, double alpha, int epoka, int warunek); //Temp = temperatura

	void generuj();
	void ustawDane(vector<int> pj, vector<int> wj, vector<int> dj);
	float kryterium(int * perm);
	int opoznione(int * perm);
private:
	
	float max(float a, float b); 
	float longTask(int par,int * perm);

	float losuj(float a, float b);
	void losujPerm(int* perm);
	void losujSasiedniaPerm(int* next, int *act);
	void zapiszPerm(int* into, int * from);

	float P();
};
