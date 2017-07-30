
#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <stdlib.h> // atoi, free

#include "allocUtils.hpp" // init*Vec, alloc*Vec, allocMat, copyMat

void centroidDec( double **X, int n, int m, int truncated);
double** load_matrix(const char *fname, int n, int m);
void write_matrix(const char *fname, double** matrix, int nrows, int ncols);

#endif /* centroidDecomp_hpp */


