#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "mythreads.h"

#define SIZE 500
int range= 499;
int* start;
void* mythread(void *arg) {
	int*  index = (int*)arg;
	int beg = start[(int)index];
	int end = beg+range;
	//printf("Index %d\n", index);
	//printf("start[1]: %d\n",start[(int)index]);
	printf("beginning : %d, end : %d\n",beg,end);
	return NULL;
}


int main(int argc, char *argv[]) {
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
pthread_t p[16];
for (int i=0; i<threads; i++) {
	int index = i;	
	Pthread_create(&p[i],NULL,mythread,(void*)index);
}
for (int i=0; i<threads; i++) { 
        Pthread_join(p[i],NULL);
}
//pthread_t p1, p2, p3,p4;
//int index=1;
//Pthread_create(&p1, NULL,mythread,(void*)index);
//Pthread_create(&p2, NULL,mythread,"222");
//Pthread_create(&p3, NULL,mythread,"250");
//Pthread_create(&p4, NULL,mythread,"375");

//Pthread_join(p1,NULL);
//Pthread_join(p2,NULL);
//Pthread_join(p3,NULL);
//Pthread_join(p4,NULL);

	

return 0;
}
