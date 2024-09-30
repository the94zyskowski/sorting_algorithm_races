cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(sorting_algorithm_races)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 20)

# Dodaj katalogi z plikami nag³ówkowymi
include_directories(${PROJECT_SOURCE_DIR}/include)

# Dodaj pliki Ÿród³owe projektu
add_executable(SortingAlgorithms
    src.cpp
    containers.cpp
    test_algorithm.cpp
)

# Dodaj definicje preprocesora
# Zmieniaj w zale¿noœci od tego, co kompilujesz
add_definitions(-DTEST_MODE=1)  # 1 dla testów
# add_definitions(-DTEST_MODE=0)  # 0 dla normalnego programu

# Ustaw œcie¿kê do lokalnego Google Test
# Zast¹p 'path/to/gtest' prawid³ow¹ œcie¿k¹ do folderu, gdzie zbudowa³eœ Google Test
add_subdirectory(C:\Users\maciej\OneDrive\Dokumenty\software\googletest)

# Linkuj Google Test z projektem
target_link_libraries(SortingAlgorithms gtest gtest_main)

# Dodaj testy
enable_testing()
add_test(NAME SortingAlgorithmsTests COMMAND sorting_algorithm_races)
