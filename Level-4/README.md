# 6 Round DES

## Commands

Commands to reach the ciphertext in the game.

> go -> dive -> dive -> back -> dive-> pull -> back -> back -> go -> wave  After this we broke the connection and then connected again to level 4.  Then we used the following command:- read-> password

## Analysis

1.We reached the magical screen and found that it can be either 4 ,6 or 10 round DES. We guessed it as 6 round DES because breaking 4 round DES is relatively easy. So it was given that two letters are of 1 byte that means one letter is of 4 bits so that means 16 letters represent 64 bit (1block size). As there were only 16 letters so we did frequency analysis and found that all the letters are between f and u. As letters are of 4 bits and only 16 letters so we mapped them with numbers 0 to 15.
 
2.Now for breaking 6 round DES we needed 4 round differential characteristics so we used 5 round characteristic up to 4 rounds i.e.(405C0000 , 04000000, 1/4 ,04000000, 00540000,5/128 , 00540000,1,00000000,00540000,5/128, 04000000 with p= ¼*5/128*1*5/128 = 0.000381. So using l = 20/p we needed around 1 lakh pair of chosen plaintext-ciphertext pairs.

3.We used random.cpp to  generate one lakh random inputs and also to get input pairs whose XOR is equal to ‘0000902010005000’ which we get from inverse initial permutation of ‘405c0000 04000000’ and it is stored in input_random.txt

4.Now, we ran a python script (script.py) with input file input_random.txt using the command “python script.py >> in.txt” to get corresponding outputs for these 1 lakh pairs of input. The output was stored in output.txt using the command “ssh -tt student@65.0.124.36 < in.txt > output.txt” then ran "strings output.txt >> human.txt". 

5.Now the waste outputs were removed by clean.cpp which takes human.txt as input. After removing waste text from the ciphertext,  it converts alphabets into 4-bit binary code and saves in output1.cpp

6.The we ran differential.cpp which takes output1.cpp as input and prints three different outputs in alphaxor.txt, betaxor.txt, and reversefinalperm.txt. 

7.In this program, firstly the block is to reverse the final permuted to get the output of the sixth round and stored in reversefinalperm.txt. Then we took the xor of the odd, even blocks (they both are pairs).

8. Gamma is the output of the expansion box that corresponds to R5 which is also equal to L6. Alpha is the value of the xor of the key6 and the output of expansion(gamma)and beta is the output of the s-box in the 6th round. we expanded R5( left-hand side bit L6). Now, this is equal to xor of gamma1 and gamma2 and also of alpha1 xor alpha2. So we stored it in alphaxor.txt. The right hand (R6) is xor with xored L5 (equal to R4 which is probabilistically equal to ‘04000000’ and then inverse permuted to give beta1 xor beta2 stored in betaxor.txt.

9.Then it computes the gamma1 values after expanding the left-hand side of the reverse final permuted block from reversefinalperm.txt and stores it in gamma.txt.

10. Then we used the s-box.cpp program to calculate the possible value of key 6 and the frequency. It is first used to get the values of alpha1 and alpha2 corresponding to alpha1 xor alpha2 and whose S(alpha1) and S(alpha2) is also equal to beta1 xor beta2. For each permuted 6 bits of alpha1, the value of alpha2 was calculated by taking xor of alpha1 and (alpha1 xor alpha2). Then we compared the value of xor of S[alpha1] and S[alpha2] with beta xor. Now the (alpha1,alpha2)which satisfies these conditions are the possible values of alpha1 and alpha2. Then key6 was calculated by taking the value of  (alpha1 xor the corresponding gamma1) and then stats.cpp was used to keep counter.

11. Using stats.cpp we calculated max and avg frequency and saved in it analysis.txt
avg : 6416 max : 6623 index : 45
avg : 6528 max : 6774 index : 45
avg : 6235 max : 6387 index : 51
avg : 6246 max : 6439 index : 13
avg : 6556 max : 6814 index : 49
avg : 6513 max : 6719 index : 49
avg : 6496 max : 6730 index : 31
avg : 6540 max : 6751 index : 18

It is to be noted that there is not a huge difference between the average frequency and the maximum occurring frequency, specially for S3 and S4. Hence nothing definite can be concluded about the keys for the S boxes. Hence it is expected that we need much more than 100k pairs of plaintext to find the maximum value, which will most likely be the key.

12.Now, using keybase.cpp we get 6 blocks values out of 8 blocks but we could not get the key values from S-boxes S3 and S4. So now we have knowledge of 36 bits out of 56 bits and then using keyscheduling.cpp we got the permutation of the 6th key (48bit). For sake of completeness, we assumed the current maximum value as the correct key and tried to find the 56 bit key for the 6th round. Let us drop S3 and S4 boxes. Hence we know 36 bits of 56 bits key. 

13. We mapped the location of bits in the 56 bit sequence using the permutation table obtained using keyscheduling.cpp and then used the program key_base to generate a base key with unknown bits as ‘x’. 

14. Now, “key_perm.cpp” was used to generate all possible 2^20 possible keys for DES, which stores the output in “key_out.txt” as all possible keys. The “key_out.txt” was given to desbruteforce.cpp which generate round key for 6 rounds and test the validity of each key with sample text “ffff ffff ffff ffff” {all zeros} which gives output as “jqhg jrnn tuml jijf”. As expected, no such key was found due to closeness of max frequency with average frequency.

If some part of the key is known with certainty, then the exact key can be derived.
