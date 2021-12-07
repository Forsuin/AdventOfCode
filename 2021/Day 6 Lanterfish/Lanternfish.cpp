#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//#define TEST

std::vector<unsigned long long> LanterfishArr(9);

void update() {
	unsigned long long temp;
	temp = LanterfishArr[0];

	for (int i = 1; i < LanterfishArr.size(); i++) {
		LanterfishArr[i - 1] = LanterfishArr[i];
	}

	LanterfishArr[8] = temp;
	LanterfishArr[6] += temp;
}

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
			LanterfishArr[std::stoll(inString.substr(0, pos))]++;

			inString.erase(0, pos + delimiter.length());
		}
		LanterfishArr[std::stoll(inString.substr(0, pos))]++;
	}
	input.close();
}

int main() {
	int numDays = 0;

#ifdef TEST
	LanterfishArr[3]++;
	LanterfishArr[4]++;
	LanterfishArr[3]++;
	LanterfishArr[1]++;
	LanterfishArr[2]++;
#endif

	ReadInput();

#ifdef TEST
	std::cout << "Initial State: ";
	for (unsigned long long c : LanterfishArr) {
		std::cout << c << ",";
	}
	std::cout << std::endl;
#endif

	while (numDays != 256) {
		update();
		numDays++;
#ifdef TEST
		std::cout << "After " << (numDays < 10 ? " " : "") << numDays << (numDays == 1 ? " day:  " : " days: ");
		for (unsigned long long c : LanterfishArr) {
			std::cout << c << ",";
		}
		std::cout << std::endl;
#endif
	}

	unsigned long long totalSize = 0;

	for (unsigned long long ll : LanterfishArr) {
		totalSize += ll;
	}

	std::cout << "Number of fish: " << totalSize << std::endl;

	std::cin.get();
}