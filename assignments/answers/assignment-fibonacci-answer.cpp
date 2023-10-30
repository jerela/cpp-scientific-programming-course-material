// A solution for topic 2 assignments, assignment 5
// Here we chose that the sequence starts with 0 and that the first index is 0. You may have chosen differently.

#include <iostream>

// non-recursive version that can be read somewhat understandably
unsigned long int fibonacci(unsigned int n) {
    unsigned long int prev = 0;
    unsigned long int recent = 1;
    unsigned long int next = prev + recent;

    // if the index of the number is 0 or 1, we return that index because the 0th fibonacci number is 0 and the 1st fibonacci number is 1 (both values correspond to the index)
    if (n == 0 || n == 1)
        return n;
    else {
        for (unsigned int i = 2; i <= n; ++i) {
            next = prev + recent;
            prev = recent;
            recent = next;
        }
        return recent;
    }
}

// recursive version that is short but horrible to read
unsigned long int recursiveFibonacci(unsigned long int n) {
    // if the index of the number is 0 or 1, we return that index because the 0th fibonacci number is 0 and the 1st fibonacci number is 1 (both values correspond to the index)
    if (n == 0 || n == 1)
        return n;
    else // otherwise, we recursively call the same functions with decreasing n until we finally get back to n==1 or n==0 and return a proper value and terminate the recursion
        return recursiveFibonacci(n - 2) + recursiveFibonacci(n - 1);
}

int main()
{
    // print numbers for different indices
    for (unsigned int n = 0; n < 22; ++n) {
        std::cout << "Non-recursive function, n=" << n << ": " << fibonacci(n) << std::endl;
        std::cout << "Recursive function, n=" << n << ": " << recursiveFibonacci(n) << std::endl;
    }
}
