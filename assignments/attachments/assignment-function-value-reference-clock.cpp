
/* ASSIGNMENT: 
- run the code below
- the code should print how long 1000000 calls of different functions take
1. Which was faster for operating on a character variable, calling by value or calling by reference?
2. How about when operating on a string variable?
3. In the context of the memory sizes the program prints, why do you think the results are as they are?
*/

#include <iostream>
#include <chrono> // required to count the duration of programmatical operations

// passes character by value
void useCharByValue(char inChar) {
    if (inChar == 'b')
        std::cout << "inChar is b" << std::endl;
}

// passes character by reference
void useCharByReference(char &inChar) {
    if (inChar == 'b')
        std::cout << "inStr is b" << std::endl;
}

// passes string by value
void useStringByValue(std::string inStr) {
    if (inStr == "b")
        std::cout << "inStr is b" << std::endl;
}

// passes string by reference
void useStringByReference(std::string &inStr) {
    if (inStr == "b")
        std::cout << "inStr is b" << std::endl;
}


int main()
{
    // define a character and string variable to give as arguments
    char letter = 'a';
    std::string text = "Hello there.";

    // print the size of the variables (how much memory they take)
    std::cout << "Size of the character variable: " << sizeof(letter) << " bytes" << std::endl;
    std::cout << "Size of the string variable: " << sizeof(text) << " bytes" << std::endl;

    // also print the size of their addresses in memory
    std::cout << "Size of the memory address of the character variable: " << sizeof(&letter) << " bytes" << std::endl;
    std::cout << "Size of the memory address of the string variable: " << sizeof(&text) << " bytes" << std::endl;

    // define the number of times we want to call each function while timing
    unsigned int iterations = 1e6; // 1e6 is just a short way to write 1000000

    // block enclosing call by value for the character variable
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
        for (unsigned int i = 0; i < iterations; ++i) {
            useCharByValue(letter);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
        double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
        std::cout << "Char by value took " << durationByValue << " milliseconds." << std::endl; // print the duration
    }

    // block enclosing call by reference for the character variable
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
        for (unsigned int i = 0; i < iterations; ++i) {
            useCharByReference(letter);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
        double durationByReference = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
        std::cout << "Char by reference took " << durationByReference << " milliseconds." << std::endl; // print the duration
    }

    // block enclosing call by value for the string variable
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
        for (unsigned int i = 0; i < iterations; ++i) {
            useStringByValue(text);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
        double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
        std::cout << "String by value took " << durationByValue << " milliseconds." << std::endl; // print the duration
    }

    // block enclosing call by reference for the string variable
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
        for (unsigned int i = 0; i < iterations; ++i) {
            useStringByReference(text);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
        double durationByReference = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
        std::cout << "String by reference took " << durationByReference << " milliseconds." << std::endl; // print the duration
    }

}

