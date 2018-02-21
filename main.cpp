/*This game of life reads the grid values from a file in the same directory, "bacteria.txt", and the values in the file are considered "alive". After the original grid, the cells change based on the following criteria-
 
 For living cells:
 1.If the cell has one or zero living neighbors, it will die of loneliness in the next generation.
 2.If the cell has four or more living neighbors, it will die of overcrowding in the next generation.
 3.If the cell has two or three neighbors, it will remain living.
 For dead cells:
 1. If the cell has exactly three living neighbors, it will come to life in the next generation.
 2. If the cell has any other number of living neighbors, it will remain empty.
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int SIZE = 20;


void readFile(int/*inout*/ life[][SIZE]);
void nextGen(int/*inout*/ life[][SIZE], int/*inout*/ storage[][SIZE]);
void outputSymbols(int/*inout*/ life[][SIZE], int/*in*/);
int  neighborcount(int/*in*/ life[][SIZE], int/*in*/ count, int/*in*/ i, int/*in*/ j);
void stats(int/*in*/ life[][SIZE], int/*in*/ aliveRow10, int/*in*/ aliveCol10, int/*in*/ deadRow16, int/*in*/ deadCol1, int/*in*/ totalAlive, int/*in*/ totalDead);


int main(){
    
    int life[SIZE][SIZE],
    storage[SIZE][SIZE];
    int aliveRow10 = 0,
    aliveCol10 = 0,
    deadRow16 = 0,
    deadCol1 = 0,
    totalAlive = 0,
    totalDead = 0;
    
    
    readFile(life);
    
    cout << "  01234567890123456789" << endl;
    int row = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cout << setw(2) << row;
        outputSymbols(life, i);
        row++;
        cout << endl;
    }
    
    
    cout << endl << "(ORIGINAL GRID) GAME OF LIFE STATS" << endl;
    stats(life, aliveRow10, aliveCol10, deadRow16, deadCol1, totalAlive, totalDead);
    
    
    for (int i = 1; i <= 5; i++) {
        
        nextGen(life, storage);
        
        //This resets the value of the values we are calculating so that we can start fresh each time a generation passes
        aliveRow10 = 0,
        aliveCol10 = 0,
        deadRow16 = 0,
        deadCol1 = 0,
        totalAlive = 0,
        totalDead = 0;
        
        cout << "The grid after " << i << " generations have passed" << endl;
        cout << "(GENERATION #" << i << ") GAME OF LIFE STATS" << endl;
        
        stats(life, aliveRow10, aliveCol10, deadRow16, deadCol1, totalAlive, totalDead);
    }
    return 0;
}








/*-------------------------------------------------------
 
 Function Definitions
 
 ---------------------------------------------------------*/


/*
 This function finds how many cells are alive in the 10th row & the 10th column, how many cells are dead in the 16th row & the 1st column, and the total dead and the total alive.
 After finding the values, they are output onto the console.
 */
void stats(int life[][SIZE], int aliveRow10, int aliveCol10, int deadRow16, int deadCol1, int totalAlive, int totalDead)
//Pre:  Grid is calculated
//Post: Values are shown
{
    for (int i = 0; i < SIZE; i++)
    {
        aliveRow10 = aliveRow10 + life[10][i];
        aliveCol10 = aliveCol10 + life[i][10];
        if (life[16][i] == 0) {
            deadRow16++;
        }
        if (life[i][1] == 0) {
            deadCol1++;
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (life[i][j] == 0) {
                totalDead++;
            }
            if (life[i][j] == 1) {
                totalAlive++;
            }
        }
    }
    
    cout << "Total alive in row 10 = " <<aliveRow10 << endl;
    cout << "Total alive in col 10 = " <<aliveCol10 << endl;
    cout << "Total dead in row 16 = " <<deadRow16 << endl;
    cout << "Total dead in col 1 = " <<deadCol1 << endl;
    cout << "Total alive = " << totalAlive << endl;
    cout << "Total dead = " << totalDead << endl;
    cout << endl << endl << endl;
}







/*
 This function counts the neighbors next to the current index position.
 However, if the cell being evaluated is on one of the corners, it only evaluates the 3 neighbors that surround it(since the others dont exist bc it is in a corner).
 Also, if a cell is on a wall(such as life[4][0]), it evaluates its 5 neighbors that it has(since it is against the wall and 3 neighbors are not there).
 Anything else, it evaluates the 8 neighbors it has(up, down, left, right, and diagonals(4x))
 */
int neighborcount(int life[][SIZE], int count, int i, int j)
//Pre:  Life array is processed
//Post: Storage is saved and overwrites life array
{
    if (i == 0 && j == 0)
    {
        count = life[1][0] + life[1][1] + life[0][1];
    }
    else if(i == 19 && j == 0)
    {
        count = life[19][1] + life[18][0] + life[18][1];
    }
    else if(i == 0 && j == 19)
    {
        count = life[0][18] + life[1][18] + life[1][19];
    }
    else if(i == 19 && j == 19)
    {
        count = life[19][18] + life[18][18] + life[18][19];
    }
    else if(i == 0 && j != 0 && j != 19)
    {
        count = life[0][j+1] + life[0][j-1] + life[1][j] + life[1][j+1] + life[1][j-1];
    }
    else if(i == 19 && j != 0 && j != 19)
    {
        count = life[19][j+1] + life[19][j-1] + life[18][j] + life[18][j+1] + life[18][j-1];
    }
    else if(i != 19 && i != 0 && j == 0)
    {
        count = life[i][1] + life[i+1][0] + life[i-1][0] + life[i+1][1] + life[i-1][1];
    }
    else if(i != 19 && i != 0 && j == 19)
    {
        count = life[i][18] + life[i+1][19] + life[i-1][19] + life[i+1][18] + life[i-1][18];
    }
    else{
        count = life[i+1][j] + life[i-1][j] + life[i][j+1] + life[i][j-1] + life[i+1][j+1] + life[i+1][j-1] + life[i-1][j-1] + life[i-1][j+1];
    }
    return count;
}



/*
 This function is probably the most important function in the program bc it makes sure that all the deaths change at the same time.
 Using a seperate array to store the values in, the generation actually dies and lives in the storage array and then the values of "storage" are stored back into the "life" array.
 This function also specifies that if a cell is dead, it must have exactly 3 neighbors to come back to life and if a cell is alive, it will die if it has less than 2 or more than 3 neighbors.
 */
void nextGen(int life[][SIZE], int storage[][SIZE])
//Pre:  Life is determined
//Post: Next generation is determined and output
{
    
    for (int i = 0; i<SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            storage[i][j]= life[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            
            int count = 0;
            
            count = neighborcount(life, count, i, j);
            if (life[i][j] == 1)
            {
                if(count < 2 || count > 3)
                {
                    storage[i][j] = 0;
                }
            }
            else if (life[i][j]==0)
            {
                if(count == 3)
                {
                    storage[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            life[i][j] = storage[i][j];
        }
    }
    cout << "  01234567890123456789" << endl;
    int row = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cout << setw(2) << row;
        outputSymbols(life, i);
        row++;
        cout << endl;
    }
    cout << endl;
}




/*
 Since int arrays are used, this function converts the 0's and 1's into *'s and blank spaces so a shape is shown instead of numbers
 */
void outputSymbols(int life[][SIZE], int i)
//Post: 1's and 0's are changed into asterisks and blank spaces
{
    for (int j = 0; j < SIZE; j++)
    {
    
        if (life[i][j] == 1)
        {
            cout << '*';
        }
        else
        {
            cout << ' ';
        }
    }
}




/*
 This function opens up the "bacteria.txt" file and finds the index values that are "alive" and then closes it up
 */
void readFile(int life[][SIZE])
//Post: Initial grid is output
{
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            life[i][j] = 0;
        }
    }
    ifstream infile("bacteria.txt");
    int row, col;
    
    infile >> row >> col;
    while (infile){
        life[row][col] = true;
        infile >> row >> col;
    }
    infile.close();
}
