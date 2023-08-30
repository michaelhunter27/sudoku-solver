#include<string>
#include<iostream>
#include<fstream>

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

int Puzzle::load_puzzle(string file_name){
    ifstream file(file_name);

    if (!file.is_open()){
        cout << "unable to open file " << file_name << endl;
        return -1;
    }

    char c;
    int v;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            file.get(c);
            
            //skip over newline characters and the like
            while (c < 48 || c > 57){
                file.get(c);
            }
            v = c - 48;
            set_cell(i, j, v);
        }
    }

    file.close();
    return 0;
}

void Puzzle::print_puzzle(){
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            grid[row][col].print_value();
            if (col == 2 || col == 5){
                cout << "|";
            }
        }
        if (row == 2 || row == 5){
            cout << endl << "---+---+---";
        }
        cout << endl;
    }
}


void Puzzle::set_cell(int row, int col, int v){
    //check v is a valid value between 1 and 9
    if (v < 1 || v > 9){
        return;
    }

    grid[row][col].set_value(v);
    
    //adjust hints for other cells in same row
    for (int j = 0; j < 9; j++){
        if (j != col){
            grid[row][j].set_note(v, 0);
        }
    }

    //adjust hints for other cells in same column
    for (int i = 0; i < 9; i++){
        if (i != row){
            grid[i][col].set_note(v, 0);
        }
    }

    //adjust hints for other cells in same box
    int box_row = row / 3;
    int box_col = col / 3;
    for (int i = box_row * 3; i < (box_row + 1) * 3 ; i++){
        for(int j = box_col * 3; j < (box_col + 1) * 3; j++){
            if (i != row || j != col){
                grid[i][j].set_note(v, 0);
            }
        }
    }

}