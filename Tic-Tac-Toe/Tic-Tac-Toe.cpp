
#include <iostream>
#include "Player.h"
#include<vector>
#include<fstream>
#include<string>
//using namespace std;



int validateInput(std::string prompt, int start, int end) {
    int value;
    bool valid = false;
    while (valid == false) {
        cout << prompt;
        cin >> value;
        if (value <= end && value >= start) {
            valid = true;
          
        }
        else {
            valid = false;
        }
    }
    return value;
}

void saveGame(vector<std::string> board) {
    ofstream file("games.json");

    std::string savedBoard[9];

    for (int i = 0;i <= 8;i++) {
        file << board[i] << endl;
    }
    file.close();
}

vector<std::string> loadGame() {
    std::string myText;
    vector<std::string> board;

    // Read from the text file
    ifstream MyReadFile("games.json");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        cout << myText << endl;
        board.push_back(myText);
    }


    //// Close the file
    MyReadFile.close();
    return board;
}

vector<std::string> setBoard() {

    int choice;
    /*cout << "would you like to 1. start a new game or 2. load a save?(1 or 2) ";*/
    choice = validateInput("would you like to 1. start a new game or 2. load a save?(1 or 2) ", 1, 2);
    if (choice == 2) {
        vector<std::string>result = loadGame();
        return result;
    }
    else {
        vector<std::string> board = { " ", " ", " ", " ", " ", " ", " ", " ", " " };
        return board;
    }
}

int place(vector<string> board, string prompt) {
    int numberPlace;
    bool canPlace = false;
    while (canPlace == false) {
        numberPlace = validateInput(prompt, 0, 9);
        if(numberPlace == 0) {
            canPlace = true;
            return numberPlace;

        }else if (board[numberPlace - 1] == " ") {
            canPlace = true;
            return numberPlace;
        }
        else
        {
            canPlace = false;
        }
    }
}

void displayBoard(vector<string> board) {
    cout << endl << endl << endl << "\t" << " " << board[0] << " | " << board[1] << " | " << board[2] << " " << endl << "\t" << "---+---+---" << endl << "\t" << " " << board[3] << " | " << board[4] << " | " << board[5] << endl << "\t" << "---+---+---" << endl << "\t" << " " << board[6] << " | " << board[7] << " | " << board[8] << endl << endl << endl;
}

bool checkDraw(vector<string> board) {

    int count = 0;

    //check if the board is full
    for (int i = 0;i <= 8;i++) {
        if (board[i] == " ") {
            count++;
        }
    }
    if (count < 1) {
        return true;
    }else {
        return false;
    }
        
}

bool checkBoard(vector<string> board) {

    //coulumns
    if (board[0] == board[1] && board[2] == board[1] && board[1] != " " || board[3] == board[4] && board[4] == board[5] && board[3] != " " || board[6] == board[7] && board[7] == board[8] && board[6] != " ")
    {
        return true;
    } else if (board[0] == board[3] && board[3] == board[6] && board[0] != " " || board[1] == board[4] && board[4] == board[7] && board[1] != " " || board[2] == board[5] && board[5] == board[8] && board[2] != " ")
    {
        return true;
    } else if (board[0] == board[4] && board[4] == board[8] && board[8] != " ")
    {
        return true;
    } else if (board[2] == board[4] && board[4] == board[6] && board[6] != " ")
    {
        return true;
    }else {
        return false;
    }

}

void gameWon(string x) {
    cout << x << " won the game!";
}

void gameDraw() {
    cout << "All the spaces are filled and no one has 3 in a row, it's a Draw!";
}

int main()
{
    vector<string> board = setBoard();
    string name;
    int spot;
    bool valid = true;
    bool won = false;
    bool draw = false;
    int playerNumber = 1;

    cout << "What is the name of Player 1? ";
    cin >> name;
    Player playerOne;
    playerOne.setName(name);
    playerOne.setNumber(1);
    playerOne.setSymbol("X");

    cout << "What is the name of Player 2? ";
    cin >> name;
    Player playerTwo;
    playerTwo.setName(name);
    playerTwo.setNumber(2);
    playerTwo.setSymbol("O");

    Player players[2] = { playerOne, playerTwo };

    while (valid && draw == false)
    {
        if (playerNumber == 0)
        {
            playerNumber++;
        }
        else
        {
            playerNumber = 0;
        }
        displayBoard(board);
        string prompt = "Which spot do you choose?(1-9)" + players[playerNumber].playerName +" ";
        spot = place(board, prompt);
        
        if (spot == 0) {
            saveGame(board);
            valid = false;
        }
        else {
            board[spot - 1] = players[playerNumber].playerSymbol;
            won = checkBoard(board);
            draw = checkDraw(board);
            if (won == true) {
                gameWon(players[playerNumber].playerName);
                displayBoard(board);
                valid = false;
            }
            else if (draw == true) {
                gameDraw();
            }
        }

    }
}