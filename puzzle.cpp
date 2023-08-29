#include<iostream>
#include "puzzle.h"

using namespace std;

Puzzle::Puzzle(){
    //not necessary since the constructor for the 
    //Cell class sets the value to 0
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            grid[i][j].set_value(0);
        }
    }
}

Puzzle::~Puzzle(){


}

void Puzzle::load_puzzle(){


}

void Puzzle::print_puzzle(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            grid[i][j].print_value();
            if (j == 2 || j == 5){
                cout << "|";
            }
        }
        if (i == 2 || i == 5){
            cout << endl << "---+---+---";
        }
        cout << endl;
    }
}
