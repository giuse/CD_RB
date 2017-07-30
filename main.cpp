//
//  main.cpp
//  CentroidDecomp
//
//  Created by Ines Arous on 3/22/17.
//  Copyright © 2017 Ines Arous. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "centroidDecomp.hpp"

using namespace std;

int main(int argc, char *argv[])
{

  ifstream myfile(argv[1]);
  //ifstream myfile("./Varying_n/input.txt");
  int n=atoi(argv[2]);
  int m=atoi(argv[3]);
  /* load the file into a matrix*/
  double **matrix = load_matrix(&myfile, n, m);


  /* Check the number of rows*/
  cout << "number of rows " << n << endl;
  /* Check the number of columns*/
  cout<< "number of cols " << m << endl;

  ofstream rmseFile;

  /* rmseFile contains the RMSE*/
  rmseFile.open ("./rmse.txt",std::ios_base::app);
  // matrixR is the file path of the matrix R
  // char const * matrixR=argv[4];
  char const * matrixR="./Rtest.txt";
  // matrixL is the file path of the matrix L
  // char const * matrixL=argv[5];
  char const * matrixL="./Ltest.txt";

  // r is the number of truncated columns
  int r = atoi(argv[6]);
  int truncated = m - r;

  //repeat the centroid decomposition 5 times in order to evaluate the average run time and rmse later
  centroidDec(matrix, n, m, truncated, matrixR, matrixL, rmseFile);

  rmseFile.close();
  myfile.close();
  free(matrix);
  return 0;
}




