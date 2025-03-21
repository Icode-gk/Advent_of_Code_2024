#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <array>

#ifndef DAY2_H
#define DAY2_H
// Day 2
bool checkSafe(const int&, const std::vector<int>&);
std::vector<std::vector<int>> getVals(const std::string&, std::vector<std::vector<int>>&);
#endif