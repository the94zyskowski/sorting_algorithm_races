#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <stdexcept>

std::mutex mtx;  // Mutex do synchronizacji dostępu do listy wyników
std::vector<std::string> results;  // Lista wyników, gdzie zapisywane są identyfikatory algorytmów


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

class algorithm_ {
private:
    std::string name;
    std::string info;
    double sorting_time;
    int sorted_elements;
    int id;
public:
    algorithm_(): name("none"), info("empty"), sorting_time(-1.0), sorted_elements(-1), id(-1) {}
    algorithm_(std::string n, std::string i) : name(n), info(i), sorting_time(-1), sorted_elements(-1), id(-1) {
        if (name == "quick" || name == "quick sort") { //I know it is not comprehensive list of cases, this is just for now, be nice.
            set_id(1);
        } else if (name == "stable" || name == "stable sort") {
            set_id(2);
        }
        else if (name == "heap" || name == "heap sort") {
            set_id(3);
        }
        else {
            throw std::invalid_argument("Algorithm not found. :(");
        }
    }
    ~algorithm_() {}

    void go(std::vector<int> v) {
        auto start = std::chrono::high_resolution_clock::now();
        if (this->get_id() == 1) {
            std::sort(v.begin(), v.end());
            
        }
        else if (this->get_id() == 2) {
            std::stable_sort(v.begin(), v.end());
        }
        else if (this->get_id() == 3) {
            std::make_heap(v.begin(), v.end());
            std::sort_heap(v.begin(), v.end());
        }
        else {
            throw std::invalid_argument("Algorithm not found and we shouldn't be here. Check constructor of class algorithm_.");
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_duration = end - start;
        this->set_sorting_time(time_duration.count());
        set_sorted_elements(v.size());
    }

    void set_name(const std::string n) { name = n; }
    std::string const get_name() { return name; }

    void set_id(const int n_id) { id = n_id; }
    int const get_id() { return id; }

    void set_sorting_time(const double st) { sorting_time = st; }
    double const get_sorting_time() { return sorting_time; }

    void set_sorted_elements(const int se) { sorted_elements = se; }
    int const get_sorted_elements() { return sorted_elements; }

    void set_info(const std::string i) { info = i; }
    std::string const get_info() { return info; }

};

int main() {
    std::vector<int> vec;
    create_pool(vec);
    
    algorithm_ quick("quick", "fast boi");

}