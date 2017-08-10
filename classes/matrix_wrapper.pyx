cimport numpy as np
from libcpp.vector cimport vector

cdef extern from "matrix.h": 
    cdef cppclass Matrix:
        Matrix() except +
        Matrix(int, int) except +
        Matrix(int, int, vector[double]) except +
        Matrix Dot(Matrix)
        Matrix T()
        int nrows, ncols
        vector[double] data
    
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
       