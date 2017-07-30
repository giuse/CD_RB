// alloc utilities :( OMG I definitely did not miss C...

#ifndef alloc_utils_hpp
#define alloc_utils_hpp

#include <stdlib.h> // malloc

void initDoubleVec(double *vec, int size, double defval);
void initIntVec(int *vec, int size, int defval);
int* allocIntVec(int size, int defval);
double* allocDoubleVec(int size, double defval);
double** allocMat(int nrows, int ncols, double defval);
double** copyMat(double **orig, int nrows, int ncols);

#endif
