#include <iostream>

using std::cout;
using std::string;

#include "matrix_multiplication.hpp"

void test() {

}

matrix_multiplication::matrix_multiplication(matrix const& leftmatr, matrix const& rightmatr, size_t thread_count) 
    : leftmatr_(leftmatr), rightmatr_(rightmatr), thread_count_(thread_count) {
}

bool matrix_multiplication::multiply(matrix& resmatr) {
    if (leftmatr_.rows() != rightmatr_.colls()) {
        cout << "\n\tWrong size of matrixes\n";
        return false;
    }
    resmatr_.resize(leftmatr_.colls(), rightmatr_.rows()); 
    
    //thread t1(test);
    
    /*
    for (size_t i = 0; i < thread_count_; ++i) {
        //thread a([&](){});
    }

     for (int i = 0; i < threads.size(); i++) {
        if (threads[i].joinable()) {
            thread::id id = threads[i].get_id();
            threads[i].join();
            cout << "Thread with id " << id << " finished.\n";
        }
    }

    for(auto& th : threads_) {
        th.join();
    }*/
    /*
    for (size_t i = 0; i < resmatr_.colls(); ++i) {
        for (size_t j = 0; j < resmatr_.rows(); ++j) {
            matrix_element_t total = 0;
            for (size_t k = 0; k < leftmatr_.rows(); ++k) {
                total += leftmatr_.at(i, k) * rightmatr_.at(k, j);
            }
            resmatr_.at(i, j) = total;
        }
    }
    resmatr = resmatr_;*/
    return true;
}

void matrix_multiplication::work(size_t coll) {
    while (count_of_calc_element < resmatr_.size()) {
        this_thread::sleep_for(chrono::milliseconds(2000));

        size_t coll = count_of_calc_element % resmatr_.colls() + 1; /// ? 
        size_t row = count_of_calc_element / resmatr_.rows() - 1;

        cout << i << '\n';

        matrix_element_t total = 0;
        for (size_t k = 0; k < leftmatr_.rows(); ++k) {
            total += leftmatr_.at(coll, k) * rightmatr_.at(k, row);
        }
        resmatr_.at(i, j) = total;

        ++count_of_calc_element;
    }





    //while (countOfCalcElement != resmatr.size()) {
        for (size_t j = 0; j < resmatr_.rows(); ++j) {
            matrix_element_t total = 0;
            for (size_t k = 0; k < resmatr_.colls(); ++k) {
                total += leftmatr_.at(coll, k) * rightmatr_.at(k, j);
            }
            resmatr_.at(coll, j) = total;
        }
       // ++countOfCalcElement;
    //}
}