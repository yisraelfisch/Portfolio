/*********************************
 * Reviewer: 
 * Author: poli m. phizem		
 * Poly and Gavri
 * File: Bitarray.hpp
 * ******************************/


#pragma once
#include <vector>
#include <algorithm>
#include <cstddef> //size_t
#include <cstring> //memset, memcpy

namespace ilrd
{

class BitCounter
{
public:

    void operator()(const size_t& chunk)
    {
        size_t temp_chunk = chunk;
        
        while(temp_chunk)
        {
            ++m_bit_counter;
            temp_chunk &= (temp_chunk - 1);
        }
    }

    operator size_t() const{return m_bit_counter;}
private:
    size_t m_bit_counter;

};

class ShiftBits
{
public: 

    ShiftBits(const size_t shift): m_shift(shift % (sizeof(size_t) * __CHAR_BIT__ )){}

    size_t operator()(const size_t& current, const size_t& next)
    {
        return ((current << m_shift) | (next >> ((sizeof(size_t) * __CHAR_BIT__)  - m_shift)));
    }
private:

    size_t m_shift;

};


template<size_t SIZE>
class BitArray
{
private:
    class Proxy;


public:
    explicit BitArray(); // Ctor 

	bool operator==(const BitArray& other);
    Proxy operator[](size_t index); 
   	bool operator[](size_t index) const;
    
    BitArray& operator<<=(size_t shift);
	//BitArray& operator>>=(size_t shift);
    size_t CountBitsOn();
    bool GetBit(size_t index) const;
    void SetBit(size_t index, bool val);
    void PrintBitArray();



    
private:
    void PrintChunk(size_t chunk);
	static const size_t ChunkSize = sizeof(size_t) * __CHAR_BIT__;
	static const size_t m_size = (SIZE + ChunkSize - 1)/ChunkSize; 
	//size_t m_arr[m_size];
    std::vector<size_t> m_arr;					
    
};// Class BitArray


template<size_t SIZE>
class BitArray<SIZE>::Proxy 
{
    public:
        Proxy(BitArray& bit_arr, size_t index);//CTOR
        Proxy& operator=(const Proxy& other);                            
        Proxy& operator=(const bool other_val);                           //Assignment
        operator bool() const;

    private:
        BitArray& m_bit_arr;
        size_t m_index;
};//class Proxy
    
    template<size_t SIZE>
    BitArray<SIZE>::BitArray(): m_arr(m_size, 0)
    {
        //memset(m_arr, 0, m_size*sizeof(size_t));
    }

    template<size_t SIZE>
    bool BitArray<SIZE>::operator==(const BitArray<SIZE> &other)
    {
        return this->m_arr == other.m_arr;
        //return (memcmp(&this->m_arr[0], &other.m_arr[0], m_size  * sizeof(size_t)) == 0);
    }

    template<size_t SIZE>
    typename BitArray<SIZE>::Proxy BitArray<SIZE>::operator[](size_t index)
    {
        return Proxy(*this, index);
    }

    template<size_t SIZE>
    bool BitArray<SIZE>::operator[](size_t index) const
    {
        return GetBit(index);
    }

    template<size_t SIZE>
    BitArray<SIZE>& BitArray<SIZE>::operator<<=(size_t shift)
    {
        size_t move_index = shift/ChunkSize;
        std::transform(m_arr.begin() + move_index,
                        m_arr.end() - 1,
                        m_arr.begin() + move_index + 1,
                        m_arr.begin() , ShiftBits(shift));

        ShiftBits temp(shift);                 
        *(m_arr.end() - 1 - move_index) = temp(*(m_arr.end()-1),0);
        
        if(move_index)
        {
            memset(&(m_arr[m_size - move_index]), 0, move_index*sizeof(size_t));
        }
        return *this;
    }

    template<size_t SIZE>
    size_t BitArray<SIZE>::CountBitsOn()
    {
        /* BitCounter count = std::for_each(m_arr.begin(), m_arr.end(), BitCounter());
        return count.m_bit_counter; */
        size_t count = std::for_each(m_arr.begin(), m_arr.end(), BitCounter());
        return count;
    }


    template<size_t SIZE>
    bool BitArray<SIZE>::GetBit(size_t index) const
    {
        return m_arr[m_size - 1 - index/ChunkSize] & 1UL << (index % ChunkSize);
    }

    template<size_t SIZE>
    void BitArray<SIZE>::SetBit(size_t index, bool val)
    {
        m_arr[m_size - 1 - index/ChunkSize] &= ~1UL << (index % ChunkSize);
        m_arr[m_size - 1 - index/ChunkSize]|= (static_cast<size_t>(val) << (index % ChunkSize));  
       //  |= (static_cast<size_t>(val) << (index  % ChunkSize - 1 ));
    }

    template<size_t SIZE>
    void BitArray<SIZE>::PrintBitArray()
    {
        for(size_t i = m_size - 1 ; i >= 1; --i)
        {
            PrintChunk(m_arr[i]);
        }
        PrintChunk(m_arr[0]);
    }

    template<size_t SIZE>
    void BitArray<SIZE>::PrintChunk(size_t chunk)
    {
        char buff[sizeof(size_t)*__CHAR_BIT__];
        int i = sizeof(size_t)*__CHAR_BIT__ - 1;
        

        while(i >= 0)
        {
            *(buff + i) = (chunk % 2) + '0';
            chunk /= 2;
            --i;
        }
        std::cout << buff << std::endl;
    }




    //-----------proxy functions--------------

    template<size_t SIZE>
    BitArray<SIZE>::Proxy::Proxy(BitArray& bit_arr, size_t index): m_bit_arr(bit_arr), m_index(index){}

    template<size_t SIZE>
    typename BitArray<SIZE>::Proxy &BitArray<SIZE>::Proxy::operator=(const Proxy &other)
    {
        return *this = static_cast<bool>(other);
        //this->m_bit_arr.SetBit(this->m_index, other.m_bit_arr.GetBit(other.m_index));
        //return *this;
    }

    template<size_t SIZE>
    typename BitArray<SIZE>::Proxy&BitArray<SIZE>::Proxy::operator=(bool other_val)
    {
        this->m_bit_arr.SetBit(this->m_index, other_val);
        return *this;
    }

    template<size_t SIZE>
    BitArray<SIZE>::Proxy::operator bool() const
    {
        return (this->m_bit_arr.GetBit(this->m_index));
    }






} // namespace ilrd

