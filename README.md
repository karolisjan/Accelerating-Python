# Accelerating Python
Examples of accelerating Python using CUDA or C/C++ (through Cython).

## Requirements
- [Cython](http://cython.org/#download) version 0.26
- [NumPy](https://docs.scipy.org/doc/numpy/user/install.html) version 1.11.2
- [Numba](https://numba.pydata.org/) for [CUDA](https://github.com/karolisjan/Accelerating-Python/blob/master/cuda/cuda_discriminant.py) examples

## Wrapping up a C++ class in Python
Let's say we have a very basic matrix class in C++ (see [matrix.h](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/matrix.h) and [matrix.cpp](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/matrix.cpp)) and we would like to be able to use it in Python. 
```
class Matrix
{
public:
  Matrix();
  Matrix(size_t, size_t);    
	Matrix(size_t, size_t, std::vector<double>);    
	Matrix Dot(Matrix);
  Matrix T();
    
	size_t nrows, ncols;
	std::vector<double> data;
};
```
This can be fairly easily achieved using Cython. First, we create a [.pyx](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/matrix_wrapper.pyx) file and tell Cython [where and how](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/matrix_wrapper.pyx#L1) the C++ class is defined. 
```
cdef extern from "matrix.h": 
    cdef cppclass Matrix:
        Matrix() except +
        Matrix(int, int) except +
        Matrix(int, int, vector[double]) except +
        Matrix Dot(Matrix)
        Matrix T()
        int nrows, ncols
        vector[double] data
```
Then we [wrap](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/matrix_wrapper.pyx#L14) the C++ class using Cython.
```
cdef class PyMatrix:
    cdef Matrix cpp_matrix
    
    def __cinit__(self, int nrows=0, int ncols=0, data=[]):
        self.cpp_matrix = Matrix(nrows, ncols, data)
        
    @staticmethod
    cdef create(Matrix matrix):
        py_matrix = PyMatrix()
        py_matrix.cpp_matrix = matrix
        return py_matrix
                
    def dot(self, PyMatrix other):
        return PyMatrix.create(self.cpp_matrix.Dot(other.cpp_matrix))       
        
    @property
    def nrows(self):
        return self.cpp_matrix.nrows
    
    @property
    def ncols(self):
        return self.cpp_matrix.ncols
        
    @property
    def T(self):
        return PyMatrix.create(self.cpp_matrix.T())
        
    def tolist(self):
        return self.cpp_matrix.data
```
Finally, to able to import and use PyMatrix in Python, we need to compile the Cython code. There are several ways to achieve this. A standard way is to create a compilation pipeline using *distutils* and *cythonize* in a [setup.py](https://github.com/karolisjan/Accelerating-Python/blob/master/classes/setup.py) file. 

Running the following on the command line would then create a **matrix_wrapper.pyd** file.
```
$ python setup.py build_ext --inplace --compiler=msvc
```
We can then use **matrix_wrapper.pyd** as a regular Python module.
```
from matrix_wrapper import PyMatrix

nrows, ncols = 2, 3
nums = [1, 2, 3, 4, 5, 6]

A = PyMatrix(nrows, ncols, nums)
```
Here is a list of how long it takes to calculate a dot product of two 100x100 matrices of floats using naive Python, NumPy, and the Cythonized C++ class.
```
pythonized_dot, elapsed time: 0.3855
First 5 values: [21.173660031172105, 23.696220196886877, 24.863351903673895, 23.838403751141865, 22.887967241487797]
Last 5 values: [26.035921065546137, 22.376557509543982, 21.352940847012672, 23.59375397622621, 23.580061345452677]

cythonized_dot, elapsed time: 0.0030
First 5 values: [21.173660031172105, 23.696220196886877, 24.863351903673895, 23.838403751141865, 22.887967241487797]
Last 5 values: [26.035921065546137, 22.376557509543982, 21.352940847012672, 23.59375397622621, 23.580061345452677]

numpyzed_dot, elapsed time: 0.0042
First 5 values: [21.173660031172105, 23.696220196886877, 24.863351903673895, 23.838403751141865, 22.887967241487797]
Last 5 values: [26.03592106554613, 22.37655750954398, 21.35294084701267, 23.593753976226203, 23.58006134545267]
```
The Cythonized C++ class was over 100 times faster than the naive Python version and marginally faster than the NumPy version.

The Cythonized C++ class was also 20 times faster at calculating a transpose of a 100x100 matrix of floats.
```
pythonized_transpose, elapsed time: 0.0021
First 5 values: [0.3745401188473625, 0.03142918568673425, 0.6420316461542878, 0.0516817211686077, 0.10312386883593261]
Last 5 values: [0.39850202880398033, 0.8090345502403417, 0.9303511771330678, 0.0415959562564695, 0.21714040403767187]

cythonized_transpose, elapsed time: 0.0001
First 5 values: [0.3745401188473625, 0.03142918568673425, 0.6420316461542878, 0.0516817211686077, 0.10312386883593261]
Last 5 values: [0.39850202880398033, 0.8090345502403417, 0.9303511771330678, 0.0415959562564695, 0.21714040403767187]

numpyzed_transpose, elapsed time: 0.0002
First 5 values: [0.3745401188473625, 0.03142918568673425, 0.6420316461542878, 0.0516817211686077, 0.10312386883593261]
Last 5 values: [0.39850202880398033, 0.8090345502403417, 0.9303511771330678, 0.0415959562564695, 0.21714040403767187]
```
