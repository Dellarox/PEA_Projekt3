#include "TimeTests.h"

long long int read_QPCForTimeTests() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForGA(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix, int sizeOfStartingPopulation, int mutationMethod) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	double timeOfTest, finalResult = 0, finalTime = 0;

	bool checker = a.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	start = read_QPCForTimeTests();

	cout << "wielkoœæ: " << numberOfCities << ", czas: 100, populacja: " << sizeOfStartingPopulation << ", mutacja(1 - inv, 2 - swap, 3 - mieszana) : " << mutationMethod << ", wynik : (wypisany ponizej)." << endl;

	for (int i = 0; i < 4; i++) 
		a.geneticAlgorithm(weightMatrix, 100, sizeOfStartingPopulation, 0.01, 0.8, mutationMethod);
}
