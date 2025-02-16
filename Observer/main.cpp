#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/signal.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

// 1 - Normal method
class Listener
{
public:
    virtual void Update() = 0;
    virtual string GetName() = 0;
};
class Publisher
{
public:
    void Subscribe(Listener *i_subscriber)
    {
        m_subscribers.push_back(i_subscriber);
    }
    void UnSubscribe(Listener *i_subscriber)
    {
        auto it = find(m_subscribers.begin(), m_subscribers.end(), i_subscriber);
        if (it != m_subscribers.end())
        {
            m_subscribers.erase(it);
        }
    }
    void Notify()
    {
        for (auto subscriber : m_subscribers)
        {
            subscriber->Update();
        }
    }
    void PrintCurrentSubscribers()
    {
        for (auto subscriber : m_subscribers)
        {
            cout << subscriber->GetName() << endl;
        }
    }

private:
    vector<Listener *> m_subscribers;
};
class ConcreteSubscriberA : public Listener
{
public:
    void Update() override
    {
        cout << "ConcreteSubscriberA::Update" << endl;
    }

    string GetName() override
    {
        return "ConcreteSubscriberA";
    }
};
class ConcreteSubscriberB : public Listener
{
public:
    void Update() override
    {
        cout << "ConcreteSubscriberB::Update" << endl;
    }

    string GetName() override
    {
        return "ConcreteSubscriberB";
    }
};

// 2 - Using singlal
struct Signals
{
    signal<void()> sigA;
    signal<void(int)> sigB;
}

struct TestClass
{
    void ReceiverForA()
    {
        cout << "TestClass::ReceiverForA" << endl;
    }

    void ReceiverForB(int i_value)
    {
        cout << "TestClass::ReceiverForB: " << i_value << endl;
    }
}

main()
{
    // 1 - Normal method
    Publisher publisher;
    ConcreteSubscriberA subscriberA;
    ConcreteSubscriberB subscriberB;
    publisher.Subscribe(&subscriberA);
    publisher.Subscribe(&subscriberB);
    publisher.PrintCurrentSubscribers();
    publisher.Notify();

    // 2 - Using singlal
    Signals signals;
    TestClass testClass;
    signals.sigA.connect(bind(&TestClass::ReceiverForA, &testClass));
    signals.sigB.connect(bind(&TestClass::ReceiverForB, &testClass, _1));
    signals.sigA();
    signals.sigB(10);

    return 0;
}