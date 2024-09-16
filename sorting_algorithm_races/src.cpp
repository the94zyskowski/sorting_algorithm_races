#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>

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

void log_result(std::string id) {
    std::lock_guard<std::mutex> guard(mtx);  // Blokujemy dostęp do wyników na czas modyfikacji
    results.push_back(id);
}

void quick_sort_racer(std::vector<int> v) { //it is copy on purpose
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> czas_trwania = end - start;
    std::cout << "Time of quick sort sorting: " << czas_trwania.count() << " s\n";
    log_result("quick_sort");
}

void stable_sort_racer(std::vector<int> v) { //it is copy on purpose
    auto start = std::chrono::high_resolution_clock::now();
    std::stable_sort(v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> czas_trwania = end - start;
    std::cout << "Time of stable sort sorting: " << czas_trwania.count() << " s\n";
    log_result("stable_sort");
}

void heap_sort_racer(std::vector<int> v) { //it is copy on purpose
    auto start = std::chrono::high_resolution_clock::now();
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> czas_trwania = end - start;
    std::cout << "Time of heap sort sorting: " << czas_trwania.count() << " s\n";
    log_result("heap_sort");
}

int main() {
    std::vector<int> vec;
    create_pool(vec);
    //show_first_30_numbers(vec);
    std::thread thr1(quick_sort_racer, vec);
    std::thread thr2(stable_sort_racer, vec);
    std::thread thr3(heap_sort_racer, vec);

    thr1.join();
    thr2.join();
    thr3.join();

    for (auto i : results) {
        std::cout << i << std::endl;
    }
}