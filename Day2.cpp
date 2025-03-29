
#include "Day2.hpp"




static void print(const int &lineNum,const std::vector<int>& printVals) 
{
	int size = printVals.size();
	std::cout << std::setw(4) << lineNum << " | ";
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(4) << printVals[i];
	}
	if (size < 9) {
		for (int i = 0; i < 9 - size; i++) std::cout << std::setw(4) << ' ';
	}
}

static void getLineOfInts(std::istream& inputStream, std::vector<int>& ints) 
{
	std::string lineString;

	if (std::getline(inputStream, lineString)) {
		std::stringstream lineBuff(lineString);
		int num;

		while (lineBuff >> num) {
			ints.push_back(num);
		}
	}else exit(1);
}

static bool checkPair(const int& val1, const int& val2, const char& order = ' ') // A return value of 1 means it's safe
{
	switch (order) {
	case ' ':
		return 0; // Makes sure order exists
	case 'a':
	case 'A':
		if (val1 > val2) return 0; // Not actually ascending
		break;
	case 'd':
	case 'D':
		if (val1 < val2) return 0; // Not actually descending
		break;
	}

	if (val1 == val2 || val1 - val2 > 3 || val2 - val1 > 3) return 0; // final value check

	else return 1; // safe state
}

static void removeAtIndex(std::vector<int>& originalVals, const int& index) 
{
	std::vector<int> tempVals(originalVals.size() - 1);

	for (int oldi = 0, newi = 0; oldi < originalVals.size(); oldi++, newi++) {
		if (oldi != index) tempVals[newi] = originalVals[oldi];
		else newi--;
	}

	originalVals.pop_back();

	for (int i = 0; i < originalVals.size(); i++) originalVals[i] = tempVals[i];

	tempVals.clear();
	return;
}

bool checkSafe(const int &lineNum, const std::vector<int>& vals) 
{
	char order = ' '; // 'a' will denote ascending, 'd' will denote descending
	print(lineNum, vals);


	// Get order
	if (vals[1] < vals[0]) order = 'd'; //descending
	else if (vals[1] > vals[0]) order = 'a'; //ascending

	// Check element in vector for safety
	for (int i = 0; i < vals.size() - 1; i++) {
		if (!checkPair(vals[i], vals[i + 1], order)) return 0; // not safe
	}

	//print(lineNum, vals); // shows changed values
	return 1; //safe
}


bool checkCanBeSafe(const std::vector<int>& c_vals) 
{
	char order = ' '; // 'a' will denote ascending, 'd' will denote descending
	std::vector<int> vals(c_vals.size());
	bool removedElement = false; // if true an element was removed

	for (int i = 0; i < c_vals.size(); i++) vals[i] = c_vals[i];
	int size = vals.size();


	// Get order
	if (vals[1] < vals[0] && vals[2] < vals[1]) order = 'd'; //descending
	else if (vals[1] > vals[0] && vals[2] > vals[1]) order = 'a'; //ascending


	// Check values
	for (int i = 0; i < size - 1; i++) {
		if (!checkPair(vals[i], vals[i + 1], order)) {
			if (i + 2 < size && !removedElement) {

				if (checkPair(vals[i], vals[i + 2], order)) {
					removeAtIndex(vals, i + 1);
					removedElement = true;
				
					size = vals.size(); // decrease size due to removed element

					i = -1; 
					continue; // restarts the loop to check again
				}
				else if (checkPair(vals[i + 1], vals[i + 2], order)) {
					removeAtIndex(vals, i);
					removedElement = true;

					size = vals.size(); // decrease size due to removed element

					i = -1;
					continue; // restarts the loop to check again
				}
				else return false;

			} 
			else if (i + 2 == size && !removedElement) {
				if (i > 0 && checkPair(vals[i - 1], vals[i + 1], order)) {
					removeAtIndex(vals, i);
					removedElement = true;

					size = vals.size(); // decrease size due to removed element

					i = -1;
					continue; // restarts the loop to check again
				}
				else return true; // the entire array has been checked, the only issue now is the last element
			}
			else return false; // no path leads to safety


		}
	}

	return true; // checked everything after removal and is safe
}

std::vector<std::vector<int>> getVals(const std::string& location, std::vector<std::vector<int>>& listMatrix) {

	std::vector<int> list;
	int num;

	if (location == "test") {
		char testVals[] =
		{ '7', '6', '4', '2', '1', '\n',  // safe
		  '1', '2', '7', '8', '9', '\n',  // unsafe
		  '9', '7', '6', '2', '1', '\n',  // unsafe
		  '1', '3', '2', '4', '5', '\n',  // safe w/ extra constraintsfe
		  '8', '6', '4', '4', '1', '\n',  // safe w/ extra constraints
		  '1', '3', '6', '7', '9', '\n',  // safe
		  '2', '3', '6', '7', '6', '\n',  // safe w/ extra constraints
		  '4', '3', '5', '7', '9', '\n',  // safe w/ extra constraints
		  '1', '3', '2', '5', '9', '\n',  // unsafe
		  '9', '9', '7', '6', '3', '\n',  // safe w/ extra constraints
		  '1', '9', '6', '3', '1', '\n',  // safe w/ extra constraints
		  '4', '6', '7', '9', '9', '\n',  // safe w/ extra constraints
		  '1', '5', '6', '7', '0', '\n'}; // safe w/ extra constraints

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
