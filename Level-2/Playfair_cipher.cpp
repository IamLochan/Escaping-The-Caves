#include <bits/stdc++.h>
using namespace std;
#define SIZE 30
std::vector<char> punctuation = {',', '.', ' ', '?', '\n', '\t', '_'};
char keyT[5][5];
int mod5(int a) {
	return (a % 5);
}

// conversion of each letter to upeercase
void tolowercase(std::string& ciphertext)
{
	std::transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), [&](char ch) -> char {
		if (not isalpha(ch))
			return ch;
		if (std::isupper(ch))
		{
			return std::tolower(ch);
		}
		return ch;
	});
}

// removal of punctuation. It is assumed that numbers are not present in the ciphertext
std::string removePunctuation(std::string& ciphertext)
{
	std::string res;
	for (auto i : ciphertext) {
		bool ispunctuation = false;
		for (auto ch : punctuation) {
			if (ch == i) {
				ispunctuation = true;
				break;
			}
		}
		if (ispunctuation)	continue;
		else res += i;
	}
	return res;
}

// generates the 5x5 key square
void generateKeyTable(std::string key)
{
	int ks = (int)key.size();
	int i, j, k;

	auto dicty = std::vector<int>(26, 0);

	for (i = 0; i < ks; i++) {
		if (key[i] != 'j')
			dicty[key[i] - 97] = 2;
	}
	dicty['j' - 97] = 1;

	i = 0;
	j = 0;
	for (k = 0; k < ks; k++) {
		if (dicty[key[k] - 97] == 2) {
			dicty[key[k] - 97] -= 1;
			keyT[i][j] = key[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
	for (k = 0; k < 26; k++) {
		if (dicty[k] == 0) {
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}
// search for the letter to be substituted with
void search(char a, char b, int arr[])
{
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}
// Actual decryption of the letter pairs
void decrypt(std::string& ciphertext)
{
	int i, a[4] = { -1};
	int ps = (int)ciphertext.size();
	for (i = 0; i < ps; i += 2) {
		search(ciphertext[i], ciphertext[i + 1], a);
		if (a[0] == a[2]) {
			ciphertext[i] = keyT[a[0]][mod5(a[1] - 1)];
			ciphertext[i + 1] = keyT[a[0]][mod5(a[3] - 1)];
		}
		else if (a[1] == a[3]) {
			ciphertext[i] = keyT[mod5(a[0] - 1)][a[1]];
			ciphertext[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
		}
		else {
			ciphertext[i] = keyT[a[0]][a[3]];
			ciphertext[i + 1] = keyT[a[2]][a[1]];
		}
	}
}
// Wrapper function
std::string decryptByPlayfairCipher(std::string& ciphertext, std::string& key)
{
	std::string ans;
	generateKeyTable(key);
	tolowercase(ciphertext);
	ciphertext = removePunctuation(ciphertext);
	if (ciphertext.size() & 1)	ciphertext += "x";
	decrypt(ciphertext);
	return ciphertext;
}

int main()
{
	std::string ciphertext = "TR XYCB MH AFC MUVY EOHPTCS, AFCSS TE QCSI NTYIMS TNA AFCSC.EMRBH XAA VAFR MIUCQPUH LMRL_CCETOT FN HM AKUXAHK. OTA WANAOTXT FFU EISCWNAF HME BFU MCVA UGTOTRE. BM HYLF IFU UVTY ANEHBSEI QYOQM OUVSF AM EAFTE PYHYS XNSKE IFUSC";
	std::string key = "security";
	std::cout << "The key used is " << key << std::endl;

	std::string ans = decryptByPlayfairCipher(ciphertext, key);
	std::cout << "Decrypted text: " << ans << endl;
	std::cout << "The 5x5 key square is:" << std::endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << keyT[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
