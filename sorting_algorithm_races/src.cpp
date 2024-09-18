#include "bubble_sort.h"
#include "src.h"

void create_pool(std::vector<int>& v) {
    std::set<int> unique_numbers;
    int x{ 0 };
    while (v.size() < 10000) {
        x = rand() % 10000;
        if (unique_numbers.find(x) == unique_numbers.end()) {
            v.push_back(x);
            unique_numbers.insert(x);
        }
    }
}

void show_first_30_numbers(std::vector<int>& v) {
    for (size_t i = 0; i < 30 && i < v.size(); ++i) {
        std::cout << v[i] << ", ";
    }
    std::cout << std::endl;
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
            bubble_sort(v);
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

void algorithm_::print_all() { //This is nice mmhm
    std::cout << "Algorithm name: " << (!name.empty() ? name : "No name") << std::endl;
    std::cout << "Info: " << (!info.empty() ? info : "No info") << std::endl;
    std::cout << "Sorted <" << (sorted_elements > 0 ? std::to_string(sorted_elements) : "No sorted elements") << "> in " << (sorting_time > 0 ? std::to_string(sorting_time) : "No sorting time") << " seconds." << std::endl;
}

int main() {
    std::vector<int> vec;
    create_pool(vec);
    
    algorithm_ quick("quick sort", "fast boi");
    quick.go(vec);
    quick.print_all();
}