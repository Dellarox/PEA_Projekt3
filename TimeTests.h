#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>
#include "Algorithm.h"

using namespace std;

class TimeTests {
public:

	void timeTestsForGA(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix, int sizeOfStartingPopulation, int mutationMethod);
};

