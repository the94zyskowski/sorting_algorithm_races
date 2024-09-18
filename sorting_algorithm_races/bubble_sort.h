//Bubble sort is simple, but immensely slow so be aware that with big containers will take a lot of time to sort.
#pragma once
#include <vector>
#include <algorithm>

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (Iterator it = begin; it != (end - 1); ++it) {
            if (*(it + 1) < *it) {
                std::iter_swap(it, it + 1);
                swapped = true;
            }
        }
    }
}