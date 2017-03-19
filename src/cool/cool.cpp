//
// Created by outcastgeek on 3/19/17.
//

#include <iostream>
#include <boost/range/irange.hpp>
#include <chrono>

using namespace std::chrono;

// Check this out: https://github.com/AnthonyCalandra/modern-cpp-features#template-argument-deduction-for-class-templates

template<typename... Args>
bool logicalAnd(Args... args) {
    // Binary folding.
    return (true && ... && args);
}

template<typename... Args>
auto sum(Args... args) {
    // Unary folding.
    return (... + args);
}

int main(int argc, char** argv){

    bool b = true;
    bool& b2 = b;

    auto boolRes = logicalAnd(b, b2, true); // == true
    std::cout << "Folded Boolean: " << boolRes << std::endl;

    auto sumRes = sum(1.0, 2.0f, 3); // == 6.0
    std::cout << "Folded Sum: " << sumRes << std::endl;

    // Destructuring
    std::tuple<int, bool, double> my_obj {1, false, 2.0};
    // later on...
    int x;
    bool y;
    bool yy;
    double z;
    std::tie(x, y, z) = my_obj;
    std::cout << "X: " << x << ", Y: " << y << ", Z: " << z << std::endl;
    // or, if we don't want all the contents:
    std::tie(std::ignore, yy, std::ignore) = my_obj;
    std::cout << "YY: " << yy << std::endl;

    // Chrono
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::cout << "Printing out 1000 stars... \n";
    for(auto i : boost::irange(1, 1000)) std::cout << "*";
    std::cout << std::endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;

    return 0;
}
