#include <iostream>
#include <memory>

void demonstrateRawPointers() {
    int* number = new int(1);
    delete number; // never forget this!
}

int main()
{
    for (unsigned int i = 0; i < 1e8; ++i) {
        demonstrateRawPointers();
        //demonstrateSmartPointers(); // Implement this function and remove the comments from this line.
    }


}

