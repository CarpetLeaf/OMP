#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000

void arrInit();

int i, j, k;
double arr1[N][N], arr2[N][N], res[N][N];
double start, finish;

int main(int argc, char* argv[])
{
	arrInit();
	for (int t = 1; t < omp_get_num_procs() + 1; t++)
	{
		omp_set_num_threads(t);
		{
			start = omp_get_wtime();
			#pragma omp parallel for shared(arr1, arr2, res) private(i, j, k)
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					res[i][j] = 0;
					for (k = 0; k < N; k++) {
						res[i][j] += (arr1[i][k] * arr2[k][j]);
					}
				}
			}
			finish = omp_get_wtime();
			printf("\nTime for %d threads: %f\n", t, finish - start);
		}
	}
	return 0;
}

void arrInit()
{
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			arr1[i][j] = rand() / 10.0;
			arr2[i][j] = rand() / 10.0;
		}
	}
}
