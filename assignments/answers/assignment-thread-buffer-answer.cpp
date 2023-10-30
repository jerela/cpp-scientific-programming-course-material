#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <string>
#include <atomic>
#include <condition_variable>

// define the buffer (a queue of strings), a condition variable to control when the consumer thread can operate, a mutex to lock threads from using the same code concurrently, and a counter for the number of active producers as global variables
std::queue<std::string> strings;
std::condition_variable cv;
std::mutex mutex;
std::atomic<int> nProducersActive;

// function to add a string to the buffer
void addToBuffer(std::string str) {
    // lock the thread when the buffer is being pushed to
    std::unique_lock<std::mutex> lock(mutex);
    strings.push(str);
    std::cout << "pushed " << str << std::endl;
    // let the consumer know that they can operate after the string is pushed to
    cv.notify_one();
}

// function to read and pop a string from the buffer
bool takeFromBuffer() {
    // boolean to control whether the consumer thread should finish; set to true if no producers are active and the string is empty
    bool finishConsumer = false;
    // lock the thread when the buffer is being read and popped from
    std::unique_lock<std::mutex> lock(mutex);
    // wait for a producer thread or another consumer thread to notify this thread that it's OK to access the buffer
    cv.wait(lock);
    // if there is a string, read and pop it
    if (strings.size() > 0) {
        std::string str = strings.front();
        strings.pop();
        std::cout << "popped " << str << std::endl;
    }
    else {
        if (nProducersActive == 0)
            finishConsumer = true;
    }
    lock.unlock();
    // notify the next consumer thread that it can operate
    cv.notify_one();
    // return a boolean to indicate if the consumer can continue operating
    return finishConsumer;
}

// function to run in the producer threads
void producerThread(int threadIndex) {
    // add to count of active producers
    ++nProducersActive;
    // add three strings to the buffer
    for (unsigned int i = 0; i < 3; ++i) {
        addToBuffer("thread " + std::to_string(threadIndex) + ", product " + std::to_string(i+1));
    }
    // decrement count of active producers
    --nProducersActive;
}

// function to run in the consumer threads
void consumerThread(int threadIndex) {
    bool keepGoing = true;
    while (keepGoing){
        keepGoing = !takeFromBuffer();
    }
}

int main()
{
    // prepare vectors to hold the threads
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // define the number of threads
    unsigned int nProducers = 3;
    unsigned int nConsumers = 3;

    // loops to start the threads; we must use emplace_back because threads don't have a valid copy constructor (we cannot create them and then copy them to the vector)
    for (unsigned int i = 0; i < nProducers; ++i) {
        producers.emplace_back(std::thread(producerThread, i+1));
    }
    for (unsigned int i = 0; i < nConsumers; ++i) {
        producers.emplace_back(std::thread(consumerThread, i+1));
    }
    
    // iterate through the containers and make sure all threads are joined
    for (auto it = producers.begin(); it < producers.end(); ++it) {
        it->join();
    }
    for (auto it = consumers.begin(); it < consumers.end(); ++it) {
        it->join();
    }

}


