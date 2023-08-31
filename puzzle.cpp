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

//checks if there is only one possible value for a cell
//looking only at that cell's notes
int Puzzle::check_cell(int row, int col){
    int value = 0;
    int num_notes = 0;

    // check if only one value is possible
    for (int v = 1; v <= 9; v++){
        num_notes += grid[row][col].get_note(v);
        if (grid[row][col].get_note(v) == 1){
            value = v;
        }
    }
    if (num_notes == 1){
        return value;
    }
    return 0;
}

int Puzzle::check_row(int row, int col){
    int num_notes = 0;
    for (int v = 1; v <= 9; v++){
        if (grid[row][col].get_note(v) == 1){
            num_notes = 0;
            for (int k = 0; k < 9; k++){
                if (k != col){
                    num_notes += grid[row][k].get_note(v);
                }
            }
            if (num_notes == 0){
                return v;
            }
        }
    }
    return 0;
}

int Puzzle::check_col(int row, int col){
    int num_notes = 0;
    for (int v = 1; v <= 9; v++){
        if (grid[row][col].get_note(v) == 1){
            num_notes = 0;
            for (int k = 0; k < 9; k++){
                if (k != row){
                    num_notes += grid[k][col].get_note(v);
                }
            }
            if (num_notes == 0){
                return v;
            }
        }
    }
    return 0;
}

int Puzzle::check_box(int row, int col){
    int box_row = row / 3;
    int box_col = col / 3;
    for (int v = 1; v <= 9; v++){
        if (grid[row][col].get_note(v) == 1){
            int num_notes = 0;
            for (int r = box_row * 3; r < (box_row + 1) * 3; r++){
              for (int c = box_col * 3; c < (box_col + 1) * 3; c++){
                   if (r != row || c != col){
                        num_notes += grid[r][c].get_note(v);
                   }
                }
            }
            if (num_notes == 0){
                return v;
            }
        }
    }
    return 0;
}

void Puzzle::notes_solve(){
    int num_filled_in = 0;
    do{
        num_filled_in = 0;
        //iterate through all cells
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                
                if (grid[i][j].get_value() != 0){
                    continue;
                }
                
                int value = 0;
                
                value = check_cell(i, j);
                if (value != 0){
                    set_cell(i, j, value);
                    num_filled_in++;
                    continue;
                }

                value = check_row(i, j);
                if (value != 0){
                    set_cell(i, j, value);
                    num_filled_in++;
                    continue;
                }

                value = check_col(i, j);
                if (value != 0){
                    set_cell(i, j, value);
                    num_filled_in++;
                    continue;
                }
                        
                value = check_box(i, j);
                if (value != 0){
                    set_cell(i, j, value);
                    num_filled_in++;
                    continue;
                }
            }
        }
    }while(num_filled_in != 0);
}