/*
 * False Sharing Experiment
 *
 * This program demonstrates a simple experiment to compare sequential and 
 * threaded execution. The experiment is designed to observe (or eventually 
 * trigger) cache-related performance issues such as false sharing when two 
 * threads operate on variables that reside on the same cache line.
 *
 * How to use:
 *   - Set USE_THREADS to 1 to run the operations concurrently.
 *   - Set USE_THREADS to 0 to run them sequentially.
 *
 * Build with a C++11-compliant compiler, e.g.:
 *     g++ -std=c++11 -O2 main.cpp -o main
 */

#include <iostream>
#include <chrono>
#include <thread>

// Set to 1 to run fx() and fy() in separate threads (concurrent mode)
// or 0 to run them sequentially.
#define USE_THREADS 1

using ms = std::chrono::milliseconds;

struct SharedData {
    int x = 0;
    int y = 1; 
};

// struct alignas(64) SharedData {
//     int x = 0;
//     int y = 1; 
// };


SharedData sharedData;

// modifying operation 
void fx() {
    for (int i = 0; i < 1000000; i++) {
        sharedData.x++;
    }
}

// non-modifying operation
void fy() {
    int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += sharedData.y;
    }
    if (sum == 0) {
        std::cout << "";
    }
}

int main() {
    std::cout << "False Sharing Experiment\n";
#if USE_THREADS
    std::cout << "Running in threaded mode.\n";
#else
    std::cout << "Running in sequential mode.\n";
#endif

    // Run the experiment 20 times and report the elapsed time for each run.
    for (int i = 0; i < 20; i++) {
        auto start = std::chrono::system_clock::now();

#if USE_THREADS
        std::thread threadFx(fx);
        std::thread threadFy(fy);
        threadFx.join();
        threadFy.join();
#else
        fx();
        fy();
#endif

        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<ms>(end - start).count();
        std::cout << "Time: " << duration << " milliseconds" << std::endl;
    }

    return 0;
}
