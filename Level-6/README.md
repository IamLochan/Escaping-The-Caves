For this assignment, we needed to decipher a low exponent RSA cipher where e = 5. We were given the following - 

n=84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093

fsociety: This door has RSA encryption with exponent 5 and the password is: 

23701787746829110396789094907319830305538180376427283226295906585301889543996533410539381779684366880970896279018807100530176651625086988655210858554133345906272561027798171440923147960165094891980452757852685707020289384698322665347609905744582248157246932007978339129630067022987966706955482598869800151693

RSA encryption and decryption works as follows:- Encryption: C = M^e Mod N , Decryption: M = C^d mod N 

So To decrypt the password, we have two ways - first is to find factors of N which are impossible to find because the length of n is too large (999 bits). Second, we could try and compute d, but as we know N can’t be factorized, we can’t compute phi(N) and that’s why d also can’t be computed efficiently. 

Now, as the public exponent is 5 (which is small) we can use a low-exponent attack (Coppersmith’s Algorithm)

notation - x0 is x nod
Coppersmith Theorem 
Statement : Let f(x) be a polynomial of degree d and N be a natural number, Let X = (N^1/d) - a for 1/d > a > 0 . Then given <f,N>, one can compute x0 < X such that f(x0) = 0 mod N.
Let f(x) = ((M+x)^e) mod N. {https://en.wikipedia.org/wiki/Coppersmith%27s_attack}
According to this theorem, If x is smaller than N^1/e, we will find the required password as the root to this polynomial.

This algorithm requires a polynomial as an input. For this, first, we have to check if the given ciphertext is padded with some padding or not. If there is no padding then, C^1/e must be an integer, but this was not the case, hence there is some padding.

Let p be the padding, For the padding scheme, first, we converted them to their binary equivalent p_bin (using the ASCII-256 mapping) and then to their decimal system equivalent p_10. Thus With padding, the final equation becomes (p_bin+M)^e = C mod N. In this equation, N, e, and C are known and p and M are unknown. We will try to guess p as Coppersmith says that if we are trying to find N^1/e of the message, it is then a small root and we should be able to find it pretty quickly.

Procedure :
Selected a custom padding p and converted to its binary equivalent form p_bin.
The length of password M is unknown, but the password can be divided into blocks of 8 bits as it must be converted from ASCII and as x0 < N^1/e (coppersmith theorem), M < 200 bits. Hence it can be brute-forced.
Hence final f(x) = (p_bin<<len(M) + M)^e - C 
Roots of the above f(x) are the required password and were found using LLL(lattice reduction) and Coppersmith Theorem.

We tried different paddings but didn't work. Then we noticed After reaching the five exits, the numbers were changing as we switched from exit1, all the way to exit4. The numbers were 2 digits numbers consisting of letters up to f and numbers from 0 to 9. We guessed it to be a hexadecimal value. It was converted to ASCII as “You see a Gold-Bug in one corner. It is the key to a treasure found by” 
So we tried p = You see a Gold-Bug in one corner. It is the key to a treasure found by

The root found by the modified Coppersmith's Algorithm was: 1000000100001001000000011010000111010101100010010000010110110000100001
Now, we picked 8-bit chunks at a time and looked at the corresponding ASCII value and the decrypted password found out was: 
                                               B@hubAl!

For the code, we used the implementation of Coppersmith and LLL reduction from the link
{https://github.com/mimoo/RSA-and-LLL-attacks/blob/master/coppersmith.sage}.
The code was wrapped in a callable function with different padding as a parameter. For testing purposes, we used the public key (n,e) to generate custom ciphertext with known plaintext to test the correctness of code.

Citations :
LLL and Coppersmith Implementation in Sage:
{https://algo.epfl.ch/_media/en/projects/bachelor_semester/rapportetiennehelfer.pdf}

