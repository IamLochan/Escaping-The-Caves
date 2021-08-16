# Playfair Cipher

## Commands

Commands to reach the ciphertext in the game.

> go => back => read 

## Analysis

1. Using the “read” command leads to the ciphertext so we used frequency analysis as a general approach but couldn’t get any understandable plaintext. So we observed we should go back and use other commands to get more information.
2. Using the “go” command we got some hidden code in “-” and “.”. We recognised it as “Morse Code” and then it was decoded to “SECURITY”.
3. The paragraph there mentioned to believe in “Play Fair” which indicated the use of the word “SECURITY” as the key for some key based encryption.
4. We observed “SECURITY” can be used as the key for playfair decryption. After using play fair and “SECURITY” as the key we got our plaintext and that’s how we figured out the cryptosystem.

## Decryption Algorithm

Key Square Lookup table generation:
Given the key - 'SECURITY'
The key square is a 5x5 grid of unique alphabets that acts as the key. Usually 'J' is omitted from the key. If the ciphertext contains J, it is combined with I. 
The initial alphabets in the key are the unique alphabets of the key in the order in which they appear in the 'SECURITY', followed by the remaining alphabets in alphabetical order.

The keysquare for the key 'SECURITY' : 
[S	E	C	U	R
I	T	Y	A	B
D	F	G	H	K
L	M	N	O	P
Q	V	W	X	Z]

Preprocessing of the ciphertext:	
1. Remove any punctuation or characters that are not present in the key square (this may mean spelling out numbers, punctuation etc.).
2. Break the plaintext into pairs of letters, e.g. 'cipher’- ‘ci ph er'. The algorithm now works on each pair of letters.

Algorithm to decrypt the letter pairs:
1. Locate the letters on the key square and mark the index of both the elements.
2.  if the letter appears on the same row: replace them with the letters to their immediate right respectively (going back to the leftmost if at the rightmost position).
else if letter appears on the same column: replace them with the letters immediately below respectively (going back to the top if at the bottom).
else: form a rectangle with the two letters and take the letters on the horizontal opposite corner of the rectangle.
Plaintext :
BEWARE OF THE NEXT CHAMBER, THERE IS VERY LITTLE JOY THERE. SPEAK OUT THE PASSWORD “OPEN_SESAME” TO GO THROUGH. MAY YOU HAVE THE STRENGTH FOR THE NEXT CHAMBER. TO FIND THE EXIT YOU FIRST WILL NEED TO UTTER MAGIC WORDS THERE.

## Password

Final command to clear this level is "OPEN_SESAME".
