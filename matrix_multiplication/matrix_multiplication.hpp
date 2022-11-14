#pragma once 

#include <memory>
#include <atomic>
#include <vector>
#include <thread>
#include <mutex>

using std::atomic;
using std::thread;
using std::vector;
using std::mutex;

#include "../matrix/matrix.hpp"

class matrix_multiplication {
    private:
        matrix resmatr_;  // result matrix
        mutex mtx_;       // mutex
        
        atomic<size_t> count_of_calc_element{0}; // atomic current number of matrix elements computed by threads

        vector<thread> threads_mult; // threads vector
        size_t thread_count_ = 0;    // thread count

        size_t sleep_sec_; // thread timeout in seconds

    public:
        // constructor by number of threads and thread timeout in seconds
        matrix_multiplication(size_t, size_t);

    public:
        void set_thread_count(size_t);
        size_t get_thread_count() const noexcept;

        void set_sleep_sec(size_t);
        size_t get_sleep_sec() const noexcept;
        
        // multiply left matrix by right
        bool multiply(matrix const&, matrix const&, matrix&);
    
    private:
        // multiplication function for threads
        void mult(matrix const&, matrix const&);
};
