Z_p^* is a commutative multiplicative group where p is the given prime number 19807040628566084398385987581.
Useful properties used in the analysis, for any two positive integers, a, b:
1. (a*b)%c  = ((a%c)*(b%c))%c.
2. a*b is an element of the multiplicative group (a*b)%p.

3. For any element in a group, let us say 'A', A^m = e, where 'e' is the identity element of the multiplicative group and 'm' is the set's cardinality Z_p^*. For prime P, m = p-1.

4. Calculation of Inverse of an element in the group:
 An element B of Z_p^* is said to be inverse of A if (A*B)%p = 1
Hence, for A, it is clear that A^(p-2) is inverse of A as A * A^(p-2) = A^(p-1) = 1 (using 3)
Now, given equations of is an ordered pair (a password*g^a).

Let (a1,a2,a3) be the tuple of 'a' and (G1,G2,G3) by the tuple of 'password*g^a' from the given equations. Let modinverse(x) be the modulo inverse of x under group Z_p^*. 
Note : The function modinverse(x) uses modular exponentiation and property 4. Modular exponentiation calculates inverse in O(log(p)) time.

 1: (324,11226815350263531814963336315)	
 2: (2345, 9190548667900274300830391220)
 3: (9513, 4138652629655613570819000497)

modinverse(G1) = modinverse(g^a) * modinverse(password) = G1^-1(say)
On multiplying G2 with G1_inverse and G3 with G1_inverse, we have two equations : 
1.	g^2021 = G2 * G1^(-1).  ------ equation (1)
2.	g^9189 = G3 * G1^(-1).  ------ equation (2)

Note : gcd(2021, 9189) = 1, hence there exists two integer x and y such that x * 2021 + y * 9189 = 1
Using the Extended Euclidean Algorithm, it is possible to find g^( gcd(2021, 9189) ) using equations (1) and (2).

Algorithm to find g:

	Let smaller_power = 2021, larger_power = 9189, G1^-1 = modinverse(G1)
	Let smaller_G = G2 * G1^-1, larger_G = G3 * G1^-1
	while smaller_power != 1:
		quotient = floor(larger_power / smaller_power), where floor() is the greatest integer function.
		smaller_G = (smaller_G^q) % p
		smaller_G = (larger_G * modinverse(smaller_G)) % p
		smaller_power = larger_power - quotient * smaller_power

	G_324 = (smaller_G^324) % p
	password = (G1 * modinverse(G_324)) % p
	print(password)


password = 3608528850368400786036725
g = 192847283928500239481729
