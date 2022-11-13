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
        matrix resmatr_;
        mutex mtx_;
        
        atomic<size_t> count_of_calc_element{0};

        vector<thread> threads_mult;
        size_t thread_count_ = 0;

        size_t sleep_sec_; // atof

    public:
        matrix_multiplication(size_t, size_t);

    public:
        void set_thread_count(size_t);
        size_t get_thread_count() const noexcept;

        void set_sleep_sec(size_t);
        size_t get_sleep_sec() const noexcept;

        bool multiply(matrix const&, matrix const&, matrix&);
    private:
        void mult(matrix const&, matrix const&);
};
