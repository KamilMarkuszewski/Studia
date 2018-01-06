#include "StdAfx.h"
#include "Problem.h"

#include <iostream>
using namespace std;

#include <stdlib.h>
#include <ctime>
#include <limits.h>

Problem::Problem(int N, float alpha, float beta, int pjMax):N(N),pjMax(pjMax)
{
	tasks = new Task[N];
	generateRandomValues();
	int pj_sum = pjSum();
	t = beta*pj_sum;
	T = alpha*pj_sum;
}

Problem::~Problem(void)
{
	delete []tasks;
}

Result Problem::getResult()
{
	Result res;
	res.benchmark = INT_MAX;
	int pj_sum = pjSum();
	res.perm = new int[N];
	for (int i = 0; i<N; i++)
		res.perm[i] = i;//tworzenie pierwszej permutacji

	double aTime = clock();

	SWPT(res);

	//nasza pêtla g³ówna
	for (int s = 0; s<T-t+1; s++)
	{
		//-----ALOKACJA FS  <- mo¿na by to kiedyœ do funkcji wrzuciæ
		float ***fs;
		fs = new float**[N+1];
		for (int i = 0; i<N+1; i++)
		{
			fs[i] = new float*[s+1];
			for (int j = 0; j<s+1; j++)
			{
				fs[i][j] = new float[T+pj_sum];
			}
		}
		//-----ALOKACJA FS ---END---

		//-----ZEROWANIE OSTATNIEJ PERM	
		for (int i=0; i<=s; i++)
		{
			for (int j = 0; j<pj_sum + T; j++)
			{
				fs[N][i][j] = 0;
			}
		}
		//-----ZEROWANIE OSTATNIEJ PERM	----END----

		//-----PÊTELKI I WZORKI
		for (int k = N-1; k>=0; k--)
		{
			for (int i = 0; i<s+1; i++)
			{
				for (int j = 0; j<pj_sum + T; j++) //0=> s+t <przyœpieszenie>
				{
					if (j+tasks[res.perm[k]].p < pj_sum + T)
					{
						if (i+tasks[res.perm[k]].p<=s)
						{
							fs[k][i][j] = min	(
													(i+tasks[res.perm[k]].p)*tasks[res.perm[k]].w + fs[ k+1][i+tasks[res.perm[k]].p][j]
												,
													(j+tasks[res.perm[k]].p)*tasks[res.perm[k]].w + fs[ k+1][i][j+tasks[res.perm[k]].p]
												);//skomplikowany wzór - jest w artykule
						}
						else
						{
							fs[k][i][j] = (j+tasks[res.perm[k]].p)*tasks[res.perm[k]].w + fs[ k+1][i][j+tasks[res.perm[k]].p];//wzór w pliku z artyku³em
						}
					}
					else
					{
						fs[k][i][j] = (j+tasks[res.perm[k]].p)*tasks[res.perm[k]].w;
					}
				}
			}
		}
		//-----PÊTELKI I WZORKI ----END----


		//TUTAJ POWINIENEM ZAPAMIÊTAC WYNIKI OBLICZEN!!!!!!!!!!
		//WYNIKI
		float bench = fs[1][0][s+t];
		if (bench<res.benchmark)
		{
			res.benchmark = bench;
			res.s = s;
		}
		//WYNIKI ----END----
		
		//-----DEALOKACJA FS  <- mo¿na by to kiedyœ do funkcji wrzuciæ
		for (int i = 0; i<N+1; i++)
		{
			for (int j = 0; j<s+1; j++)
			{
				delete []fs[i][j];
			}
			delete []fs[i];
		}
		delete []fs;
		//-----DEALOKACJA FS ---END---

	}

	double bTime = clock();
	res.time = (bTime-aTime)/CLOCKS_PER_SEC; 	

	return res;
}

void Problem::SWPT(Result res)
{	
	quickSort(0,N-1,res.perm);
}

void Problem::generateRandomValues()
{
	for (int i = 0; i<N; i++)
	{
		tasks[i].p = rand()%pjMax+1;
		tasks[i].w = randomFloat(1,10);
		tasks[i].p_div_w = (float)tasks[i].p/tasks[i].w;
	}
}

//quick sort
void Problem::quickSort(int left,int right, int *perm) //sortujemy perm[] wg. tasks[perm[]].d
{
	int center,l;
	int piwot;
    
	center=(left+right)/2; //wyliczam srodek   
    piwot=perm[center];     //piwot = srodkowy
    perm[center]=perm[right]; //srodkowy <-prawy
    
    for (int k=l=left;k<right;k++)
    {
        if (tasks[perm[k]].p_div_w<tasks[piwot].p_div_w) 
        {
		   //swap k,l
		   int help = perm[k];
		   perm[k] = perm[l];
		   perm[l] = help;
           l++;
        }        
    }
    
    perm[right]=perm[l];
    
    perm[l]=piwot; 
    
    if(left<l) 
        quickSort(left,l-1,perm);
    
    if(l+1<right)
        quickSort(l+1,right,perm);

}

int Problem::pjSum()
{
	int sum = 0;
	for (int i = 0; i<N; i++)
	{
		sum+= tasks[i].p;
	}
	return sum;
}

float Problem::min(float p1, float p2)
{
	if (p1<p2)
		return p1;
	return p2;
}

float Problem::randomFloat(float low, float high)
{
	return ( rand()/(float)RAND_MAX ) * (high - low) + low;
	//to dzia³a... naprawdê ;p
}