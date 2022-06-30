#include "game.h"

/*
* Player is asked to choose an option to set the balance. Input is validated before it is returned.
*/
string AskForBalance()
{
    string userInput;

    do {
        cout << "\nPlease choose an option(1-3) for the starting balance:\n";
        cout << "1. 100kr\n2. 300kr\n3. 500kr\n\nYour option: ";
        getline(cin, userInput);

        system("cls");

    } while (!ValidateBalance(userInput));

    return userInput;
}

/*
* User input has to fulfill either of the requirements within the if-statement in order to set the balance.
*/
bool ValidateBalance(string userInput)
{
    if (userInput == "1" || userInput == "100" || userInput == "2" || userInput == "300" || userInput == "3" || userInput == "500")
        return true;

    cout << "Wrong input. Try to choose a valid option(1-3).\n";
    return false;
}

/*
* Assign a value to "balance" according to a valid user input.
*/
void SetBalance(string userInput, int& balance)
{
    if (userInput == "1" || userInput == "100")
        balance = 100;
    else if (userInput == "2" || userInput == "300")
        balance = 300;
    else if (userInput == "3" || userInput == "500")
        balance = 500;

    system("cls");
}


/*
* A helper function that asks for the user to set a bet. Input is validated with regards to the balance before returned.
*/
string AskForBet(int balance)
{
    string userInput;

    do {
        cout << "Your current balance is: " << balance << "kr\n";
        cout << "How much do you want to bet?\n";
        getline(cin, userInput);

        system("cls");

    } while (!ValidateBet(userInput, balance));

    return userInput;
}

/*
* Checks if the user input is in numbers and whether the proposed bet is below the balance. If all the requirements are passed a true value is returned.
*/
bool ValidateBet(string userInput, int balance)
{
    char regEx[] = "[0-9]+";
    regex reg(regEx);

    if (!regex_match(userInput, reg))
    {
        cout << "Wrong input. Write only numbers.\n";
        return false;
    }

    int inputInt;
    stringstream ss;
    ss << userInput;
    ss >> inputInt;

    if (inputInt <= 0)
    {
        cout << "Invalid bet. Please bet with a number higher than.\n";
        return false;
    }

    if (inputInt > balance && inputInt <= 0)
    {
        cout << "You don't have enough money. Try again with a lower bet.\n";
        return false;
    }

    return true;
}

/*
* Assign a value to "bet" according to a valid user input.
*/
void SetBet(string userInput, int& balance, int& bet)
{
    stringstream ss;
    ss << userInput;
    ss >> bet;

    balance -= bet;
}

/*
* Assign random tokens (chars) to the game board using double for-loops 
*/
void SetGameBoard(char(*gameBoard)[3], int rows, int columns)
{
    //Set time-based seed for random number generator
    srand(time(0));

    //Generate the 3x3 game board
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int rndNum = rand() % 3 + 1;

            if (rndNum == 1)
                gameBoard[i][j] = 'A';
            else if (rndNum == 2)
                gameBoard[i][j] = 'O';
            else
                gameBoard[i][j] = 'X';

            cout << "|" << gameBoard[i][j] << "|";
        }
        cout << endl;
    }
}

/*
* Each matched rows increments "matchedLines"
*/
void MatchRows(char(*gameBoard)[3], int rows, int columns, int& matchedLines)
{
    //Check if all chars are the same for each row
    for (int i = 0; i < rows; i++)
    {
        bool isMatched = true;
        char charToMatch = gameBoard[i][0];

        for (int j = 0; j < columns; j++)
        {
            if (charToMatch != gameBoard[i][j])
            {
                isMatched = false;
                break;
            }
        }

        if (isMatched)
            matchedLines++;
    }
}


/*
* Each matched columns increments "matchedLines"
*/
void MatchColumns(char(*gameBoard)[3], int rows, int columns, int& matchedLines)
{
    //Check if all chars are the same for each column
    for (int j = 0; j < columns; j++)
    {
        bool isMatched = true;
        char charToMatch = gameBoard[0][j];

        for (int i = 0; i < rows; i++)
        {
            if (charToMatch != gameBoard[i][j])
            {
                isMatched = false;
                break;
            }
        }

        if (isMatched)
            matchedLines++;
    }
}

/*
* Each matched diagonals increments "matchedLines"
*/
void MatchDiagonals(char(*gameBoard)[3], int index, int& matchedLines)
{
    //Check if all chars are the same for the two diagonals

    //Top left -> Bottom right
    bool isMatched = true;
    char charToMatch = gameBoard[0][0];

    for (int i = 0; i < index; i++)
    {
        if (charToMatch != gameBoard[i][i])
        {
            isMatched = false;
            break;
        }
    }

    if (isMatched)
        matchedLines++;

    //Bottom left -> Top right
    isMatched = true;
    charToMatch = gameBoard[2][0];

    for (int i = 0; i < index; i++)
    {
        if (charToMatch != gameBoard[2 - i][i])
        {
            isMatched = false;
            break;
        }
    }

    if (isMatched)
        matchedLines++;
}

/*
* Calculate the payout based on the number of matched lines with a switch statement 
*/
int CalculatePayout(char(*gameBoard)[3], int rows, int columns)
{
    int matchedLines = 0;

    MatchRows(gameBoard, rows, columns, matchedLines);
    MatchColumns(gameBoard, rows, columns, matchedLines);
    MatchDiagonals(gameBoard, rows, matchedLines);

    cout << "\nYou achieved " << matchedLines << " line(s) with same characters!\n";

    //Payout factor
    int factor = 0;

    switch(matchedLines) {
    case 1:
        factor = 2;
        break;
    case 2:
        factor = 3;
        break;
    case 3:
        factor = 4;
        break;
    case 4:
        factor = 5;
        break;
    case 5:
        factor = 7;
        break;
    case 8:
        factor = 10;
        break;
    }

    return factor;
}

/*
* Capitalizes all letters in a user input
*/
void ToUpper(string& userInput)
{
    for (int i = 0; i < userInput.length(); i++)
    {
        char c = toupper(userInput.at(i));
        userInput.at(i) = c;
    }
}


/*
* Checks the user input before confirming whether to start a new round or not
*/
bool ValidateRestart(string& userInput)
{
    ToUpper(userInput);

    if (userInput == "Y" || userInput == "YES" || userInput == "N" || userInput == "NO")
        return true;

    cout << "Wrong input. Try again.";
    return false;
}


/*
* Player is asked to decide whether to exit to continue the game.
*/
void RestartGame(bool& retry)
{
    string userInput;
    
    do {
        cout << "\nContinue to play?(Y/N): ";
        getline(cin, userInput);

        system("cls");
    } while (!ValidateRestart(userInput));

    if (userInput == "Y" || userInput == "YES")
        return;

    retry = false;
}
