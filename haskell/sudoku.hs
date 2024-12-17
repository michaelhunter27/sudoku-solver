
isSolved :: (Integral a) => [[a]] -> Bool
isSolved grid = allRowsSolved grid && allColsSolved grid && allBoxesSolved grid

grid1 = [[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9],[1,2,3,4,5,6,7,8,9]]
grid2 = [[1,2,3,4,5,6,7,8,9],[2,3,4,5,6,7,8,9,1],[3,4,5,6,7,8,9,1,2],[4,5,6,7,8,9,1,2,3],[5,6,7,8,9,1,2,3,4],[6,7,8,9,1,2,3,4,5],[7,8,9,1,2,3,4,5,6],[8,9,1,2,3,4,5,6,7],[9,1,2,3,4,5,6,7,8]]
grid3 = [[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[1,1,1,2,2,2,3,3,3],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[4,4,4,5,5,5,6,6,6],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9],[7,7,7,8,8,8,9,9,9]]
grid4 = [[1,2,3,4,5,6,7,8,9],[4,5,6,7,8,9,1,2,3],[7,8,9,1,2,3,4,5,6],[2,3,4,5,6,7,8,9,1],[5,6,7,8,9,1,2,3,4],[8,9,1,2,3,4,5,6,7],[3,4,5,6,7,8,9,1,2],[6,7,8,9,1,2,3,4,5],[9,1,2,3,4,5,6,7,8]]

rowSolved :: (Integral a) => [a] -> Bool
rowSolved row = and [ x `elem` row | x <- [1..9] ]

allRowsSolved :: (Integral a) => [[a]] -> Bool
allRowsSolved grid = and [ rowSolved row | row <- grid ]

colSolved :: (Integral a) => [a] -> Bool
colSolved col = and [x `elem` col | x <- [1..9]]

allColsSolved :: (Integral a) => [[a]] -> Bool
allColsSolved grid = and [ colSolved col | col <- gridCols grid ]

boxSolved :: (Integral a) => [a] -> Bool
boxSolved box = and [x `elem` box | x <- [1..9]]

allBoxesSolved :: (Integral a) => [[a]] -> Bool
allBoxesSolved grid = and [ boxSolved box | box <- gridBoxes grid ]

gridCols :: [[a]] -> [[a]]
gridCols grid = [[(grid !! x) !! y | x <- [0..8]] | y <- [0..8]]

gridBoxes :: [[a]] -> [[a]]
gridBoxes grid = [[(grid !! (x1 + 3 * (box `div` 3))) !! (x2 + 3 * (box `mod` 3)) | x1 <- [0..2], x2 <- [0..2] ] | box <- [0..8]]
