import math
import numpy as np
from numba import vectorize, cuda
from timeit import default_timer as timer

np.random.seed(42)

@vectorize('float32(float32, float32, float32)', target='cuda')
def cuda_discriminant(a, b, c):
	return math.sqrt(b**2 - 4*a*c)
	
n = 1e6

a = np.random.random(size=n).astype(np.float32)
b = np.random.random(size=n).astype(np.float32) + 10
c = np.random.random(size=n).astype(np.float32)

start = timer()
d = cuda_discriminant(a, b, c)
elapsed_time = timer() - start

print('D[:5]=', d[:5])
print('D[-5:]=', d[-5:])
print('Elapsed_time: %.4f' % (elapsed_time))
