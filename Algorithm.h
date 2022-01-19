#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <windows.h>

using namespace std;

struct solution {
	int result;
	vector<int> path;

	bool comparator(const solution& first, const solution& second);
};
class Algorithm {
public:

	bool fileReadLine(ifstream& file, int tab[], int size);

	bool fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix);

	void geneticAlgorithm(vector<vector<int>> weightMatrix, float timeAlg, int sizeOfStartingPopulation, float mutationRate, float crossoverRate, int mutationMethod);
	solution tournamentSelection(vector<solution>& populations);
	int intDraw(int range1, int range2);
	double crossoverMutationDraw(int range1, int range2);
	solution cycleCrossover(solution& maleParent, solution& femaleParent);
	void swapMutation(solution& child);
	void inversionMutation(solution& child);
};