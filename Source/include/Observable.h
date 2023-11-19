#pragma once
#include <vector>

#include "Listener.h"

namespace Codova
{
    template<class T>
    class Observable
    {
    public:

        /*==================*\
        |*   Constructors   *|
        \*==================*/
        
        Observable(T init) { m_value = init; }
        ~Observable() { for (auto listener : m_listeners) delete listener; }

        /*============*\
        |*   Getter   *|
        \*============*/
        
        T GetValue() { return m_value; }

        /*==============*\
        |*   Controls   *|
        \*==============*/
        
        void ChangeValue(T value)
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
        template<class TClass>
        void AddListener(TClass* c, void(TClass::*func)(T, T))
        {
            // Create listener
            // ---------------
            auto listener = new ClassListener<T, TClass>(c, func);

            // Add listener
            // ------------
            m_listeners.push_back(listener);
        }
        void AddListener(void(*func)(T, T))
        {
            // Create listener
            // ---------------
            auto listener = new FuncListener<T>(func);

            // Add listener
            // ------------
            m_listeners.push_back(listener);
        }
        
    protected:

        /*=================*\
        |*   Data Memory   *|
        \*=================*/

        T m_value; 
        std::vector<Listener<T>*> m_listeners;

    private:

        /*=================*\
        |*   Auxiliaries   *|
        \*=================*/
        
        void Notify(T from, T to) 
        { 
            // Iterate over listeners
            // ----------------------
            for (auto listener : m_listeners) 
            {
                // Decouple listeners
                // ------------------
                try         { listener->Invoke(from, to); }
                catch (...) { std::cout << "[" + listener->GetName() + "]: Crashed!"; }
            }
        }

    };
}