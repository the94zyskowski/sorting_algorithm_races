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

    void go(std::vector<int> v);

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

    void print_all();
};

std::unordered_map<std::string, int> algorithm_::algorithm_map = {
    {"quick sort", 1}, //I am aware there are more combinations, but this is not the focus of this project and should be sufficient for now.
    {"Quick Sort", 1},
    {"quicksort", 1},
    {"stable sort", 2},
    {"Stable Sort", 2},
    {"stablesort", 2},
    {"heap sort", 3},
    {"Heap Sort", 3},
    {"heapsort", 3},
    {"bubble sort", 4},
    {"Bubble Sort", 4},
    {"bubblesort", 4}
};
