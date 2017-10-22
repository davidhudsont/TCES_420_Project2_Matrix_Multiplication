#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "mythreads.h"
#include <time.h>
#define SIZE 2000
int **A;
int **B;
int **C;

int range= 499;
int* start;
void* mythread(void *arg) {
	int*  index = (int*)arg;
	int beg = start[(int)index];
	int end = beg+range;
	int count =0;
	for (int rows = beg; rows<end+1; rows++) {
		for (int colb=0; colb<SIZE; colb++) {
			int entry = 0;
			for (int columns=0; columns<SIZE; columns++) {
				entry = A[rows][columns]*B[columns][colb]+entry; 
			}
			C[rows][colb] = entry;
		}
	}
	printf("count: %d\n",count);
	//printf("Index %d\n", index);
	//printf("start[1]: %d\n",start[(int)index]);
	printf("beginning : %d, end : %d\n",beg,end);
	return NULL;
}
struct select{
	int *row;
	int *col;
};

int main(int argc, char *argv[]) {
time_t timer;
double t;
int threads = atoi(argv[1]);
range = (SIZE/threads)-1;
printf("threads : %d, range: %d\n",threads,range);

start = malloc(threads*sizeof(int));
int count = 0;
for (int i=0; i<threads; i++) {
	//start[i] =(int*)malloc(sizeof(int));
	start[i] = count;
	count += range+1;
	//printf("start[i]: %d\n",start[i]); 
}
A = malloc(SIZE*SIZE*sizeof(int*));
B = malloc(SIZE*SIZE*sizeof(int*));
C = malloc(SIZE*SIZE*sizeof(int*));
for (int i =0; i<SIZE*SIZE; i++) {
	A[i] = (int*)malloc(sizeof(int*));
	B[i] = (int*)malloc(sizeof(int*));
	C[i] = (int*)malloc(sizeof(int*));
}

for (int rows=0; rows<SIZE; rows++) {
	for(int columns=0; columns<SIZE; columns++) {
		A [rows][columns] = abs(rand()%10);
		B [rows][columns] = abs(rand()%10);
	}
}
printf("\n");
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
pthread_t p[16];
struct timespec begin, end;
double elapsed;
clock_gettime(CLOCK_MONOTONIC, &begin);
//t = time(&timer);
printf("Start\n");
for (int i=0; i<threads; i++) {
	int index = i;	
	Pthread_create(&p[i],NULL,mythread,(void*)index);
}
//t = clock() - t;
//printf("Operation took: %f\n", ((float)t)/(CLOCKS_PER_SEC));

for (int i=0; i<threads; i++) { 
        Pthread_join(p[i],NULL);
}
//t = time(&timer) - t;
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
	free((void*)B[i]);
	free((void*)C[i]);
}
free((void*)A);
free((void*)B);
free((void*)C);
*/
return 0;
}
