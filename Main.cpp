#include "Header.hpp"


void day1();
void day2(std::string&);

int main() {
	std::string file = "Day2.txt";

	day2(file);


	return 0;
}




// Day 1 Code
void day1() {
	std::vector<int> listA = {}, listB = {};
	long int distance = 0, similarity = 0;

	if (!getData(listA, listB, "Day1_Puzzle1_data.txt")) std::cerr << "Could not fetch data";

	if (listA.size() == listB.size()) {
		std::sort(listA.begin(), listA.end());
		std::sort(listB.begin(), listB.end());

		for (int i = 0; i < listA.size(); i++) {
			distance += getDistance(listA[i], listB[i]);
			similarity += listA[i] * std::count(listB.begin(), listB.end(), listA[i]);
			//std::cout << listA[i] << ' ' << listB[i] << '\n';
		}
	}

	std::cout << "\nTotal Distance is : " << distance << "\nSimilarity Score is: " << similarity << '\n';


	return;
}




// Day 2 Code
void day2(std::string &file) {
	std::vector<std::vector<int>> listMatrix;
	int numSafe = 0;

	getVals(file, listMatrix);

	for (int i = 0; i < listMatrix.size(); i++) {
		//if (i == 7) {
		//	std::cout << "breakpoint\n"; // Debug point
		//}

		if (checkSafe((i + 1), listMatrix[i])) {
			std::cout << ": safe\n";
			numSafe++;
		}
		else if (checkCanBeSafe(listMatrix[i])) {
			std::cout << ": safe\n";
			numSafe++;
		}
		else std::cout << ": unsafe\n";

	}

	std::cout << "Total Safe: " << numSafe << std::endl;

	return;
}
