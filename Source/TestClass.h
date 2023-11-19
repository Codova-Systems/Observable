#pragma once
#include <iostream>

class TestClass
{
public:

    template <typename T>
    void Print(T t) { std::cout << t << std::endl; }
    void Notify(int from, int to) { std::cout << "Changed from " << from << " to " << to << std::endl; };
};
