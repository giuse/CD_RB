//
//  centroidDecomp.hpp
//  CentroidDecomp
//
//  Created by Ines Arous on 3/22/17.
//  Copyright © 2017 Ines Arous. All rights reserved.
//

#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <stdio.h>

class centroidDecomp
{
public:
    centroidDecomp();
    virtual ~centroidDecomp();
    void centroidDec( std::vector< std::vector<double> > X, unsigned long n, unsigned long m,unsigned long truncated,const char* matrixR,const char* matrixL,std::ofstream &runTimeFile,std::ofstream &rmseFile);
    void load_matrix(std::istream* is,unsigned int n,unsigned int m,
                     std::vector< std::vector<double> >* matrix,
                     const std::string& delim = ",");
    void write_matrix(std::ofstream* is,std::vector< std::vector<double> >* matrix);
    
};

#endif /* centroidDecomp_hpp */


