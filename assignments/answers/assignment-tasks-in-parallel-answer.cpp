// assignment-tasks-in-parallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <thread>

// read the file into a vector
std::vector<bool> readGenders() {

    // first, read the contents of the file into a vector of strings
    std::vector<std::string> fileContents;
    std::ifstream ifs;
    ifs.open("predictors.txt", std::ifstream::in);
    if (ifs.is_open()){
        while (!ifs.eof()) {
            char newString[256];
            ifs.getline(newString, 256, '\n');
            fileContents.push_back(newString);
        }
    }
    ifs.close();

    // then, knowing the gender is either 0 by 1 at the end of the string, read that end of the string and push booleans to a vector correspondingly
    std::vector<bool> genders;
    for (unsigned int i = 0; i < fileContents.size(); ++i) {
        bool gender = true;
        char genderChar = *--(fileContents[i].end());
        if (genderChar == '1')
            gender = true;
        else if (genderChar == '0')
            gender = false;
        genders.push_back(gender);
    }

    return genders;
}

void countAllMales(std::vector<bool> genderVector) {
    int n = 0;
    for (auto it = genderVector.begin(); it < genderVector.end(); ++it) {
        if (*it)
            ++n;
    }
    std::cout << "Number of rows corresponding to males in vector: " << n << std::endl;
}

void countMales(std::vector<bool> genderVector, unsigned int start, unsigned int end) {
    int n = 0;
    for (unsigned int i = start; i < end; ++i) {
        if (genderVector[i])
            ++n;
    }
    std::cout << "Number of rows corresponding to males between indices " << start << " and " << end << ": " << n << std::endl;
}

int main()
{
    std::vector<bool> genders = readGenders();

    // count all males without threads
    countAllMales(genders);

    // find the index halfway through the vector
    int cutoff = (int)genders.size() / 2;

    // count males in two subtasks
    std::thread thr1(countMales, genders, 0, cutoff);
    std::thread thr2(countMales, genders, cutoff, genders.size());

    // make sure the threads have finished before the main function goes out of scope
    thr1.join();
    thr2.join();

}
