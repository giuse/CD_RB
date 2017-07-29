
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include "centroidDecomp.hpp"
using namespace std;


/* find the sign vector that maximizes the product X'Z according to the SSV algorithm*/
static int* findSignVector (std::vector< std::vector<double> > X, long n, long m)
{
  int pos = -1, val=0;
  // vector<int>  Z(n,1);
  int *Z = (int*)malloc(n * sizeof(int));
  for (int i=0; i<n; i++) Z[i] = 1;
  // vector<double> V(n,0);
  double *V = (double*)malloc(n * sizeof(double));
  for (int i=0; i<n; i++) V[i] = 0;
  // vector<double>  S(m, 0);
  double *S = (double*)malloc(m * sizeof(double));
  for (int i=0; i<m; i++) S[i] = 0;

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
void centroidDecomp::centroidDec(std::vector< std::vector<double> > X,  long n, long m,
                                  long truncated,const char* matrixR,const char* matrixL,std::ofstream &runTimeFile,std::ofstream &rmseFile)
{
  // std::vector< std::vector<double> > R(m, vector<double>(m));
  double **R = (double**)malloc(m * sizeof(double*));
  for (int i=0; i<m; i++) {
    R[i] = (double*)malloc(m * sizeof(double));
    for (int j=0; j<m; j++) R[i][j] = 0;
  }

  // std::vector< std::vector<double> > L(n, vector<double>(m));
  double **L = (double**)malloc(n * sizeof(double*));
  for (int i=0; i<n; i++) {
    L[i] = (double*)malloc(m * sizeof(double));
    for (int j=0; j<m; j++) L[i][j] = 0;
  }

  // vector<int>  Z(n,0);
  int* Z;

  std::vector< std::vector<double> > X1=X;

  long long elapsed_msec;
  auto startCD= std::chrono::high_resolution_clock::now();
  for (int k=0;k<truncated;k++)
  {
    //calculating the sign vector
    Z=findSignVector (X,n,m);

    // vector <double> C(m,0);
    double *C = (double*)malloc(m * sizeof(double));
    for (int i=0; i<m; i++) C[i] = 0;

    for(int i=0;i<n;i++)
    {
      for (int j=0;j<m;j++)
      {
        C[j]+=X[i][j]*Z[i];
      }
    }
    //calculating R
    for (int i=0; i<m; i++)
    {
      R[i][k]=C[i]/norm2(C,m);
    }
    //calculating L
    for (int i=0;i<n;i++)
    {
      L[i][k]=0;
      for (int j=0; j<m; j++)
      {
        L[i][k]+=X[i][j]*R[j][k];
      }
    }
    //Calculating the new X
    for (int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
      {
        X[i][j]=X[i][j]-(L[i][k]*R[j][k]);
      }
    }
  }

  //End of the centroid  decomposition
  auto endCD = std::chrono::high_resolution_clock::now();
  elapsed_msec=std::chrono::duration_cast<std::chrono::milliseconds>(endCD-startCD).count() ;
  //file containing matrix R
  ofstream myR;
  myR.open (matrixR,std::ofstream::out | std::ofstream::trunc);
  //file containing matrix L
  ofstream myL;
  myL.open (matrixL,std::ofstream::out | std::ofstream::trunc);
  //write R
  write_matrix(&myR,R,m,m);

  //write L
  write_matrix(&myL,L,n,m);
  myR.close();
  myL.close();
  //calculation the rmse with the Frobenhius norm
  float check=0;
  for (int k=0; k<m;k++)
  {
    for (int i=0;i<n; i++)
    {
      double  sum=0;
      for (int j=0; j<m;j++)
      {
        sum+=L[i][j]*R[k][j];
      }
      if (abs(X1[i][k]-sum)>(1e-3))
      {
        check+=(X1[i][k]-sum)*(X1[i][k]-sum);
      }
    }
  }

  //writing the result in the cdFile
  runTimeFile << n << "\t" << truncated <<"\t"<< elapsed_msec<<endl;
  rmseFile << n << "\t" << truncated <<"\t"<<  "\t" << sqrt(check) << endl;
  cout << "time for cd " << "\t" <<elapsed_msec<<endl;
}

void centroidDecomp::write_matrix(std::ofstream* is, double** matrix, int nrows, int ncols)
{
    ostream_iterator<double> output_iterator(* is, ",");
    for (int i = 0 ; i < nrows ; i++ ) {
      // copy(matrix[i], matrix[i+ncols], output_iterator);
      for (int j = 0 ; j < ncols ; j++ ) {
        *is << matrix[i][j];
        *is << ",";
      }
      *is << endl;
    }
}
// load matrix from an ascii text file.
void centroidDecomp::load_matrix(std::istream* is, int n, int m,
                                 std::vector< std::vector<double> >* matrix,
                                 const string& delim /*= ","*/)
{
    using namespace std;

    string      line;
    string      strnum;

    // clear first
    matrix->clear();

    for (int j=0;j<n;j++)

    {
        getline(*is, line);
        matrix->push_back(vector<double>());
         int countCol=0;
        for (string::const_iterator i = line.begin(); i != line.end(); ++ i)
        {
            if (countCol==m)
            {
                break;
            }
            // If i is not a delim, then append it to strnum
            if (delim.find(*i) == string::npos)
            {
                strnum += *i;
                if (i + 1 != line.end()) // If it's the last char, do not continue
                    continue;
            }
            // if strnum is still empty, it means the previous char is also a
            // delim (several delims appear together). Ignore this char.

            if (strnum.empty())
                continue;

            // If we reach here, we got a number. Convert it to double.
            double       number;

            istringstream(strnum) >> number;
            matrix->back().push_back(number);
            strnum.clear();
            countCol++;


        }

    }
}


