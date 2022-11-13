#include <iostream>

using std::string;
using std::cout;
using std::atoi;

#include "matrix\matrix.hpp"
#include "matrix_multiplication\matrix_multiplication.hpp"

bool check_file_extension(string const&);

int main(int argc, char** argv) {
    if (argc != 5) {
        cout << "\n\tWrong count of arguments\n";
        return -1;
    }

    string fname_matrleft = argv[1], fname_matrright = argv[2], fname_out = argv[3];
    if ( (!check_file_extension(fname_matrleft)) || (!check_file_extension(fname_matrright)) || (!check_file_extension(fname_out)) ) {
        return -1;
    }

    int thread_count = atoi(argv[4]);
    if ( !thread_count || thread_count < 0 ) {
        cout << "\n\tWrong input of thread count\n";
        return -1;
    }

    matrix leftmatr, rightmatr;
    if ( (!leftmatr.readfromfile(fname_matrleft)) || (!rightmatr.readfromfile(fname_matrright)) ) {
        return -1;
    }

    leftmatr.writetofile("f.txt");
    rightmatr.writetofile("f2.txt");

    matrix resmatr;
    matrix_multiplication matrix_mult(leftmatr, rightmatr, leftmatr.colls());
    if (!matrix_mult.multiply(resmatr)) {
        return -1;
    }

    if (!resmatr.writetofile(fname_out)) {
        return -1;
    }

    cout << "\n\tresult saved in: " + fname_out << '\n';

    return 0;
}

bool check_file_extension(string const& fname) {
    size_t pos = fname.find(".txt");
    if (pos == string::npos) {
        cout << "\n\tFiles must have txt extension: " + fname << '\n';
        return false;
    }
    return true;
}