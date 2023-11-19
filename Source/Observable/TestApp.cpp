#include <iostream>

#include "Observable.h"
#include "TestClass.h"

void Notify(int from, int to) { std::cout << "[FuncListener]: Changed from " << from << " to " << to << std::endl; };

int main(int argc, char* argv[])
{
    TestClass testClass;
    Codova::Observable<int> observable(0);
    observable.AddListener(&testClass, &TestClass::Notify);
    observable.AddListener(Notify);
    observable.ChangeValue(4);
}
