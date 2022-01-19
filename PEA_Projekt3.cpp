#include <iostream>
#include "Algorithm.h"
#include "TimeTests.h"
#include <vector>

using namespace std;

vector<vector<int>> weightMatrixGlobal;
int numberOfCitiesGlobal;
TimeTests tt;
Algorithm att;

void showRow(vector<int> weightMatrix) { // funkcja pomocnicza w wyświetlaniu macierzy
    for (int i = 0; i < (int)weightMatrix.size(); i++) {
        cout << weightMatrix[i];
        if (weightMatrix[i] > 9) {
            if (weightMatrix[i] < 100) {
                cout << "  ";
            }
            else {
                cout << " ";
            }
        }
        else {
            cout << "   ";
        }
    }
}

void showWeightMatrix(int numberOfCities, vector<vector<int>> weightMatrix) { // funkcja wyświetlajaca macierz

    if (numberOfCities == 0) {
        cout << "Nie wczytano struktury lub liczba miast wynosi 0!" << endl;
    }
    else {
        for (int i = 0; i < numberOfCities; i++) {
            showRow(weightMatrix[i]);
            cout << endl;
        }
        cout << endl;
    }
}

void doGA(float time, int sizeOfStartingPopulation, float mutationRate, float crossoverRate, int mutationMethod) {
    Algorithm a;
    a.geneticAlgorithm(weightMatrixGlobal, time, sizeOfStartingPopulation, mutationRate, crossoverRate, mutationMethod);
}

void tests() { // funkcja, w ktorej odpalane sa wszystkie testy

    cout << "KONIEC TESTOW" << endl;
}

int main()
{
    srand(time(NULL));
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    setlocale(LC_ALL, "polish");

    int menuOperation;
    char menuContinue;
    string fileName;
    bool checker;
    bool endProgram = false;
    Algorithm a;
    float time = 20;
    int sizeOfStartingPopulation = 40, mutationMethod = 1;
    float mutationRate = 0.01, crossoverRate = 0.8;

    cout << "Projekt PEA    Kajetan Krason    252767" << endl << endl;

    do {
        cout << "1. Wczytaj strukture z pliku i ja pokaz." << endl;
        cout << "2. Pokaz wczytana strukture." << endl;
        cout << "3. Ustaw parametry." << endl;
        cout << "Aktualnie ustawione parametry: max. czas wykonywania algorytmu: " << time << " sekund; wielkosc populacji poczatkowej: " << sizeOfStartingPopulation << "; wspolczynnik mutacji: " << mutationRate << "; wspolczynnik krzyzowania: " << crossoverRate << "; metoda mutacji: " << mutationMethod << " (1 - inversion mutation; 2 - swap mutation; cokolwiek innego - jedno dziecko swap, drugie inversion)." << endl;
        cout << "4. Rozwiaz problem komiwojazera na wczytanej strukturze  - algorytm genetyczny." << endl;
        cout << "5. Testy. " << endl;
        cout << "6. Opuśc program. " << endl;
        cin >> menuOperation;


        switch (menuOperation)
        {
        case 1:
            cout << "Podaj nazwe pliku (plik txt, bez rozszerzenia): " << endl;
            cin >> fileName;
            fileName.append(".txt");
            checker = a.fileReadGraph(fileName, false, numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 2:
            cout << "Odległości miedzy miastami:" << endl << endl;
            showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
            break;
        case 3:
            cout << "Podaj czas wykonania algorytmu:" << endl;
            cin >> time;
            cout << "Podaj rozmiar populacji startowej:" << endl;
            cin >> sizeOfStartingPopulation;
            cout << "Podaj wspolczynnik mutacji:" << endl;
            cin >> mutationRate;
            cout << "Podaj wspolczynnik krzyzowania:" << endl;
            cin >> crossoverRate;
            cout << "Podaj metodę mutacji (1 - inversion mutation; 2 - swap mutation; cokolwiek innego - jedno dziecko swap, drugie inversion):" << endl;
            cin >> mutationMethod;
            break;
        case 4:
            if (time < 0)
                cout << "Nie wprowadzono parametru." << endl;
            else
                doGA(time, sizeOfStartingPopulation, mutationRate, crossoverRate, mutationMethod);
            break;
        case 5:
            tests();
            break;
        case 6:
            endProgram = true;
            break;
        }
        cout << endl << endl;

    } while (!endProgram);
}