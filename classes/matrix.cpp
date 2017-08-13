#include "matrix.h"
#include <omp.h>
#include <algorithm>
#include <cassert>

Matrix::Matrix() {}

Matrix::Matrix(size_t nrows, size_t ncols) : nrows(nrows), ncols(ncols)
{
    this->data = std::vector<double>(nrows * ncols);
}

Matrix::Matrix(size_t nrows, size_t ncols, std::vector<double> data) : nrows(nrows), ncols(ncols)
{    
    this->data = std::vector<double>(nrows * ncols);
        
	if (data.size() > nrows * ncols)
		return;
    
    std::copy(data.begin(), data.begin() + nrows * ncols, this->data.begin());
}

Matrix Matrix::Dot(Matrix other)
{
    assert(nrows == other.ncols);

	Matrix result(nrows, other.ncols);
    
    std::vector<double> &data = this->data;
        
    int i, j, k;
	
    #pragma omp parallel shared(result, data, other), private(i, j, k)
    {
        #pragma omp for schedule(static) 
        for (i = 0; i < nrows; ++i) {
            for (j = 0; j < other.ncols; ++j) {
                result.data[i * result.ncols + j] = data[i * ncols + 0] * other.data[0 * other.ncols + j];
                
                for (k = 1; k < ncols; ++k) {
                    result.data[i * result.ncols + j] += data[i * ncols + k] * other.data[k * other.ncols + j];
                }
            }
        }
    }
    
	return result;
}

Matrix Matrix::T()
{
    Matrix result(ncols, nrows);
 
    #pragma omp parallel for
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            result.data[j * result.ncols + i] = data[i * ncols + j];
        }
    }

	return result;
}

std::ostream& operator<<(std::ostream& os, Matrix m)
{
    size_t i, j, idx;
    
    for (i = 0; i < m.nrows; ++i) {
        for (j = 0; j < m.ncols; ++j) {
            idx = i * m.ncols + j;
            os << m.data[idx] << " ";
        }
        os << std::endl;
    }
    
    return os;
}
