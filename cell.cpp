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


void Cell::print_value(){
    cout << value;
}