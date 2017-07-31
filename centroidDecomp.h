
#ifndef centroidDecomp_h
#define centroidDecomp_h

#include <stdlib.h> // atoi, free
#include "utils.h"  // init*Vec, alloc*Vec, allocMat, copyMat, printMat


void centroidDec( double **X, int n, int m, int truncated);
double** load_matrix(const char *fname, int n, int m);
void write_matrix(const char *fname, double** matrix, int nrows, int ncols);

#endif /* centroidDecomp_hpp */


