#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <vector>
#include <iostream>

class Matrix
{
public:
    Matrix();
    Matrix(size_t, size_t);    
	Matrix(size_t, size_t, std::vector<double>);    
	Matrix Dot(Matrix);
    Matrix T();
    friend std::ostream& operator<<(std::ostream&, Matrix);
    
	size_t nrows, ncols;
	std::vector<double> data;
};

#endif