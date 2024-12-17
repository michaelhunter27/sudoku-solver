#include<cstdlib>
#include<iostream>

#include "cell.h"


using namespace std;

//initializes the cell to value 0 (empty)
Cell::Cell(){
    value = 0;
    for (int i = 0; i < 9; i++){
       notes[i] = 1;
    }
}

//initializes the cell to value v
Cell::Cell(int v){
    if (v >= 1 && v <= 9){
        value = v;

        for (int i = 0; i < 9; i++){
            notes[i] = 0;
            if (i == v - 1){
               notes[i] = 1;
            }
        }
    }
    else{
        value = 0;
        for (int i = 0; i < 9; i++){
            notes[i] = 1;
        }
    }
}

Cell::~Cell(){
    value = -1;
}


//sets the value of the cell to v
void Cell::set_value(int v){
    if (v >= 1 && v <= 9){
        value = v;
        
        for (int i = 0; i < 9; i++){
            notes[i] = 0;
            if (i == v - 1){
               notes[i] = 1;
            }
        }
    }
    //for initialization purposes
    if (v == 0){
        value = 0;
        for (int i = 0; i < 9; i++){
            notes[i] = 1;
        }
    }
}


// returns the value of the cell
int Cell::get_value(){
    return value;
}


//prints the value of the cell to the terminal
void Cell::print_value(){
    cout << value;
}


//prints the cell's notes to the terminal
void Cell::print_notes(){
    for (int i = 0; i < 9; i++){
        cout << notes[i];
    }
    cout << endl;
}


//sets the cell's note corresponding to the index to the value a.  
//index should be 1-9 and n should be 1 (n is a possible value for
//the cell) or 0 (n is not a possible value for the cell)
void Cell::set_note(int index, int n){
    if (index >= 1 && index <= 9){
        notes[index-1] = n;
    }
}


//returns the cell's note corresponding to the index
//returns 1 if index is a valid value for the cell
//returns 0 if index is not a valid value for the cell
int Cell::get_note(int index){
    if (index >= 1 && index <= 9){
        return notes[index-1];
    }
    return -1;
}