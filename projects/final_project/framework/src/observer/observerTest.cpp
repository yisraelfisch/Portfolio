#include <iostream>
#include <unistd.h>
#include "observer.hpp"


namespace ilrd
{

class Publisher
{
public:
    Publisher();
    ~Publisher();
    void Subscribe(const Callback<int>& callback);
    void UnSubscribe(const Callback<int>& callback);
    void Notify(int x);
private:
    Dispatcher<int>* m_dispatcher;

};

Publisher::Publisher():m_dispatcher(new Dispatcher<int>)
{}

Publisher::~Publisher()
{
    delete m_dispatcher;
}

void Publisher::Subscribe(const Callback<int> &callback)
{
    m_dispatcher->Add(callback);
}


void Publisher::UnSubscribe(const Callback<int> &callback)
{
    m_dispatcher->Remove(callback);
}
void Publisher::Notify(int x)
{
    m_dispatcher->Notify(x);
}

class Subscriber
{
public:
    virtual void OnUpdate(int x) = 0;
};

class Subone : public Subscriber
{
public:
    Subone():m_callback(Callback<int>(Function<void(int)>(&Subone::OnUpdate, this)))
    {}

    virtual void OnUpdate(int x)
    {
        std::cout << "num was update to:\n" << x << std::endl;
    }
    const Callback<int>& GetCallback();

private:
    const Callback<int> m_callback;

};

const Callback<int> &Subone::GetCallback()
{
    return m_callback;
}

}

using namespace ilrd;

int main()
{
    Publisher publish;
    Subone sub1;
    Subone sub2;
    Subone sub3;

    sleep(1);
    publish.Notify(1);
    publish.Subscribe(sub1.GetCallback());
    publish.Subscribe(sub2.GetCallback());
    publish.Subscribe(sub3.GetCallback());


    sleep(1);
    publish.Notify(2);


    return 0;
}