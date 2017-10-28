#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
	srand(time(NULL));
	int SIZE = 2000;
	
	int *A = malloc(SIZE*SIZE * sizeof(int));
	int *B = malloc(SIZE*SIZE * sizeof(int));
	int *C = malloc(SIZE*SIZE * sizeof(int));

	for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			A[SIZE*rows+columns] = rand()%10;
			B[SIZE*rows+columns] = rand()%10;
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
				entry += A[SIZE*rows+columns]*B[SIZE*columns+colb]; 
			}
			C[SIZE*rows+colb] = entry;
		}
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	elapsed = end.tv_sec - begin.tv_sec;
	elapsed += (end.tv_nsec - begin.tv_nsec)/1000000000.0;
	printf("Operation took: %f\n\n", elapsed);
	free(A);
	free(B);
	free(C);
	return 0;
	
}
