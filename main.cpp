
#include <fstream>
#include "centroidDecomp.hpp"

using namespace std;

int main(int argc, char *argv[])
{

  ifstream myfile(argv[1]);
  int n=atoi(argv[2]);
  int m=atoi(argv[3]);
  /* load the file into a matrix*/
  double **matrix = load_matrix(&myfile, n, m);


  // matrixR is the file path of the matrix R
  char const * matrixR="./Rtest.txt";
  // matrixL is the file path of the matrix L
  char const * matrixL="./Ltest.txt";

  // r is the number of truncated columns
  int r = atoi(argv[6]);
  int truncated = m - r;

  //repeat the centroid decomposition 5 times in order to evaluate the average run time and rmse later
  centroidDec(matrix, n, m, truncated, matrixR, matrixL, rmseFile);

  myfile.close();
  // rmseFile.close();
  free(matrix);
  return 0;
}




