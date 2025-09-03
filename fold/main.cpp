#include <iostream>


template<typename ...Args>
void Print(Args... args) {
    (std::cout << args << ...);
}


int main() {
    Print("A", "B", "C");
    return 0;
}