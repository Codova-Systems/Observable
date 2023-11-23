/*===================*\
|*   System Usings   *|
\*===================*/

using System;
using System.Collections.Generic;

namespace Codova
{
    /*==========================*\
    |*   CLASS: Observable<T>   *|
    \*==========================*/
    
    public class Observable<T>
    {
        /*==================*\
        |*   Constructors   *|
        \*==================*/

        public Observable(T init) { m_value = init; }

        /*=============================*\
        |*   Public Member Functions   *|
        \*=============================*/

            /*============*\
            |*   Getter   *|
            \*============*/

            public T GetValue() { return m_value; }

            /*==============*\
            |*   Controls   *|
            \*==============*/

            public void ChangeValue(T value)
            {
                // Get former value
                // ----------------
                T from = m_value;

                // Set new value
                // -------------
                m_value = value;

                // Notify
                // ------
                Notify(from, m_value);
            }
            public void AddListener(Action<T, T> listener)     { m_listeners.Add(listener); }
            public void RemoveListener(Action<T, T> listener)  { m_listeners.Remove(listener); }

        /*================================*\
        |*   Protected Member Functions   *|
        \*================================*/

            /*=================*\
            |*   Data Memory   *|
            \*=================*/

            protected T m_value                     = default;
            protected List<Action<T,T>> m_listeners = new List<Action<T, T>>();

        /*==============================*\
        |*   Private Member Functions   *|
        \*==============================*/

            /*=================*\
            |*   Auxiliaries   *|
            \*=================*/

            void Notify(T from, T to)
            {
                // Iterate over listeners
                // ----------------------
                foreach (var listener in m_listeners)
                {
                    // Decouple listeners
                    // ------------------
                    try                  { listener.Invoke(from, to); }
                    catch (Exception ex) { Console.WriteLine("Listener: " + listener.Method.Name + " crashed!"); }
            }
    }
}
}