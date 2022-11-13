#pragma once 

#include <memory>
#include <atomic>
#include <vector>
#include <thread>

using std::atomic;
using std::thread;
using std::vector;

#include "..\matrix\matrix.hpp"

class matrix_multiplication {
    private:
        matrix const& leftmatr_;
        matrix const& rightmatr_;

        matrix resmatr_;
        
        atomic<size_t> count_of_calc_element{0};
        size_t thread_count_ = 0;

        vector<thread> threads_;

    public:
        matrix_multiplication() = default;
        matrix_multiplication(matrix const&, matrix const&, size_t);

    public:
        bool multiply(matrix&);

    //private:
        void work(size_t coll);
};
