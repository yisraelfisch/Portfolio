#include <iostream>
#include "bit_array.hpp"
const size_t bitarray_size = 180;



/* void PrintChunk(size_t chunk)
{
    char buff[sizeof(size_t)*__CHAR_BIT__];
	int i = sizeof(size_t)*__CHAR_BIT__ - 1;
	assert(str);

	while(i >= 0)
	{
		*(str + i) = (chunk % 2) + '0';
		chunk /= 2;
		--i;
	}
	std::cout << buff << std::endl;
} */

int main ()
{
    ilrd::BitArray<bitarray_size> array1;
    ilrd::BitArray<bitarray_size> array2;
    ilrd::BitArray<bitarray_size> array3;

    //std::cout << sizeof(array1) << std::endl;

    bool res1 = array1 == array2;
    if(!res1)
    {
        std::cout <<  "erorr - not equal" << std::endl;
    }

    if(array1[110])
    {
        std::cout <<  "erorr true" << std::endl;
    }

    array1[25] = array1[110] = true;

    bool res2 = array1 == array2;

    if(res2)
    {
        std::cout <<  "erorr -equal" << std::endl;
    }

    if(!array1[110])
    {
        std::cout <<  "erorr false" << std::endl;
    }

    array1[25] = array1[110] = false;

    if(array1[110] && array1[25])
    {
        std::cout <<  "erorr true" << std::endl;
    }
    
    bool res3 = false;
    array2[80] = true;
    array1[110] = res3 = array2[80];

    if(!array1[110] && !array1[25])
    {
        std::cout <<  "erorr false" << std::endl;
    }
   
    if(array1.CountBitsOn() != 1UL)
    {
        std::cout << "erorr count bit on" << std::endl;
    }

    array1[0] = true;
     if(array1.CountBitsOn() != 2UL)
    {
        std::cout << "erorr count bit on" << std::endl;
    }
    array3[0] = true;
    //array3[64] = true;
    array3[128] = true;

    array3.PrintBitArray();
    array3 <<= 65;
    std::cout << "after shift " << std::endl;
    array3.PrintBitArray();
    
    return 0;
}