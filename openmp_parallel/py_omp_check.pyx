cdef extern from "omp_check.h":
    void parallel_print()
    
def omp_check():
    parallel_print()