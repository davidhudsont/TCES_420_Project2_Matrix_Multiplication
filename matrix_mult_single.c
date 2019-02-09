#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 2000

#if SIZE <= 4
	#define PRINT 1
#else
	#define PRINT 0
#endif

void printMatrix(int* A, int size) {
	for (int rows=0; rows<size; rows++) {
		printf("| ");
			for (int columns=0; columns<size; columns++) {
				printf("%d ",  A[size*rows+columns]);
			}
		printf(" |\n");
	}
	printf("\n");
}

int main() {

int main() {
	clock_t t;

	srand(time(NULL));
	// Allocate Memory for Large Matrices
	int *A = malloc(SIZE*SIZE * sizeof(int));
	int *B = malloc(SIZE*SIZE * sizeof(int));
	int *C = malloc(SIZE*SIZE * sizeof(int));

	for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			A[SIZE*rows+columns] = rand()%10;
			B[SIZE*rows+columns] = rand()%10;
		}
	}
	// Setup for timing the computation
	struct timespec begin, end;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	printf("Start\n"); // Start of Calculation
	for (int rows=0; rows<SIZE; rows++) {
		for (int colb=0; colb<SIZE; colb++) {
			int entry = 0;
			for (int columns=0; columns<SIZE; columns++) {
				entry += A[SIZE*rows+columns]*B[SIZE*columns+colb]; 
			}
			C[SIZE*rows+colb] = entry;
		}
	}
	
	#if PRINT == 1
		printMatrix(A,SIZE);
		printMatrix(B,SIZE);
		printMatrix(C,SIZE);
	#endif
	
	clock_gettime(CLOCK_MONOTONIC,&end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec)/1000000000.0;
	printf("Operation took: %f\n\n", elapsed);
	// printMatrix(C,SIZE);
	free(A);
	free(B);
	free(C);
	return 0;
	
}
