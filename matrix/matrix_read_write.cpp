#include <iostream>

using namespace std;

#include "matrix.hpp"

bool read_matrix_from_file(matrix& leftmatr, matrix& rightmatr, string const& fnamein) {
    ifstream fin(fnamein);

    if(!fin) {
        cout << "\n\tFile not founed\n";
        return false;
    }

    size_t leftcolls, leftrows, rightcolls, rightrows;
    if (!(fin >> leftcolls >> leftrows >> rightcolls >> rightrows)) {
        cout << "\n\tWrong size of matrixes\n";
        return false;
    }

    leftmatr.resize(leftcolls, leftrows);
    for(size_t i = 0; i < leftmatr.colls(); ++i) {
        for(size_t j = 0; j < leftmatr.rows(); ++j) {
            if (!(fin >> leftmatr.at(i, j))) {
                cout << "\n\tElement (" << i <<  ", " << j << ") is not a number\n";
                return false;
            }
        }
    }

    rightmatr.resize(rightcolls, rightrows);
    for(size_t i = 0; i < rightmatr.colls(); ++i) {
        for(size_t j = 0; j < rightmatr.rows(); ++j) {
            if (!(fin >> rightmatr.at(i, j))) {
                cout << "\n\tElement (" << i << ", " << j << ") is not a number\n";
                return false;
            }
        }
    }
    fin.close();
    return true;
}

bool write_matrix_to_file(matrix const& matr, string const& fname) {
    ofstream fout(fname, ios_base::app);

    if (!fout) {
        cout << "\n\tError of file open\n";
        cin.get();
        return false;
    }

    string matrstr = "";
    for(size_t i = 0; i < matr.colls(); ++i) {
        for(size_t j = 0; j < matr.rows(); ++j) {
            matrstr += (to_string(matr.at(i, j)) + '\t');
        }
        matrstr += '\n';
    }

    matrstr += "---------------------------------------------------------------------------\n";
    
    fout << matrstr;
    fout.close();

    return true;
}