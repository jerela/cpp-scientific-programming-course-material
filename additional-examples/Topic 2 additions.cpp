/* Example: difference between passing by value, passing by reference, and passing by const reference when calling functions
- passing by value creates a local copy of the argument in the scope of the function
- passing by reference doesn't, which is fast when passing large objects and allows you to modify the argument inside the function
- passing by const reference assumes that the argument won't be modified by the function; theoretically the fastest way to pass large objects as arguments
- furthermore, rvalues (objects that are not stored into a named variable) cannot be arguments when calling by reference
*/

#include <iostream>

int funcValue(int in) {
    return in;
}

int funcReference(int& in) {
    return in;
}

int funcConstRef(const int& in) {
    return in;
}

int main()
{
    int a = funcValue(1 + 2); // valid
    int b = funcReference(1 + 2); // error
    int c = funcConstRef(1 + 2); // valid
}
