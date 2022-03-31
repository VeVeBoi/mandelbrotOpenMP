# mandelbrotOpenMP
The Mandelbrot set is the set of complex numbers c for which the function {\displaystyle f_{c}=z^{2}+c} does not diverge to infinity when iterated from z=0, i.e., for which the sequence {\displaystyle f_{c}}, {\displaystyle f_{c}}, etc., remains bounded in absolute value.

## Task
Implement a parallel version of the Mandelbroth problem using OpenMP. Compare different scheduling options; Both for the Parallel for and tasks. Hint: Consider grain-sizes.

## local machine result 
![LocalMachine](https://user-images.githubusercontent.com/68075605/161066046-04d528ce-6fef-4417-acb7-180f51eb50d4.png)


### Running
To run this program you can call the make file "make" and then you'll get an runnable program, to select what type of methid you want to use you can use the flags  
- -serial
- -omp
- -task

#### Example
```
$ make all

$ ./mandel -omp
```
This will result in you running the mandelbrot in omp or the for loop, not the scheduling "task"
