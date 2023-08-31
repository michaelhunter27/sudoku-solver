#include<cstdlib>
#include<iostream>
#include<fstream>

#include "puzzle.h"
#include "cell.h"


using namespace std;

int wmain(){


    Puzzle Q;
    //Q.print_puzzle();
    cout << endl;
    Q.load_puzzle("sudoku1.txt");
    Q.print_puzzle();
    cout << endl;

    Q.notes_solve();
    Q.print_puzzle();
    cout << endl;

    return 0;
}