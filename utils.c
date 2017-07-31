
#include "utils.h"

// debug utilities :( better tell this 2017 language how to print an array...

void printMat(double *matrix, int nrows, int ncols) {
  printf("[");
  for (int r=0; r<nrows; r++) {
  printf(" [");
    for (int c=0; c<ncols; c++)
      printf("%f ", matrix[r*ncols+c]);
    printf("]\n");
  }
  printf("]\n");
}

// alloc utilities :( OMG I definitely did not miss C...

void initDoubleVec(double *vec, int size, double defval) {
  for (int i=0; i<size; i++) vec[i] = defval;
}

void initIntVec(int *vec, int size, int defval) {
  for (int i=0; i<size; i++) vec[i] = defval;
}

int* allocIntVec(int size, int defval) {
  int *ret = (int*)malloc(size * sizeof(int));
  initIntVec(ret, size, defval);
  return ret;
}

double* allocDoubleVec(int size, double defval) {
  double *ret = (double*)malloc(size * sizeof(double));
  initDoubleVec(ret, size, defval);
  return ret;
}

double* copyVec(double *orig, int size) {
  double *ret = allocDoubleVec(size, 0);
  for (int i=0; i<size; i++)
    ret[i] = orig[i];
  return ret;
}
