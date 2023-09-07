#include<string>
#include<iostream>
#include<fstream>

#include "puzzle.h"

using namespace std;

//initializes an empty grid
Puzzle::Puzzle(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            grid[i][j].set_value(0);
        }
    }
}


Puzzle::~Puzzle(){
}

//initializes the puzzle to an empty grid
void Puzzle::clear_puzzle(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            grid[i][j].set_value(0);
        }
    }
}

//loads a puzzle from the text file file_name
//file_name should contain a 9x9 grid of numbers
//with 0s to denote empty cells
int Puzzle::load_puzzle(string file_name){
    ifstream file(file_name);

    if (!file.is_open()){
        cout << "unable to open file " << file_name << endl;
        return -1;
    }

    char c;
    int value;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            file.get(c);
            
            //skip over newline characters and the like
            while (c < 48 || c > 57){
                file.get(c);
            }
            value = c - 48;
            set_cell(i, j, value);
        }
    }

    file.close();
    return 0;
}


//copies the cells of the Puzzle that calls the function
//into the cells of the Puzzle destination_puzzle points to
void Puzzle::copy_puzzle_to(Puzzle *destination_puzzle){  
    destination_puzzle->clear_puzzle();
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            destination_puzzle->set_cell(i, j, get_cell(i, j));
        }
    }
}


//copies the cells of Puzzle source_puzzle into the 
//cells of the Puzzle that calls the function
void Puzzle::copy_puzzle_from(Puzzle source_puzzle){
    clear_puzzle();
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            set_cell(i, j, source_puzzle.get_cell(i, j));
        }
    }
}


//prints the puzzle to the terminal
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


//sets the cell in at (row, col) to value
//value must be between 1 and 9
void Puzzle::set_cell(int row, int col, int value){
    //check v is a valid value between 1 and 9
    if (value < 1 || value > 9){
        return;
    }

    grid[row][col].set_value(value);
    
    //adjust hints for other cells in same row
    for (int j = 0; j < 9; j++){
        if (j != col){
            grid[row][j].set_note(value, 0);
        }
    }

    //adjust hints for other cells in same column
    for (int i = 0; i < 9; i++){
        if (i != row){
            grid[i][col].set_note(value, 0);
        }
    }

    //adjust hints for other cells in same box
    int box_row = row / 3;
    int box_col = col / 3;
    for (int i = box_row * 3; i < (box_row + 1) * 3 ; i++){
        for(int j = box_col * 3; j < (box_col + 1) * 3; j++){
            if (i != row || j != col){
                grid[i][j].set_note(value, 0);
            }
        }
    }

}


//returns the value of the cell at (row, col)
int Puzzle::get_cell(int row, int col){
    return grid[row][col].get_value();
}



//checks if there is only one possible value for a cell
//looking only at that cell's notes.  If so, returns that value
int Puzzle::check_cell(int row, int col){
    int value = 0;
    int num_notes = 0;

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


//checks if the cell at (row, col) is the only cell in its row
//where a value is permitted can go.  If so, returns that value
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


//checks if the cell at (row, col) is the only cell in its column
//where a value is permitted can go.  If so, returns that value
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


//checks if the cell at (row, col) is the only cell in its box
//where a value is permitted can go.  If so, returns that value
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


/*Attempts to solve the puzzle by filling in cells using the
    basic rules of sudoku - each row, column and box must contain
    each of the numbers 1-9 exactly once.  Fills in cells until
    these rules fail to find a cell to fill in. */
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


/*Attempts to solve the puzzle by finding the first empty cell 
    of the puzzle and then attempting to solve each of the puzzles
    that result by setting that cell to each of its possible values.
    This can result in recursive calls if solving the resulting
    puzzle requires further guessing and checking. */
void Puzzle::guess_solve(){
    int flag = 0;
    Puzzle guess;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (grid[i][j].get_value() != 0){
                continue;
            }
            else{
                for(int v = 1; v <= 9; v++){
                    if (grid[i][j].get_note(v) == 1){
                        guess.clear_puzzle();
                        copy_puzzle_to(&guess);
                        guess.set_cell(i, j, v);
                        
                        if (guess.solve() == 1){
                            //cout << "guessed " << v << " at (";
                            //cout << i << "," << j << ")" << endl;
                            copy_puzzle_from(guess);
                            flag = 1;
                            break;
                        }
                    }
                }
            }
            if (flag == 1){
                break;
            }
        }
        if (flag == 1){
            break;
        }
    }
}


/*Attempts to solve the puzzle.  If it cannot solve it with basic
    sudoku logic, it resorts to guess and check, which can result in
    recursive function calls if it requires multiple guesses.
    Returns 1 if the puzzle is completely filled in, 
    or -1 if it is unsolvable */
int Puzzle::solve(){
    notes_solve();
    if (is_solved() == 0){
        guess_solve();
    }

    return is_solved();
}


/*returns 1 if the puzzle is completely filled in, returns 0 if 
    the puzzle is not filled in, returns -1 if the puzzle is not solvable 
    (there is a cell with no possible values) */
int Puzzle::is_solved(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(grid[i][j].get_value() == 0){
                int t = 0;
                for(int v = 1; v <= 9; v++){
                    t += grid[i][j].get_note(v);
                }
                //bad puzzle, not solvable
                if (t == 0){
                    return -1;
                }
                return 0;
            }
        }
    }
    return 1;
}