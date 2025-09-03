#include<iostream>
#include<future>

int main() {

    std::function<int(int,std::promise<int>&)> fn = [](int a, std::promise<int>& b) {

        std::cout << "calling fn" << std::endl;

        auto f = b.get_future();

        return a + f.get();
    };

    std::promise<int> data;

    std::future<int> f = std::async(std::launch::async, fn, 1, std::ref(data));

    std::cout << "launched async" << std::endl;

    data.set_value(22);

    std::cout << "result: " << f.get() << std::endl;

    return 0;

}