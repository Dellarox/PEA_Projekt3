#include "TimeTests.h"

long long int read_QPCForTimeTests() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForGA(Algorithm a, string fileName, int numberOfCities, vector<vector<int>> weightMatrix) {
	/*srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	double timeOfTest, finalResult = 0, finalTime = 0;
	int result;
	vector<int> path;

	bool checker = a.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	start = read_QPCForTimeTests();
	for (int i = 0; i < 30; i++) {
		timeOfTest = 0;
		a.geneticAlgorithm(weightMatrix, result, path, 60);
		elapsed = read_QPCForTimeTests() - start;
		finalResult += result;
		finalTime += elapsed;
	}

	finalTime = (1.0 * elapsed) / frequency;
	cout << "Usredniony czas testów dla " << numberOfCities << " miast w [s]: " << finalTime / 30 << "." << endl;
	cout << "Usredniona droga dla " << numberOfCities << " miast: " << finalResult / 30 << "." << endl;*/
}
