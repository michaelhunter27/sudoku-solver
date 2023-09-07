# sudoku-solver

Solves sudoku puzzles.  Basic solving uses just the rules of sudoku.  
If this solving method fails, it will guess and check to find the 
solution to the puzzle.  Will identify if there is no valid solution
to the puzzle.

Use the included Makefile to build the project.  Use the command
`make solver`
The output of this is the program `solver.exe`

Command line usage:
`solver.exe file_name1 [file_name2...]`
Solves the puzzle contained in each of the files provided.
The files should be text files containing 9 rows of 9 numbers 0-9, 
with the 0s representing empty cells and numbers 1-9 representing
the starting clues.  For example, a text file containing the following
```
205908010
000040070
008000500
000007600
082506730
007100000
001000400
030050000
070403805
```
represents the following sudoku puzzle:
```
2 5|9 8| 1 
   | 4 | 7 
  8|   |5  
---+---+---
   |  7|6  
 82|5 6|73 
  7|1  |   
---+---+---
  1|   |4  
 3 | 5 |   
 7 |4 3|8 5
```
