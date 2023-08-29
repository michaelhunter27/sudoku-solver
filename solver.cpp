#include<cstdlib>
#include<iostream>
#include<fstream>

#include "puzzle.h"
#include "cell.h"


using namespace std;

int wmain(){
    Puzzle P;

    cout << "puzzle:" << endl;

    P.print_puzzle();

    return 0;
}