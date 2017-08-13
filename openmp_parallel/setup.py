'''
    $ python setup.py build_ext --inplace --compiler=msvc
'''
from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = [Extension('*',
                 ['py_omp_check.pyx', 'omp_check.cpp'],                 
                 language='c++',
                 extra_compile_args=['/openmp'])]

setup(ext_modules=cythonize(ext))