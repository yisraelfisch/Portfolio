/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: String.hpp
 * ******************************/

#include <cstring>
#include "string.hpp"

namespace ilrd
{

static char *BuildString(const char *str)
{
    char *new_str = new char[strlen(str) + 1];
    return strcpy(new_str, str);
}

String::String(const char* str): m_str(BuildString(str))
{

}

String::String(const String& str): m_str(BuildString(str.m_str))
{

}

String::~String()
{
    CleanUp();
}

String& String::operator=(const String& other_)
{
    if(m_str!= other_)
    {
        char *new_str = BuildString(other_.m_str);
        CleanUp();
        this->m_str = new_str;
    }
    return *this;
}

char& String::operator[](size_t index)
{
    return const_cast<char&>(const_cast<const String&>(*this)[index]);
}

const char& String::operator[](size_t index) const
{
    return this->m_str[index];
}

bool operator==(const String& lhs, const String& rhs)
{
    return strcmp(&lhs[0], &rhs[0]) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return strcmp(&lhs[0], &rhs[0]) != 0;
}

bool operator>(const String& lhs, const String& rhs)
{
    return strcmp(&lhs[0], &rhs[0]) > 0;
}

bool operator<(const String& lhs, const String& rhs)
{
    return strcmp(&lhs[0], &rhs[0]) < 0;
}

std::ostream& operator<<(std::ostream& cout, const String& str)
{
    return cout << &str[0];
}

void String::CleanUp()
{
    delete[] this->m_str;
    this->m_str = NULL;
}
}
