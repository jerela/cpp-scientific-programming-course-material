// cpp-course.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

class LCG {
public:

    // constructor, sets the random seed
    LCG(long long int seed) {
        setSeed(seed);
    }

    // set the initial random seed
    void setSeed(long long int seed) {
        pseudorandomNumber_ = seed;
    }

    // generates a new pseudorandom number
    void generate() {
        // first do the basics of the linear congruential generator
        long long int m = 101;
        long long int a = 7;
        long long int c = 31;
        pseudorandomNumber_ = (a * pseudorandomNumber_ + c) % m;

        // now we have a pseudorandom integer between 0 and m-1, convert it to double
        pseudorandomDouble_ = (double)pseudorandomNumber_;

        // scale between min_ and max_
        pseudorandomDouble_ *= (max_ - min_) / (double)m;

        // recenter so the values fall between min_ and max_
        pseudorandomDouble_ += min_;

        std::cout << pseudorandomNumber_ << ", " << pseudorandomDouble_ << std::endl;
    }

    // sets the min and max values for the pseudorandom double
    void setBoundaries(double min, double max) { min_ = min; max_ = max; }

    // returns the latest generated pseudorandom double
    double getDouble() { return pseudorandomDouble_; }

private:
    // initial random seed and subsequent integers
    long long int pseudorandomNumber_ = 0;
    // pseudorandom double from the latest generation
    double pseudorandomDouble_ = 0;
    // boundaries for the pseudorandom double
    double min_ = 0;
    double max_ = 0;
};

int main()
{

    // define how many points to use
    const unsigned int n = 1000;

    // create two double arrays
    double randoms1[n];
    double randoms2[n];

    double rangeMin = -10;
    double rangeMax = 10;

    // construct two pseudorandom number generators with different initial seeds
    LCG lcg1((long long int)time(0));
    LCG lcg2((long long int)time(0) + 10000);

    // set the boundaries of the generators
    lcg1.setBoundaries(rangeMin, rangeMax);
    lcg2.setBoundaries(rangeMin, rangeMax);

    // generate a desired number of doubles
    for (unsigned int i = 0; i < n; ++i)
    {
        lcg1.generate();
        randoms1[i] = lcg1.getDouble();
        lcg2.generate();
        randoms2[i] = lcg2.getDouble();
    }


    // sum all generated doubles and calculate the mean
    double sum1 = 0;
    double sum2 = 0;
    for (unsigned int i = 0; i < n; ++i) {
        sum1 += randoms1[i];
        sum2 += randoms2[i];
    }
    double mean1 = sum1 / n;
    double mean2 = sum2 / n;

    // calculate the standard deviation of generated doubles
    double squaredErrors1 = 0;
    double squaredErrors2 = 0;
    for (unsigned int i = 0; i < n; ++i) {
        squaredErrors1 += pow(randoms1[i] - mean1, 2);
        squaredErrors2 += pow(randoms2[i] - mean2, 2);
    }
    double std1 = sqrt(squaredErrors1 / n);
    double std2 = sqrt(squaredErrors2 / n);

    std::cout << "Generator 1, mean: " << mean1 << ", standard deviation: " << std1 << std::endl;
    std::cout << "Generator 2, mean: " << mean2 << ", standard deviation: " << std2 << std::endl;

    // print out the standard deviation of a uniform distribution for our range; if our generators' standard deviations match it, they generate numbers from a uniform distribution
    std::cout << "The standard deviation of a uniform distribution for our range is " << (rangeMax - rangeMin) / sqrt(12) << std::endl;

    unsigned int withinStd1 = 0;
    unsigned int withinStd2 = 0;
    for (unsigned int i = 0; i < n; ++i) {
        if (abs(randoms1[i] - mean1) < std1)
            ++withinStd1;
        if (abs(randoms2[i] - mean2) < std2)
            ++withinStd2;
    }

    // for a normal distribution, approximately 68% of the values should be within one standard deviation from the mean
    std::cout << "Generator 1 has " << 100 * (double)withinStd1 / (double)n << "% of its values within one standard deviation of the mean." << std::endl;
    std::cout << "Generator 2 has " << 100 * (double)withinStd2 / (double)n << "% of its values within one standard deviation of the mean." << std::endl;



}

