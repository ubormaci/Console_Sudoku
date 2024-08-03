#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

int table[9][9];

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
    const int max_lines = 36604;
    ifstream inread("starting_configurations.txt");

}

void displayTable()
{

}
