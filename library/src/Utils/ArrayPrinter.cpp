#pragma once

#include <iostream>
#include <string>

template<typename T>
void array_printer(const std::string& message, const T& array) {
    std::cout << message << std::endl;
    for (const auto& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void double_array_printer(const std::string& message, const T& arrays) {
    std::cout << message << std::endl;
    int i = 1;
    for (const auto& array : arrays) {
        std::cout << "Array " << i << ":" << std::endl;
        for (const auto& num : array) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        ++i;
    }
}
