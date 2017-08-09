def integrate(a, b, f):
	cdef:
		int i
		int n = 2000
		float dx, s = 0.0
	
	dx = (b - a) / n
	
	for i in range(n):
		s += f(a + i * dx)
	
	return s * dx