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
        matrix_element_t* buff_ = nullptr;
        size_t rows_ = 0, colls_ = 0;
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
        size_t rows()  const noexcept;
        size_t colls() const noexcept;
        size_t size()  const noexcept;
        bool isempty() const noexcept;

    public:

    public:
        bool readfromfile(string const&);
        bool writetofile(string const&); 
        void print();
};
