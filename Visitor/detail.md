# General
## Double dispatch
First, we need to know a bit about double dispatch.
Double dispatch is a special form of multiple dispatch, and a mechanism that dispatches a function call to different concrete functions depending on the runtime types of two objects involved in the call.

## What we need
1 - First dispatch
- Inside the object.

2 - Second dispatch
- It's inside the the visitor itself.
- Using the overload function for it or call to the parent class method (pure virtual).

## Structure
### Basic method
Class Visitor
    Virtual void Accept(ElementA &e) = 0;
    Virtual void Accept(ElementB &e) = 0;
Class Element
    virtual void Visit(Visitor &visitor) = 0;

Then concreteElement.Visit(concreteVisitor)

=> So, everytime we add a new element, we need to add Accept method to Visitor class (also its inherted methods).

### Morden method with varian
First, we need a variant. Using std::variant.
Then, we need a class/struct which has functors for all member of the above variant.
Finally, use `std::visit(Functors(), variantVariable)` to get the result.

# When we should/shouldn't use it
The visitor pattern's main advantage is its ability to add new operations to existing object structures without modifying the object classes themselves, promoting flexibility and maintainability. However, its major downside is the potential for increased code complexity due to the need to define separate visitor classes for each new operation, which can become cumbersome with a large object hierachy.

## Pros
- Open/Closed Principle. You can introduce a new behavior that can work with objects of different classes without changing these classes.
- Single Responsibility Principle. You can move multiple versions of the same behavior into the same class.
- A visitor object can accumulate some useful information while working with various objects. This might be handy when you want to traverse some complex object structure, such as an object tree, and apply the visitor to each object of this structure.
## Cons
- Need to update all visitors each time a class gets aded or removed from the element hierachy
- Visitors might lack the necessary access the private fields and methods of the elements that they're supposed to work with.