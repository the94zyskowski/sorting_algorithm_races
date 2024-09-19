#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Parametry algorytmu genetycznego
const int POPULATION_SIZE = 20;
const int NUM_GENERATIONS = 50;
const int VECTOR_SIZE = 10;
const int MUTATION_RATE = 5; // 5% szans na mutację

// Struktura reprezentująca algorytm (genotyp)
struct Algorithm {
    std::vector<int> operations; // Sekwencja operacji (porównania i zamiany)
    int fitness; // Ocena jakości (jak dobrze sortuje wektor)
};

// Funkcja pomocnicza do zamiany dwóch elementów
void swap(int& a, int& b);

// Funkcja generująca losowy wektor do sortowania
std::vector<int> generateRandomVector(int size);

// Funkcja oceniająca fitness algorytmu
int evaluateFitness(const Algorithm& algo, const std::vector<int>& targetVec);

// Funkcja mutacji (zmiana operacji)
void mutate(Algorithm& algo);

// Funkcja krzyżowania (łączenie dwóch algorytmów)
Algorithm crossover(const Algorithm& parent1, const Algorithm& parent2);

// Tworzenie początkowej populacji
std::vector<Algorithm> initializePopulation();

// Algorytm genetyczny do znalezienia najlepszego algorytmu sortowania
Algorithm geneticAlgorithm(const std::vector<int>& targetVec);

// Funkcja sortująca podobna do std::sort, która korzysta z wygenerowanego algorytmu
template <typename Iter>
void customSort(Iter begin, Iter end, const Algorithm& algo) {
    std::vector<int> vec(begin, end); // Tworzymy wektor z zakresu iteratorów
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

    // Zaktualizuj oryginalny zakres za pomocą posortowanego wektora
    std::copy(vec.begin(), vec.end(), begin);
}
