#pragma once
#include "Stack.h"
using namespace std;

// Structure to hold PackerSolver data
struct PackerSolver
{

};


// Structure to hold box data
struct Box {
    int _width;
    int _height;
    string _name;
};

// Structure to hold PackerProblem data
struct PackerProblem {
    int _rows;
    int _columns;
    int _Nboxes;
    string** parameters;
    string** EmptyCon;

    // Initializes the SudokuPuzzle
    void PackerInitializer(unsigned int rows, unsigned int columns, unsigned int Nboxes,
        unsigned int width, unsigned int height, string name, string** puzzle)
    {
        _rows = rows;
        _columns = columns;
        _Nboxes = Nboxes;
        parameters = puzzle;
    }

    // Check if the box can be placed in the container
    bool canPlaceBox(string** container, int row, int col, int width, int height) {
        for (int i = row; i < row + height; ++i) {
            for (int j = col; j < col + width; ++j) {
                if (i >= _rows || j >= _columns || container[i][j] != "X") {
                    return false;
                }
            }
        }
        return true;
    }

    // Place the box in the container
    void placeBox(string** container, int row, int col, int width, int height, const string& name) {
        for (int i = row; i < row + height; ++i) {
            for (int j = col; j < col + width; ++j) {
                container[i][j] = name;
            }
        }
    }

    // Remove the box from the container
    void removeBox(string** container, int row, int col, int width, int height) {
        for (int i = row; i < row + height; ++i) {
            for (int j = col; j < col + width; ++j) {
                container[i][j] = "X";
            }
        }
    }

    // Helper function to recursively fit boxes in the container
    bool boxFittingHelper(string** container, Stack<Box>& boxStack) {
        if (boxStack.isEmpty()) {
            return true;
        }

        Box currentBox = boxStack.top();
        boxStack.pop();

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns; ++j) {
                if (canPlaceBox(container, i, j, currentBox._height, currentBox._width)) {
                    placeBox(container, i, j, currentBox._height, currentBox._width, currentBox._name);

                    if (boxFittingHelper(container, boxStack)) {
                        return true;
                    }

                    removeBox(container, i, j, currentBox._height, currentBox._width);
                }
            }
        }

        boxStack.push(currentBox);
        return false;
    }

    // Solve the box fitting problem
    void BoxSolver() {
        // Allocate memory for the empty container

                // Allocate memory for the empty container
        string** EmptyCon = new string * [_rows];
        for (int i = 0; i < _rows; i++) {
            EmptyCon[i] = new string[_columns];
        }

        // Replace values in EmptyCon with "X"
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                EmptyCon[i][j] = "X";
            }
        }

        // Create a Stack to store the boxes
        Stack<Box> boxStack;

        // Push boxes into the stack
        for (int i = 0; i < _Nboxes; ++i) {
            Box box = { stoi(parameters[i][0]), stoi(parameters[i][1]), parameters[i][2] };
            boxStack.push(box);
        }

        // If the box fitting helper returns true, print the solution
        if (boxFittingHelper(EmptyCon, boxStack)) {
            cout << "Solution:" << endl;
            // Print the solution
            string z = "";
            for (int i = 0; i < _rows; i++) {
                z = z + "-";
            }
            cout << "+" << z << "+" << endl;
            for (int i = 0; i < _rows; i++) {
                cout << "|";
                for (int j = 0; j < _columns; j++) {
                    cout << EmptyCon[i][j];
                }
                cout << "|" << endl;
            }
            cout << "+" << z << "+" << endl;
            cout << " " << endl;

        }
        else {
            cout << "No solution found." << endl;
        }

        // Deallocate the memory
        for (int i = 0; i < _rows; i++) {
            delete[] EmptyCon[i];
        }
        delete[] EmptyCon;
    }

    // Print the initial container and box configuration
    void PrintBeforeSolve() {
        string x = "";
        cout << "Container Configuration(" << _rows << "x" << _columns << ")" << endl;
        for (int i = 0; i < _rows; i++) {
            x = x + "-";
        }
        cout << "+" << x << "+" << endl;
        for (int i = 0; i < _columns; i++) {
            cout << "|";
            for (int j = 0; j < _rows; j++) {
                cout << "X";
            }
            cout << "|" << endl;
        }
        cout << "+" << x << "+" << endl;
        cout << " " << endl;

        cout << _Nboxes << " Boxes to be placed" << endl;

        // Print box information
        for (int i = 0; i < _Nboxes; i++) {
            cout << parameters[i][2] << " (" << parameters[i][0] << "x" << parameters[i][1] << ")" << endl;
            for (int y = 0; y < stoi(parameters[i][0]); y++) {
                for (int z = 0; z < stoi(parameters[i][1]); z++) {
                    cout << parameters[i][2];
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    // Create an empty container
    void EmptyContainer() {
        string** EmptyCon = new string * [_rows];
        for (int i = 0; i < _rows; i++) {
            EmptyCon[i] = new string[_columns];
        }

        // Fill the empty container with "X"
        for (int i = 0; i < _columns; i++) {
            for (int j = 0; j < _rows; j++) {
                EmptyCon[i][j] = "X";
            }
        }
    }


    // Main function to solve the problem
    void solve() {
        PrintBeforeSolve();
        BoxSolver();


    }





};


