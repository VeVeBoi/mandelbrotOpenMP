all:
	gcc-11 -g -Wall -fopenmp -o mandel mandel.c
clean:
	rm mandel