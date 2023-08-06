/*********************************
 * Reviewer:  
 * Author:             
 * File: function.hpp
 * ******************************/

#pragma once
#include <memory>
#include <iostream>
namespace ilrd
{

template <typename>
class Function;
//-------------------first tamplate specialization-----------
template <typename RET>
class Function<RET(void)>
{
public:

    explicit Function(){};
    
    template <typename BIND_ARG>
    explicit Function(RET (*callable)(BIND_ARG arg), BIND_ARG arg); 
    // Free function Ctor
    
    template <typename T, typename BIND_ARG>
    explicit Function(RET (T::*callable)(BIND_ARG arg), T *object, BIND_ARG arg); 
    // Member function Ctor

    RET operator()();

private:
    class IFunction;
    std::shared_ptr<IFunction> m_ifunction;

    template <typename BIND_ARG>
    class FreeFunction;

    template <typename T, typename BIND_ARG>
    class MemberFunction; 

}; // class Function

template <typename RET>
class Function<RET(void)>::IFunction
{
public:
    explicit IFunction() {}
    virtual ~IFunction() {}
    virtual RET Run() = 0;

}; // class Function<RET(void)::IFunction

template <typename RET>
template <typename BIND_ARG>
class Function<RET(void)>::FreeFunction: public Function::IFunction
{
public:
    explicit FreeFunction(RET (*callable)(BIND_ARG arg), BIND_ARG arg);
    // ~FreeFunction() {}

    RET Run();

private:
    RET (*m_callable)(BIND_ARG arg);
    BIND_ARG m_arg;

}; // class Function<RET(void)>::FreeFuncion

template <typename RET>
template <typename T, typename BIND_ARG>
class Function<RET(void)>::MemberFunction: public Function::IFunction
{
public:
    explicit MemberFunction(RET (T::*callable)(BIND_ARG arg), T *obj, BIND_ARG arg);
    // ~MemberFunction() {}

    RET Run();

private:
    RET (T::*m_callable)(BIND_ARG arg);
    T *m_obj;
    BIND_ARG m_arg;

}; // class Function<RET(void)>::MemberFunction

/* *******class Function impl*************************************************** */

template <typename RET>
template <typename BIND_ARG>
inline Function<RET(void)>::Function(RET (*callable)(BIND_ARG arg), BIND_ARG arg):
        m_ifunction(new FreeFunction<BIND_ARG>(callable, arg)){}

template <typename RET>
template <typename T, typename BIND_ARG>
inline Function<RET(void)>::Function(RET (T::*callable)(BIND_ARG arg), T *object, BIND_ARG arg):
        m_ifunction(new MemberFunction<T, BIND_ARG>(callable, object, arg)){}

template <typename RET>
inline RET Function<RET(void)>::operator()()
{
    return m_ifunction->Run();
}

/* *******class FreeFunction impl*********************************************** */

template <typename RET>
template <typename BIND_ARG>
inline Function<RET(void)>::FreeFunction<BIND_ARG>::FreeFunction(RET (*callable)(BIND_ARG arg), BIND_ARG arg):
        m_callable(callable), m_arg(arg){}

template <typename RET>
template <typename BIND_ARG>
inline RET Function<RET(void)>::FreeFunction<BIND_ARG>::Run()
{
    return m_callable(m_arg);
}

/* *******class MemberFunction impl********************************************* */

template <typename RET>
template <typename T, typename BIND_ARG>
inline Function<RET(void)>::MemberFunction<T, BIND_ARG>::MemberFunction(RET (T::*callable)(BIND_ARG arg), T *object, BIND_ARG arg):
        m_callable(callable), m_obj(object), m_arg(arg){}

template <typename RET>
template <typename T, typename BIND_ARG>
inline RET Function<RET(void)>::MemberFunction<T, BIND_ARG>::Run()
{
    return (m_obj->*m_callable)(m_arg);
}




//-------------------second tamplate specialization-----------


template <typename RET, typename INVOCATION_ARG>
class Function<RET(INVOCATION_ARG)>
{
public:

    explicit Function(){};
    
    explicit Function(RET (*callable)(INVOCATION_ARG)); 
    // Free function Ctor
    
    template <typename T>
    explicit Function(RET (T::*callable)(INVOCATION_ARG), T *object); 
    // Member function Ctor

    RET operator()(INVOCATION_ARG arg) const;

private:
    class IFunction;
    std::shared_ptr<IFunction> m_ifunction;

    class FreeFunction;

    template <typename T>
    class MemberFunction; 

}; // class Function

template <typename RET, typename INVOCATION_ARG>
class Function<RET(INVOCATION_ARG)>::IFunction
{
public:
    explicit IFunction() {}
    virtual ~IFunction() {}
    virtual RET Run(INVOCATION_ARG arg) = 0;

}; // class Function<RET(void)::IFunction

template <typename RET, typename INVOCATION_ARG>
class Function<RET(INVOCATION_ARG)>::FreeFunction : public Function::IFunction
{
public:
    explicit FreeFunction(RET (*callable)(INVOCATION_ARG arg));
    // ~FreeFunction() {}
    RET Run(INVOCATION_ARG arg);

private:
    RET (*m_callable)(INVOCATION_ARG);

}; // class Function<RET(INVOCATION_ARG)>::FreeFuncion

template <typename RET, typename INVOCATION_ARG>
template <typename T>
class Function<RET(INVOCATION_ARG)>::MemberFunction : public Function::IFunction
{
public:
    explicit MemberFunction(RET (T::*callable)(INVOCATION_ARG), T *obj);
    // ~MemberFunction() {}

    RET Run(INVOCATION_ARG arg);

private:
    RET (T::*m_callable)(INVOCATION_ARG);
    T *m_obj;

}; // class Function<RET(INVOCATION_ARG)>::MemberFunction

/* *******class Function impl*************************************************** */

template <typename RET, typename INVOCATION_ARG>
inline Function<RET(INVOCATION_ARG)>::Function(RET (*callable)(INVOCATION_ARG)):
        m_ifunction(new FreeFunction(callable)){}

template <typename RET, typename INVOCATION_ARG>
template <typename T>
inline Function<RET(INVOCATION_ARG)>::Function(RET (T::*callable)(INVOCATION_ARG), T *object):
        m_ifunction(new MemberFunction<T>(callable, object)){}

template <typename RET, typename INVOCATION_ARG>
inline RET Function<RET(INVOCATION_ARG)>::operator()(INVOCATION_ARG arg) const
{
    return m_ifunction->Run(arg);
}

/* *******class FreeFunction impl*********************************************** */

template <typename RET, typename INVOCATION_ARG>
inline Function<RET(INVOCATION_ARG)>::FreeFunction::FreeFunction(RET (*callable)(INVOCATION_ARG)):
        m_callable(callable){}

template <typename RET, typename INVOCATION_ARG>
inline RET Function<RET(INVOCATION_ARG)>::FreeFunction::Run(INVOCATION_ARG arg)
{
    return m_callable(arg);
}

/* *******class MemberFunction impl********************************************* */

template <typename RET, typename INVOCATION_ARG>
template <typename T>
inline Function<RET(INVOCATION_ARG)>::MemberFunction<T>::MemberFunction(RET (T::*callable)(INVOCATION_ARG), T *object):
        m_callable(callable), m_obj(object){}

template <typename RET, typename INVOCATION_ARG>
template <typename T>
inline RET Function<RET(INVOCATION_ARG)>::MemberFunction<T>::Run(INVOCATION_ARG arg)
{
    return (m_obj->*m_callable)(arg);
}
} // namespace ilrd
