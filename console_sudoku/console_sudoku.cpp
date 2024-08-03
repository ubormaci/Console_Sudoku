#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <random>
#include <conio.h> 
using namespace std;

int table[9][9];
bool locked[9][9]; // locked values
int n = 9;
// table[y][x] in terms of coordinates, or table[i][j] in terms of for loop structure

bool nums[10];

void initializeTable();
void displayTable();
void commandWait();
void startGame();
void saveGame();
void loadGame();
void stateCheck();
bool checkCollection();
void resetCollection();

int main()
{
    srand((unsigned)time(NULL));

    /*
    for (int i = 32; i < 255; i++)
    {
        cout << "\nchar(" << i << ") = " << (char)i;
    }
    */

    startGame();
}

void startGame()
{
    initializeTable();
    displayTable();
}

void initializeTable()
{
    // values taken from above
    // https://web.archive.org/web/20061126162713/http://www.csse.uwa.edu.au/~gordon/sudokumin.php

    string line;

    const int max_lines = 36604;
    ifstream inread("starting_configurations.txt");
    long int chosen = rand() % max_lines;
    for (int i = 0; i < chosen; i++)
    {
        getline(inread, line);
    }

    int iter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string curchar = line.substr(iter++, 1);
            table[i][j] = stoi(curchar);
            if (table[i][j] != 0)
            {
                locked[i][j] = true;
            }
        }
    }

    //cout << "\ncurrent table is " << chosen;

    return;
}

void displayTable()
{
    system("cls");

    cout << "\n\n";
    cout << "       ";
    for (int i = 0; i < n; i++)
    {
        cout << i << "  ";
    }

    char horbar = (char)196; 
    // in standard Windows-1252, the horizontal bar is at 151
    // but for me, it is at 196
    // but checking with PowerShell, it looks like *I* also have CP-1252
    // so this is a bit weird and might cause it to function differently on other machines

    cout << "\n       ";
    for (int i = 0; i < 9; i++)
    {
        cout << horbar << "  ";
    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << "  " << i << "  | ";
        for (int j = 0; j < n; j++)
        {
            cout << table[i][j] << "  ";
        }
        cout << "\n\n";
    }
    
    commandWait();
}

void commandWait()
{
    // commands:
    // "new" - start a new game
    // "save" - save the current state of the board
    // "load" - load the last saved state
    // "help" - print out all other commands
    // "{x} {y} {value}" - place a value at x,y coordinates

    cout << "\n>>> ";
    //char get[100];
    //cin.getline(get, 100);

    string get;
    getline(cin, get);

    if (get == "exit")
    {
        exit(0);
    }

    if (get == "new")
    {
        startGame();
    }

    if (get == "save")
    {
        saveGame();
        cout << "Game saved";
        commandWait();
    }

    if (get == "load")
    {
        loadGame();
        displayTable();
    }

    if (get == "help")
    {
        cout << "commands:\nnew - start a new game\nsave - save the current state of the board";
        cout << "\nload - load the last saved state\nhelp - print out all commands\n{x} {y} {value} - place a value at x, y coordinates";
        commandWait();
    }

    int x = stoi(get.substr(0, 1));
    int y = stoi(get.substr(2, 1));
    int value = stoi(get.substr(4, 1));

    if (locked[y][x] == false)
    {
        table[y][x] = value;
    }
    else
    {
        cout << "Sorry, that can't be changed.";
        commandWait();
    }

    stateCheck();

    displayTable();
}

void saveGame()
{
    ofstream out("savegame.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            out << table[i][j];
        }
    }
}

void loadGame()
{
    ifstream in("savegame.txt");

    string line;
    getline(in, line);

    int iter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string curchar = line.substr(iter++, 1);
            table[i][j] = stoi(curchar);
        }
    }
}

void stateCheck()
{
    // first off, we check if we are even *ready* checking
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (table[i][j] == 0)
            {
                return;
            }
        }
    }

    //cout << "\ngrid is filled in";

    bool done = true;

    // checking by lines:
    for (int i = 0; i < n; i++)
    {
        resetCollection();
        for (int j = 0; j < n; j++)
        {
            nums[table[i][j]] = true;
        }
        if (!checkCollection())
        {
            done = false;
            return;
        }
    }

    //cout << "\nrows are alright";

    // checking by columns
    for (int i = 0; i < n; i++)
    {
        resetCollection();
        for (int j = 0; j < n; j++)
        {
            nums[table[j][i]] = true;
        }
        if (!checkCollection())
        {
            done = false;
            return;
        }
    }

    //cout << "\ncolumns are alright";

    //checking by cubes
    for (int i = 0; i < n; i+=3)
    {
        for (int j = 0; j < n; j+=3)
        {
            resetCollection();

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    nums[table[i + k][j + l]] = true;
                }
            }

            if (!checkCollection())
            {
                done = false;
                return;
            }
        }
    }

    // if we've reached this point, it means that our sudoku is finished
    cout << "\n\nCongratulations, you successfully completed this sudokue! :D";
    cout << "\nWrite 'new' if you'd like to play another, or 'exit' if you were satisfied.";
    cout << "\nThank you for playing!";
    commandWait();
}

bool checkCollection()
{
    for (int i = 1; i < n + 1; i++)
    {
        if (nums[i] == false)
        {
            return false;
        }
    }

    return true;
}
void resetCollection()
{
    for (int i = 1; i < n + 1; i++)
    {
        nums[i] = false;
    }
}
