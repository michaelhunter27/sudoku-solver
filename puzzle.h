#ifndef PUZZLE_H
#define PUZZLE_H

#include "cell.h"


class Puzzle{
    private:
        Cell grid[9][9];
        
    
    public:
        Puzzle();
        ~Puzzle();
        
        void load_puzzle();
        void print_puzzle();


    



};



#endif