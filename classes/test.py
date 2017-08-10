import cProfile
import numpy as np
from matrix_wrapper import PyMatrix
from timeit import default_timer as timer

np.random.seed(42)
nrows, ncols = 100, 100
nums = np.random.random(size=(nrows * ncols)).tolist()

def pythonized_dot():
    A = nums
    B = nums
    C = [None] * nrows * ncols
    
    for i in range(nrows):
        for j in range(ncols):
            C[i * ncols + j] = A[i * ncols + 0] * B[0 * ncols + j]
            for k in range(1, ncols):
                C[i * ncols + j] += A[i * ncols + k] * B[k * ncols + j]    

    return C    
   
def cythonized_dot():
    A = PyMatrix(nrows, ncols, nums)
    B = PyMatrix(nrows, ncols, nums)
    return A.dot(B)
    
def numpyzed_dot():
    A = np.array(nums, dtype="float").reshape(nrows, ncols)
    B = np.array(nums, dtype="float").reshape(nrows, ncols)
    return A.dot(B)
    
def pythonized_transpose():
    A = nums
    B = [None] * nrows * ncols
    
    for i in range(nrows):
        for j in range(ncols):
            B[j * nrows + i] = A[i * ncols + j] 

    return B  
    
def cythonized_transpose():
    M = PyMatrix(nrows, ncols, nums)
    return M.T
    
def numpyzed_transpose():
    M = np.array(nums, dtype="float").reshape(nrows, ncols)
    return M.T

def time_it(func):
    start = timer()
    res = func()
    end = timer() - start
    print('%s, elapsed time: %.4f' % (func.__name__, end))
    
    if "numpyzed" in func.__name__:
        res = res.ravel()
        
    if "pythonized" not in func.__name__:
        res = res.tolist()

    print("First 5 values:", res[:5])
    print("Last 5 values:", res[-5:])
    print()

if __name__ == "__main__":
    time_it(pythonized_dot)
    time_it(cythonized_dot)
    time_it(numpyzed_dot)
    time_it(pythonized_transpose)
    time_it(cythonized_transpose)
    time_it(numpyzed_transpose)
    
    print('cProfile of cythonized_dot()')
    cProfile.run('cythonized_dot()', sort='time')
