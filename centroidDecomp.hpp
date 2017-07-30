
#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <fstream>

#include "allocUtils.hpp" // init*Vec, alloc*Vec, allocMat, copyMat

void centroidDec( double **X, int n, int m, int truncated,
                  const char* matrixR, const char* matrixL,
                  std::ofstream &rmseFile);
double** load_matrix(std::istream* is, int n, int m,
                     const std::string& delim = ",");
void write_matrix(std::ofstream* is, double** matrix, int nrows, int ncols);

#endif /* centroidDecomp_hpp */


