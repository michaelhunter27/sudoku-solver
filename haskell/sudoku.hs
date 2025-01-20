-- returns true if the sudoku is solved
isSolved :: (Eq a) => [[a]] -> [a] -> Bool
isSolved grid vals = allRowsSolved grid vals && allColsSolved grid vals && allBoxesSolved grid vals

-- some 9x9 grids for testing isSolved, rowSolved, colSolved, allboxesSolved, etc.
--grid1 = [[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9]]
--grid2 = [[1,2,3,4,5,6,7,8,9],[2,3,4,5,6,7,8,9,1],[3,4,5,6,7,8,9,1,2],[4,5,6,7,8,9,1,2,3],[5,6,7,8,9,1,2,3,4],[6,7,8,9,1,2,3,4,5],[7,8,9,1,2,3,4,5,6],[8,9,1,2,3,4,5,6,7],[9,1,2,3,4,5,6,7,8]]
--grid3 = [[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9]]
--grid4 = [[1,2,3,4,5,6,7,8,9],[4,5,6,7,8,9,1,2,3],[7,8,9,1,2,3,4,5,6],[2,3,4,5,6,7,8,9,1],[5,6,7,8,9,1,2,3,4],[8,9,1,2,3,4,5,6,7],[3,4,5,6,7,8,9,1,2],[6,7,8,9,1,2,3,4,5],[9,1,2,3,4,5,6,7,8]]

-- some 4x4 grids for testing missingOne, missingValues, fillInMissingValue
grid01 = [[1,2,0,4],[3,4,1,2],[2,3,4,1],[4,1,2,3]]
grid02 = [[1,2,3,4],[0,4,1,2],[2,3,4,0],[4,1,2,3]]
grid03 = [[1,2,3,4],[3,4,1,2],[2,0,0,1],[4,1,2,3]]
grid04 = [[0,2,3,4],[3,0,1,2],[2,3,0,1],[4,1,2,0]]

-- returns true if each element of vals is present in row
rowSolved :: (Eq a) => [a] -> [a] -> Bool
rowSolved row vals = and [ x `elem` row | x <- vals ]

-- returns true if each row of grids is solved
-- i.e., rowSolved returns true for each row of grids
allRowsSolved :: (Eq a) => [[a]] -> [a] -> Bool
allRowsSolved grid vals = and [ rowSolved row vals | row <- grid ]

colSolved :: (Eq a) => [a] -> [a] -> Bool
colSolved col vals = and [x `elem` col | x <- vals]

allColsSolved :: (Eq a) => [[a]] -> [a] -> Bool
allColsSolved grid vals = and [ colSolved col vals | col <- gridCols grid ]

boxSolved :: (Eq a) => [a] -> [a] -> Bool
boxSolved box vals = and [x `elem` box | x <- vals]

allBoxesSolved :: (Eq a) => [[a]] -> [a] -> Bool
allBoxesSolved grid vals = and [ boxSolved box vals | box <- gridBoxes grid ]

-- returns a list each element of which is (a list of) the cells of a column of the grid
gridCols :: [[a]] -> [[a]]
gridCols grid = [[(grid !! x) !! y | x <- [0..size-1]] | y <- [0..size-1]]
    where size = length grid

-- returns a list each element of which is (a list of) the cells of a box of the grid
gridBoxes :: [[a]] -> [[a]]
gridBoxes grid = [[(grid !! (x1 + 2 * (box `div` 2))) !! (x2 + 2 * (box `mod` 2)) | x1 <- [0..1], x2 <- [0..1] ] | box <- [0..3]]
    where size = length grid

-- hopefully this function will solve a sudoku one day
-- currently:
-- if the grid is already solved: returns the original grid
-- otherwise, completes rows that are missing a single value and returns that grid
solve :: (Num a, Eq a) => [[a]] -> [a] -> [[a]]
solve grid vals
    | isSolved grid vals = grid
    | otherwise = [fillInMissingValue grid row vals !! row | row <- [0..size] ]
    where size = length grid - 1

-- returns true if exactly 1 value of the set is 0 (exactly one cell is not filled)
missingOne :: (Num a, Eq a) => [a] -> Bool
missingOne set = sum [if x == 0 then 1 else 0 | x <- set ] == 1

-- returns a list of the values that are not present elements of a set
missingValues :: (Num a, Eq a) => [a] -> [a] -> [a]
missingValues set values = [x | x <- values, x `notElem` set]

-- given a grid, the index of a row, the index of a column (col) and a value (val)
-- returns the same grid but the cell at (row, col) is replaced with val
fillInValue :: (Num a, Eq a) => [[a]] -> Int -> Int -> a -> [[a]]
fillInValue grid row col val = [if x == row then [if y == col then val else (grid !! x) !! y | y <- [0..size]] else grid !! x | x <- [0..size]]
    where size = length grid - 1

-- given a grid, the index of a row and a set of values for the sudoku
-- if there is exactly one value not present in the cell, 
--  returns a grid with the first empty cell replaced with the missing value
-- otherwise, returns the original grid
fillInMissingValue :: (Num a, Eq a) => [[a]] -> Int -> [a] -> [[a]]
fillInMissingValue grid row values
    | missingOne (grid !! row) = fillInValue grid row index value
    | otherwise = grid
    where index = head [x | x <- [0..3], (grid !! row) !! x == 0 ]
          value = head (missingValues (grid !! row) values)

-- given a grid and the indexes of the row and col of a cell,
-- returns the values that can go in an empty cell
-- returns an empty list if the cell is not empty
possibleValues :: (Num a, Eq a) => [[a]] -> Int -> Int -> [a] -> [a]
possibleValues grid row col values
    | (grid !! row !! col) == 0 = missingValues (grid !! row ++ gridCols grid !! col ++ gridBoxes grid !! box) values
    | otherwise = []
    where box = row `div` 2 * 2 + col `div` 2

-- returns True if there is only one value that can go in the cell
-- returns false if the cell is already filled
onePossible :: (Num a, Eq a) => [[a]] -> Int -> Int -> [a] -> Bool
onePossible grid row col values
    | grid !! row !! col == 0 = length (possibleValues grid row col values) == 1
    | otherwise = False

-- returns a grid with the cell cell at row col filled in if there is only one value it could be
fillInOnlyPossibleValue :: (Num a, Eq a) => [[a]] -> Int -> Int -> [a] -> [[a]]
fillInOnlyPossibleValue grid row col values
    | onePossible grid row col values = fillInValue grid row col value
    | otherwise = grid
    where value = head (possibleValues grid row col values)

solve' :: (Num a, Eq a) => [[a]] -> [a] -> [[a]]
solve' grid values
    | isSolved grid values = grid
    | otherwise = solveHelper grid 0 0 values


-- uses recursive calls to loop through the cells of the sudoku
-- fills in cells that have only one possible value
solveHelper :: (Num a, Eq a) => [[a]] -> Int -> Int -> [a] -> [[a]]
solveHelper grid row col values
    | (col == size - 1) && (row == size - 1) = fillInOnlyPossibleValue grid row col values
    | col == size - 1 = solveHelper (fillInOnlyPossibleValue grid row col values) (row + 1) 0 values
    | otherwise = solveHelper (fillInOnlyPossibleValue grid row col values) row (col + 1) values
    where size = length grid
          
-- empty grid for testing purposes
grid00 = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]

-- cell 1 1 can only be a 4
grid05 = [[1,2,0,0],[3,0,0,0],[0,0,0,0],[0,0,0,0]]

-- cell 0 1 can only be a 2
grid06 = [[1,0,0,0],[0,0,0,4],[0,0,0,0],[0,3,0,0]]

-- one box missing, can be solved in one pass
grid07 = [[0,0,3,4],[0,0,1,2],[2,3,4,1],[4,1,2,3]]

-- two boxes missing, can be solved in one pass
grid08 = [[0,0,3,4],[0,0,1,2],[2,3,0,0],[4,1,0,0]]

-- two boxes and one cell missing, can be solved, but not in one pass
grid09 = [[0,0,3,0],[0,0,1,2],[2,3,0,0],[4,1,0,0]]

-- trickier? sudokus
grid10 = [[0,1,0,0],[3,0,0,1],[4,0,0,2],[0,0,4,0]]
grid11 = [[2,0,0,0],[0,0,0,4],[4,0,0,0],[0,0,0,3]]
grid12 = [[0,0,0,1],[0,4,0,0],[0,0,3,0],[2,0,0,0]]