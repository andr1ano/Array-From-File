#pragma once

#include <algorithm>

template<typename Iterator>
Iterator partition(Iterator low, Iterator high) {
    auto pivot = *high;
    auto i = low;

    for (auto j = low; j != high; ++j) {
        if (*j < pivot) {
            std::iter_swap(i, j);
            ++i;
        }
    }

    std::iter_swap(i, high);
    return i;
}

template<typename Iterator>
void quicksort(Iterator low, Iterator high) {
    if (low < high) {
        Iterator pivot = partition(low, high);
        if (pivot != low) {
            quicksort(low, pivot - 1);
        }
        if (pivot != high) {
            quicksort(pivot + 1, high);
        }
    }
}