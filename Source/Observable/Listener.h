#pragma once

namespace Codova
{
    template<typename T>
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void Invoke(T from, T to) = 0;
    };

    template<typename T>
    class FuncListener : public Listener<T>
    {
    public:
        FuncListener(void(*func)(T, T)) { m_func  = func; }
        void Invoke(T from, T to) override { m_func(from, to); }
        
        void(*m_func)(T, T);
    };

    template<typename T, class TClass>
    class ClassListener : public Listener<T>
    {
    public:
        ClassListener(TClass* c, void(TClass::*func)(T, T))
        {
            m_class = c;
            m_func  = func;
        }
        void Invoke(T from, T to) override { (m_class->*m_func)(from, to); }
        
        TClass* m_class;
        void(TClass::*m_func)(T, T);
    };
}
