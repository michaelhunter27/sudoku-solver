#ifndef PUZZLE_H
#define PUZZLE_H

#include<string>
#include<iostream>
#include<fstream>

#include "cell.h"

using namespace::std;

class Puzzle{
    private:
        //Cell grid[9][9];
        
    
    public:
        Cell grid[9][9];
        
        Puzzle();
        ~Puzzle();
        
        int load_puzzle(string);
        void print_puzzle();
        void set_cell(int, int, int);


    



};



#endif