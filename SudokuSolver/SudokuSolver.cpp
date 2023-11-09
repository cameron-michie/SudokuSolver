#include "Cell.h"
#include "Sudoku.h"
#include <vector>
#include <iostream>

void main() {

    int BoardValues[9][9] = {
        {8, 5, 0, 0, 0, 2, 4, 0, 0},
        {7, 2, 0, 0, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 7, 0, 0, 2},
        {3, 0, 5, 0, 0, 0, 9, 0, 0},
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 7, 0},
        {0, 1, 7, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 6, 0, 4, 0} };


    Sudoku sudoku(BoardValues);

    sudoku.PrintBoard(sudoku.CurrentBoard);

    for (int i = 0; i < 10000; i++)
    {
        // collapse the board, getting all states from start to end
        std::vector<Cell> collapseIterations = sudoku.Collapse();

        // display all states
        for (Cell boardstate : collapseIterations) {
            sudoku.PrintBoard(boardstate);
        }

        if (!sudoku.ValidSolve())
        {
            sudoku.Reset();
            sudoku.PrintBoard(sudoku.CurrentBoard);
        }
        else
        {
            std::cout << "Solved on iteration" << i + 1 << ".");
            sudoku.PrintBoard(sudoku.CurrentBoard);
            break;
        }
    }
}