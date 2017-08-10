'''
    $ python setup.py build_ext --inplace --compiler=msvc
'''
import numpy as np
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

sourcefiles  = ['matrix_wrapper.pyx', 'matrix.cpp']

ext = [Extension('*',
                 sourcefiles,
                 language='c++')]

setup(
  ext_modules=cythonize(ext), 
  include_dirs=np.get_include(),
)