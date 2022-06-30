#include "game.h"

void StartGame();

int main()
{
    StartGame();
}

/*
* Overview of the game procedure. A gameboard of 3x3 is declared.
*/
void StartGame()
{
    int balance, bet, prize;
    bool retry = true;

    char gameBoard[3][3];
    int rows = sizeof(gameBoard) / sizeof(gameBoard[0]);
    int columns = sizeof(gameBoard[0]) / sizeof(char);

    cout << "Welcome to the one-armed bandit game!\n";
    cout << "=====================================\n";

    // Player is asked to insert money(100kr, 300kr or 500kr) to the game
    SetBalance(AskForBalance(), balance);

    // Game will loop until player wishes to quit
    while (retry)
    {
        // Player is asked to set a bet (>0 kr and less than "balance")
        SetBet(AskForBet(balance), balance, bet);
        cout << "Your bet is: " << bet << "kr\n";

        cout << "\nThe generated game board is:\n";

        // The gameboard is filled with tokens (chars)
        SetGameBoard(gameBoard, rows, columns);

        // Number of matched lines is returned from "CalculatePayout"
        prize = bet * CalculatePayout(gameBoard, rows, columns);
        balance += prize;

        // Print win or lose message depending on if the player has received a price or not
        if (prize > 0)
            cout << "\nCongratulations you won: " << prize << "kr\n";
        else
            cout << "You lost " << bet << "kr!\n";

        cout << "Your current balance is: " << balance << "kr\n";

        // If the player doesn't have any money left, exit the game. Else check if the player wants to continue.
        if (balance > 0)
            RestartGame(retry);
        else
        {
            cout << "You are out of money. Game over~~";
            retry = false;
        }
    }
}
