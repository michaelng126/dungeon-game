#include <iostream>
#include <string>
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

void printBoard(Player player){
    // get player position
    int row = player.getRow();
    int col = player.getCol();

    // loop through array, taking into account where player is

    cout << endl; // padding for visual aesthetic

    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 10; j++){
            if (i == row && j == col){
                //player
                cout << 'G';
            } else {
                //board
                cout << board[i][j];
            }

        } 
        cout << endl;
    }

    cout << endl; // padding for visual aesthetic

}

int main() {

    /// PLAYER GENERATION ///
    Player player;

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


    /// MAIN CODE ///

    for (;;){
        // 1. display the board
        printBoard(player);

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
            cout << "You've got the treasure! You win!" << endl;
            break;
        }

        if (board[player.getRow()][player.getCol()] == 'T'){
            // Lose!
            cout << "Oh no! You landed on a trap! But not all is lost. You can try again!" << endl;
            break;
        }

    }
}