﻿#include "src.h"

#include <iostream>
#include <mutex>

std::mutex cout_mutex;

void print_safe(const std::string& message) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << message << std::endl;
}

algorithm_::algorithm_(): name("none"), info("empty"), sorting_time(-1.0), sorted_elements(-1), id(-1) {}
algorithm_::algorithm_(std::string n, std::string i) : name(n), info(i), sorting_time(-1), sorted_elements(-1), id(-1) {
        if (algorithm_map.find(name) != algorithm_map.end()) {
            id = algorithm_map[name];
        }
        else {
            throw std::invalid_argument("Algorithm not found. :(");
        }
    }
algorithm_::~algorithm_() {}

void algorithm_::go(std::vector<int> v) {
        auto start = std::chrono::high_resolution_clock::now();
        if (id == 1) {
            std::sort(v.begin(), v.end());
            
        }
        else if (id == 2) {
            std::stable_sort(v.begin(), v.end());
        }
        else if (id == 3) {
            std::make_heap(v.begin(), v.end());
            std::sort_heap(v.begin(), v.end());
        }
        else if (id == 4) {
            bubble_sort(v.begin(), v.end());
        }
        else {
            throw std::invalid_argument("Algorithm not found and we shouldn't be here. Check constructor of class algorithm_.");
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_duration = end - start;
        sorting_time = time_duration.count();
        sorted_elements = v.size();
}

void algorithm_::set_name(const std::string n) { name = n; }
std::string const algorithm_::get_name() { return name; }

void algorithm_::set_id(const int n_id) { id = n_id; }
int const algorithm_::get_id() { return id; }

void algorithm_::set_sorting_time(const double st) { sorting_time = st; }
double const algorithm_::get_sorting_time() { return sorting_time; }

void algorithm_::set_sorted_elements(const int se) { sorted_elements = se; }
int const algorithm_::get_sorted_elements() { return sorted_elements; }

void algorithm_::set_info(const std::string i) { info = i; }
std::string const algorithm_::get_info() { return info; }

std::string algorithm_::get_formatted_output() {
    std::string output;
    output += "Algorithm name: " + (!name.empty() ? name : "No name") + "\n";
    output += "Info: " + (!info.empty() ? info : "No info") + "\n";
    output += "Sorted <" + (sorted_elements > 0 ? std::to_string(sorted_elements) : "No sorted elements") + "> elements in " + (sorting_time > 0 ? std::to_string(sorting_time) : "No sorting time") + " seconds.\n";
    return output;
}


int main() {
    algorithm_ quick("quick sort", "fast boi");
    algorithm_ stable("stable sort", "more stable");
    algorithm_ heap("heap sort", "heap based");
    algorithm_ bubble("bubble sort", "blop blop");

    std::vector<int> vec;
    create_pool(vec, 1000);

    run_algorithms_async(vec, quick, stable, heap, bubble);

    return 0;
}