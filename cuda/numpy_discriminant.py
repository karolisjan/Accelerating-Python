import numpy as np
from timeit import default_timer as timer

np.random.seed(42)

def np_discriminant(a, b, c):
	return np.sqrt(b**2 - 4*a*c)
	
n = 1e6

a = np.random.random(size=n).astype(np.float32)
b = np.random.random(size=n).astype(np.float32) + 10
c = np.random.random(size=n).astype(np.float32)

start = timer()
d = np_discriminant(a, b, c)
elapsed_time = timer() - start

print('D[:5]=', d[:5])
print('D[-5:]=', d[-5:])
print('Elapsed_time: %.4f' % (elapsed_time))