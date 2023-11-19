# Observer / Observable Pattern

This repository contains an implementation of the Observer Pattern in C++.

## Intent

"The Observer Pattern defines a one-to-many dependency between objects so that when one object changes state, 
all its dependents are notified and updated automatically." [[1]](#references)

The intent of this pattern is to create a loosely coupled relationship between objects where changes in one object trigger updates in multiple dependent objects.
It therefore makes us the inversion of control principle

## Implementation

#### Public Interfaces:

- **Constructor**: `Observable(T init)`: Initializes the observable with an initial value.
- **Destructor**: `~Observable()`: Cleans up listeners upon destruction.
- **Getter**: `T GetValue()`: Retrieves the current observed value.
- **Control Methods**:
  - `void ChangeValue(T value)`: Updates the observed value and notifies all registered listeners of the change.
  - `void AddListener(TClass* c, void(TClass::*func)(T, T))`: Adds a class method as a listener to observe value changes.
  - `void AddListener(void(*func)(T, T))`: Adds a function as a listener to observe value changes.

### How to Use

The Observer Pattern facilitates objects receiving notifications about changes in another object's state.
The Observable.h class currently supports three types of Listeners.
- Lambda Listeners
- Static Function Listeners
- Class Function Listeners

1. **Lambda Listeners**:

   ```cpp
    #include "Observable.h"

    using namespace Codova;

    int main() {
        Observable<int> observable(0);

        // Lambda listener
        observable.AddListener([](int from, int to) {
            std::cout << "Lambda listener: Value changed from " << from << " to " << to << std::endl;
        });

        // Changing the value triggers the lambda listener
        observable.ChangeValue(5);

        return 0;
    }

2. **Function Listeners**:

   ```cpp
    #include "Observable.h"

    using namespace Codova;

    // Function listener
    void testFunction(int from, int to) {
        std::cout << "Function listener: Value changed from " << from << " to " << to << std::endl;
    }

    int main() {
        Observable<int> observable(0);

        // Adding the function as a listener
        observable.AddListener(testFunction);

        // Changing the value triggers the function listener
        observable.ChangeValue(8);

        return 0;
    }

3. **Function Listeners**:

    ```cpp
    #include "Observable.h"

    using namespace Codova;

    class TestClass {
    public:
        void Notify(int from, int to) {
            std::cout << "Class method listener: Value changed from " << from << " to " << to << std::endl;
        }
    };

    int main() {
        Observable<int> observable(0);
        TestClass testClass;

        // Adding the class method as a listener
        observable.AddListener(&testClass, &TestClass::Notify);

        // Changing the value triggers the class method listener
        observable.ChangeValue(12);

        return 0;
    }


## References

- [[1]](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612)
 **Design Patterns: Elements of Reusable Object-Oriented Software** by Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides. Addison-Wesley, 1994.

## Contributors

- Pascal Möller ( office@codova.at )

## License

MIT

## Troubleshooting

If you encounter the following error: LNK1104 could not open gtest_maind.lib" 
Reinstall the Google Test dependency from nuget.
