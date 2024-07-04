#pragma once

#include <iostream>
#include <fstream>
#include <string>

template<typename OuterContainer = std::vector<std::vector<int>>, typename InnerContainer = std::vector<int>>
class DataProcessor {
private:
    OuterContainer arrays;
    Sorter<OuterContainer, InnerContainer> sorter;
    Intersector<OuterContainer, InnerContainer> intersector;
    UniqueSorter<OuterContainer, InnerContainer> uniqueSorter;

    InnerContainer parseLine(const std::string& line) {
        InnerContainer array;
        std::string num;
        for (char ch : line) {
            if (ch == ',' || ch == ' ') {
                if (!num.empty()) {
                    array.push_back(std::stoi(num));
                    num.clear();
                }
            }
            else {
                num += ch;
            }
        }
        if (!num.empty()) {
            array.push_back(std::stoi(num));
        }
        return array;
    }

public:
    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            arrays.push_back(parseLine(line));
        }
    }

    OuterContainer getSorted() {
        OuterContainer sortedArrays = arrays;
        sorter.transform(sortedArrays);
        return sortedArrays;
    }

    OuterContainer getIntersectionResults() {
        OuterContainer intersectedArrays = arrays;
        intersector.transform(intersectedArrays);
        return intersectedArrays;
    }

    InnerContainer getUniqueSortedDescending() {
        OuterContainer uniqueArray = arrays;
        uniqueSorter.transform(uniqueArray);
        return uniqueArray.front();
    }

    const OuterContainer& getArrays() const {
        return arrays;
    }
};