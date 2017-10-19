#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
int *j;


void *myThread(void *arg){
	
}	

int main(int argc) {
	int core = argc;
	
	clock_t t;
	
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
	printf("Start\n");
	t = clock();
	for (int rows=0; rows<SIZE; rows++) {
		for (int colb=0; colb<SIZE; colb++) {
			int entry = 0;
			for (int columns=0; columns<SIZE; columns++) {
				entry = A[rows][columns]*B[columns][colb]+entry; 
			}
			C[rows][colb] = entry;
		}
	}
	t = clock() - t;
	printf("Operation took: %f\n", ((float)t)/(CLOCKS_PER_SEC));
	
	return 0;
	
}
