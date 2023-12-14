# Sudoku Solver

This project focuses on designing and implementing a Sudoku solver, which can also be used to generate solvable boards. The algorithm can solve and generate both standard (9x9) Sudoku puzzles and Hexadecimal boards on a 16x16 grid. The project uses object-oriented programming to create a flexible and modular codebase for both types of Sudoku boards, and can easily be extended to other square board sizes. 

### Introduction:

Sudoku is a popular logic-based number-placement puzzle, typically played on a 9x9 grid with decimal numbers. In this project, we have chosen to extend the traditional Sudoku to a 16x16 grid using hexadecimal numbers (0-9, A-F). The objective of the puzzle remains the same: fill the grid so that each row, column, and region (4x4 in our case) contains all of the numbers from 1 to 16 exactly once.

### Code Design and Implementation:

The code is structured using object-oriented principles, with several key classes and inheritance to manage different Sudoku board types. The classes are as follows:

1\.	Cell: Represents a single cell in the Sudoku board, containing its current value and a list of possible values.

2\.	Region: An abstract class representing a row, column, or square in the Sudoku board. It checks for duplicates and ensures that the cells sum to the expected value.

3\.	BaseSudokuBoard: A base class for both decimal and hexadecimal Sudoku boards, containing shared functionality such as board initialization, input/output handling, and basic Sudoku solving/generation methods.

4\.	HexadecimalSudokuBoard: A derived class that implements the specific logic for hexadecimal Sudoku, including methods to generate, solve, and print the board.

The algorithm employs a combination of constraint propagation and backtracking to generate and solve Sudoku puzzles. Constraint propagation is performed by the updatePossibleValues method, which iterates over the cells in each region and removes any values that are already present in the region from the possible values of other cells. The backtracking is done through the collapse\_inner method, which sets cells to random possible values and checks if the resulting board is solvable.

