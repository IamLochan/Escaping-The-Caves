# Substitution cipher

## Commands

Commands to reach the first ciphertext in the game.

> climb => read => enter => read 

## Analysis

- Incorrect distribution of spaces between the words,as there were three distinct single letter words in the cipher text, but ‘I’ and ‘A’ are only single letter words.
- The frequency of each letter in the ciphertext space was counted using a computer program.
- No punctuation on the last line and capitalization of the first word, hence the words "Mew awameyt" was shifted to beginning of the ciphertext.
- Occurrence of different trigraphs and digraphs were counted in the ciphertext.
- Evert digit(in plaintext) was shifted by 4, hence 8(ciphertext) shifted to 4 and password was found by shifting every number by ‘4’(in reverse order) i.e. 0-> 6 and 3-> 9.
- Use of website : <https://crypto.interactive-maths.com/frequency-analysis-breaking-the-code.html> for counting trigraphs and digraphs.
## Maping

> Cipher text space : {A,B,D,E,F,G,H,I,J,K,M,N,O,P,R,S,T,U,V,W,X,Y,8,0,3}

> Plain text space : {A,B,C,D,E,F,G,H,I,L,M,N,O,P,Q,R,S,T,U,V,W,Y,4,6,9}

> Mapping as (cipher-text, plain-text) : { (Y,E), (M,T), (A,S), (W,I), (E,H), (G,O), (P,A), (S,R), (H,N), (I,C), (J,M), (N,U), (O,B), (T,F), (U,D), (K,L), (R,G), (F,P), (V,W), (D,Q), (X,Y), (B,V),(8,4),(0,6),(3,9)}
 
In the deciphered text we got to know that the digits are shifted by 8, so 8 itself must be shifted by some number x, so (2 * x) must be 8, so x = 4. The digits are shifted by 4 towards the left, so 0 maps to 6 and 3 maps to 9. 

## Password

Final command to clear this level is "tyRgU69diqq".
