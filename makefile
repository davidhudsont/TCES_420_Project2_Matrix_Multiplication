
main: threaded single

threaded: matrix_mult_threaded.o
	gcc -o threaded matrix_mult_threaded.o

single: matrix_mult_single.o
	gcc -o single matrix_mult_single.o

matrix_mult_threaded.o : matrix_mult_threaded.c
	gcc -c matrix_mult_threaded.c -lpthread
	
matrix_mult_single.o : matrix_mult_single.c
	gcc -c matrix_mult_single.c
	
clean :
	rm single matrix_mult_single.o threaded matrix_mult_threaded.o