#include <math.h>   // fabs
#include <string.h> // strtok
#include <stdio.h>
#include <stdlib.h>

#include "centroidDecomp.h"

/* find the sign vector that maximizes the product X'Z according to the SSV algorithm*/
static int* findSignVector (double *X, int nrows, int ncols)
{
  int pos = -1, val = 0;
  int *Z = allocIntVec(nrows, 1);
  double *V = allocDoubleVec(nrows, 0);
  double *S = allocDoubleVec(ncols, 0);

  for (int r=0; r<nrows; r++)
    for (int c=0; c<ncols; c++)
      S[c] += X[r*ncols+c];

  for (int r=0; r<nrows; r++)
    for (int c=0; c<ncols;c++)
      V[r] += X[r*ncols+c] * (S[c] - X[r*ncols+c]);

  int iteration=0;
  do {
    for (int c=0; c<ncols; c++) S[c] = 0;
    if (pos != -1) {
      Z[pos] *= -1;
      for (int r=0; r<nrows;r++ )
        if (r != pos)
          for (int c=0; c<ncols;c++)
            V[r] -= 2 * X[r*ncols+c] * X[pos*ncols+c];
    }
    val = 0;
    pos = -1;
    for (int r=0; r<nrows; r++)
      if (Z[r] * V[r] < 0)
        if(fabs(V[r]) > val) {
          val = fabs(V[r]);
          pos = r;
        }

    iteration++;
  } while(pos != -1);

  free(V);
  free(S);
  return Z;
}

/* Calculate the norm 2 of an array */
static double norm2 (double *ary, int size) {
  double acc = 0;
  for (int i=0; i<size; i++) {
    acc += ary[i] * ary[i];
  }
  return sqrt(acc);
}

/* The centroid decomposition algorithm*/
void centroidDec(double *X,  int nrows, int ncols, int truncated)
{
  // results file paths (for testing)
  char const * matrixR="./Rtest.txt";
  char const * matrixL="./Ltest.txt";

  double *R = allocDoubleVec(ncols * ncols, 0);
  double *L = allocDoubleVec(nrows * ncols, 0);
  int *Z;

  double *X1 = copyVec(X, nrows * ncols);

  for (int t=0; t<truncated; t++)
  {
    //calculating the sign vector
    Z = findSignVector(X, nrows, ncols);

    double *C = allocDoubleVec(ncols, 0);

    for(int r=0;r<nrows;r++)
      for (int c=0;c<ncols;c++)
        C[c] += X[r*ncols+c] * Z[r];

    //calculating R
    for (int c=0; c<ncols; c++)
      R[c*ncols+t] = C[c] / norm2(C, ncols);

    //calculating L
    for (int r=0; r<nrows; r++) {
      L[r*ncols+t] = 0;
      for (int c=0; c<ncols; c++)
        L[r*ncols+t] += X[r*ncols+c] * R[c*ncols+t];
    }

    //Calculating the new X
    for (int r=0; r<nrows; r++)
      for(int c=0; c<ncols; c++)
        X[r*ncols+c] = X[r*ncols+c] - (L[r*ncols+t] * R[c*ncols+t]);
  }

  //write R and L
  write_matrix(matrixR, R, ncols, ncols);
  write_matrix(matrixL, L, nrows, ncols);

  //calculation the rmse with the Frobenius norm
  double check = 0;
  double sum;
  for (int r=0;r<nrows; r++) {
    for (int c=0; c<ncols; c++) {
      sum=0;
      for (int c2=0; c2<ncols; c2++)
        sum += L[r*ncols+c2] * R[c*ncols+c2];
      if (fabs(X1[r*ncols+c] - sum) > 1e-3)
        check += (X1[r*ncols+c] - sum) * (X1[r*ncols+c] - sum);
    }
  }
  check = sqrt(check); // rmse

  free(R);
  free(L);
}

void write_matrix(const char *fname, double* matrix, int nrows, int ncols)
{
  FILE *file = fopen(fname, "wb");
  for (int r=0; r<nrows; r++) {
    for (int c=0; c<ncols; c++)
      fprintf(file, "%g,", matrix[r*ncols+c]);
    fprintf(file, "\n");
  }
  fclose(file);
}

// load matrix from an ascii text file.
double* load_matrix(const char *fname, int nrows, int ncols)
{
  FILE* file = fopen(fname, "r");
  const char *delim = ",";
  char line[1024];        // buffer
  char *ptr;              // pointer on line
  double *matrix = allocDoubleVec(nrows * ncols, 0);
  int r = 0, c = 0;   // indices on matrix

  while (fgets(line, sizeof(line), file)) {
    c = 0;
    ptr = strtok(line, delim);      // split line by token
    while (ptr != NULL) {
        matrix[r*ncols+c++] = atof(ptr);
        ptr = strtok(NULL, delim); // scan to next token
    }
    r++;
  }
  // printMat(matrix, nrows, ncols);

  fclose(file);
  return matrix;
}


