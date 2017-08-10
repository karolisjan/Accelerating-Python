#include "matrix.h"
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
	Matrix result(this->nrows, other.ncols);
    
    assert(this->nrows == other.ncols);
    assert(result.data.size() != 0);
	
	size_t i, j, k;
	
    for (i = 0; i < this->nrows; ++i) {
		for (j = 0; j < other.ncols; ++j) {
			result.data[i * result.ncols + j] = this->data[i * this->ncols + 0] * other.data[0 * other.ncols + j];
			for (k = 1; k < this->ncols; ++k) {
				result.data[i * result.ncols + j] += 
                this->data[i * this->ncols + k] * other.data[k * other.ncols + j];
			}
		}
	}
	
	return result;
}

Matrix Matrix::T()
{
    Matrix result(this->ncols, this->nrows);

    size_t i, j;
    
	for (i = 0; i < this->nrows; ++i) {
		for (j = 0; j < this->ncols; ++j) {
			result.data[j * result.ncols + i] = this->data[i * this->ncols + j];
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
