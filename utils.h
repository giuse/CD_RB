
#ifndef utils_h
#define utils_h

#include <stdlib.h> // malloc
#include <stdio.h>  // printf

// debug utils
void printMat(double *matrix, int nrows, int ncols);

// alloc utilities :( OMG I definitely did not miss C...
void initDoubleVec(double *vec, int size, double defval);
void initIntVec(int *vec, int size, int defval);
int* allocIntVec(int size, int defval);
double* allocDoubleVec(int size, double defval);
double* copyVec(double *orig, int size);

#endif
