#include <iostream>
#include <span>
#include <array>

template<typename T>
T Add(T a, T b) {
    return a + b;
};

template<typename T, size_t N>
T Sum(const std::array<T, N>& array) {
    T sum = 0;
    for (const auto& value : array) {  // Range-based for loop
        sum += value;
    }
    return sum;
}

// template<typename T, size_t N>
// T Max(const std::array<T, N>& arr) {
//     T max = 0;
//     bool set = false;
//     for (const auto& val : arr) {
//         if (val > max || !set) {
//             max = val;
//             set = true;
//         }
//     }

//     return max;
// }

template<typename T, size_t N>
std::pair<T,T> Pair(const std::array<T, N>& arr) {
    T min{};
    T max{};
    bool minSet{};
    bool maxSet{};

    for (const auto& val : arr) {
        if (val > max || !maxSet) {
            max = val;
            maxSet = true;
        }
        if (val < min || !minSet) {
            min = val;
            minSet = true;
        }
    }

    return std::pair<T,T>{min,max};
}

template<typename T, size_t N>
void Print(const std::array<T,N>& arr) {
    bool first = true;
    for (const T& val : arr) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << val;

        first = false;
    }
    std::cout << std::endl;
}

template<typename T>
struct Max {
    int operator()(int x, int y) {
        return x > y ? x : y;
    }
};

int main() {
    int x = 5;
    int y = 2;

    // Max<int> val = Max<int>{};

    auto maxFn = [](auto x, auto y) {
        return x > y ? x : y;
    };

    auto greaterFn = [](auto x, auto y) {
        return x > y;
    };

    auto minMaxFn = [](std::begin, auto arr2) {

    }

    std::cout << greaterFn(x,y) << std::endl;
}