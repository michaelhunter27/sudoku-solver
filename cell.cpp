#include<cstdlib>
#include<iostream>

#include "cell.h"


using namespace std;

Cell::Cell(){
    value = 0;
    for (int i = 0; i < 9; i++){
       notes[i] = 1;
    }
}

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
}

int Cell::get_value(){
    return value;
}


void Cell::print_value(){
    cout << value;
}

void Cell::print_notes(){
    for (int i = 0; i < 9; i++){
        cout << notes[i];
    }
    cout << endl;
}


void Cell::set_note(int i, int v){
    if (i >= 1 && i <= 9){
        notes[i-1] = v;
    }
}

int Cell::get_note(int i){
    if (i >= 1 && i <= 9){
        return notes[i-1];
    }
    return -1;
}