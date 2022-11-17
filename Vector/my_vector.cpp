#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray<int> test(3);
    test.push_back(2);
    test.push_back(1);
    test.push_back(3);
    test.print();
    test.resize(2);
    std::cout << std::endl;
    test.print();
    //test.resize(5);
    //std::cout << std::endl;
    //test.print();
    std::cout << std::endl;
    std::cout << test.size() << std::endl;
    std::cout << test.get_capacity() << std::endl;
    test.push_back(8);
    test.print();
    std::cout << std::endl;
    std::cout << test.size() << std::endl;
    std::cout << test.get_capacity() << std::endl;
    test.reserve(10);
    std::cout << test.get_capacity() << std::endl;
    test.shrink_to_fit();
    std::cout << test.get_capacity() << std::endl;
}

