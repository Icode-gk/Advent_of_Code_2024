
#include "Day2.hpp"




static void print(const int &lineNum,const std::vector<int>& printVals) {
	int size = printVals.size();
	std::cout << std::setw(4) << lineNum << " | ";
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(4) << printVals[i];
	}
	if (size < 9) {
		for (int i = 0; i < 9 - size; i++) std::cout << std::setw(4) << ' ';
	}
}

static void getLineOfInts(std::istream& inputStream, std::vector<int>& ints) {
	std::string lineString;

	if (std::getline(inputStream, lineString)) {
		std::stringstream lineBuff(lineString);
		int num;

		while (lineBuff >> num) {
			ints.push_back(num);
		}
	}else exit(1);
}

static bool checkPair(const int& val1, const int& val2, const char& order) // A return value of 1 means it's safe
{

	if (order == ' ' || !val2 || !val1) return 0; // Makes sure values exist

	if ((val1 == val2) ||
		(order == 'a' && val1 > val2) ||
		(order == 'd' && val1 < val2) ||
		val1 - val2 > 3 || 
		val2 - val1 > 3) 
		
		return 0; // unsafe state

	return 1; // safe state
}


bool checkSafe(const int &lineNum, const std::vector<int>& vals) {
	char order = ' '; // 'a' will denote ascending, 'd' will denote descending
	print(lineNum, vals);
	if (vals[1] - vals[0] > 3 || vals[0] - vals[1] > 3 || vals[1] == vals[0]) ; //immediate unsafe check
	else if (vals[0] > vals[1]) order = 'd'; //descending
	else if (vals[1] > vals[0]) order = 'a'; //ascending



	for (int i = 1; i < vals.size() - 1; i++) {
		if (!checkPair(vals[i], vals[i + 1], order)) return 0;

	};

	return 1; //safe
}

std::vector<std::vector<int>> getVals(const std::string& location, std::vector<std::vector<int>>& listMatrix) {

	std::vector<int> list;
	int num;

	if (location == "test") {
		char testVals[36] = { '7', '6', '4', '2', '1', '\n',
			'1', '2', '7', '8', '9', '\n',
			'9', '7', '6', '2', '1', '\n',
			'1', '3', '2', '4', '5', '\n',
			'8', '6', '4', '4', '1', '\n',
			'1', '3', '6', '7', '9', '\n' };

		for (int i = 0; i < sizeof(testVals); i++) {
			if (testVals[i] == '\n') {
				listMatrix.push_back(list);
				list.clear();
				std::cout << '\n';
				continue;
			}
			else {
				num = testVals[i] - '0';
				std::cout << num << ' ';
				list.push_back(num);
			}
		}
	}
	else {
		std::ifstream ifs(location);


		if (!ifs.is_open()) {
			std::cerr << "Not a valid file\n";
			return listMatrix;
		}

		else {
			std::stringstream lineSS;
			std::string line;

			while (ifs.peek() != std::ifstream::traits_type::eof()) {
				getLineOfInts(ifs, list);
				listMatrix.push_back(list);
				list.clear();
			}
		}
	}

	std::cout << "-------------\n\n";
	return listMatrix;
}
