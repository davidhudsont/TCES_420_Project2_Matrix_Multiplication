matrix: matrix_mult_single.c matrix_mult_threaded.c
	gcc -o single matrix_mult_single.c -lpthread
	gcc -o threaded matrix_mult_threaded.c -lpthread
