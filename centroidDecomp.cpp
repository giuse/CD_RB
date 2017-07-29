
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include "centroidDecomp.hpp"
using namespace std;


/* find the sign vector that maximizes the product X'Z according to the SSV algorithm*/
static int* findSignVector (double **X, long n, long m)
{
  int pos = -1, val = 0;
  int *Z = allocIntVec(n, 1);
  double *V = allocDoubleVec(n, 0);
  double *S = allocDoubleVec(m, 0);

  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      S[i] += X[j][i];

  for (int i=0; i<n; i++)
    for (int j=0; j<m;j++)
      V[i] += X[i][j] * (S[j] - X[i][j]);

  int iteration=0;
  do {
    for (int i=0; i<m; i++) S[i] = 0;
    if (pos != -1) {
      Z[pos] *= -1;
      for (int i=0; i<n;i++ )
        if (i != pos)
          for (int j=0; j<m;j++)
            V[i] -= 2 * X[i][j] * X[pos][j];
    }
    val = 0;
    pos = -1;
    for (int i=0; i<n; i++)
      if (Z[i] * V[i] < 0)
        if(abs(V[i]) > val) {
          val = abs(V[i]);
          pos = i;
        }

    iteration++;
  } while(pos != -1);

  return Z;
}

/* Calculate the norm 2 of an array */
static double norm2 (double *C, int size)
{
  double accum = 0.;
  for (int i=0; i<size; i++) {
    accum += C[i] * C[i];
  }
  return sqrt(accum);
}

/* The  centroid decomposition algorithm*/
void centroidDecomp::centroidDec(double **X,  long n, long m,
                                  long truncated, const char* matrixR, const char* matrixL, std::ofstream &runTimeFile, std::ofstream &rmseFile)
{
  double **R = allocMat(m, m, 0);
  double **L = allocMat(n, m, 0);
  int *Z;
  double **X1 = X;

  for (int k=0; k<truncated; k++)
  {
    //calculating the sign vector
    Z = findSignVector(X, n, m);

    double *C = allocDoubleVec(m, 0);

    for(int i=0;i<n;i++)
      for (int j=0;j<m;j++)
        C[j] += X[i][j] * Z[i];

    //calculating R
    for (int i=0; i<m; i++)
      R[i][k] = C[i] / norm2(C, m);

    //calculating L
    for (int i=0; i<n; i++) {
      L[i][k] = 0;
      for (int j=0; j<m; j++)
        L[i][k] += X[i][j] * R[j][k];
    }

    //Calculating the new X
    for (int i=0; i<n; i++)
      for(int j=0; j<m; j++)
        X[i][j] = X[i][j] - (L[i][k] * R[j][k]);
  }

  //write R
  ofstream myR;
  myR.open(matrixR,std::ofstream::out | std::ofstream::trunc);
  write_matrix(&myR,R,m,m);
  myR.close();

  //write L
  ofstream myL;
  myL.open(matrixL,std::ofstream::out | std::ofstream::trunc);
  write_matrix(&myL,L,n,m);
  myL.close();

  //calculation the rmse with the Frobenius norm
  float check = 0;
  for (int k=0; k<m; k++) {
    for (int i=0;i<n; i++) {
      double sum=0;
      for (int j=0; j<m; j++)
        sum += L[i][j] * R[k][j];
      if (abs(X1[i][k] - sum) > 1e-3)
        check += (X1[i][k] - sum) * (X1[i][k] - sum);
    }
  }

  //writing the result in the cdFile
  rmseFile << n << "\t" << truncated <<"\t"<<  "\t" << sqrt(check) << endl;
}

void centroidDecomp::write_matrix(std::ofstream* is, double** matrix, int nrows, int ncols)
{
    ostream_iterator<double> output_iterator(* is, ",");
    for (int i=0; i<nrows; i++) {
      for (int j=0; j<ncols; j++) {
        *is << matrix[i][j];
        *is << ",";
      }
      *is << endl;
    }
}

// load matrix from an ascii text file.
double** centroidDecomp::load_matrix(std::istream* is, int n, int m,
                                 const string& delim /*= ","*/)
{
  string line, strnum;
  double **matrix = allocMat(n, m, 0);

  for (int j=0; j<n; j++) {
    getline(*is, line);
    // matrix->push_back(vector<double>());
    int countCol = 0;
    for (string::const_iterator i = line.begin(); i != line.end(); ++ i) {
        if (countCol==m) break;

        // If i is not a delim, then append it to strnum
        if (delim.find(*i) == string::npos) {
          strnum += *i;
          // If it's the last char, do not continue
          if (i + 1 != line.end()) continue;
        }
        // if strnum is still empty, it means the previous char is also a
        // delim (several delims appear together). Ignore this char.

        if (strnum.empty()) continue;

        // If we reach here, we got a number. Convert it to double.
        double number;

        istringstream(strnum) >> number;
        // matrix->back().push_back(number);
        matrix[j][countCol] = number;
        strnum.clear();
        countCol++;
    }
  }
  return matrix;
}


