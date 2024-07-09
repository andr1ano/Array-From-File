#include "library/include/ArrayTransformer/ArrayTransformer.hpp"
#include "library/include/DataProcessor/DataProcessor.hpp"
#include "library/include/Utils/ArrayPrinter.hpp"

int main(int argc, char* argv[]) {

    // Get name of the file to read numbers
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::cout << "test";
    std::string filename = argv[1];

    // Create instance of class to read numbers 
    DataProcessor<std::vector<std::vector<int>>, std::vector<int>> processor;
    processor.processFile(filename);

    std::cout << "Arrays read from file:" << std::endl;
    double_array_printer(" ", processor.getArrays());

    // Sort each row of numbers using Sorter child of ArrayTransformer
    auto sortedArrays = processor.getSorted();
    double_array_printer("\nSorted arrays:", sortedArrays);

    // Find intersection of two biggest lines (Array 1) and all three (Array 2) 
    // using Intersector child of ArrayTransformer
    auto intersectedArrays = processor.getIntersectionResults();
    double_array_printer("\nIntersected arrays:", intersectedArrays);

    // Sort unique elements of three arrays in descending order using UniqueSorter child of ArrayTransformer
    auto uniqueArrays = processor.getUniqueSortedDescending();
    array_printer("\nUnique arrays:", uniqueArrays);

    return 0;
}