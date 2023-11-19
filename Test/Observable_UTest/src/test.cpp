#include "pch.h"
#include "Observable.h"

using namespace Codova;

TEST(ObservableTest, LambdaListenersGetCalled) 
{
	Observable<int> observable(0);
	observable.AddListener([](int from, int to)
	{
		std::cout << "Changing from " << from << " to " << to << std::endl;
		EXPECT_TRUE(from == 0);
		EXPECT_TRUE(to == 1);
	});
	observable.ChangeValue(1);
}

void testFunction(int from, int to)
{
	std::cout << "Changing from " << from << " to " << to << std::endl;
	EXPECT_TRUE(from == 3);
	EXPECT_TRUE(to == 5);
}

TEST(ObservableTest, FuncationalListenersGetCalled)
{
	Observable<int> observable(3);
	observable.AddListener(testFunction);
	observable.ChangeValue(5);
}

class TestClass
{
public:
	void Notify(int from, int to) 
	{ 
		std::cout << "Changed from " << from << " to " << to << std::endl;
		EXPECT_TRUE(from == 2);
		EXPECT_TRUE(to == 3);
	};
};

TEST(ObservableTest, ClassListenersGetCalled)
{
	TestClass testClass;
	Observable<int> observable(2);
	observable.AddListener(&testClass, &TestClass::Notify);
	observable.ChangeValue(3);
}