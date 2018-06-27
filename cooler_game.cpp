#include <iostream>
#include <string>
#include <time.h>
#define BOARDWIDTH 10
#define BOARDHEIGHT 7

using namespace std;

//// CUSTOMIZE ////

//##### SET TRAPS HERE #####
// coordinates need to be in bounds
int numberOfTraps = 3; // could use sizeOf(traps array), but seems cumbersome?
int traps[3][2] = {
    {2,6}, {4,4}, {6,6} // trap location will be array of arrays of two elements, as coordinates
    };

//##### SET TRAPS HERE #####
int treasure[2] = {6,9};

////     END   ////



// set up board as a character array
char board[BOARDHEIGHT][BOARDWIDTH];

// class for our Player
class Player {
    //current coords
    int row = 0;
    int col = 0; //start top left say
    
    public: 
        void moveUp(){
            if (row == 0){
                cout << "Unfortunately, you cannot move up. Please select a different action." << endl;
            } else {
                row -= 1;
            }
        }

        void moveDown(){
            if (row == BOARDHEIGHT - 1){
                cout << "Unfortunately, you cannot move down. Please select a different action." << endl;
            } else {
                row += 1;
            }
        }

        void moveLeft(){
            if (col == 0){
                cout << "Unfortunately, you cannot move left. Please select a different action." << endl;
            } else {
                col -= 1;
            }
        }

        void moveRight(){
            if (col == BOARDWIDTH - 1){
                cout << "Unfortunately, you cannot move right. Please select a different action." << endl;
            } else {
                col += 1;
            }
        }
    
        int getRow(){
            return row;
        }
        int getCol(){
            return col;
        }
};

// class for evil monsters M. They can move diagonally, but also off the game!
class Monster {
    int mrow;
    int mcol;

    // Constructor
    public: 
    
        Monster(int startRow, int startCol){
            mrow = startRow;
            mcol = startCol;
        }

        void move(){
            int upwards = (rand() % 3) - 1;
            int downwards = (rand() % 3) - 1;

            mrow = mrow + upwards;
            mcol = mcol + downwards;
        }

        int getRow(){
            return mrow;
        }
        int getCol(){
            return mcol;
        }

};

void printBoard(Player player, Monster monster1, Monster monster2){

    // monsters will move here
    monster1.move();
    monster2.move();

    /// BOARD GENERATION ///

    //populate board with ','
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 10; j++){
            board[i][j] = '.';
        }
    }

    //replace trap locations with T
    for (int i = 0; i < numberOfTraps; i++){
        board[traps[i][0]][traps[i][1]] = 'T';
    }

    //replace treasure with X
    board[treasure[0]][treasure[1]] = 'X';

    //replace player with G
    int row = player.getRow();
    int col = player.getCol();
    board[row][col] = 'G';

    //replace monsters with M
    row = monster1.getRow();
    col = monster1.getCol();
    board[row][col] = 'M';
    row = monster2.getRow();
    col = monster2.getCol();
    board[row][col] = 'M';

    // loop through array, taking into account where player is

    cout << endl; // padding for visual aesthetic

    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 10; j++){
                cout << board[i][j];
        } 
        cout << endl;
    }

    cout << endl; // padding for visual aesthetic

}

int main() {

    srand(time(NULL));

    /// PLAYER GENERATION ///
    Player player;

    /// MONSTER GENERATION ///
    Monster monster1(4,3);
    Monster monster2(5,8);

    /// MAIN CODE ///

    for (;;){
        // 1. display the board
        printBoard(player,monster1,monster2);

        // 2. prompt the player to move up, down, left or right
        cout << "Pick a direction to move; Up [u], Down [d], Left [l] or Right [r]:";
        string theInput;
        
        bool isInputBad = true; //used this instead of 'break' because that would break the outside for loop
        while(isInputBad){
            // We use an infinite loop to keep asking until correct input is given.
            cin >> theInput;

            if (theInput == "u"){
                player.moveUp();
                isInputBad = false;
            }
            if (theInput == "d"){
                player.moveDown();
                isInputBad = false;
            }
            if (theInput == "l"){
                player.moveLeft();
                isInputBad = false;
            }
            if (theInput == "r"){
                player.moveRight();
                isInputBad = false;
            }

            if (isInputBad){
                cout << "Please use the given instructions." << endl;
            }
        }

        // 3. Check conditions
        if (board[player.getRow()][player.getCol()] == 'X'){
            // Win!
            cout << "You've got the treasure! You win!";
            break;
        }

        if (board[player.getRow()][player.getCol()] == 'T'){
            // Lose!
            cout << "Oh no! You landed on a trap! You lose... but you can always try again.";
            break;
        }

        if (board[player.getRow()][player.getCol()] == 'M'){
            // Lose!
            cout << "Oh no! You were eaten by a monster! You lose... but you can always try again.";
            break;
        }

    }
}