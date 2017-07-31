
#include "centroidDecomp.h"

int main(int argc, char *argv[])
{

  int nrows = atoi(argv[2]);
  int ncols = atoi(argv[3]);
  const char *matfile = argv[1];

  /* load the file into a matrix*/
  double *matrix = load_matrix(matfile, nrows, ncols);

  // number of truncated columns
  int ntrunc = atoi(argv[6]);
  int truncated = ncols - ntrunc;

  // return arguments
  double *L = allocDoubleVec(nrows * ncols, 0);
  double *R = allocDoubleVec(ncols * ncols, 0);

  // centroid decomposition
  centroidDec(matrix, nrows, ncols, truncated, L, R);

  printf("ntrunc: `%d`; truncated: `%d`\n", ntrunc, truncated);

  // closing up
  free(R);
  free(L);
  free(matrix);
  return 0;
}




