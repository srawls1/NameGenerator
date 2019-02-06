// NameGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MarkovChain.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

static std::string characters = " abcdefghijklmnopqrstuvwxyz`"; // We'll use 0 to represent the beginning or end of a name in this case

char toLowerCase(char arg)
{
	static int dif = 'a' - 'A';
	if (arg >= 'A' && arg <= 'Z')
	{
		return arg + dif;
	}
	return arg;
}

char toUpperCase(char arg)
{
	static int dif = 'A' - 'a';
	if (arg >= 'a' && arg <= 'z')
	{
		return arg + dif;
	}
	return arg;
}

void normalizeToProbabilities(Matrix& frequencies)
{
	for (int col = 0; col < frequencies.numColumns(); ++col)
	{
		float columnTotal = 0.f;
		for (int row = 0; row < frequencies.numRows(); ++row)
		{
			columnTotal += frequencies.getAt(row, col);
		}

		if (columnTotal == 0.f)
		{
			float probability = 1.f / frequencies.numRows();
			for (int row = 0; row < frequencies.numRows(); ++row)
			{
				frequencies.setAt(row, col, probability);
			}
		}
		else
		{
			for (int row = 0; row < frequencies.numRows(); ++row)
			{
				frequencies.setAt(row, col, frequencies.getAt(row, col) / columnTotal);
			}
		}
	}
}

Matrix readTransitionProbabilities(std::istream& in)
{
	std::string sampleName;

	Matrix frequencies(characters.length(), characters.length());

	while (in >> sampleName)
	{
		int previousState = 0;
		for (int i = 0; i < sampleName.length(); ++i)
		{
			int currentState = characters.find(toLowerCase(sampleName[i]));
			frequencies.setAt(currentState, previousState, frequencies.getAt(currentState, previousState) + 1.f);
			previousState = currentState;
		}
		frequencies.setAt(0, previousState, frequencies.getAt(0, previousState) + 1.f);
	}

	normalizeToProbabilities(frequencies);
	return frequencies;
}

std::string generateName(MarkovChain& chain)
{
	std::string result = "";
	chain.transitionStates();
	while (chain.getCurrentState() != 0)
	{
		result += characters[chain.getCurrentState()];
		chain.transitionStates();
	}
	result[0] = toUpperCase(result[0]);
	return result;
}

bool containsVowels(std::string& str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (toLowerCase(str[i]) == 'a' ||
			toLowerCase(str[i]) == 'e' ||
			toLowerCase(str[i]) == 'i' ||
			toLowerCase(str[i]) == 'o' ||
			toLowerCase(str[i]) == 'u' ||
			(i > 0 && toLowerCase(str[i]) == 'y'))
		{
			return true;
		}
	}
	
	return false;
}

std::string getNameWithVowelsAndMinimumLength(MarkovChain& chain)
{
	while (true)
	{
		std::string result = generateName(chain);
		if (result.length() > 0 && containsVowels(result))
		{
			return result;
		}
	}
}

void seedRandom()
{
	int seed;
	std::cout << "Enter a random seed. Enter a negative number to use the default" << std::endl;
	std::cin >> seed;
	if (seed < 0)
	{
		seed = time(NULL);
	}
	srand(seed);
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << "Usage: .\\NameGenerator.exe <sample name file>" << std::endl;
		return 1;
	}

	seedRandom();

	std::ifstream in(argv[1]);
	Matrix probabilities = readTransitionProbabilities(in);
	MarkovChain chain(probabilities.numColumns(), 0, probabilities);

	char input[2];
	std::cout << "Press enter to get a name. Type anything and press enter to quit" << std::endl;
	while (std::cin.getline(input, 2) && strlen(input) == 0)
	{
		std::string name = getNameWithVowelsAndMinimumLength(chain);
		std::cout << name << std::endl;
	}
    return 0;
}

