#include <iostream>
#include <fstream>
#include <string>

#include "BoxProblem.h"
#include "Stack.h"


using namespace std;


PackerProblem* loadPackerProblem(string filename) {
    PackerProblem* s1 = new PackerProblem();

    ifstream file(filename);

    if (!file)
    {
        cout << "Invalid file";
    }
    else
    {

        string rows;
        string columns;
        string Nboxes;

        string width;
        string height;
        string name;

        getline(file, rows, ' '); // gets the number of rows from a file
        getline(file, columns, '\n'); // gets the nubmer of columns from a file
        getline(file, Nboxes, '\n');

        string** puzzle = new string * [stoi(Nboxes)];
        for (int i = 0; i < stoi(Nboxes); i++) {
            puzzle[i] = new string[3];
        }

        for (int i = 0; i < stoi(Nboxes); i++)
        {
            getline(file, height, ' ');//gets the number as a string from a file
            puzzle[i][0] = height; // converts the number to an integer and assigns it to the puzzle
            getline(file, width, ' ');//gets the number as a string from a file
            puzzle[i][1] = width; // converts the number to an integer and assigns it to the puzzle
            getline(file, name, '\n');//gets the number as a string from a file
            puzzle[i][2] = name; // converts the number to an integer and assigns it to the puzzle
        }

        s1->_rows = stoi(rows);
        s1->_columns = stoi(columns);
        s1->_Nboxes = stoi(Nboxes);
        s1->parameters = puzzle;

        return s1;
    }

}


int main()
{
    PackerProblem* s1 = loadPackerProblem("test2.txt");
    s1->solve();
}