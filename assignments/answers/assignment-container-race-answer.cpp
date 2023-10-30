// Container race: clock different container functions


/* ANSWERS:

Vector pushBack() duration: 2.2946
Vector popBack() duration: 0.481
Vector insertBegin() duration: 2.6609
Vector eraseBegin() duration: 39.6022
Vector insertEnd() duration: 0.0076
Vector eraseEnd() duration: 0.0048

Deque pushBack() duration: 8.5564
Deque popBack() duration: 0.4209
Deque insertBegin() duration: 0.1462
Deque eraseBegin() duration: 0.0384
Deque insertEnd() duration: 0.084
Deque eraseEnd() duration: 0.0365

List pushBack() duration: 26.7244
List popBack() duration: 23.0174
List insertBegin() duration: 0.2546
List eraseBegin() duration: 0.1701
List insertEnd() duration: 0.2579
List eraseEnd() duration: 0.1682


For list, inserting and deleting elements anywhere is cheap performance-wise. This is why insertEnd, insertBegin(), eraseEnd(), and eraseBegin() have similar performances.

Deques are similar to vectors, but insertion and deletion is efficient also at the beginning of the container.

For vector, deleting and inserting elements at the end of the vector is cheap but not elsewhere (such as in the beginning). When appending elements elsewhere, the elements towards the end of the vector have to be relocated, which is not efficient.
This is why insertEnd() and eraseEnd() are faster than insertBegin() and eraseBegin() for the vector, and also why insertBegin() and eraseBegin() for the vector are slower than for the list and for the deque.

Vectors have a single array that is usually larger than the current number of elements in the vector, but if the vector grows past it, it has to be reallocated.
Deques may have their elements scattered in different memory locations.

For push_back(), vectors and deques both automatically reserve extra space, but differently.
With very large containers, vectors tend to win in performance.
However, with the numbers in this example, the method deque uses appears to be a combination of faster in terms of individual operations and less calls in total.
This would explain why push_back() is faster for deque.

List performs the worst for push_back() and pop_back() because it is designed to be faster than deque and vector in situations where we insert and delete anywhere (including the middle) in the container, rather than being optimized for the back of the container (vector) or the front and the back of the container (deque).
Inserting and deleting in the middle of a large container is where list should outperform deque and vector, but we did not test that condition.

Note that your results may differ depending on your system, how you implement the operations and whether you preallocate storage for the containers. The point of this exercise was to have you delve into the differences between the containers.
*/

#include <iostream>
#include <chrono>
#include <vector>
#include <deque>
#include <list>


// function templates for clocking the container methods to test

template <typename container>
double pushBack(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e6; ++i) {
        con.push_back(i);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}

template <typename container>
double popBack(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e6; ++i) {
        con.pop_back();
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}

template <typename container>
double insertBegin(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e4; ++i) {
        con.insert(con.begin(), i);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}


template <typename container>
double eraseBegin(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e4; ++i) {
        con.erase(con.begin());
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}

template <typename container>
double insertEnd(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e4; ++i) {
        con.insert(con.end(), i);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}


template <typename container>
double eraseEnd(container& con) {
    std::chrono::time_point<std::chrono::high_resolution_clock> timeStart = std::chrono::high_resolution_clock::now(); // start counting time
    for (int i = 0; i < 1e4; ++i) {
        con.erase(--con.end());
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> timeFinish = std::chrono::high_resolution_clock::now(); // finish counting time
    double durationByValue = std::chrono::duration<double, std::milli>(timeFinish - timeStart).count(); // count the duration that passed between the time points
    return durationByValue;
}



int main()
{
    {
        std::vector<int> vec;
        std::cout << "Vector pushBack() duration: " << pushBack(vec) << std::endl;
        std::cout << "Vector popBack() duration: " << popBack(vec) << std::endl;
        std::cout << "Vector insertBegin() duration: " << insertBegin(vec) << std::endl;
        std::cout << "Vector eraseBegin() duration: " << eraseBegin(vec) << std::endl;
        std::cout << "Vector insertEnd() duration: " << insertEnd(vec) << std::endl;
        std::cout << "Vector eraseEnd() duration: " << eraseEnd(vec) << std::endl;
    }
    
    std::cout << std::endl;

    {
        std::deque<int> deq;
        std::cout << "Deque pushBack() duration: " << pushBack(deq) << std::endl;
        std::cout << "Deque popBack() duration: " << popBack(deq) << std::endl;
        std::cout << "Deque insertBegin() duration: " << insertBegin(deq) << std::endl;
        std::cout << "Deque eraseBegin() duration: " << eraseBegin(deq) << std::endl;
        std::cout << "Deque insertEnd() duration: " << insertEnd(deq) << std::endl;
        std::cout << "Deque eraseEnd() duration: " << eraseEnd(deq) << std::endl;
    }

    std::cout << std::endl;

    {
        std::list<int> lis;
        std::cout << "List pushBack() duration: " << pushBack(lis) << std::endl;
        std::cout << "List popBack() duration: " << popBack(lis) << std::endl;
        std::cout << "List insertBegin() duration: " << insertBegin(lis) << std::endl;
        std::cout << "List eraseBegin() duration: " << eraseBegin(lis) << std::endl;
        std::cout << "List insertEnd() duration: " << insertEnd(lis) << std::endl;
        std::cout << "List eraseEnd() duration: " << eraseEnd(lis) << std::endl;
    }

}