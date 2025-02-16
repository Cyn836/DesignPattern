# General
Observer is a behavior design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they're observing.

## Structure
1. Normal method
Necessary classes:
- We need a class like Publisher which is going to notify the change.
    - Have an array/vector to save current subscribed listener
    - Subscribe/Ubsubscirbe function
    - Some logic that call to `Update` function of the Listeners
- Another class like Listener with have a pure virtual function (like `Update`) which will be called by Publisher.

2. Using signal (we need to install boost for this)
- Instead of using a vector of Listener, we just create a function to emit a signal then class which was connected to this signal wihh receive the change.
- This approanch won't require to maintain the list of Subscrible, also won't require a unite interface.

# When we should/shouldn't use it
- We should use this pattern when the changes to the state of one object may require changing other objects, and the actual set of objects is unknown beforehand or changes dynamically.
- When some objects must observe others, but only for a limited time or in specific cases.

## Pros
- Open/Closed Principle: You can introduce new subscriber classes without having to change the publisher's code (and vice versa if there's a publisher interface)
- You can establish relattions between objects at runtime

## Cons
- Subscribers are notified in random order