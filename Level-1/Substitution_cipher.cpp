#include <bits/stdc++.h>
std::string ciphertext = "";
std::string plaintext = "";
std::map<char, char> ciphermap;
std::map<char, int> frequency;
void substitution()
{
	for (int i = 0; i < 26; i++)
	{
		char a, b;
		std::cin >> a >> b;
		if (std::islower(a))
		{
			a = std::toupper(a);
		}
		ciphermap[a] = b;
	}
}
int main()
{
	// add a extra " #"  without quotes at the end of the ciphertext to the input
	while (1)
	{
		std::string ch;
		std::cin >> ch;
		if (ch != "#")
		{
			ciphertext += ch;
			ciphertext += " ";
		}
		else
			break;
	}
	// conversion of each letter to upeercase
	std::transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), [&](char ch) -> char {
		if (not isalpha(ch))
			return ch;
		if (std::islower(ch))
		{
			return std::toupper(ch);
		}
		return ch;
	});

	// Count the frequency of each element in the string and storing it in frequency map
	for (auto i : ciphertext)
	{
		if (not isalpha(i))
			continue;
		frequency[i]++;
	}
	// Function call to take the substitution key for the text
	// If a letter is not present in the ciphertext, map it to itself
	substitution();

	// Converting the text to actual letter using the mapping ciphermap
	for (auto &i : ciphertext)
	{
		if (ciphermap.find(i) != ciphermap.end())
		{
			i = ciphermap[i];
		}
	}
	// Output of the plaintext
	std::cout << ciphertext << std::endl;

	// Output of the frequency of each alphabet
	for (auto element : frequency)
	{
		std::cout << element.first << "-->" << element.second << std::endl;
	}

	return 0;
}
