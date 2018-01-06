#pragma once

#include "Task.h"
#include "Result.h"

class Problem
{

	Task *tasks;
	int T;
	int t;
	int N;
	int pjMax;
public:
	Problem(int N, float alpha, float beta, int pjMax);
	~Problem(void);
	Result getResult();

private:
	void SWPT(Result res);
	void generateRandomValues();
	void quickSort(int left,int right, int *perm);
	int pjSum();
	float min(float, float);
	float randomFloat(float low, float high);
};
