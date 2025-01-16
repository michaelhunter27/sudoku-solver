isSolved :: (Eq a) => [[a]] -> [a] -> Bool
isSolved grid vals = allRowsSolved grid vals && allColsSolved grid vals && allBoxesSolved grid vals

--grid1 = [[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9]]
--grid2 = [[1,2,3,4,5,6,7,8,9],[2,3,4,5,6,7,8,9,1],[3,4,5,6,7,8,9,1,2],[4,5,6,7,8,9,1,2,3],[5,6,7,8,9,1,2,3,4],[6,7,8,9,1,2,3,4,5],[7,8,9,1,2,3,4,5,6],[8,9,1,2,3,4,5,6,7],[9,1,2,3,4,5,6,7,8]]
--grid3 = [[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9]]
--grid4 = [[1,2,3,4,5,6,7,8,9],[4,5,6,7,8,9,1,2,3],[7,8,9,1,2,3,4,5,6],[2,3,4,5,6,7,8,9,1],[5,6,7,8,9,1,2,3,4],[8,9,1,2,3,4,5,6,7],[3,4,5,6,7,8,9,1,2],[6,7,8,9,1,2,3,4,5],[9,1,2,3,4,5,6,7,8]]
--grida = ["abcd", "cdab", "bcda", "dabc"]
grid01 = [[1,2,0,4],[3,4,1,2],[2,3,4,1],[4,1,2,3]]
grid02 = [[1,2,3,4],[0,4,1,2],[2,3,4,1],[4,1,2,3]]
grid03 = [[1,2,3,4],[3,4,1,2],[2,0,4,1],[4,1,2,3]]
grid04 = [[1,2,3,4],[3,4,1,2],[2,3,4,1],[4,1,2,0]]


rowSolved :: (Eq a) => [a] -> [a] -> Bool
rowSolved row vals = and [ x `elem` row | x <- vals ]

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

gridCols :: [[a]] -> [[a]]
gridCols grid = [[(grid !! x) !! y | x <- [0..size-1]] | y <- [0..size-1]]
    where size = length grid

gridBoxes :: [[a]] -> [[a]]
gridBoxes grid = [[(grid !! (x1 + 2 * (box `div` 2))) !! (x2 + 2 * (box `mod` 2)) | x1 <- [0..1], x2 <- [0..1] ] | box <- [0..3]]
    where size = length grid

solve :: (Eq a) => [[a]] -> [a] -> [[a]]
solve grid vals
    | isSolved grid vals = grid

missingOne :: (Num a, Eq a) => [a] -> Bool
missingOne set = sum [if x == 0 then 1 else 0 | x <- set ] == 1

missingValues :: (Num a, Eq a) => [a] -> [a] -> [a]
missingValues set values = [x | x <- values, x `notElem` set]

fillInValue :: (Num a, Eq a) => [[a]] -> Int -> Int -> a -> [[a]]
fillInValue grid row col val = [if x == row then [if y == col then val else (grid !! x) !! y | y <- [0..size]] else grid !! x | x <- [0..size]]
    where size = length grid - 1

fillInMissingValue :: (Num a, Eq a) => [[a]] -> Int -> [a] -> [[a]]
fillInMissingValue grid row values
    | missingOne (grid !! row) = fillInValue grid row index value
    | otherwise = grid
    where index = [x | x <- [0..3], (grid !! row) !! x == 0 ] !! 0
          value = (missingValues (grid !! row) values) !! 0
