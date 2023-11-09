#include "Cell.h"
#include <string>
#include <vector>
#include <random>
#include <numeric>

class region
{
private:

	std::vector<Cell> cells;

public:
	// Constructor
    region() {};
	region(std::vector<Cell> cells_) : cells(cells_) {};


};

class row : region 
{
private:

	std::vector<Cell> cells;

};

class column : region
{
private:

	std::vector<Cell> cells;

};

class square : region
{
private:

	std::vector<Cell> cells;
    int square_no;

public : 
    // Default constructor
    square() {};

    std::vector<int> which_square_range(int x) {
        std::vector<int> xRange(3);

        if (x <= 2) {
            std::iota(xRange.begin(), xRange.end(), 0);
        }
        else if (x <= 5) {
            std::iota(xRange.begin(), xRange.end(), 3);
        }
        else {
            std::iota(xRange.begin(), xRange.end(), 6);
        }

        return xRange;
    }

    int which_square(int x, int y) {

        if (x <= 2 && y <= 2)       { return 1; }
        else if (x <= 5 && y <= 2)  { return 2; }
        else if (y <= 2)            { return 3; }

        if (x <= 2 && y <= 5)       { return 4; }
        else if (x <= 5 && y <= 5)  { return 5; }
        else if (y <= 5)            { return 6; }

        if (x <= 2 && y <= 9)       { return 1; }
        else if (x <= 5 && y <= 9)  { return 2; }
        else if (y <= 9)            { return 3; }
    }
};