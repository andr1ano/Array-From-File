#include "../Utils/QuickSort.hpp"
 
#include <unordered_set>

template<typename OuterContainer, typename InnerContainer>
class ArrayTransformer {
public:
    virtual void transform(OuterContainer& arrays) = 0;
    virtual ~ArrayTransformer() = default;
};

template<typename OuterContainer, typename InnerContainer>
class Sorter : public ArrayTransformer<OuterContainer, InnerContainer> {
public:
    void transform(OuterContainer& arrays) override {
        for (auto& array : arrays) {
            quicksort(array.begin(), array.end() - 1);
        }
    }
};

template<typename OuterContainer, typename InnerContainer>
class Intersector : public ArrayTransformer<OuterContainer, InnerContainer> {
public:
    void transform(OuterContainer& arrays) override {
        OuterContainer temp_arr(2);
        temp_arr.front() = findIntersectionOfTwoBiggest(arrays);
        temp_arr.back() = findIntersectionOfAll(arrays);
        arrays = temp_arr;
    }

    InnerContainer findIntersectionOfTwoBiggest(const OuterContainer& arrays) {
        if (arrays.size() < 2) return InnerContainer();

        auto largest1 = arrays.begin();
        auto largest2 = arrays.begin();
        if (arrays.size() > 1) {
            largest2 = std::next(largest1);
        }

        for (auto it = arrays.begin(); it != arrays.end(); ++it) {
            if (it->size() > largest1->size()) {
                largest2 = largest1;
                largest1 = it;
            }
            else if (it->size() > largest2->size() && it != largest1) {
                largest2 = it;
            }
        }

        std::unordered_set<int> set1(largest1->begin(), largest1->end());
        InnerContainer intersection;
        for (const auto& num : *largest2) {
            if (set1.find(num) != set1.end()) {
                intersection.push_back(num);
            }
        }

        return intersection;
    }


    InnerContainer findIntersectionOfAll(const OuterContainer& arrays) {

        std::unordered_set<int> intersection(arrays.front().begin(), arrays.front().end());

        for (const auto& array : arrays) {
            std::unordered_set<int> currentSet(array.begin(), array.end());
            std::unordered_set<int> tempIntersection;

            for (const auto& element : intersection) {
                if (currentSet.find(element) != currentSet.end()) {
                    tempIntersection.insert(element);
                }
            }

            intersection = tempIntersection;
            if (intersection.empty()) break;
        }

        return InnerContainer(intersection.begin(), intersection.end());
    }
};

template<typename OuterContainer, typename InnerContainer>
class UniqueSorter : public ArrayTransformer<OuterContainer, InnerContainer> {
public:
    void transform(OuterContainer& arrays) override {
        std::unordered_set<int> uniqueElements;
        for (const auto& array : arrays) {
            uniqueElements.insert(array.begin(), array.end());
        }

        InnerContainer uniqueSorted(uniqueElements.begin(), uniqueElements.end());
        quicksort(uniqueSorted.begin(), uniqueSorted.end() - 1);
        std::reverse(uniqueSorted.begin(), uniqueSorted.end());
        arrays.front() = uniqueSorted;
    }
};