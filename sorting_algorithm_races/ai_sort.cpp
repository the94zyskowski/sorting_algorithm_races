#include "ai_sort.h"

// Funkcja pomocnicza do zamiany dwóch elementów
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Funkcja generująca losowy wektor do sortowania
std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = rand() % 100; // losowe liczby 0-99
    }
    return vec;
}

// Funkcja oceniająca fitness algorytmu
int evaluateFitness(const Algorithm& algo, const std::vector<int>& targetVec) {
    std::vector<int> vec = targetVec;
    int size = vec.size(); // Zapisz rozmiar wektora, by nie obliczać za każdym razem

    // Iterujemy po operacjach w algorytmie
    for (int op : algo.operations) {
        // Obliczamy indeksy i oraz j
        int i = op % size;
        int j = (op / size) % size;

        // Sprawdzenie poprawności indeksów przed dostępem do elementów wektora
        if (i >= 0 && i < size && j >= 0 && j < size && i != j) {
            if (vec[i] > vec[j]) {
                swap(vec[i], vec[j]);
            }
        }
    }

    // Ocena, czy wektor jest posortowany
    return std::is_sorted(vec.begin(), vec.end()) ? 1000 : 0; // prosty fitness
}

// Funkcja mutacji (zmiana operacji)
void mutate(Algorithm& algo) {
    for (int& op : algo.operations) {
        if (rand() % 100 < MUTATION_RATE) {
            op = rand() % (VECTOR_SIZE * VECTOR_SIZE); // nowa losowa operacja
        }
    }
}

// Funkcja krzyżowania (łączenie dwóch algorytmów)
Algorithm crossover(const Algorithm& parent1, const Algorithm& parent2) {
    Algorithm offspring;
    int crossoverPoint = rand() % parent1.operations.size();
    for (int i = 0; i < parent1.operations.size(); ++i) {
        if (i < crossoverPoint)
            offspring.operations.push_back(parent1.operations[i]);
        else
            offspring.operations.push_back(parent2.operations[i]);
    }
    return offspring;
}

// Tworzenie początkowej populacji
std::vector<Algorithm> initializePopulation() {
    std::vector<Algorithm> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Algorithm algo;
        algo.fitness = 0;
        for (int j = 0; j < VECTOR_SIZE * 2; ++j) {
            algo.operations.push_back(rand() % (VECTOR_SIZE * VECTOR_SIZE));
        }
        population.push_back(algo);
    }
    return population;
}

// Algorytm genetyczny do znalezienia najlepszego algorytmu sortowania
Algorithm geneticAlgorithm(const std::vector<int>& targetVec) {
    std::vector<Algorithm> population = initializePopulation();
    Algorithm bestAlgorithm;

    for (int generation = 0; generation < NUM_GENERATIONS; ++generation) {
        // Ocena jakości populacji
        for (Algorithm& algo : population) {
            algo.fitness = evaluateFitness(algo, targetVec);
        }

        // Sortowanie populacji według fitness
        std::sort(population.begin(), population.end(), [](const Algorithm& a, const Algorithm& b) {
            return a.fitness > b.fitness;
            });

        // Zaktualizuj najlepszy algorytm
        if (population[0].fitness > bestAlgorithm.fitness) {
            bestAlgorithm = population[0];
        }

        // Krzyżowanie i mutacja, aby utworzyć nowe algorytmy
        std::vector<Algorithm> newPopulation;
        for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
            Algorithm parent1 = population[i];
            Algorithm parent2 = population[POPULATION_SIZE - i - 1];
            Algorithm offspring = crossover(parent1, parent2);
            mutate(offspring);
            newPopulation.push_back(offspring);
        }
        population = newPopulation;
    }

    return bestAlgorithm; // Zwracamy najlepszy znaleziony algorytm
}
