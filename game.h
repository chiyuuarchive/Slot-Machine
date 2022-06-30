#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

string AskForBalance();

string AskForBet(int deposit);

bool ValidateBalance(string userInput);

void SetBalance(string userInput, int& balance);

bool ValidateBet(string userInput, int balance);

void SetBet(string userInput, int& balance, int& bet);

void SetGameBoard(char(*gameBoard)[3], int rows, int columns);

int CalculatePayout(char(*gameBoard)[3], int rows, int columns);

void RestartGame(bool &retry);