#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <random>
using namespace std;

int table[9][9];
// table[y][x] in terms of coordinates, or table[i][j] in terms of for loop structure

// commands:
// "new" - start a new game
// "save" - save the current state of the board
// "load" - load the last saved state
// "help" - print out all other commands
// "{x} {y} {value}" - place a value at x,y coordinates

void initializeTable();
void displayTable();

int main()
{
        
}

void initializeTable()
{
    // values taken from above
    // https://web.archive.org/web/20061126162713/http://www.csse.uwa.edu.au/~gordon/sudokumin.php

    srand((unsigned)time(NULL));

    string line;

    const int max_lines = 36604;
    ifstream inread("starting_configurations.txt");
    long int chosen = rand() % max_lines;
    for (int i = 0; i < chosen; i++)
    {
        getline(inread, line);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

        }
    }
}

void displayTable()
{

}
