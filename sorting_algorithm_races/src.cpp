// IMPORTANT!!!
// TEST_MODE preprocessor variable must be set in VC2022 settings: C++ > Preprocessor
// For normal operation TEST_MODE = 0
// For google tests TEST_MODE = 1
#include "src.h"

std::mutex cout_mutex;  // Mutex for thread-safe printing

void print_safe(const std::string& message) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << message << std::endl;
}

// Default constructor
algorithm_::algorithm_() : name("none"), info("empty"), sorting_time(-1.0), sorted_elements(-1), id(-1) {}

// Constructor with algorithm name and info
algorithm_::algorithm_(std::string n, std::string i) : name(n), info(i), sorting_time(-1), sorted_elements(-1), id(-1) {
    if (algorithm_map.find(name) != algorithm_map.end()) {
        id = algorithm_map[name];  // Map name to id
    }
    else {
        throw std::invalid_argument("Algorithm not found.");
    }
}

algorithm_::~algorithm_() {}

// Main sorting function
std::vector<int> algorithm_::go(std::vector<int> v) {
    auto start = std::chrono::high_resolution_clock::now();  // Start timing

    // Choose sorting algorithm based on id
    if (id == 1) {
        std::sort(v.begin(), v.end());  // Quick sort
    }
    else if (id == 2) {
        std::stable_sort(v.begin(), v.end());  // Stable sort
    }
    else if (id == 3) {
        std::make_heap(v.begin(), v.end());
        std::sort_heap(v.begin(), v.end());  // Heap sort
    }
    else if (id == 4) {
        bubble_sort(v.begin(), v.end());  // Bubble sort
    }
    else {
        throw std::invalid_argument("Invalid algorithm id.");
    }

    auto end = std::chrono::high_resolution_clock::now();  // End timing
    std::chrono::duration<double> time_duration = end - start;
    sorting_time = time_duration.count();  // Store sorting time
    sorted_elements = v.size();  // Store sorted element count
    return v;  // Return sorted vector
}

// Getters and setters
std::string algorithm_::get_name() const { return name; }
int algorithm_::get_id() const { return id; }
double algorithm_::get_sorting_time() const { return sorting_time; }
int algorithm_::get_sorted_elements() const { return sorted_elements; }
std::string algorithm_::get_info() const { return info; }

// Formatted output for printing results
std::string algorithm_::get_formatted_output() {
    std::string output;
    output += "Algorithm name: " + name + "\n";
    output += "Info: " + info + "\n";
    output += "Sorted " + std::to_string(sorted_elements) + " elements in " + std::to_string(sorting_time) + " seconds.\n";
    return output;
}

// Map of algorithm names to ids
std::unordered_map<std::string, int> algorithm_::algorithm_map = {
    {"quick sort", 1}, {"stable sort", 2}, {"heap sort", 3}, {"bubble sort", 4}
};

#if TEST_MODE == 0
int main() {
    algorithm_ quick("quick sort", "fast boi");
    algorithm_ stable("stable sort", "not for horses");
    algorithm_ heap("heap sort", "heap based");
    algorithm_ bubble("bubble sort", "blop blop");

    std::vector<int> vec;
    create_pool(vec, 1000);  // Create pool of random numbers

    run_algorithms_async(vec, quick, stable, heap, bubble);  // Run sorting algorithms asynchronously

    return 0;
}
#endif
