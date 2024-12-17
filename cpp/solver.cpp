#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

#include "puzzle.h"
#include "cell.h"


using namespace std;

/* Usage: solver file_name.txt
    Loads a sudoku puzzle from text file file_name.txt, 
    solves the puzzle if possible, and prints the complete
    puzzle to the terminal. */
int wmain(int argc, char* argv[]){
    for (int i = 1; i < argc; i++){
        Puzzle P;
        
        string file_name = "";
        int a = 0;
        while (argv[i][a] != 0){
            file_name += argv[i][a];
            a += 2;
        }
        
        if (P.load_puzzle(file_name) != 0){
            continue;
        }

        int result = P.solve();
        cout << "Puzzle " << i << ":";
        if (result == 1){
            cout << "solved" << endl;
        }
        else if (result == -1){
            cout << "bad puzzle" << endl;
        }
        else if (result == 0){
            cout << "not solved" << endl;
        }
        P.print_puzzle();
        cout << endl;
        
    }
    
    return 0;
}