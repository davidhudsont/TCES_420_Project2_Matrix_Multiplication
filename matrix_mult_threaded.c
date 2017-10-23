#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>

#define SIZE 2000 // SIZE of the rows and columns of a matrix
int **A;
int **B;
int **C;

int range= 2000;
int* start; // used to set the start index of each thread

void* mythread(void *arg) {
	int*  index = (int*)arg;
	int beg = start[(int)index];
	int end = beg+range;
	int count =0;
	for (int rows = beg; rows<end; rows++) {
		for (int colb=0; colb<SIZE; colb++) {
			int entry = 0;
			for (int columns=0; columns<SIZE; columns++) {
				entry = A[rows][columns]*B[columns][colb]+entry; 
			}
			C[rows][colb] = entry;
		}
	}
	printf("beginning : %d, end : %d\n",beg,end);
	return NULL;
}

int main(int argc, char *argv[]) {

	int threads = atoi(argv[1]);
	range = (SIZE/threads);
	printf("threads : %d, range: %d\n",threads,range);

	start = malloc(threads*sizeof(int));
	int count = 0;
	// Create the range each thread calculates
	for (int i=0; i<threads; i++) {
		start[i] = count;
		count += range; 
	}
	// Allocate memory for each matrix
	A = malloc(SIZE*SIZE*sizeof(int*));
	B = malloc(SIZE*SIZE*sizeof(int*));
	C = malloc(SIZE*SIZE*sizeof(int*));
	for (int i =0; i<SIZE*SIZE; i++) {
		A[i] = (int*)malloc(sizeof(int*));
		B[i] = (int*)malloc(sizeof(int*));
		C[i] = (int*)malloc(sizeof(int*));
	}
	// Create two random matrices A and B
	for (int rows=0; rows<SIZE; rows++) {
		for(int columns=0; columns<SIZE; columns++) {
			A [rows][columns] = abs(rand()%10);
			B [rows][columns] = abs(rand()%10);
		}
	}
	printf("\n");
	// Print the matrix A and B
	/*
	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
			for (int columns=0; columns<SIZE; columns++) {
				printf("%d ",  A [rows][columns]);
			}
		printf(" |\n");
		}
	printf("\n");

	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
		for (int columns=0; columns<SIZE; columns++) {
		    printf("%d ",  B [rows][columns]);
		}
		printf(" |\n");
	}
	*/
	pthread_t p[16]; // create 16 thread variables
	struct timespec begin, end; // create timing 
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	printf("Start\n"); // Start of Calculation
	// Create the threads for Matrix Calculation
	for (int i=0; i<threads; i++) {
		int index = i;	
		int rc = pthread_create(&p[i],NULL,mythread,(void*)index);
		assert(rc == 0);
	}
	// Join the threads
	for (int i=0; i<threads; i++) { 
		int rc = pthread_join(p[i],NULL);
		assert(rc == 0);
	}
	// End of calculation
	clock_gettime(CLOCK_MONOTONIC,&end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec)/1000000000.0;
	printf("Operation took: %f\n", elapsed);
	/*
	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
			for (int columns=0; columns<SIZE; columns++) {
				printf("%d ",  C [rows][columns]);
			}
		printf(" |\n");
	}
	*/
	/*
	for (int i=0; i<SIZE; i++) {
		free((void*)A[i]);
	}
	for (int i=0; i<SIZE; i++) {
		free((void*)B[i]);
	}
	for (int i=0; i<SIZE; i++) {
		free((void*)C[i]);
	}
	free((void*)A);
	free((void*)B);
	free((void*)C);
	*/
	return 0;
}
