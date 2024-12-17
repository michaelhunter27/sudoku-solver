#ifndef PUZZLE_H
#define PUZZLE_H

#include<string>
#include<iostream>
#include<fstream>

#include "cell.h"

using namespace::std;

class Puzzle{
    private:
        Cell grid[9][9];
        
    
    public:
        
        Puzzle();
        ~Puzzle();
        
        void clear_puzzle();
        int load_puzzle(string);
        void copy_puzzle_to(Puzzle *);
        void copy_puzzle_from(Puzzle);
        void print_puzzle();
        void set_cell(int, int, int);
        int get_cell(int, int);
        int check_cell(int, int);
        int check_row(int, int);
        int check_col(int, int);
        int check_box(int, int);
        void notes_solve();
        void guess_solve();
        int solve();
        int is_solved();

};

#endif