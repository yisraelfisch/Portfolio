/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: String.hpp
 * ******************************/

#pragma once

#include <cstddef> // size_t 
#include <ostream> //std::ostream


namespace ilrd
{

class RcString;
bool operator==(const RcString& lhs, const RcString& rhs);  // symmetric equality
bool operator!=(const RcString& lhs, const RcString& rhs);
bool operator>(const RcString& lhs, const RcString& rhs);
bool operator<(const RcString& lhs, const RcString& rhs);
std::ostream& operator<<(std::ostream& cout, const RcString& str); 


class RcString
{
    private:
        class Proxy;
        
    public:

        /* non- explicit */ RcString(const char *str = " ");	//CTOR
        RcString(const RcString& str);				            //CCTOR
        ~RcString(); 								            //Destructor
        RcString& operator=(const RcString& other_);            //Assignment
        
        
        Proxy operator[](size_t index);
        const char& operator[](size_t index) const;//impl
        const char *Cstr() const;
            
    private:

        const char& Get(size_t index);
        const char& Set(size_t index, const char c);
        class StringData;
        StringData *m_string_data;
}; // class RcString

class RcString::Proxy
{
    public:
        Proxy(RcString& str, size_t index);//CTOR
        const char& operator= (const Proxy& other_);                            
        const char& operator=(const char c);                           //Assignment
        operator char() const;

    private:
        RcString& m_str;
        size_t index;
};//class Proxy

}// namespace ilrd