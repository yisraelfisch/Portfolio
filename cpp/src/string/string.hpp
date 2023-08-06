/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: String.hpp
 * ******************************/

#pragma once

#include <cstddef> /* size_t */
#include <ostream> 


namespace ilrd
{

class String;
bool operator==(const String& lhs, const String& rhs); // symmetric equality
bool operator!=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
std::ostream& operator<<(std::ostream& cout, const String& str); 


class String
{
public:

    /* non- explicit */ String(const char *str = "");	//CTOR
    String(const String& str);				        //CCTOR
    ~String(); 								        //Destructor
    String& operator=(const String& other_);        //Assignment
	  
    
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
		
private:

    void CleanUp();
    char *m_str;
}; // class String

}// namespace ilrd

