#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Part 1 
//foward X- increases horizontal position by X units
//down X - increases depth by X
//up X - decreases depth by X


//Part 2
//forward X - increases horizontal position by X units and increases depth by aim * X
//down X - increases aim by X
//up X - decreases aim by X


struct Position {
	int horizontal;
	int depth;
	int aim;

	Position() : horizontal(0), depth(0), aim(0){}
};

void ReadInput(std::vector<std::string>& output) {
	std::ifstream input;

	input.open("input.txt", std::ios::in);
	if (input.is_open()) {
		std::string temp;
		while (std::getline(input, temp)) {
			output.push_back(temp);
		}
	}

	input.close();
}

void ParseInput(std::vector<std::string> input, Position& location) {
	size_t pos = 0;
	std::string token;
	std::string delimiter = " ";

	for (std::string str : input) {
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);

			str.erase(0, pos + delimiter.length());
		}

		if (token == "forward") {
			location.horizontal += std::stoi(str);
			location.depth += location.aim * std::stoi(str);
		}
		else if (token == "up") {
			location.aim -= std::stoi(str);
		}
		else {
			location.aim += std::stoi(str);
		}
	}
}

int main() {
	Position pos;

	std::vector<std::string> stringArr;

	ReadInput(stringArr);
	ParseInput(stringArr, pos);

	std::cout << "Horizontal: " << pos.horizontal << std::endl;
	std::cout << "Depth: " << pos.depth << std::endl;
	std::cout << "Multiplied depth * horizontal: " << pos.horizontal * pos.depth << std::endl;


	std::cin.get();
}