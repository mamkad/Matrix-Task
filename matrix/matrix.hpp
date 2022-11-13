#pragma once

#include <memory>
#include <string>
#include <cstddef>
#include <utility>
#include <mutex>

using std::pair;
//using std::mutex;

using matrix_element_t = double;

/*
class matrix_element {
    private:
        mutex mtx_;
        matrix_element_t val_ = 0;
        bool iscalculated_ = false;

    public:
        matrix_element(matrix_element_t);
        bool set(matrix_element_t);
    
    public:
        //bool islocked()     const noexcept;
        bool iscalculated() const noexcept; 
};

matrix_element::matrix_element(matrix_element_t val) : val_(val) {

}

bool matrix_element::set(matrix_element_t val) {
    if (iscalculated()) {
        return false;
    }
    if (mtx_.try_lock()) {
        val_ = val;
        iscalculated_ = true;
        mtx_.unlock();
        return true;
    }
    return false;
}

bool matrix_element::islocked() const noexcept {
    return islocked_;
}

bool matrix_element::iscalculated() const noexcept {
    return iscalculated_;
}*/

class matrix {
    private:
        matrix_element_t* buff_ = nullptr;
        size_t colls_ = 0, rows_ = 0;
        size_t buffsize_ = 0;

    private:
        void reset();   // обнулить параметры

    public:
        matrix() = default;
        matrix(size_t, size_t);
        ~matrix();

    public:
        matrix(matrix const&);
        matrix(matrix&&);
        matrix& operator= (matrix const&);
        matrix& operator= (matrix &&);

    public:
        void clear();  // удалить всё содержимое
        void resize(size_t, size_t);

    public:
        matrix_element_t& at(size_t, size_t);
        matrix_element_t const& at(size_t, size_t) const;
        size_t colls() const noexcept;
        size_t rows()  const noexcept;
        size_t size()  const noexcept;
        size_t isempty() const noexcept;

    public:
        bool iscalculated(size_t, size_t) const noexcept;

    public:
        bool readfromfile(string const&);
        bool writetofile(string const&); 
};
