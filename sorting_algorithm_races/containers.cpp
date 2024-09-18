#include "containers.h"

void create_pool(std::vector<int>& v, int size) {
    std::set<int> unique_numbers;
    int x{ 0 };
    while (v.size() < size) {
        x = rand() % size;
        if (unique_numbers.find(x) == unique_numbers.end()) {
            v.push_back(x);
            unique_numbers.insert(x);
        }
    }
}

void show_numbers(std::vector<int>& v, int start, int length) {
    if ((start + length) <= v.size()) {
        for (size_t i = start; i < length && i < v.size(); ++i) {
            std::cout << v[i] << ", ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Out of bounds!" << std::endl;
    }
}
