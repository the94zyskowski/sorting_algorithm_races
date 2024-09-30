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

extern std::mutex cout_mutex;  // Mutex for thread-safe console output

void print_safe(const std::string& message);

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

    std::vector<int> go(std::vector<int> v);  // Sort function returns the sorted vector

    // Use 'const' for getter methods since they do not modify the object
    std::string get_name() const;
    int get_id() const;
    double get_sorting_time() const;
    int get_sorted_elements() const;
    std::string get_info() const;
    std::string get_formatted_output();
};

// Template function that runs algorithms asynchronously
template <typename Algorithm, typename... Algorithms>
void run_algorithms_async(std::vector<int>& vec, Algorithm& first_algorithm, Algorithms&... other_algorithms) {
    std::vector<std::future<void>> futures;

    // Run the first algorithm asynchronously
    futures.push_back(std::async(std::launch::async, [&first_algorithm, &vec]() {
        first_algorithm.go(vec);  // Sort using the first algorithm
        print_safe(first_algorithm.get_formatted_output());  // Print the result
        }));

    // Run the remaining algorithms asynchronously
    ((futures.push_back(std::async(std::launch::async, [&other_algorithms, &vec]() {
        other_algorithms.go(vec);  // Sort using the next algorithm
        print_safe(other_algorithms.get_formatted_output());
        }))), ...);

    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.get();
    }
}
