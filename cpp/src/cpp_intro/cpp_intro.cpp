#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>


// Ex 38 - Exception saftey Ctors
using namespace std;

struct X
{
    X() { cerr << "X Ctor" << endl; throw int(9); }
    X(int) { cerr << "X Ctor (int)" << endl; }
    ~X() { cerr << "X Dtor" << endl;}
};

struct Y
{
    Y() {cerr << "Y Ctor" << endl; }
    ~Y() {cerr << "Y Dtor" << endl; }
};

class L
{
public:
    L() : m_x() { cerr << "L Ctor" << endl;}
    ~L() {cerr << "L Dtor" << endl; }
private:
    Y m_y;
    X m_x;
    static int m_;

};



class M
{
public:
    M()  { cerr << "M Ctor" << endl;}
    ~M() {cerr << "M Dtor" << endl; }
private:
    X m_x;
    Y m_y;

};

class N
{
public:
    N()  { cerr << "N Ctor" << endl;}
    ~N() {cerr << "N Dtor" << endl; }
private:
    X m_x;
    Y m_y;

};

class J
{
public:
    J(): m_y(new Y), m_x(new X)  { cerr << "J Ctor" << endl;}
    ~J() {cerr << "J Dtor" << endl; delete m_x; delete m_y; }
private:
    X *m_x;
    Y *m_y;

};

class K
{
public:
    K()  {cerr << "K Ctor" << endl; try{m_y = new Y, m_x = new X;} catch(int& i)
    {delete m_y;  exit(1);} }
    ~K() {cerr << "K Dtor" << endl; delete m_x; delete m_y; }
private:
    X *m_x;
    Y *m_y;

};

int main()
{
    L a;
    cout << L::m_;
    /*try 
    {
        K var1;
    }
    catch(int& e)
    {
        cerr << "exception cout. what:" << e << endl; exit(1);
    }*/
    return 0;
}

