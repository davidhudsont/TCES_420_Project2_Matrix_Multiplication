#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int **A;
int **B;
int **C;
int SIZE;

void *myThread(void * temp);

struct index{
    int *row;
    int *col;
};
void *myThread(void * input){
    struct index *temp = (struct index*) input;
	C [*(temp->row)][*(temp->col)] = 0;
    for(int i=0; i <SIZE; i++){
        C[*(temp->row)][*(temp->col)] += A[*(temp->row)][i]* B[i][*(temp->col)];
//        printf("i= %d, %d %d, %d =%d * %d \n", i, *(temp->row),*(temp->col), C[*(temp->row)][*(temp->col)], A[*(temp->row)][i], B[i][*(temp->col)]);
    }
    free(input);
    pthread_exit(0);
}	
int main(int argc, char *argv[]) {
    int core;
    if (argv[1])
        core = atoi(argv[1]);
    pthread_t *pointer = malloc(sizeof(pthread_t)*core);
	clock_t t;
	
	srand(time(NULL));
    
    SIZE = 2000;
    
    int **first  = malloc(SIZE*SIZE*sizeof(int *));
    int **second = malloc(SIZE*SIZE*sizeof(int *));
    int **third  = malloc(SIZE*SIZE*sizeof(int *));
    for (int i=0; i<SIZE * SIZE; i++) {
		first[i]  = (int *)malloc(sizeof(int *));
		second[i] = (int *)malloc(sizeof(int *));
		third[i]  = (int *)malloc(sizeof(int *));
	}
    
    A = first;
    B = second;
    C = third;

    
	for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			A [rows][columns]=  abs(rand()%10);
			B [rows][columns]=  abs(rand()%10);
		}
	}
 /*  print out the first 2 array 
    for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			printf("%d ",  A [rows][columns]);
		}
        printf("\n");
	}
    
    for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
            printf("%d ",  B [rows][columns]);
		}
        printf("\n");
	}
 */   
    
	printf("Start\n");
    int counter = 0;
    int rc;
	t = clock();
    for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
            struct index *temp = malloc(sizeof (struct index));
            temp->row = malloc(sizeof(int));
            temp->col = malloc(sizeof(int));
            *(temp->row) = rows;
            *(temp->col) = columns;
            //printf("NUM = %d %d \n", *(temp->row), *(temp->col));
            rc = pthread_create(&pointer[counter],NULL, myThread,(void*)temp);
            pthread_join(pointer[counter], NULL);
            counter++;
            if(counter < core){
                counter = 0;
            }
 /*           if(rc != 0){
                printf("rc error %d\n", counter);
            }*/
        }
    }
	t = clock() - t;
	printf("Operation took: %f\n", ((float)t)/(CLOCKS_PER_SEC));
/* print out the output of the array after a delay
    sleep(5); // wait for all the data to come in since schedualer count in main 
    for (int rows=0; rows<SIZE; rows++) {
		for (int columns=0; columns<SIZE; columns++) {
			printf("%d ",  C [rows][columns]);
		}
        printf("\n");
	}
 */
	return 0;
}
