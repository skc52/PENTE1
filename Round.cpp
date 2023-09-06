#include "Round.h"
#include "Player.h"
#include "Tournament.h"
#include "Board.h"
#include <random>
#include <ctime>
#include <string>
#include <iostream>

Round::Round()
{
    this->currentTurnNum = 0;
}
bool Round::coinToss()
{
    char humanChoice;
    std::cout << "Coin toss: Enter 'H' for heads or 'T' for tails: ";
    std::cin >> humanChoice;
    // Use the current time as a seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Generate a random number
    humanChoice = toupper(humanChoice);
    int toss = (std::rand() % 2) ? 'H' : 'T';
    std::cout << "It was : " << toss << std::endl;

    if (humanChoice == toss)
    {
        std::cout << "You won the toss! You will start the game.\n";
        return true;
    }
    else
    {
        std::cout << "Computer won the toss. Computer will start the game.\n";
        return false;
    }
}

void Round::startRound(Tournament *t, Board *b)
{
    // Implementation for startRound
    std::cout << "STARTING ROUND\n";
    // intialize white and black players
    if (coinToss())
    { // on winning coin toss white will be human
        currentPlayer = t->getHuman();
        nextPlayer = t->getComputer();
    }
    else
    {
        currentPlayer = t->getComputer();
        nextPlayer = t->getHuman();
    }

    // Place the piece in J10 (10, 10)

    currentPlayer->makeMove(this, b);
}

void Round::changeTurn()
{
    // Implementation for changeTurn
    incrementTurnNum();
    // swap
    Player *temp = currentPlayer;
    currentPlayer = nextPlayer;
    nextPlayer = temp;
}

int Round::getTurnNum()
{
    return currentTurnNum;
}

void Round::incrementTurnNum()
{
    // Implementation for incrementTurnNum

    this->currentTurnNum += 1;
}

void Round::askPositionInput(Board *b)
{
    // Implementation for askPositionInput
    bool isValidPos = false;
    std::string position;
    while (!isValidPos)
    {
        std::cout << "Enter the intersection you want to put your piece in. Follow the format A10, B2, K16.\n";
        std::cout << "Else, enter H for suggestion\n";
        std::cin >> position;
        if (!b->parsePosition(position))
            continue;
        isValidPos = b->checkValidity();
    }
}

int Round::getPairsCapturedNum(Player *p)
{
    // Implementation for getPairsCapturedNum
    if (pairsCaptured.find(p) != pairsCaptured.end())
    {
        return pairsCaptured[p];
    }
    else
    {
        return 0;
    }
}

int Round::getFourConsecutivesNum(Player *p)
{
    // Implementation for getFourConsecutivesNum
    if (fourConsecutive.find(p) != fourConsecutive.end())
    {
        return fourConsecutive[p];
    }
    else
    {
        return 0;
    }
}

int Round::getGamePoints(Player *p)
{
    // Implementation for getGamePoints
    if (gamePoints.find(p) != gamePoints.end())
    {
        return gamePoints[p];
    }
    else
    {
        return 0;
    }
}

void Round::setPairsCapturedNum(Player *p)
{
    // Implementation for setPairsCapturedNum
    pairsCaptured[p] += 1;
}

void Round::setFourConsecutive(Player *p, int foursCount)
{
    // Implementation for setFourConsecutive
    fourConsecutive[p] = foursCount;
}

void Round::setGamePoints(Player *p)
{
    // Implementation for setGamePoints
    gamePoints[p] = 5;
    winnerOfTheRound = currentPlayer;
}

void Round::announceWinnerOfTheRound(Player *p)
{
    // Implementation for announceWinnerOfTheRound
    if (!getWinner())
    {
        std::cout << "ROUND WINNER " << getWinner()->getName() << std::endl;
    }
    else
    {
        std::cout << "ROUND WAS A DRAW" << std::endl;
    }
}

void Round::displayClosingStats()
{
    // Implementation for displayClosingStats
    std::cout << currentPlayer->getName() << " : "
              << "Pairs captured = " << getPairsCapturedNum(currentPlayer);
    std::cout << " Four consecutives = " << getFourConsecutivesNum(currentPlayer) << " Game Points " << getGamePoints(currentPlayer) << std::endl;
    std::cout << nextPlayer->getName() << " : "
              << "Pairs captured = " << getPairsCapturedNum(nextPlayer);
    std::cout << " Four consecutives = " << getFourConsecutivesNum(nextPlayer) << " Game Points " << getGamePoints(nextPlayer) << std::endl;
}

bool Round::askToContinueGame()
{
    // Implementation for askToContinueGame
    char response;

    // Ask the player if they want to continue the game
    std::cout << "Do you want to continue the tournament? (y/n): ";
    std::cin >> response;

    // Check the player's response
    if (response == 'y' || response == 'Y')
    {
        return true; // Player wants to continue
    }
    else
    {
        return false; // Player does not want to continue
    }
}

Player *Round::getCurrentPlayer()
{
    // Implementation for getCurrentPlayer
    return currentPlayer;
}

Player *Round::getNextPlayer()
{
    // Implementation for getNextPlayer
    return nextPlayer;
}

Player *Round::getWinner()
{
    // Implementation for getWinner
    return winnerOfTheRound;
}