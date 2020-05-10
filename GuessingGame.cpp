// Guessing Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <unordered_map>

//Prototyping
void game();
int countVowels(std::string word);
std::vector<std::string> parseFile(std::string path);

//Program Entry point
int main()
{
	srand(time(0));
	game();
}

//The game operating function
void game()
{
	//Variable Declaration
	int attempts = 0, index, vowelCount, consonantCount, wordLength;
	char buffer = '*', input;
	bool gameOver = false, incorrectGuess = false;
	std::string path = "words.txt", word, masked;

	//Assigning variables
	std::vector<std::string> wordBank = parseFile(path);
	index = rand() % wordBank.size();
	word = wordBank.at(index);
	wordLength = word.length();
	vowelCount = countVowels(word);
	consonantCount = wordLength - vowelCount;
	masked = std::string(word.length(), '*');

	//Prompt
	std::cout << "Word to guess " << masked << std::endl;
	std::cout << "Hint: The word contains " << vowelCount << " vowels and " << consonantCount << " consonants" << std::endl;

	//Game logic
	while (!gameOver)
	{
		std::cout << "enter a letter: ";
		std::cin >> input;
		
		incorrectGuess = true; //Assume the input is incorrect until proven otherwise

		for (int i = 0; i < masked.length(); i++)
		{
			if (input == toupper(word.at(i)) || input == tolower(word.at(i)))
			{
				masked[i] = input;
				incorrectGuess = false;
			}
		}

		std::cout << masked << std::endl;

		if (masked == word)
		{
			gameOver = true;
			std::cout << "you win!" << std::endl;
		}

		if (incorrectGuess)
		{
			attempts++;

			if (attempts >= wordLength * 2)
			{
				std::cout << "you lose\n The word was " << word << std::endl;
				gameOver = true;
			}
		}
	}
}

std::vector<std::string> parseFile(std::string path)
{
	std::ifstream in(path);
	std::vector<std::string> wordBank;
	std::string parsed;
	while (std::getline(in, parsed))
	{
		wordBank.insert(wordBank.begin(), parsed);
	}
	return wordBank;
}

int countVowels(std::string word)
{
	std::unordered_map<char, int> vowelMap;
	
	int count = 0;

	for (char c : word)
	{
		switch (c)
		{
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			if (vowelMap[c] < 1)
			{
				count++;
				vowelMap[c]++;
			}
		default:
			break;
		}
	}

	return count;
}


