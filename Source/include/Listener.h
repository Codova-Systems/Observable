/*
 * Copyright 2023 Codova Systems
 * Author: Pascal Möller
 *
 * SPDX-License-Identifier: MIT
 *
 * GitHub: https://github.com/Codova-Systems/Observable/tree/master
 * Date: November 19, 2023
 */

#pragma once

#include <string>

namespace Codova
{
    template<typename T>
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void Invoke(T from, T to) = 0;
        std::string GetName() { return m_name; }
    protected:
        std::string m_name;
    };

    template<typename T>
    class FuncListener : public Listener<T>
    {
    public:
        FuncListener(void(*func)(T, T)) 
        { 
            // Define inputs
            // -------------
            m_func = func; 
            // m_name = func.__func__;
        }
        void Invoke(T from, T to) override { m_func(from, to); }        
    
    protected:
        void(*m_func)(T, T);
    };

    template<typename T, class TClass>
    class ClassListener : public Listener<T>
    {
    public:
        ClassListener(TClass* c, void(TClass::*func)(T, T))
        {
            // Define inputs
            // -------------
            m_class = c;
            m_func  = func;
            // m_name  = func.__func__;
        }
        void Invoke(T from, T to) override { (m_class->*m_func)(from, to); }

    protected:
        TClass* m_class;
        void(TClass::*m_func)(T, T);
    };
}
