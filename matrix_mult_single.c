#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(NULL));
	int SIZE = 2000;
	
	int **A = (int **)malloc(SIZE * sizeof(int *));
	int **B = (int **)malloc(SIZE * sizeof(int *));
	int **C = (int **)malloc(SIZE * sizeof(int *));
	
	for (int i=0; i<SIZE; i++) {
		A[i] = (int *)malloc(SIZE * sizeof(int));
		B[i] = (int *)malloc(SIZE * sizeof(int));
		C[i] = (int *)malloc(SIZE * sizeof(int));
		
	}
	for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			A[rows][columns] = rand()%10;
			B[rows][columns] = rand()%10;
		}
	}
	struct timespec begin, end; // create timing 
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	printf("Start\n"); // Start of Calculation
	for (int rows=0; rows<SIZE; rows++) {
		for (int colb=0; colb<SIZE; colb++) {
			int entry = 0;
			for (int columns=0; columns<SIZE; columns++) {
				entry = A[rows][columns]*B[columns][colb]+entry; 
			}
			C[rows][colb] = entry;
		}
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec)/1000000000.0;
	printf("Operation took: %f\n\n", elapsed);
	return 0;
	
}
