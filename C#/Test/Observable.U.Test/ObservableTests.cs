/*===================*\
|*   System Usings   *|
\*===================*/

using System;

/*===================*\
|*   Custom Usings   *|
\*===================*/

using NUnit.Framework;

namespace Codova
{
    /*============================*\
    |*   CLASS: ObservableTests   *|
    \*============================*/
    
    public class ObservableTests
    {
        [Test]
        public void Lambda_Listeners_Get_Called()
        {
            Observable<int> observable = new Observable<int>(0);
            observable.AddListener((from, to) =>
            {
                Console.WriteLine("Changing from " + from + " to " + to);
                Assert.True(from == 0);
                Assert.True(to == 1);
            });
            observable.ChangeValue(1);
        }
        [Test]
        public void Funcational_Listeners_Get_Called()
        {
            Observable<int> observable = new Observable<int>(2);
            observable.AddListener(Notify);
            observable.ChangeValue(3);
        }
        private void Notify(int from, int to)
        {
            Console.WriteLine("Changing from " + from + " to " + to);
            Assert.True(from == 2);
            Assert.True(to == 3);
        }
        [Test]
        public void Class_Listeners_Get_Called()
        {
            TestClass testClass         = new TestClass();
            Observable<int> observable  = new Observable<int>(3);
            observable.AddListener(testClass.Notify);
            observable.ChangeValue(1);
        }
        private class TestClass
        {
            public void Notify(int from, int to)
            {
                Console.WriteLine("Changing from " + from + " to " + to);
                Assert.True(from == 3);
                Assert.True(to == 1);
            }

        }
        [Test]
        public void Listeners_Do_Not_Influence_One_Another()
        {
            Observable<int> observable = new Observable<int>(3);
            observable.AddListener(FaultyFunction);
            observable.AddListener(WorkingFunction);
            observable.ChangeValue(1);
        }
        private void FaultyFunction(int from, int to)  { throw new NotImplementedException(); }
        private void WorkingFunction(int from, int to) 
        { 
            Console.WriteLine("WorkingFunction still gets called!"); 
            Assert.True(true); 
        }
    }
}