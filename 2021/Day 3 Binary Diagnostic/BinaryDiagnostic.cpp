#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <list>
#include <ranges>
#include <algorithm>

//Input is a list of binary numbers which need to be decoded

//First parameter to check is power consumption
//Use binary numbers from input to generate two new binary numbers: gamma rate and epsilon rate
//Power consumption == gamma rate * epsilon rate
//Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of input
// Given the following input: 
//	00100
//	11110
//	10110
//	10111
//	10101
//	01111
//	00111
//	11100
//	10000
//	11001
//	00010
//	01010
//The first bit of the gamma rate is 1, second is 0, etc. Gamma rate == 10110 or 22
//Epsilon rate is found by finding the least common bit
//Epsilon == 01001 or 9
//Power consumption is gamma (22) * epsilon (9) = 198

void readInput(std::vector<std::string>& output) {
	//read binary from input file
	std::ifstream input;
	input.open("input.txt", std::ios::in);	//Remember to change
	if (input.is_open()) {
		std::string temp;
		while (std::getline(input, temp)) {
			output.push_back(temp);
		}
	}
	input.close();
}

int findPowerConsumption(std::vector<std::string>& inputArr) {
	short twelveBit = 0b000000000000;

	short gammaRate = twelveBit;		//Remember to change
	short epsilonRate = twelveBit;	//Remember to change
	std::vector<short> mostCommonDigit(12);	//Remember to change

		//loop through each input binary and count the number of 1s that appear
	for (std::string str : inputArr) {
		for (short i = 0; i < str.length(); i++) {
			if (str[i] == '1') {
				mostCommonDigit[i]++;
			}
		}
	}

	std::cout << "Most Common Digits: " << std::endl;
	for (short i : mostCommonDigit) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::cout << "Gamma Rate: " << std::endl;
	for (short i : mostCommonDigit) {
		if (i > 500) {	//Remember to change
			gammaRate = (gammaRate++) << 1;
			std::bitset<12> x(gammaRate);	//Remember to change
			std::cout << x << std::endl;
		}
		else {
			gammaRate = gammaRate << 1;
			std::bitset<12> x(gammaRate);	//Remember to change
			std::cout << x << std::endl;
		}
	}

	epsilonRate = gammaRate ^ 0b0000'1111'1111'1111;
	std::cout << "Bitflipped last 12 bits" << std::endl; //Remember to change
	std::bitset<16> x(epsilonRate);
	std::cout << x << std::endl;

	return gammaRate * epsilonRate;
}

//Returns the most frequently occuring value in column column
char findMostCommonValue(std::list<std::string>& inputArr, char column) {
	short countOfOnes = 0;

	for (std::string str : inputArr) {
		if (str[column] == '1') {
			countOfOnes++;
		}
	}

	if (countOfOnes == inputArr.size() / 2) {
		return -1;
	}
	else if (countOfOnes > inputArr.size() / 2) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
	life support rating = oxygenGeneratorRating * CO2ScrubberRating
	O2 and CO2 can be found in diagnostic report- input array
	Consider just the first bit of numbers:
		Keep only numbers selected by the bit criteria for the type of rating being searched for.
		If only one number is left, stop; that is the rating value being searched for
		Otherwise, repeat the process, considering the next bit to the right
	Bit Criteria depends on which rating value trying to be found
		Oxygen Generator Rating
			determine the most common value in the current bit position, and keep only numbers with that bit in that position
			If 0 and 1 are equally common, keep values with a 1 in the position being considered
		CO2 Scrubber Rating
			determine the least common value in the current bit position, and keep only numbers that bit in the position
			IF 0 and 1 are equally common, keep values with a 0 in the position

	00100
	11110	11110
	10110	10110	10110	10110	10110
	10111	10111	10111	10111	10111	10111
	10101	10101	10101	10101
	01111
	00111
	11100	11100
	10000	10000	10000
	11001	11001
	00010
	01010

	To find the O2 rating using the above values:
		Consider only the first bit of each number- there are 7 1-bits and 5 0-bits, so keep only the 7 numbers with a 1 in the first position
		Then, consider the second bit of the 7 remaining numbers- there are 4 0-bits and 3 1-bits, so keep only the 4 numbers with a 0 in the second position
		In the third position, there are 3 1-bits and 1 0-bits, so keep the 3 1-bit numbers
		In the fourth position, 2 1-bits and 1 0-bit
		Fifth, there are equal 0-bit and 1-bit, so for finding the O2 rating keep the 1-bit number
		As there is only 1 number left, stop and set the O2 rating to 10111 or 23

	Finally, to find the life support rating, multiply O2 (23) by CO2 (10) to get 230
	*/

int findOxygenRating(std::vector<std::string>& inputArr) {
	std::list<std::string> temp;

	for (std::string str : inputArr) {
		temp.push_back(str);
	}

	char column = 0;
	char mostCommonValue;

	//loop over each column until 1 element remains
	for (int i = 0; temp.size() > 1 && i < 12; i++) {
		mostCommonValue = findMostCommonValue(temp, i);
		if (mostCommonValue == -1) {
			//keep all elements that have a 1 at j'th column
			for (const std::string& str : temp) {
				if (str[i] != '1') {
					temp.remove(str);
				}
			}
		}
		else {
			for (int j = temp.size(); j >= 0; --j) {
				if(temp.)
			}
		}
	}
	return std::stoi(temp.front());
}

int findCarbDioxRating(std::vector<std::string>& inputArr) {
	std::list<std::string> temp;

	for (std::string str : inputArr) {
		temp.push_back(str);
	}

	for (char i = 0; i < 12; i++) {
		char mostCommonValue = findMostCommonValue(temp, i);
		if (mostCommonValue == -1) {
			//keep all elements that have a 0 at j'th column
			for (std::string str : temp) {
				if (str[i] != '0') {
					temp.remove(str);
				}
			}
		}
		else {
			//keep the least common value
			for (std::string str : temp) {
				if (str[i] != (mostCommonValue == 0 ? '1' : '0')) {
					temp.remove(str);
				}
			}
		}
	}

	return std::stoi(temp.front());
}

int findLifeSupportRating(std::vector<std::string>& inputArr) {
	return findOxygenRating(inputArr) * findCarbDioxRating(inputArr);
}

int main() {
	int powerConsumption;
	int lifeSupportRating;
	std::vector<std::string> binaryArr;

	readInput(binaryArr);
	powerConsumption = findPowerConsumption(binaryArr);
	lifeSupportRating = findLifeSupportRating(binaryArr);

	std::cout << "Power Consumption: " << powerConsumption << std::endl;
	std::cout << "Life Support Rating: " << lifeSupportRating << std::endl;

	std::cin.get();
}