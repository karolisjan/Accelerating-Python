from distutils.core import setup, Extension
from Cython.Build import cythonize

exts = cythonize([Extension("fib", sources=["cfib.c", "fib.pyx"])])

setup(
	ext_modules = exts,
)