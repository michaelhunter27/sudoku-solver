#include<cstdlib>
#include<iostream>
#include<fstream>

#include "puzzle.h"
#include "cell.h"


using namespace std;

int wmain(){
    Puzzle P;

    cout << "puzzle:" << endl;

    P.print_puzzle();
    cout << endl;

    P.set_cell(0, 4, 7);
    P.set_cell(3, 4, 9);
    P.print_puzzle();

    cout << "notes for 0, 4: ";
    P.grid[0][4].print_notes();
    cout << "notes for 4, 0: ";
    P.grid[4][0].print_notes();
    cout << "notes for 4, 4: ";
    P.grid[4][4].print_notes(); 
    cout << "notes for 0, 0: ";
    P.grid[0][0].print_notes();
    cout << "notes for 2, 5: ";
    P.grid[2][5].print_notes();



    Puzzle Q;
    Q.print_puzzle();
    cout << endl;
    Q.load_puzzle("sudoku1.txt");
    Q.print_puzzle();
    cout << endl;

    cout << "notes for 0, 4: ";
    Q.grid[0][4].print_notes();
    cout << "notes for 4, 0: ";
    Q.grid[4][0].print_notes();
    cout << "notes for 4, 4: ";
    Q.grid[4][4].print_notes(); 
    cout << "notes for 0, 0: ";
    Q.grid[0][0].print_notes();
    cout << "notes for 2, 5: ";
    Q.grid[2][5].print_notes();

    return 0;
}