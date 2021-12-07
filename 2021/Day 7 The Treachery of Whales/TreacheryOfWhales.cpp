#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<unsigned short> arr;

void ReadInput() {
	size_t pos = 0;
	std::string token;
	std::string delimiter = ",";

	std::ifstream input;
	input.open("input.txt", std::ios::in);
	if (input.is_open()) {
		std::string inString;
		std::getline(input, inString);
		while ((pos = inString.find(delimiter)) != std::string::npos) {
			arr.push_back(std::stoi(inString.substr(0, pos)));

			inString.erase(0, pos + delimiter.length());
		}
		arr.push_back(std::stoi(inString.substr(0, pos)));
	}
	input.close();
}

int main() {
	unsigned int minFuelUsage = UINT32_MAX;

	ReadInput();

	unsigned short largestNum = 0;

	for (unsigned short i : arr) {
		if (i > largestNum) {
			largestNum = i;
		}
	}

	std::cout << "Largest Number: " << largestNum << std::endl;



	for (unsigned short i = 0; i < largestNum; i++) {
		unsigned int currentFuelUsage = 0;

		//Part 1
		// 
		//for (unsigned short num : arr) {
		//	currentFuelUsage += abs(num - i);
		//}
		//if (currentFuelUsage < minFuelUsage) {
		//	minFuelUsage = currentFuelUsage;
		//}

		//Part 2
		for (unsigned short num : arr) {
			int distance = abs(num - i);
			for (int j = 0; j < distance; j++) {
				currentFuelUsage += j + 1;
			}
		}
		if (currentFuelUsage < minFuelUsage) {
			minFuelUsage = currentFuelUsage;
		}


		//std::cout << "Number to move to: " << i << ", Total Fuel Usage: " << currentFuelUsage << std::endl;
	}

	std::cout << "Min fuel usage is: " << minFuelUsage << std::endl;

	std::cin.get();
}