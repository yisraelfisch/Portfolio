/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: String.hpp
 * ******************************/

#include <cstring> //strcpy
#include "string.hpp"

namespace ilrd
{

    class RcString::StringData
    {
        public:
            static StringData* Create(const char *str);
            bool IsShared();
            void Attach();
            void Detach();
            char *Cstr();
            const char& Get(size_t index);
            const char& Set(size_t index, const char c);
            
        private:
            explicit StringData(const char *str);
            size_t m_ref_counter;
            char m_string[1];
    };// class RCString

    //-----------------Proxy- functions-----------------

    RcString::Proxy::Proxy(RcString &str, size_t index): m_str(str), index(index){}//Proxy ctor

    const char &RcString::Proxy::operator=(const RcString::Proxy &other_)
    {
        return *this = static_cast<char>(other_);
        //return *this = other_.m_str.Get(other_.index); option a;   
    }

    const char& RcString::Proxy::operator=(char c)
    {
        if(m_str.m_string_data->IsShared())
        {
            m_str.m_string_data->Detach();
            m_str.m_string_data = m_str.m_string_data->Create(m_str.Cstr());
        }

        return m_str.Set(index, c);   
    }

    RcString::Proxy::operator char() const
    {
        return m_str.Get(index);
    }


    //-----------------StringData- functions-----------------
    RcString::StringData::StringData(const char *str): m_ref_counter(1)//StringData ctor
    {
        strcpy(m_string, str);
    }

    RcString::StringData* RcString::StringData::Create(const char *str)
    {
        void *buff = ::operator new (offsetof(StringData, m_string) + strlen(str) + 1);
        return new (buff) StringData(str);
    }

    bool RcString::StringData::IsShared()
    {
        return this->m_ref_counter > 1;
    }

    void RcString::StringData::Attach()
    {
        this->m_ref_counter++;
    }

    void RcString::StringData::Detach()
    {
        this->m_ref_counter--;
        if (this->m_ref_counter == 0)
        {
            delete this;
        }
    }

    char* RcString::StringData::Cstr()
    {
        return this->m_string;
    }

    const char &RcString::StringData::Get(size_t index)
    {
        return this->m_string[index];
    }

    const char &RcString::StringData::Set(size_t index, char c)
    {
        return this->m_string[index] = c;
    }

    //-----------------RcString-functions-----------------

    RcString::RcString(const char *str) : m_string_data(StringData::Create(str)){}//RcString ctor


    RcString::RcString(const RcString& str)//RcString cctor
    {
        this->m_string_data = str.m_string_data;
        this->m_string_data->Attach();
    }

    RcString &RcString::operator=(const ilrd::RcString &other_)
    {
        this->m_string_data->Detach();

        this->m_string_data = other_.m_string_data;
        this->m_string_data->Attach();
        
        return *this;
    }

    RcString::~RcString()//RcString dtor
    { 
            this->m_string_data->Detach();
    }

    RcString::Proxy RcString::operator[](size_t index)
    {
        return Proxy(*this, index);
    }

    const char& RcString::operator[](size_t index) const
    {
        return this->Cstr()[index];
    }

    const char *RcString::Cstr() const
    {
        return this->m_string_data->Cstr();
    }       

    const char &RcString::Get(size_t index)
    {
        return this->m_string_data->Get(index);
    }

    const char &RcString::Set(size_t index, char c)
    {
        return this->m_string_data->Set(index, c);
    }
//-----------------RcString-non_member-functions-----------------

    bool operator==(const RcString& lhs, const RcString& rhs)
    {
        return !strcmp(lhs.Cstr(), rhs.Cstr());
    }

    bool operator!=(const RcString& lhs, const RcString& rhs)
    {
        return strcmp(lhs.Cstr(), rhs.Cstr());
    }

    bool operator>(const RcString& lhs, const RcString& rhs)
    {
        return strcmp(lhs.Cstr(), rhs.Cstr()) > 0;
    }

    bool operator<(const RcString& lhs, const RcString& rhs)
    {
        return strcmp(lhs.Cstr(), rhs.Cstr()) < 0;
    }

    std::ostream& operator<<(std::ostream& cout, const RcString& str)
    {
        return cout << str.Cstr();
    }
    
}