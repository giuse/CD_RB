
#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <fstream>

#include "allocUtils.hpp" // init*Vec, alloc*Vec, allocMat, copyMat

void centroidDec( double **X, int n, int m, int truncated,
                  const char* matrixR, const char* matrixL);
double** load_matrix(const char *fname, int n, int m);
void write_matrix(const char *fname, double** matrix, int nrows, int ncols);

#endif /* centroidDecomp_hpp */


