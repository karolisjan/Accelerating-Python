import math
import numpy as np
from timeit import default_timer as timer

np.random.seed(42)

def py_discriminant(a, b, c):
	d = np.zeros_like(a)
	
	for i in range(len(d)):
		d[i] = math.sqrt(b[i]**2 - 4*a[i]*c[i])
		
	return d
	
n = 1e6

a = np.random.random(size=n).astype(np.float32)
b = np.random.random(size=n).astype(np.float32) + 10
c = np.random.random(size=n).astype(np.float32)

start = timer()
d = py_discriminant(a, b, c)
elapsed_time = timer() - start

print('D[:5]=', d[:5])
print('D[-5:]=', d[-5:])
print('Elapsed_time: %.4f' % (elapsed_time))