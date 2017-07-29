
#ifndef centroidDecomp_hpp
#define centroidDecomp_hpp

#include <stdio.h>

class centroidDecomp
{
public:
    void centroidDec( std::vector< std::vector<double> > X, long n, long m, long truncated,const char* matrixR,const char* matrixL,std::ofstream &runTimeFile,std::ofstream &rmseFile);
    void load_matrix(std::istream* is, int n, int m,
                     std::vector< std::vector<double> >* matrix,
                     const std::string& delim = ",");
    void write_matrix(std::ofstream* is, double** matrix, int nrows, int ncols);

};

#endif /* centroidDecomp_hpp */


