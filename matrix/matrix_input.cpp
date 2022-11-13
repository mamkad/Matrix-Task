#include <iostream>
#include <fstream> 

using namespace std;

#include "matrix.hpp"

/*
bool read_matrix_from_console(matrix& leftmatr, matrix& rightmatr) {
    size_t leftcolls, leftrows, rightcolls, rightrows;

    cout << "Введите размерность матриц\n\tРазмерность первой матрицы: ";
    cin >> leftcolls >> leftrows;

    if (!cin) {
        cout << "Неправильный ввод\n";
        cin.get();
        return false;
    }

    if (!leftcolls || !leftrows) {
        cout << "Нельзя вводить нулевые значения\n";
        cin.get();
        return false;
    }

    cout << "\tРазмерность второй матрицы: ";
    cin >> rightcolls >> rightrows;

    if (!cin) {
        cout << "Неправильный ввод\n";
        cin.get();
        return false;
    }

    if (!rightcolls || !rightrows) {
        cout << "Нельзя вводить нулевые значения\n";
        cin.get();
        return false;
    }

    cout << "Ввод первой матрицы:\n";
    leftmatr.resize(leftcolls, leftrows);
    for(size_t i = 0; i < leftmatr.colls(); ++i) {
        for(size_t j = 0; j < leftmatr.rows(); ++j) {
            cin >> leftmatr.at(i, j);
        }
        cout << '\n';
    }

    cout << "Ввод второй матрицы:\n";
    rightmatr.resize(rightcolls, rightrows);
    for(size_t i = 0; i < rightmatr.colls(); ++i) {
        for(size_t j = 0; j < rightmatr.rows(); ++j) {
            cin >> rightmatr.at(i, j);
        }
        cout << '\n';
    }

    return true;
}
*/



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