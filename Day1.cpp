
#include "Day1.hpp"


int getDistance(int& num1, int& num2) {
	int result = num2 - num1;

	if (result <= 0) result *= -1;

	return result;
}

bool getData(std::vector<int>& listA, std::vector<int>& listB, const std::string &txtFile) {
	std::ifstream ifs;
	int numberTemp, index = 0;
	ifs.open(txtFile);

	if (!ifs.is_open()) {
		std::cerr << "File could not open";
		return 0;
	}

	while (ifs >> numberTemp) {
		if (index++ % 2 == 0) {
			listA.push_back(numberTemp);
			//std::cout << numberTemp << ' ';
		}
		else {
			listB.push_back(numberTemp);
			//std::cout << numberTemp << '\n';
		}
	}

	return 1;
}
