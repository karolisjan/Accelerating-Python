/*
	g++ -Wall test.cpp matrix.cpp -o test
*/

#include "matrix.h"
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

int main()
{
    int n = 2, m = 3;
    
	std::vector<double> a = {1, 2, 3, 4, 5, 6};
	std::vector<double> b = {7, 8, 9, 10, 11, 12};
    
    std::cout << "Vector a = " << a << std::endl;
    std::cout << "Vector a = " << b << std::endl;    
	
	Matrix A(n, m, a), B(n, m, b);
	
	Matrix D = A.Dot(B.T());
	
    std::cout << "Matrix A\n" << A << std::endl;
    std::cout << "Matrix B\n" << B << std::endl;
    std::cout << "Transpose of matrix B\n" << B.T() << std::endl;
	std::cout << "dot product of A and B\n" << D << std::endl;	
	
	return 0;
}