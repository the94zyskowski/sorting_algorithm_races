# Sorting Algorithm Racer
This is a simple C++ project designed for fun to experiment with various sorting algorithms. The goal is to compare their performance in sorting a randomly generated vector of unique integers.

## The project currently includes the following algorithms:

- Quick Sort
- Stable Sort
- Heap Sort
- Bubble Sort

## Features
Algorithm Selection: Select an algorithm by name (e.g., "quick sort", "bubble sort") from a mapped list of available algorithms.
Performance Measurement: The time taken for each algorithm to sort the data is measured and displayed.
Random Data Generation: A pool of unique random numbers is generated for sorting.

## How to Run
This project was developed and tested using Visual Studio 2022. To run it:

- Clone the repository.
- Open the project in Visual Studio.
- Build and run the project.
- Observe the results in the console, including the algorithm used and the sorting time.

## Example Output
```sh
Algorithm name: quick sort
Info: fast boi
Sorted <10000> in 0.00321 seconds.
```

## Unit Tests with Google Test
This project includes unit tests implemented with Google Test to ensure the correctness of the sorting algorithms. To run the tests:

- Make sure Google Test is installed or available in your environment.
- Build the project in a testing configuration (TEST_MODE = 1).
- Run the tests via Visual Studio Test Explorer or directly from the console.

## Example Google Test output
```sh
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from SortingAlgorithmTest
[ RUN      ] SortingAlgorithmTest.QuickSortTest
[       OK ] SortingAlgorithmTest.QuickSortTest (0 ms)
[ RUN      ] SortingAlgorithmTest.StableSortTest
[       OK ] SortingAlgorithmTest.StableSortTest (0 ms)
[ RUN      ] SortingAlgorithmTest.HeapSortTest
[       OK ] SortingAlgorithmTest.HeapSortTest (0 ms)
[ RUN      ] SortingAlgorithmTest.BubbleSortTest
[       OK ] SortingAlgorithmTest.BubbleSortTest (0 ms)
[----------] 4 tests from SortingAlgorithmTest (1 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (3 ms total)
[  PASSED  ] 4 tests.

```

## Future Improvements
- Add more sorting algorithms (e.g., Merge Sort, Insertion Sort).
- <del>Improve input handling for custom algorithms. </del>
- <del>Implement multi-threaded race conditions for sorting algorithms. </del>
- <del>Add Google Test and implement some unit tests. </del>

## License
This project is for educational and personal use.
