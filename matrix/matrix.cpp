#include "matrix.hpp"

#include <algorithm>
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <iomanip>

using std::cout;
using std::copy_n;
using std::ostringstream;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::setw;

// reset params
void matrix::reset() {
   buff_ = nullptr;
   rows_ = 0;
   colls_ = 0;
   buffsize_ = 0;
}

// constructor by rows and colls
matrix::matrix(size_t r, size_t c) {
    resize(r, c);
}

matrix::~matrix() {
    clear(); // deleting content
}

matrix::matrix(matrix const& m) {
    resize(m.rows_, m.colls_);
	copy_n(m.buff_, buffsize_, buff_);
}

matrix::matrix(matrix&& m) {
    rows_ = m.rows_;
    colls_ = m.colls_;
    buffsize_ = m.buffsize_;
    buff_ = m.buff_;
    m.reset();
}

matrix& matrix::operator= (matrix const& m) {
    if (this == &m) {
	return *this;
    }
    resize(m.rows_, m.colls_);
    copy_n(m.buff_, buffsize_, buff_);
    return *this;
}

matrix& matrix::operator= (matrix && m) {
    if (this == &m) {
	return *this;
    }
    clear();
    rows_ = m.rows_;
    colls_ = m.colls_;
    buffsize_ = m.buffsize_;
    buff_ = m.buff_;
    m.reset();
    return *this;
}

// clear matrix content
void matrix::clear() {
    if (isempty()) { // if matrix is empty return
        return;
    }
    delete[] buff_; // 
    reset();
}

bool matrix::isempty() const noexcept {
    return (buff_ == nullptr);
}

// resize matrix. if matrix was not empty, old content is deleting
void matrix::resize(size_t r, size_t c) {
    clear();
    rows_ = r;
    colls_ = c;
    buffsize_ = rows_ * colls_;
    buff_ = new matrix_element_t[buffsize_];
}

// get matrix element by i and j without check
matrix_element_t& matrix::at(size_t i, size_t j) {
    return buff_[i * colls_ + j];
}

// get matrix element by i and j without check
matrix_element_t const& matrix::at(size_t i, size_t j) const {
    return buff_[i * colls_ + j];
}

size_t matrix::colls() const noexcept {
    return colls_;
}

size_t matrix::rows() const noexcept {
    return rows_;
}

// size of buffer (rows_ * colls_)
size_t  matrix::size()  const noexcept {
    return buffsize_;
}

bool matrix::readfromfile(string const& fnamein) {
    ifstream fin(fnamein);
	
    // if file is not open
    if (!fin) {
        return false;
    }

    // the first two numbers in the file are interpreted as rows and columns of the matrix
    size_t rows, colls;
    if ( !(fin >> rows >> colls) ) {
        return false;
    }
    
    // allocating buffer and writing remaining  numbers from file to allocated buffer
    resize(rows, colls);
    for(size_t i = 0; i < rows_; ++i) {
        for(size_t j = 0; j < colls_; ++j) {   
            if (!(fin >> at(i, j))) {
                return false;
            }
        }
    }

    fin.close();
    return true;
}

bool matrix::writetofile(string const& fnameout) {
    ofstream fout(fnameout, ios_base::app);
    
    // if file is not open
    if (!fout) {
        return false;
    }
    
    // convert matrix conent to str 
    ostringstream stream;
    for(size_t i = 0, stri = 0; i < rows_; ++i) {
        for(size_t j = 0; j < colls_; ++j) {
            stream << at(i, j);
            if (j < colls_ - 1) {
                stream << setw(20);
            } else {
                 stream << '\n';
            }
        }
    } 
	
    // add end line
    stream << "---------------------------------------------------------------------------\n";
    
    // write to file
    fout << stream.str();
    fout.close();

    return true;
}

void matrix::print() {
    cout << "\n\tresult:\n\t";
    for(size_t i = 0; i < rows_; ++i) {
        for(size_t j = 0; j < colls_; ++j) {   
            cout << at(i, j) << setw(5);
        }
        cout << "\n\t";
    }
    cout << '\n';
}
