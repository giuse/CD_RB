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


//unsigned int n=3;
//unsigned int m=2;
int main(int argc, char *argv[])
{

    //  vector<vector<double> > matrix(n, vector<double>(m));
    //    double array1[n][m]={{2,-2},{0,3},{-4,2}};

    //for (unsigned int i =0; i<n;i++)
    //{
    //for (unsigned int j=0;j<m;j++)
    //{
    //       (matrix[i])[j]=array1[i][j];
    //    }
    //  }


    ifstream myfile(argv[1]);
    unsigned int n=atoi(argv[2]);
    unsigned int m=atoi(argv[3]);
    //ifstream myfile("./Varying_n/input.txt");
    /* load the file into a matrix*/
    double **matrix = load_matrix(&myfile, n, m);


    /* Check the number of rows*/
    cout << "number of rows " << n << endl;
    /* Check the number of columns*/
    cout<< "number of cols " << m << endl;

    ofstream runTimeFile;
    /* runTime contains the run Time*/

    runTimeFile.open ("./runTime.txt",std::ios_base::app);
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
    unsigned int r=atoi(argv[6]);
    //cout << r << endl;
    unsigned long truncated=m-r;

    //repeat the centroid decomposition 5 times in order to evaluate the average run time and rmse later

        centroidDec(matrix,n,m,truncated,matrixR,matrixL,runTimeFile,rmseFile);



    rmseFile.close();
    runTimeFile.close();
    myfile.close();
    return 0;
}




