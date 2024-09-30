#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <future>
#include <mutex>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "bubble_sort.h"
#include "containers.h"

extern std::mutex cout_mutex;

void print_safe(const std::string& message);

void create_pool(std::vector<int>& v, int size);

void show_numbers(std::vector<int>& v, int start, int length);

class algorithm_ {
private:
    std::string name;
    std::string info;
    double sorting_time;
    int sorted_elements;
    int id;

    static std::unordered_map<std::string, int> algorithm_map;
public:
    algorithm_();
    algorithm_(std::string n, std::string i);
    ~algorithm_();

    std::vector<int> go(std::vector<int> v);

    void set_name(const std::string n);
    std::string const get_name();

    void set_id(const int n_id);
    int const get_id();

    void set_sorting_time(const double st);
    double const get_sorting_time();

    void set_sorted_elements(const int se);
    int const get_sorted_elements();

    void set_info(const std::string i);
    std::string const get_info();

    std::string get_formatted_output();
};

// Template function that takes a vector, at least one algorithm, and a variadic number of algorithms
template <typename Algorithm, typename... Algorithms>
void run_algorithms_async(std::vector<int>& vec, Algorithm& first_algorithm, Algorithms&... other_algorithms) {
    // Vector to store futures (asynchronous tasks)
    std::vector<std::future<void>> futures;

    // Run the first algorithm, capturing vec by reference
    futures.push_back(std::async(std::launch::async, [&first_algorithm, &vec]() {
        first_algorithm.go(vec);       // Pass the vector to the first algorithm's go() method
        print_safe(first_algorithm.get_formatted_output());   // Print the results of the first algorithm
        }));

    // Fold expression to run remaining algorithms in the variadic list, also capturing vec by reference
    ((futures.push_back(std::async(std::launch::async, [&other_algorithms, &vec]() {
        other_algorithms.go(vec);       // Pass the vector to the remaining algorithms' go() methods
        print_safe(other_algorithms.get_formatted_output());   // Print the results of the remaining algorithms
        }))), ...);

    // Wait for all futures to complete by calling future.get() on each
    for (auto& future : futures) {
        future.get();  // This blocks until the task is complete
    }
}

extern std::unordered_map<std::string, int> algorithm_map;
