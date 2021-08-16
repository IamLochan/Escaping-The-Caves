a = [324, 2345, 9513]
P = 19807040628566084398385987581
A = [11226815350263531814963336315, 9190548667900274300830391220, 4138652629655613570819000497]

def modInverse(a, p):
	# P is assumed to be a prime number
    return pow(a, p - 2, p)

def power(x, y, m):
	if (y == 0):
		return 1
	p = power(x, y // 2, m) % m
	p = (p * p) % m
	if(y % 2 == 0):
		return p
	else:
		return ((x * p) % m)


g1 = (A[1] * modInverse(A[0],P)) % P
g2 = (A[2] * modInverse(A[0],P)) % P
pow_small,pow_large = 2021,9189
while pow_small != 1 :
    q = (pow_large//pow_small)
    g1 = power(g1,q,P)
    g1 = (g2 * modInverse(g1,P)) % P
    pow_small = pow_large-q*pow_small
print(g1)
g_324 = power(g1,324,P)
g_324_inverse = modInverse(g_324,P)
password = (A[0] * g_324_inverse)%P
print(password)
