
#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <stdio.h>
#include "allocUtils.hpp" // init*Vec, alloc*Vec, allocMat, copyMat

void centroidDec( double **X, long n, long m, long truncated,
                  const char* matrixR, const char* matrixL,
                  std::ofstream &rmseFile);
double** load_matrix(std::istream* is, int n, int m,
                     const std::string& delim = ",");
void write_matrix(std::ofstream* is, double** matrix, int nrows, int ncols);

#endif /* centroidDecomp_hpp */


