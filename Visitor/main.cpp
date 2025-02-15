#include <iostream>
#include <variant>
using namespace std;

// Basic method
class Visitor
{
public:
    virtual void Accept(class ConcreteElementA &element) = 0;
};

class Element
{
public:
    virtual void Visit(Visitor &visitor) = 0;
};

class ConcreteElementA : public Element
{
public:
    void Visit(Visitor &visitor) override
    {
        visitor.Accept(*this);
    }
};

class ConcreteVisitor1 : public Visitor
{
public:
    void Accept(ConcreteElementA &element) override
    {
        cout << "ConcreteVisitor1 visited ConcreteElementA" << endl;
    }
};
// End of basic method

// Morden method - Using variant
class PrintResult
{
public:
    void operator()(int i) const
    {
        cout << "int: " << i << endl;
    }

    void operator()(string i) const
    {
        cout << "string: " << i << endl;
    }

    void operator()(double i) const
    {
        cout << "double: " << i << endl;
    }
};

using Result = variant<int, double, string>;

int main()
{
    // For basic method
    ConcreteElementA elementA;
    ConcreteVisitor1 visitor1;
    elementA.Visit(visitor1);

    // For morden method
    Result r = "morning.";

    visit(PrintResult(), r);

    return 0;
}