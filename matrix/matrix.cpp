#include <algorithm>
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <iomanip>

using std::cout;
using std::copy_n;
using std::string;
using std::ostringstream;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::setw;
using std::endl;
using std::left;

#include "matrix.hpp"

void matrix::reset() {
    buff_ = nullptr;
    colls_ = rows_ = buffsize_ = 0;
}

matrix::matrix(size_t c, size_t r) {
    resize(c, r);
}

matrix::~matrix() {
    clear();
}

matrix::matrix(matrix const& m) {
    resize(m.colls_, m.rows_);
	copy_n(m.buff_, buffsize_, buff_);
}

matrix::matrix(matrix&& m) {
    colls_ = m.colls_;
	rows_ = m.rows_;
	buffsize_ = m.buffsize_;
	buff_ = m.buff_;
	m.reset();
}

matrix& matrix::operator= (matrix const& m) {
    if (this == &m) {
		return *this;
	}
    resize(m.colls_, m.rows_);
	copy_n(m.buff_, buffsize_, buff_);
    return *this;
}

matrix& matrix::operator= (matrix && m) {
    if (this == &m) {
		return *this;
	}
    clear();
	colls_ = m.colls_;
	rows_ = m.rows_;
	buffsize_ = m.buffsize_;
	buff_ = m.buff_;
	m.reset();
    return *this;
}

void matrix::clear() {
    if (isempty()) {
        return;
    }
    delete[] buff_;
    reset();
}

size_t matrix::isempty() const noexcept {
    return (buff_ == nullptr);
}

void matrix::resize(size_t c, size_t r) {
    clear();
    colls_ = c;
    rows_ = r;
    buffsize_ = colls_ * rows_;
    buff_ = new matrix_element_t[buffsize_];
}

matrix_element_t& matrix::at(size_t i, size_t j) {
    return buff_[i * rows_ + j];
}

matrix_element_t const& matrix::at(size_t i, size_t j) const {
    return buff_[i * rows_ + j];
}

size_t matrix::colls() const noexcept {
    return colls_;
}

size_t matrix::rows() const noexcept {
    return rows_;
}

size_t  matrix::size()  const noexcept {
    return buffsize_;
}

bool matrix::readfromfile(string const& fnamein) {
    ifstream fin(fnamein);

    if (!fin) {
        cout << "\n\tFile not found: " + fnamein + '\n';
        return false;
    }

    size_t colls, rows;
    if ( !(fin >> colls >> rows) ) {
        cout << "\n\tWrong size of matrixes\n";
        return false;
    }

    resize(colls, rows);
    for(size_t i = 0; i < colls_; ++i) {
        for(size_t j = 0; j < rows_; ++j) {
            cout << i << ' ' << j << '\n';
            if (!(fin >> at(i, j))) {
                cout << "\n\tElement is not a number\n";
                return false;
            }
        }
    }

    fin.close();
    return true;
}

bool matrix::writetofile(string const& fnameout) {
    ofstream fout(fnameout, ios_base::app);

    if (!fout) {
        cout << "\n\tError of file open: " + fnameout + '\n';
        return false;
    }

    ostringstream stream;
    for(size_t i = 0, stri = 0; i < colls_; ++i) {
        for(size_t j = 0; j < rows_; ++j) {
            stream << at(i, j);
            if (j < rows_ - 1) {
                stream << setw(20);
            } else {
                 stream << endl;
            }
        }
    }
    stream << "---------------------------------------------------------------------------\n";

    fout << stream.str();
    fout.close();

    return true;
}