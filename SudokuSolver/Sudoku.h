#include "region.h"
#include "Cell.h"
#include <vector>
#include <numeric>
#include <random>
#include <set>

class Sudoku
{

public:
    int Width = 9;
    int Height = 9;

    // a snap shot to keep the starting state of this sudoku board
    int _startingBoardSnapshot[9][9];

    // the board that will be modified
    Cell CurrentBoard;


    Sudoku(int startValues[9][9])
    {
        CurrentBoard = InitializeBoardCells(startValues);
        _startingBoardSnapshot = startValues;
    }


    // Resets the current board to a snapshot of the starting board
    void Reset()
    {
        CurrentBoard = InitializeBoardCells(_startingBoardSnapshot);
    }
    
    std::vector<Cell> Collapse();

    bool ValidSolve();

private:
    Cell InitializeBoardCells(int fromValues[9][9]);

    void UpdatePossibleValues();

    std::string GetValue(Cell cell) const {
        return std::to_string(cell.value);
    };

    std::vector<Cell> CellsInColumn(Cell grid, int colIndex, int gridHeight)
    {
        std::vector<Cell> cells;

        for (int i = 0; i < gridHeight; i++)
        {
            Cell this_cell(i, colIndex);
            cells.push_back(this_cell);
        }

        return cells;
    }

    std::vector<Cell> CellsInRow(Cell grid, int rowIndex, int gridLength)
    {
        std::vector<Cell> cells;

        for (int i = 0; i < gridLength; i++)
        {
            Cell this_cell(rowIndex, i);
            cells.push_back(this_cell);
        }


        return cells;
    }

    
    std::string GetValue(Cell value);
    /*
    std::string GetValue(Cell value) = > value.Value == -1 ? "-" : value.Value.ToString();

    /// <summary>
    /// Pretty prints the board in a nice grid
    /// </summary>
    /// <param name="cells">Board to print</param>
    public static void PrintBoard(Cell[, ] cells)
    {
        Console.WriteLine($"-------------------------");

        for (var y = 0; y < Height; y++)
        {

            Console.Write($"| {GetValue(cells[y,0])} {GetValue(cells[y,1])} {GetValue(cells[y,2])} ");
            Console.Write($"| {GetValue(cells[y,3])} {GetValue(cells[y,4])} {GetValue(cells[y,5])} ");
            Console.Write($"| {GetValue(cells[y,6])} {GetValue(cells[y,7])} {GetValue(cells[y,8])} |\n");

            if (y is 2 or 5 or 8)
            {
                Console.WriteLine("-------------------------");
            }
        }
    }
    */
}

    /// Executes a wave function collapse algorithm based on the sudoku rules
    /// May or may not return a full board as a cell may not always have a valid value
    /// simply reset the board and try again
    // Returns An vectors of cells of all board states between each collapse
std::vector<Cell> Sudoku::Collapse()
{
    // Update the boards cells
    UpdatePossibleValues();

    // run '10' iterations on the board choosing random values and collapsing cells
    // if the collapsed value stays true when checking the board then the board is full
    // and the loop will exit early.
    //
    // after '10' iterations the board will be returned, it may or may not be full as it's
    // possible for a cell to have no possible values due to how the random values are chosen
    // if this is the case then the board can be reset,
    // and the wave function collapse algorithm to be run again
    for (int p = 0; p < 10; p++)
    {

        // choose random cell and choose random value for that cell
        int randX = Random.Shared.Next(0, Width);
        int randY = Random.Shared.Next(0, Height);
        Cell CurrentBoard{ randY, randX };
        CurrentBoard.ChooseValue();
        // update the board as the random value has been chosen
        UpdatePossibleValues(CurrentBoard);
        yield return CurrentBoard;

        bool collapsed = true;
        // loop through all the cells in the board, check if the cell is collapsed
        // if collapsed stays true then the board is full as all cells have only 1 possible value
        for (var i = 0; i < CurrentBoard.LongLength; i++)
        {
            // convert 1d index into 2d index
            var x = i % Width;
            var y = i / Height;

            if (CurrentBoard[y, x].Value != -1) continue;

            collapsed = false;
            // choose a random value for this cell
            CurrentBoard[y, x].ChooseValue();
            // update the possible values
            UpdatePossibleValues(CurrentBoard);
            break;
        }



        if (collapsed) yield break;

    }

    yield return CurrentBoard;
}

Cell Sudoku::InitializeBoardCells (int fromvalues[9][9])
    // initializes the board with all cells.
    // cells not marked -1 have a single value
    // cells marked -1 have a list of possible values from 1-9
    // <param name="fromValues">an int array to initialize cells from</param>
    /// <returns>A new 2d array with created cells</returns>
{

    Cell boardInitialized;
    // initialise all cells, cells marked with -1 are given a list of all possible values
    // cells with a value already are marked as un-editable
    for (int y = 0; y < boardInitialized.getHeight(); y++)
    {
        for (int x = 0; x < boardInitialized.getWidth(); x++)
        {
            if (fromvalues[y, x] != -1) {
                Cell boardInitialized{ y, x, std::vector<int> { fromvalues[y][x] } };
                }
            else {
                Cell boardInitialized{ y, x, std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9} };
            }


        }
    }

    return boardInitialized;
}


// Updates each cells possible values based on the values in it's row/column/square
// if a cell collapses while removing possible values then this function is recursively called

void Sudoku::UpdatePossibleValues()
{
    /*
     * Loop through all the cells in the grid
     * for each cell that is editable, remove from it's possible values
     * all values already in it's row, column or square
     *
     * if the cell collapses, recursively call this function as the cell collapsing causes
     * a ripple effect to all other cells which may in turn cause more cells to collapse
     */
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Cell currentcell( y, x );

            // skip this cell if it is not editable (i.e the cell has already been collapsed)
            if (!currentcell.Editable) continue;


            // iterate over each value in the current cells column (y axis)
            for (int colCell = 0; colCell < currentcell.getHeight(); colCell++)
            {
                Cell colcell(colCell, x);
                int val = colcell.value;
                currentcell.Remove(val);
            }


            // iterate over all cells in the current cells row (x axis)
            for (int rowCell = 0; rowCell < currentcell.getWidth(); rowCell++)
            {
                Cell rowcell(rowCell, x);
                int val = rowcell.value;
                currentcell.Remove(val);
            }

            //
            // calculate which square the current cell belongs to
            //
            std::vector<int> yRange = which_square(y);
            std::vector<int> xRange = which_square(x);

            // iterate over each cell in the square the cell belongs to removing possible values
            for(int squareY : yRange)
            {
                for(int squareX : xRange)
                {
                    Cell tempcell{ squareY, squareX };
                    int value = tempcell.value;
                    currentcell.Remove(value);
                }
            }

            // if the cell is no longer editable then it has collapsed
            // so recursively call this function
            if (!currentcell.Editable)
            {
                UpdatePossibleValues();
            }

        }
    }

    // return cells;

}

/// Checks that each row and column of the board add up to 45.
    /// 1+2+3+4+5+6+7+8+9 = 45
    /// and that there are no duplicate values in any row,column or square
    /// Returns true when valid, false when not
bool Sudoku::ValidSolve()
{

    // check every row
    for (int y = 0; y < Height; y++)
    {
        std::vector<Cell> rowcells = CellsInRow(CurrentBoard, y, Width);
        int sum_rows;
        for (Cell c : rowcells) {
            sum_rows += c.value;
        }
        if (sum_rows != 45) {
            return false;
        }
        // check if duplicates exists
        std::set<int> no_duplicates(rowcells.begin(), rowcells.end());
        if (no_duplicates.size() != rowcells.size()) {
            return false;
        };
    }

    for (int x = 0; x < Width; x++)
    {
        // fetch cells for current column
        std::vector<Cell> colcells = CellsInRow(CurrentBoard, x, Width);
        int sum_cols;
        for (Cell c : colcells) {
            sum_cols += c.value;
        }
        if (sum_cols != 45) {
            return false;
        }

        // check if duplicates exists
        std::set<int> no_duplicates(colcells.begin(), colcells.end());
        if (no_duplicates.size() != colcells.size()) { 
            return false;
        };
    }

    //
    // Check that each square sums to 45.
    //



    // FIXME: make a static const?
    // each tuple is a square, (y,x)

        std::vector<tuple<std::vector<int>, std::vector<int>>> squareRanges = {
            // top row of squares
            {std::vector<int>{0,1,2}, std::vector<int>{0,1,2}}, {std::vector<int>{0,1,2}, std::vector<int>{3,4,5}}, {std::vector<int>{0,1,2}, std::vector<int>{6,7,8}},

            // middle row of squares
            {std::vector<int>{3,4,5}, std::vector<int>{0,1,2}}, {std::vector<int>{3,4,5}, std::vector<int>{3,4,5}}, {std::vector<int>{3,4,5}, std::vector<int>{6,7,8}},

            // bottom row of squares
            {std::vector<int>{6,7,8}, std::vector<int>{0,1,2}}, {std::vector<int>{6,7,8}, std::vector<int>{3,4,5}}, {std::vector<int>{6,7,8}, std::vector<int>{6,7,8}}
        };

        // loop through each tuple
        for (auto [yRange, xRange] : squareRanges)
        {
            int sum = 0;
            vector<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            for (auto y : yRange)
            {
                for (auto x : xRange)
                {
                    int value = currentBoard[y][x];
                    sum += value;
                    // if false is returned then value has already been removed meaning
                    // it's a duplicate or it's -1
                    auto it = find(list.begin(), list.end(), value);
                    if (it == list.end()) return false;
                    list.erase(it);
                }
            }

            if (sum != 45) return false;
            // if values are still in list then there were duplicates in the square or empty(-1) cells
            if (!list.empty()) return false;
        }

        // if we get to here then the list is valid
        return true;
    }

}
