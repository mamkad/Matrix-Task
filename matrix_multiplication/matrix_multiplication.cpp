#include "matrix_multiplication.hpp"

#include <iostream>
#include <chrono>

using std::cout;
using std::string;
using std::cref;

// constructor by number of threads and thread timeout in seconds
matrix_multiplication::matrix_multiplication(size_t thread_count, size_t sleep_sec) : thread_count_(thread_count),  sleep_sec_(1000 * sleep_sec) {
}

void matrix_multiplication::set_thread_count(size_t v) {
    thread_count_ = v;
}

size_t matrix_multiplication::get_thread_count() const noexcept {
    return thread_count_;
}

void matrix_multiplication::set_sleep_sec(size_t v) {
    sleep_sec_ = v;
}

size_t matrix_multiplication::get_sleep_sec() const noexcept {
    return sleep_sec_;
}

 // multiply left matrix by right
bool matrix_multiplication::multiply(matrix const& leftmatr, matrix const& rightmatr, matrix& resmatr) {
    // checking that the multiplication operation makes sense for such matrices (NxK KxM)
    if (leftmatr.colls() != rightmatr.rows()) {
        cout << "\n\tWrong size of matrixes\n";
        return false;
    }
    
    // resize result matrix
    resmatr_.resize(leftmatr.rows(), rightmatr.colls()); 
  
    // creating threads
    for (size_t i = 0; i < thread_count_; ++i) {
        threads_mult.push_back(thread(&matrix_multiplication::mult, this, cref(leftmatr), cref(rightmatr)));
    }
   
    // wait threads
    for(auto& thd : threads_mult) {
        thd.join();
    }
    
    // clear threads vector and save resull in resmatr
    threads_mult.clear();
    resmatr = resmatr_;

    return true;
}

// multiplication function for threads
void matrix_multiplication::mult(matrix const& leftmatr, matrix const& rightmatr) {
    // thread loop
    while (true) { 
        mtx_.lock(); 
        // calculate the i and j elements of the new matrix, which will calculate
        size_t row = 0, coll = 0;
        // check that not all elements have been calculated yet
        if (count_of_calc_element < resmatr_.size()) {
             // ij
            row  = count_of_calc_element / resmatr_.rows(); 
            coll = count_of_calc_element % resmatr_.colls();
            mtx_.unlock();
        } else {
            mtx_.unlock();
            break;
        }
        
        // calculating the value of the new element
        matrix_element_t total = 0;   // value of new element
        size_t K = leftmatr.colls();  // (NxK KxM)
        for (size_t k = 0; k < K; ++k) {
            total += leftmatr.at(row, k) * rightmatr.at(k, coll);
        }
        resmatr_.at(row, coll) = total;
        
        // increase the counter of calculated elements
        ++count_of_calc_element; // atomic
        
        // sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_sec_));
        // cout << std::this_thread::get_id() << ' ' << count_of_calc_element << '\n';
    }
}
