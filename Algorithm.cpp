#include "Algorithm.h"

bool comparator(const solution& first, const solution& second)
{
	if (first.result < second.result)
		return true;
	else
		return false;
}

long long int read_QPCForAlgorithm() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

bool Algorithm::fileReadLine(ifstream& file, int tab[], int size) {
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}

bool Algorithm::fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix) {
	ifstream file;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			weightMatrix.clear();
			weightMatrix.resize(0);

			numberOfCities = tabNumberOfCities[0]; // przypisanie ilosci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Ilosc miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie wartosci do vectora
				}
			}
		}
		else
			cout << "File error - READ INFO" << endl;
		file.close();
		return false;
	}
	else
		cout << "File error - OPEN" << endl;

	return false;
}

int pathLenght(vector<vector<int>> weightMatrix, vector<int> path) { // funkcja obliczajaca dlugosc sciezki
	int lenght = 0;

	for (int i = 0; i < path.size() - 1; i++)
		lenght += weightMatrix[path[i]][path[i + 1]];

	lenght += weightMatrix[path[path.size() - 1]][path[0]];
	return lenght;
}

void Algorithm::geneticAlgorithm(vector<vector<int>> weightMatrix, float timeAlg,
								int sizeOfStartingPopulation, float mutationRate, float crossoverRate, int mutationMethod) {

	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPCForAlgorithm();
	srand(unsigned(time(NULL)));

	vector<solution> populations; // wektor przechowuj¹cy wszystkie rozwi¹zania (chromosomy)

	for (int i = 0; i < sizeOfStartingPopulation; i++) { // pêtla odpowiadaj¹ca za wpisanie wszystkich miast do wektora wszystkich rozwi¹zañ i ich przelosowanie w tym wektorze
		solution population; // wektor pomocniczy przechowuj¹cy jedno rozwi¹zanie
		for (int j = 0; j < weightMatrix.size(); j++)
			population.path.push_back(j);

		populations.push_back(population);
		random_shuffle(populations[i].path.begin(), populations[i].path.end());
	}

	while (((float)elapsed / frequency) < timeAlg) { // pêtla trwaj¹ca dopóki nie minie czas, który zosta³ podany do wykonania algorytmu

		for (int i = 0; i < populations.size(); i++) // pêtla obliczaj¹ca tzw. "fitness", czyli "wartoœæ" chromosomu, w naszym przypadku jest to d³ugoœæ ka¿dej œcie¿ki
			populations[i].result = pathLenght(weightMatrix, populations[i].path);

		vector<solution> newPopulations;

		sort(populations.begin(), populations.end(), comparator); // sortuje w celu wykonania "elitaryzmu"
		for (int i = 0; i < populations.size() / 10; i++) // tutaj zastosowany jest tzw. elitaryzm, czyli czesc najlepszych osobnikow z poprzedniej populacji jest zostawiana do nowej populacji
			newPopulations.push_back(populations[i]);
		

		while(newPopulations.size() < sizeOfStartingPopulation){ // pêtla wyznaczaj¹ca nowe populacje
			// wykorzystana zostanie metoda turniejowa w celu wyznaczenia "rodzicow"

			solution maleParent = tournamentSelection(populations), femaleParent = tournamentSelection(populations);

			// kolejnym etapem jest skrzyzowanie "rodzicow", w wyniku ktorego pojawia sie dzieci

			solution child1 = maleParent, child2 = femaleParent; // tworzê "dzieci" i przypisuje im cechy "rodzicow"

			double drawForCrossover = crossoverMutationDraw(0, 1); // losujemy liczbê

			if (drawForCrossover < crossoverRate) { // i sprawdzamy czy wykonamy krzyzowanie
				child1 = cycleCrossover(femaleParent, maleParent);
				child2 = cycleCrossover(femaleParent, maleParent);
			} // jezeli krzyzwowanie wykonamy to tworza sie nowe cechy "dzieci", jezeli nie to "stare dzieci" zostaja

			double drawForMutationForFirstChild = crossoverMutationDraw(0, 1); // losujemy liczbê

			if (drawForMutationForFirstChild < mutationRate) { // mutowanie pierwszego dziecka
				if (mutationMethod == 1)
					inversionMutation(child1);
				else if (mutationMethod == 2) {
					swapMutation(child1);
				}
				else
					inversionMutation(child1);
				newPopulations.push_back(child1);
			}

			double drawForMutationForSecondChild = crossoverMutationDraw(0, 1);

			if (drawForMutationForSecondChild < mutationRate) { // mutowanie drugiego dziecka
				if (mutationMethod == 1)
					inversionMutation(child2);
				else if (mutationMethod == 2) {
					swapMutation(child1);
				}
				else
					swapMutation(child2);
				newPopulations.push_back(child2);
			}

			populations = newPopulations; // przypisanie nowej populacji jako aktualnej

			elapsed = read_QPCForAlgorithm() - start;
		}

		for (int i = 0; i < populations.size(); i++) // liczymy droge dla kazdego rozwiazania
			populations[i].result = pathLenght(weightMatrix, populations[i].path);	
	}
	
	sort(populations.begin(), populations.end(), comparator); // sortuje rozwiazania 

	cout << "Najlepsza droga: " << endl; // wypisanie wyników
	for (int j = 0; j < populations[0].path.size() -1; j++) {
		cout << populations[0].path[j] << "->";
	}
	cout << populations[0].path[0] << endl;

	cout << "Wynik znalezionej drogi: " << endl << populations[0].result << endl;
	
	cout << endl << endl;
}

solution Algorithm::tournamentSelection(vector<solution>& populations) { // rodzice wyznaczani sa na podstawie metody turniejowej 
	solution individual1 = populations[intDraw(0, populations.size() - 1)]; // losuje pierwszego osobnika
	solution individual2 = populations[intDraw(0, populations.size() - 1)]; // losuje drugiego osobnika

	return comparator(individual1, individual2) ? individual1 : individual2; // zwracam tego osobnika, ktory jest lepszy
}

int Algorithm::intDraw(int range1, int range2) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(range1, range2);
	return dist(gen);
}

double Algorithm::crossoverMutationDraw(int range1, int range2) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dist(range1, range2);
	return dist(gen);
}

solution Algorithm::cycleCrossover(solution& maleParent, solution& femaleParent) { // w tej funkcji wykonuje sie krzyzowanie, dla uproszczenia bedziemy nazywali rodzicow mama i tata
	vector<int> afterCrossoverChildPath(femaleParent.path.size(), INT_MAX); // tablica, w ktorej beda skrzyzowane "dane", wype³niamy losowymi wartosciami
	int positionHlp = intDraw(0, femaleParent.path.size() - 1); // zmienna przechowujaca pozycje, wybierana losowo na samym pocz¹tku krzyzowania
	solution newChild; // dziecko, które na koniec zostanie "zwrocone"
	int checkStartOfCycle = femaleParent.path[positionHlp]; // zmienna pomocnicza wykorzystywana w if'ie w pêtli odpowiedzialnej za szukanie cyklu w celu sprawdzenia, czy dotarlismy ponownie do poczatku cyklu

	while (true) { // pêtla odpowiedzialna za szukanie cyklu
		afterCrossoverChildPath[positionHlp] = femaleParent.path[positionHlp]; // przypisujemy tablicy ze skrzyzowanymi danymi wartosc z tablicy mamy z pozycji wylosowanej na poczatku

		if (checkStartOfCycle == maleParent.path[positionHlp]) // jezeli na tej samej pozycji u taty jest ta sama wartosc to znaczy, ze znalezlismy cykl i wychodzimy z petli
			break;
		else {																									// jednak gdy sie nie znajduje to
			auto it = find(femaleParent.path.begin(), femaleParent.path.end(), maleParent.path[positionHlp]);	// wykonujemy poszukiwanie w tablicy mamy w poszukiwaniu wartosci z tablicy taty (czyli kolejnej wartosci do cyklu)
			int newPosition;
			if (it != femaleParent.path.end())					// jezeli znalezlismy
				newPosition = it - femaleParent.path.begin();	// to przypisujemy to jako nowa pozycje

			positionHlp = newPosition; // i nadpisujemy pozycje
		}
	}

	for (int i = 0; i < femaleParent.path.size(); i++) { 
		if (afterCrossoverChildPath[i] == INT_MAX)				// reszte nieruszonych elementow w tablicy ze skrzyzowanymi danymi
			afterCrossoverChildPath[i] = maleParent.path[i];	// biezemy od taty
	}

	newChild.path = afterCrossoverChildPath; // na koniec do stworzego na poczatku dziecka przypisujemy tablice ze skrzyzowanymi danymi

	return newChild;
}

void Algorithm::swapMutation(solution& child) {
	int x = 0, y = 0;

	while (x == y) { // losujemy 2 wartosci
		x = intDraw(0, child.path.size() - 1);
		y = intDraw(0, child.path.size() - 1);
	}

	int tmp = child.path[x]; // zamieniamy miasta pod tymi wartosciami miejscami
	child.path[x] = child.path[y];
	child.path[y] = tmp;
}

void Algorithm::inversionMutation(solution& child) {
	int x = 0, y = 0, tmp;

	while (x == y) { // losujemy 2 wartosci
		x = intDraw(0, child.path.size() - 1);
		y = intDraw(0, child.path.size() - 1);
	} 

	if (x > y) {
		tmp = x;
		x = y;
		y = tmp;
	}

	tmp = child.path[x]; 
	child.path[x] = child.path[y];
	child.path[y] = tmp;
	x++;
	y--;

	while (x <= y) { // wykonuje odwrocenie kawalka tablic
		tmp = child.path[x];
		child.path[x] = child.path[y];
		child.path[y] = tmp;
		x++;
		y--;
	}
	
}