#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <format>
#include <math.h>

#define TEST


struct Line {
	int x1, y1;
	int x2, y2;

	std::string toString() const {
		return std::format("({}, {}) -> ({}, {})", x1, y1, x2, y2);
	}
};

struct Point {
	short overlaps = 0;
};

Line ParseInput(std::string input) {
	Line line;
	sscanf_s(input.c_str(), "%d,%d %*s %d,%d", &line.x1, &line.y1, &line.x2, &line.y2);
	return line;
}

void ReadInput(std::vector<Line>& output) {
	std::ifstream input;
#ifdef TEST
	input.open("inputTest.txt", std::ios::in);
#else
	input.open("input.txt", std::ios::in);
#endif
	if (input.is_open()) {
		std::string temp;
		while (std::getline(input, temp)) {
			output.push_back(ParseInput(temp));
		}
	}
	input.close();
}

void PrintGrid(short size, std::vector<std::vector<Point>>& pointArr){
#ifndef TEST
	return;
#endif // !TEST
	std::cout << "\nOverlap Count" << std::endl;
	for (short y = 0; y < size + 1; y++) {
		for (short x = 0; x < size + 1; x++) {
			std::cout << (pointArr.at(x).at(y).overlaps == 0 ? "." : std::to_string(pointArr.at(x).at(y).overlaps)) << ' ';
		}
		std::cout << std::endl;
	}
}

void PrintGrid(short size, std::vector<std::vector<Point>>& pointArr, const char* str) {
#ifndef TEST
	return;
#endif // !TEST

	std::cout << "\nOverlap Count" << std::endl;
	std::cout << str << std::endl;
		for (short y = 0; y < size + 1; y++) {
			for (short x = 0; x < size + 1; x++) {
				std::cout << (pointArr.at(x).at(y).overlaps == 0 ? "." : std::to_string(pointArr.at(x).at(y).overlaps)) << ' ';
			}
			std::cout << std::endl;
		}
}

void PrintCoord(short size, std::vector<std::vector<Point>>& pointArr) {
#ifdef TEST
	std::cout << "Coords of each point" << std::endl;
	for (short y = 0; y < size + 1; y++) {
		for (short x = 0; x < size + 1; x++) {
			std::cout << "(" << x << ", " << y << ") ";
		}
		std::cout << std::endl;
	}
#endif
}

bool isDiagonal(const Line& line) {
	return (abs(line.x1 - line.x2) == abs(line.y1 - line.y2));
}

int main() {
	std::vector<Line> lineArr;
	ReadInput(lineArr);

	short size;

#ifdef TEST
	size = 9;
#else
	size = 1000;
#endif // TEST


	std::vector<std::vector<Point>> pointArr(size + 1);

	for (short x = 0; x < size + 1; x++) {
		for (short y = 0; y < size + 1; y++) {
			pointArr.at(x).push_back({ 0 });
		}
	}

	//std::cout << "The size of pointArr in bytes is " << sizeof(Point) * size * size << std::endl;

	PrintCoord(size, pointArr);

	for (const Line& line : lineArr) {
		if (line.x1 == line.x2) {
			//vertical lines

			//moving up in the graph
			if (line.y2 > line.y1) {
				for (short i = (line.y1 == 0 ? 0 : line.y1); i <= line.y2; i++) {
					pointArr[line.x1][i].overlaps++;
				}
				PrintGrid(size, pointArr, line.toString().c_str());
			}

			//moving down in the graph
			else if (line.y1 > line.y2) {
				for (short i = (line.y2 == 0 ? 0 : line.y2); i <= line.y1; i++) {
					pointArr[line.x1][i].overlaps++;
				}
				PrintGrid(size, pointArr, line.toString().c_str());
			}
		}
		else if (line.y1 == line.y2) {
			//horizontal line

			//moving right across the graph
			if (line.x2 > line.x1) {
				for (short i = line.x1; i <= line.x2; i++) {
					pointArr[i][line.y1].overlaps++;
				}
				PrintGrid(size, pointArr, line.toString().c_str());
			}

			//moving left across the graph
			else if (line.x1 > line.x2) {
				for (short i = (line.x2 == 0 ? 0 : line.x2); i <= line.x1; i++) {
					pointArr[i][line.y1].overlaps++;
				}
				PrintGrid(size, pointArr, line.toString().c_str());
			}
		}
		else if(isDiagonal(line)){
			//any 45 degree line
			//the origin of the line is assumed to be x1, y1 for simplicity
			if (line.x1 > line.x2) {
				//point left

				if (line.y1 > line.y2) {
					//point up

					for (short x = line.x2, y = line.y2; x <= line.x1 && y <= line.y1; x++, y++) {
						pointArr[x][y].overlaps++;
					}
					PrintGrid(size, pointArr, line.toString().c_str());
				}
				else {
					//point down
					for (short x = line.x1, y = line.y1; x >= line.x2 && y <= line.y2; x--, y++) {
						pointArr[x][y].overlaps++;
					}
					PrintGrid(size, pointArr, line.toString().c_str());
				}
			}
			else {
				//point right

				if (line.y1 > line.y2) {
					//point up

					for (short x = line.x2, y = line.y2; x <= line.x1 && y <= line.y1; x++, y++) {
						pointArr[x][y].overlaps++;
					}
					PrintGrid(size, pointArr, line.toString().c_str());
				}
				else {
					//point down
					for (short x = line.x1, y = line.y1; x >= line.x2 && y <= line.y2; x--, y++) {
						pointArr[x][y].overlaps++;
					}
					PrintGrid(size, pointArr, line.toString().c_str());
				}
			}
			
		}
	}

	PrintGrid(size, pointArr);

	int numDangerous = 0;
	for (std::vector<Point> arr: pointArr) {
		for (const Point& point : arr) {
			if (point.overlaps >= 2) {
				numDangerous++;
			}
		}
	}

	std::cout << "Number of dangerous spots: " << numDangerous << std::endl;

	std::cin.get();
}