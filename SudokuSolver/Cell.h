#include <string>
#include <vector>
#include <random>
#include <numeric>

class Cell
{  

private :
    int value; 
    int width; 
    int height;
    bool Editable;
    std::vector<int> PossibleValues;

public :
    // Default constructor
    Cell() : width(0), height(0), value(-1) {}

    // Parameterised constructor
   Cell(int width, int height) {
       int value = -1;
    }

   // Parameterised constructor
   Cell(int width, int height, std::vector<int> PossibleValues) {
       
   }

    // If this cell is editable, returns true when the length PossibleValues > 1
    bool Editable = PossibleValues.size() > 1;

    // The cells value. equal to -1 if length of PossibleValues > 1
    int value = PossibleValues.size() > 1 ? -1 : PossibleValues[0];

    int getHeight() {
        return height;
    }

    int getWidth() {
        return width;
    }

    // Removes the value from the cells possible values, will only remove the value if the cell is editable
    void Remove(int value)
    {
        if (Editable) {
            PossibleValues.erase(std::remove_if(PossibleValues.begin(), PossibleValues.end(), value), PossibleValues.end());
        }
    }

    // Randomly choose a value from the cells possible values and removes all other values in the array.
    void ChooseValue()
    {
        if (!Editable) { return; }

        // choose random index
        int RandIndex = rand() % PossibleValues.size();
        // remove all other values except for the one randomly chosen
        int value = PossibleValues[RandIndex];
        PossibleValues = std::vector<int>{ value };
    }


    std::string DisplayPossibleValues()
    {
        if (!Editable) { return; }
        else {
            std::string str = std::accumulate(PossibleValues.begin(), PossibleValues.end(), std::string(","));
            return str;
        }
    }
}