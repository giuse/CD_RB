//
//  centroidDecomp.cpp
//  CentroidDecomp
//
//  Created by Ines Arous on 3/22/17.
//  Copyright © 2017 Ines Arous. All rights reserved.
//



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



centroidDecomp::centroidDecomp()
{
    //ctor
}

centroidDecomp::~centroidDecomp()
{
    //dtor
}
/* find the sign vector that maximizes the product X'Z according to the SSV algorithm*/
static vector <int> findSignVector ( std::vector< std::vector<double> > X,unsigned long n,unsigned long m)
{
    int pos=-1;
    int val=0;
    vector<int>  Z(n,1);
    vector<double> V(n,0);
    vector<double>  S(m, 0);
    for (unsigned int i=0; i<m; i++)
    {
        for (unsigned int j=0; j<n; j++)
        {
            S[i]+=X[j][i];
        }
    }
    
    for (unsigned int i=0; i<n; i++)
    {
        for (unsigned int j=0; j<m;j++)
        {
            V[i]+=X[i][j]*(S[j]-X[i][j]);
        }
    }
    int iteration=0;
    do
    {
        vector<double>  S(m, 0);
        if (pos!=-1)
        {
            Z[pos]*=-1;
          for (unsigned int i=0; i<n;i++ )
                            
            {
                      if (i!=pos)
                      {
                                for (unsigned int j=0; j<m;j++)
                                {
                                          V[i]-=2*X[i][j]*X[pos][j];
                                }
                      }
            }
        }
        val=0;
        pos=-1;
        for (unsigned int i=0; i<n; i++)
        {
            if (Z[i]*V[i]<0)
                
                if(abs(V[i])>val)
                {
                    val=abs(V[i]);
                    pos=i;
                }
        }
        iteration++;
    } while(pos!=-1);

    return Z;
}
/* Calculate the norm 2 of a vector */
static double norm2 (vector <double> &C)
{
    double accum = 0.;
    for (unsigned int i = 0; i < C.size(); ++i) {
        accum += C[i] * C[i];
    }
    return sqrt(accum);
}
/* The  centroid decomposition algorithm*/
void centroidDecomp::centroidDec( std::vector< std::vector<double> > X, unsigned long n,unsigned long m,
                                 unsigned long truncated,const char* matrixR,const char* matrixL,std::ofstream &runTimeFile,std::ofstream &rmseFile)
{
    std::vector< std::vector<double> > R(m, vector<double>(m));
    std::vector< std::vector<double> > L(n, vector<double>(m));
    vector<int>  Z(n,0);
    std::vector< std::vector<double> > X1=X;
    
    long long elapsed_msec;
    auto startCD= std::chrono::high_resolution_clock::now();
    for (int k=0;k<truncated;k++)
    {
        //calculating the sign vector
        Z=findSignVector (X,n,m);
        
        vector <double> C(m,0);
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
            R[i][k]=C[i]/norm2(C);
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
    write_matrix(&myR,&R);
  
    //write L
    write_matrix(&myL,&L);
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

void centroidDecomp::write_matrix(std::ofstream* is,std::vector< std::vector<double> >* matrix)
{
    ostream_iterator<double> output_iterator(* is, ",");
    for (unsigned int i = 0 ; i < matrix->size() ; i++ )
    {
        
        copy(matrix->at(i).begin(), matrix->at(i).end(), output_iterator);
        *is << endl;
    }
    
}
// load matrix from an ascii text file.
void centroidDecomp::load_matrix(std::istream* is,unsigned int n,unsigned int m,
                                 std::vector< std::vector<double> >* matrix,
                                 const string& delim /*= ","*/)
{
    using namespace std;
    
    string      line;
    string      strnum;
    
    // clear first
    matrix->clear();

    for (unsigned int j=0;j<n;j++)
    
    {
        getline(*is, line);
        matrix->push_back(vector<double>());
        unsigned int countCol=0;
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


