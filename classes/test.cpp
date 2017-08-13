#include "matrix.h"
#include "timer.h"
#include <iostream>
#include <vector>

template<class T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v)
{
    for (auto &val : v)
        os << val << " ";
    os << std::endl;
    
    return os;
}

void TestDotProduct(Matrix &A, Matrix &B)
{
    Matrix D = A.Dot(B.T());
}

int main()
{
    int n = 1000, m = 1000;
    
    std::vector<double> a = std::vector<double>(n * m, 1);
    std::vector<double> b = std::vector<double>(n * m, 1);
            
	Matrix A(n, m, a), B(n, m, b);
    
    std::cout << "Elapsed time: " << timer<>::timeit(TestDotProduct, A, B) << "ms" << std::endl;
	
	return 0;
}