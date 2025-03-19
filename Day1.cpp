#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

void sort(std::vector<int>& vec, const int &size) {
	for (int i = 0; i < size; i++) {
		bool swapped = 1;
		for (int j = 0; j < size - (i + 1); j++) {
			if (vec[j] > vec[j + 1]) {
				int swap = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = swap;
				swapped = 1;
			}
		}

		if (!swapped) return;
	}

	return;
}

int getDistance(int &num1, int &num2) {
	int result = num2 - num1;

	if (result <= 0) result *= -1;

	return result;
}

bool getData(std::vector<int>& listA, std::vector<int>& listB, const std::string txtFile) {
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


int main() {
	std::vector<int> listA = {}, listB = {};
	long int distance = 0, similarity = 0;

	if (!getData(listA, listB, "Day1_Puzzle1_data.txt")) std::cerr << "Could not fetch data";

	if (listA.size() == listB.size()) {
		sort(listA, listA.size());
		sort(listB, listB.size());

		for (int i = 0; i < listA.size(); i++) {
			distance += getDistance(listA[i], listB[i]);
			similarity += listA[i] * std::count(listB.begin(), listB.end(), listA[i]);
			//std::cout << listA[i] << ' ' << listB[i] << '\n';
		}
	}

	std::cout << "\nTotal Distance is : " << distance << "\nSimilarity Score is: " << similarity << '\n';


	return 0;
}