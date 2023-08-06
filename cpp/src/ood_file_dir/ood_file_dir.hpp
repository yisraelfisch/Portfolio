/*********************************
 * Reviewer: Rami Fortis
 * Author: Berry Sakharof
 * File: file_dir.hpp
 * ******************************/

#pragma once
#include <cstddef>		/* size_t */
#include <cassert>		/* assert */
#include <vector>		/* vector */
#include <string>		/* string */

namespace ilrd
{


class iFile
{
protected:
	explicit iFile(const std::string& name);
    virtual ~iFile();
	const std::string m_name;

public: 
	virtual void List() const = 0 ;		// pure virtual
  	size_t virtual Size() const = 0;	// pure virtual
  

}; //class iFile



class File: public iFile
{

public:
	explicit File(const std::string& name, size_t file_size = 0);
	virtual ~File();
	virtual void List();
    virtual size_t Size(); 

private:
	File(const File& other);		//tells the compiler don't generate
    File& operator=(const File& other);
    size_t m_file_size;
  
}; // class File

 
class Directory: public iFile
{

public:
	explicit Directory(const std::string& name);
    virtual ~Directory();
	virtual void List();
    virtual size_t Size();
    void Add(iFile* file);
    void Remove(const std::string& name);
  
private:
	Directory(const Directory& other);	//tells the compiler don't generate
    Directory& operator=(const Directory& other);
	std::vector <iFile *> m_arr;

}; // class Directory

} // namespace ilrd



