After trying some inputs, we found that 16 letters in the output are from ‘f’ to ‘u’. so intuitively we considered that input should also consist of these letters only as only 16 letters could be represented by four bits so we mapped each alphabet with a number from 0 to 15. Also, as the input was 8 bytes but the field was G_F(128), so we could have inputs from ’ff’ to ‘mu’ considering the most significant bit for any letter will always be 0.

We noticed that on giving any inputs of the form ‘gf’ or ‘gff’ & ‘hf’ or ‘hff’, it produced the same output as inputs ‘gf’ or ‘hf’ respectively. That means ‘f’ has been used as padding.
So, We kept input having a format as C^7P, so only the last Byte of output had different values, and all others were constants. So, we thought of trying out different formats such as C^6PC1 and so on. And we figured out that by changing nth Byte of input, it changes all Bytes of output after the nth Byte. This gave us a feeling that the transformation matrix used here is a lower triangular matrix.

Explanation : Consider a plaintext of form C^6PC^1, as the output is of form C^6P^2, which means for the 7th and 8th element, there is contribution of P from C^6PC^1 as all other C are zero and zero element gives zero as result, hence ‘ff’ is present in each row in A matrix and it is towards the end of the row, hence the matrix can be assumed to be a lower triangular matrix.

Thus, using inputgenerator.py  we generated chosen input plain text.

Now, we ran a python script (script.py) with the input file input.txt using the command “python script.py >> in.txt” to get corresponding outputs of input. The output was stored in output.txt using the command “ssh -tt student@65.0.124.36 < in.txt > output.txt” then ran "strings output.txt >> human.txt". Now the waste outputs were removed by clean.cpp which takes human.txt as input. After removing waste text from the ciphertexts.

Due to the input format we used, only 1 block is non-zero per input, so we can iterate over all possible values of diagonal elements and exponents since the matrix is lower triangular if x is the value of the non-zero input block (say i), then the corresponding block of output has the value O = (aii(aii*x^ei)^ei)^ei.

We then implemented operations over the finite field of 128 with generator x^7 + x + 1 which will be used to carry out operations throughout the code in BruteCipher.py.

Now, for each pair of plaintext-ciphertext; we iterate through all possible values of ei and ai,i (using the above operations) and compare the output. We kept on storing the possible value pairs of (ei and ai,i) and found out that there are 3 pairs per block.

The possible value of aii and ei:
>	Block 0 :  aii -> [84, 8, 109], ei ->[17, 41, 69]
>	Block 1 :  aii -> [127, 9, 70], ei ->[59, 90, 105]
>	Block 2 :  aii ->[43, 78, 87], ei ->[36, 42, 49]
>	Block 3 :  aii -> [43, 26, 12], ei ->[3, 57, 67]
>	Block 4 :  aii -> [64, 100, 112], ei ->[18, 21, 88]
>	Block 5 : aii -> [11, 73, 103], ei -> [52, 99, 103]
>	Block 6 : aii ->[52, 27, 27], ei -> [1, 19, 107]
>	Block 7 : aii-> [108, 38, 9], ei -> [12, 14, 101]

Now, we need to eliminate pairs and also find non-diagonal elements. To do this we will use some more plaintext-ciphertext pairs and iterate over the above pairs to find elements within 0 to 127 such that the equation O = (aii(aii*x^ei)^ei)^ei. holds. We do this in a triangular fashion such that we use ai,i & aj,j to find ai,j. Thus, after this iteration, we found every element next to each diagonal element.

This also helped us to reduce possible pairs to 1 element each as only for certain pairs we could produce an element next to the diagonal entry 
Now, we found each element of this matrix by iterating over all possible values (0 to 127) and using the Final Values of Exponent Matrix and the above-found values of Linear Transformation Matrix and checked the validity of the function.
Final Matrices as we found them in above step as follows
Hence, 
A = transpose of LINEAR_MATRIX =
         >  	           	[[84,125, 27, 104, 110, 30, 2, 88],
         >			[ 0, 70, 16, 20, 42, 47, 118, 2],
         >    			[ 0, 0, 43, 24, 1, 28, 1, 94],
         >   			[ 0, 0, 0,12, 114, 54, 105, 27],
         >  		  	[ 0, 0, 0, 0,112, 110, 23, 16],
         > 		  	[ 0, 0, 0, 0, 0,11, 92, 69],
         >   		 	[ 0, 0, 0, 0, 0, 0,27, 3],
         >		     	[ 0, 0, 0, 0, 0, 0, 0, 38]]
				
EXPONENT_MATRIX = [17, 105, 36, 67, 88, 52, 19, 14]

Now to decrypt the password we used the same way i.e. we iterated over all possible values for a block and check if our EAEAE function’s output is the same as the current password block we have. We did it in two halves as the password contained 32 letters. The decrypted password found out was:
 
             	                                       qjmizylkfi

