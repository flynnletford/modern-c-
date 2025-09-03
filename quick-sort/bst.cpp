#include <iostream>
#include <vector>

int pivot(std::vector<int>& vec, int pivotIndex, int endIndex) {

    int pivotVal = vec[pivotIndex];
    int swapIndex = pivotIndex;

    for (int i = pivotIndex + 1; i <= endIndex; i++) {
        int currentVal = vec[i];

        if (currentVal < pivotVal) {
            swapIndex++;

            std::cout << "swapping: " << i << " and " << swapIndex << std::endl;
            std::swap(vec[i], vec[swapIndex]);
        }
    }

    std::swap(vec[pivotIndex], vec[swapIndex]);

    return swapIndex;
}


void quickSortSub(std::vector<int>& vec, int pivotIndex, int endIndex) {

    std::cout<< "quick sort with pivotIndex: " << pivotIndex << ", endIndex: " << endIndex << std::endl;
    if (pivotIndex >= endIndex) {
        return;
    }

    int swapIndex = pivot(vec, pivotIndex, endIndex);

    std::cout << "swap index: " << swapIndex << std::endl;

    // Left side.
    quickSortSub(vec, pivotIndex, swapIndex - 1);

    // Right side.
    quickSortSub(vec, swapIndex + 1, endIndex);
}

void quickSort(std::vector<int>& vec) {
    int pivotIndex = 0;
    int endIndex = vec.size() - 1;

    quickSortSub(vec, pivotIndex, endIndex);
}

void print(const std::vector<int>& vec) {

    int index = 0;
    for (const auto& val : vec) {
        if (index != 0) {
            std::cout << ", ";
        }
        std::cout << val;
        index++;
    }

    std::cout << std::endl;
}

int main() {

    // std::vector<int> vec{5,1,7,8,0, 10, 12, -3, 18, 200, -6, 2000};
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

    print(vec);

    quickSort(vec);

    print(vec);
}