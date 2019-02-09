#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>


#define SIZE 4 // SIZE of the rows and columns of a matrix

#if SIZE <= 4
	#define PRINT 1
#else
	#define PRINT 0
#endif

// Matrices
int *A;
int *B;
int *C; 

int range = 2000;
int threads = 1;
// Print a Matrix 
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


// Thread for Matrix Multiplication
void* matrix_mult(void *p_index) {
	long beg = range*(long)p_index; // Cast to int pointer and de-reference
	long end = (range*((long)p_index+1));
	printf("Beg: %d, End: %d\n",beg,end-1);

#define SIZE 2 // SIZE of the rows and columns of a matrix
int *A;
int *B;
int *C;

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
				entry += A[SIZE*rows+columns]*B[SIZE*columns+colb]; 
			}
			C[SIZE*rows+colb] = entry;
		}
	}
	//printf("beginning : %d, end : %d\n",beg,end);
	pthread_exit(0);
}


/*
	Main Program
*/
int main(int argc, char *argv[]) {
	
	// Read the number of threads from user
	threads = atoi(argv[1]);
	// Compute how much each thread with traverse
	range = (SIZE/threads);
	assert(threads <= SIZE);
	// Print # of threads, their range and the size of the Matrix
	printf("threads : %d, range: %d, SIZE: %d\n",threads,range,SIZE);
	// Get random seed based on time
	srand(time(NULL));
	

	printf("beginning : %d, end : %d\n",beg,end);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	int threads = atoi(argv[1]);
	range = (SIZE/threads);
	printf("threads : %d, range: %d\n",threads,range);
	srand(time(NULL));
	start = malloc(threads*sizeof(int));
	int count = 0;
	// Create the range each thread calculates
	for (int i=0; i<threads; i++) {
		start[i] = count;
		count += range; 
	}

	// Allocate memory for each matrix
	A = malloc(SIZE*SIZE*sizeof(int));
	B = malloc(SIZE*SIZE*sizeof(int));
	C = malloc(SIZE*SIZE*sizeof(int));

	
	// Create two matrices A and B and fill them with random numbers

	// Create two random matrices A and B

	for (int rows=0; rows<SIZE; rows++) {
		for(int columns=0; columns<SIZE; columns++) {
			A [SIZE*rows+columns] = abs(rand()%10);
			B [SIZE*rows+columns] = abs(rand()%10);
		}
	}

	// Create pthreads
	pthread_t p[threads]; 
	// Setup for timing the computation
	struct timespec begin, end; 
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	printf("Start\n");
	
	// Create the threads for Matrix Calculation
	for (long id=0; id<threads; id++) {
		int rc = pthread_create(&p[id],NULL,matrix_mult, (void *)id);

	printf("\n");
	// Print the matrix A and B
	
	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
			for (int columns=0; columns<SIZE; columns++) {
				printf("%d ",  A [SIZE*rows+columns]);
			}
		printf(" |\n");
		}
	printf("\n");
	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
		for (int columns=0; columns<SIZE; columns++) {
		    printf("%d ",  B [SIZE*rows+columns]);
		}
		printf(" |\n");
	}
	
	pthread_t p[threads]; // create 16 thread variables
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

	printf("Operation took: %f\n\n", elapsed);

	#if PRINT == 1
		printMatrix(A,SIZE);
		printMatrix(B,SIZE);
		printMatrix(C,SIZE);
	#endif
	
	// Free Each Matrix
	free(A);
	free(B);
	free(C);
	return 0;
}

	printf("Operation took: %f\n", elapsed);
	
	for (int rows=0; rows<SIZE; rows++) {
		printf("| ");
			for (int columns=0; columns<SIZE; columns++) {
				printf("%d ",  C [SIZE*rows+columns]);
			}
		printf(" |\n");
	}
	
	
	free(A);
	free(B);
	free(C);
	free(start);
	return 0;
}

