#include <iostream>
#include <vector>

template<typename T>
class Heap {
    private:
        std::function<T(T, T)> compare;

    
    protected:
        std::vector<T> values;

    public:

        Heap() = delete;

        Heap(std::function<T(T,T)> c) {
            std::cout << "Compare param constructor called" << std::endl;
            compare = c;
        }

        virtual ~Heap() {
            std::cout << "Default destructor called" << std::endl;
        }

        bool empty() {
            return values.empty();
        }

        void print() {
            int index = 0;
            for (const auto& val : values) {
                if (index != 0) {
                    std::cout << ", ";
                }
                std::cout << val;
                ++index;
            }
            std::cout << std::endl;
        }

        int leftChild(int parentIndex) {
            return 2*parentIndex + 1;
        }
        int rightChild(int parentIndex) {
            return 2*parentIndex + 2;
        }
        int parent(int childIndex) {
            return (childIndex-1)/2;
        }

        void swap(int childIndex, int parentIndex) {
            T tmp = values[parentIndex];
            values[parentIndex] = values[childIndex];
            values[childIndex] = tmp;
        }

        void insert(T value) {
            values.push_back(value);

            int currentIndex = values.size() - 1;

            while(currentIndex > 0) {
                int parentIndex = parent(currentIndex);

                T currentVal = values[currentIndex];
                T parentVal = values[parentIndex];

                if (compare(currentVal, parentVal) == currentVal) {
                    swap(currentIndex, parentIndex);
                    currentIndex = parentIndex;
                    continue;
                }

                break;
            }
        }

        T pop() {

            if (values.empty()) {
                return T();
            }

            T valToReturn = values.front();
            values[0] = values.back();
            values.pop_back();

            int currentIndex = 0;

            while(true) {

                // Find the max child.
                int priorityChildIndex = findPriorityChildIndex(currentIndex);

                if (priorityChildIndex == -1) {
                    break;
                }

                T currentVal = values[currentIndex];

                if (compare(currentVal, values[priorityChildIndex]) == currentVal) {
                    break;
                }

                swap(priorityChildIndex, currentIndex);

                currentIndex = priorityChildIndex;
            }

            return valToReturn;
        }

        int findPriorityChildIndex(int parentIndex) {

            int leftChildIndex = leftChild(parentIndex);
            int rightChildIndex = rightChild(parentIndex);

            int lastIndex = values.size() - 1;

            if (leftChildIndex > lastIndex) {
                return -1;
            }

            if (rightChildIndex > lastIndex) {
                return leftChildIndex;
            }

            int leftChildVal = values[leftChildIndex];
            int rightChildVal = values[rightChildIndex];

            return compare(leftChildVal, rightChildVal) == leftChildVal ? leftChildIndex : rightChildIndex;
        }
};

template<typename T>
class MinHeap : public Heap<T> {   
    public:
        MinHeap() : Heap<T>([](T a, T b) {return a < b ? a : b; }) {
            std::cout << "Min heap constructor called" << std::endl;
        }

        MinHeap(std::vector<T> values) : MinHeap() {
            std::cout << "Min heap param constructor called" << std::endl;

            for (auto it = values.begin(); it != values.end(); ++it) {
                Heap<T>::insert(*it);
            }
        }

        ~MinHeap() {
            std::cout << "Min heap destructor called" << std::endl;
        }
};

template<typename T>
class MaxHeap : public Heap<T> {   
    public:
        MaxHeap() : Heap<T>([](T a, T b) {return a > b ? a : b; }) {
            std::cout << "Max heap constructor called" << std::endl;
        }

        MaxHeap(std::vector<T> values) : MaxHeap() {
            std::cout << "Max heap param constructor called" << std::endl;

            for (auto it = values.begin(); it != values.end(); ++it) {
                Heap<T>::insert(*it);
            }
        }

        ~MaxHeap() {
            std::cout << "Max heap destructor called" << std::endl;
        }
};


int main() {

    std::vector<double> values{400, 1, 2, -2, 100, 300,10};

    auto h = std::make_shared<MinHeap<double>>(std::move(values));

    while (!h->empty()) {
        const auto& front = h->pop();
        std::cout << "val: " << front << std::endl;
    }
}