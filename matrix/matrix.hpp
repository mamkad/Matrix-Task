#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cstddef>

using std::string;
using std::vector;

using matrix_element_t = double;

class matrix {
    private:
        matrix_element_t* buff_ = nullptr;  // matrix data
        size_t rows_ = 0, colls_ = 0;       // rows and colls
        size_t buffsize_ = 0;               // size of buffer (rows_ * colls_)

    private:
        void reset();   // reset params

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
        void clear();                    // clear matrix content
        void resize(size_t, size_t);     // resize matrix. if matrix was not empty, old content is deleting

    public:
        matrix_element_t& at(size_t, size_t);               // get matrix element by i and j without check
        matrix_element_t const& at(size_t, size_t) const;   // get matrix element by i and j without check
    
        size_t rows()  const noexcept; 
        size_t colls() const noexcept;
        size_t size()  const noexcept; // size of buffer (rows_ * colls_)
        bool isempty() const noexcept; // check 
    
    public:
        bool readfromfile(string const&); 
        bool writetofile(string const&); 
        void print();
};
