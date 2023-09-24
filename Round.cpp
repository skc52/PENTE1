#include "Round.h"
#include "Player.h"
#include "Tournament.h"
#include "ComputerStrategy.h"
#include "Board.h"
#include <random>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
Round::Round()
{
    this->currentTurnNum = 0;
}
void Round::loadRound(std::string filename, Player *human, Player *computer, Tournament *t)
{
    int hCapturedPairs = 0, hScore = 0;
    int cCapturedPairs = 0, cScore = 0;
    std::string currPlayer;
    std::string currColor;
    // read from the file captured pairs and scores of human and computer

    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Find and skip the "Human:" line
    std::string line;
    // Read and parse lines until "Human:" is found
    while (std::getline(inputFile, line))
    {
        if (line.find("Human:") != std::string::npos)
        {
            std::getline(inputFile, line);
            size_t pos = line.find("Captured pairs:");
            if (pos != std::string::npos)
            {
                hCapturedPairs = std::stoi(line.substr(pos + 15));
            }

            std::getline(inputFile, line);
            pos = line.find("Score:");
            if (pos != std::string::npos)
            {
                hScore = std::stoi(line.substr(pos + 6));
            }

            break;
        }
    }

    // Read and parse lines until "Computer:" is found
    while (std::getline(inputFile, line))
    {
        if (line.find("Computer:") != std::string::npos)
        {
            std::getline(inputFile, line);
            size_t pos = line.find("Captured pairs:");
            if (pos != std::string::npos)
            {
                cCapturedPairs = std::stoi(line.substr(pos + 15));
            }

            std::getline(inputFile, line);
            pos = line.find("Score:");
            if (pos != std::string::npos)
            {
                cScore = std::stoi(line.substr(pos + 6));
            }

            break;
        }
    }

    // Read and parse lines until "Next Player:" is found
    while (std::getline(inputFile, line))
    {
        if (line.find("Next Player:") != std::string::npos)
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                std::string playerInfo = line.substr(colonPos + 2);
                size_t hyphenPos = playerInfo.find('-');
                if (hyphenPos != std::string::npos)
                {
                    currPlayer = playerInfo.substr(0, hyphenPos - 1);
                    currColor = playerInfo.substr(hyphenPos + 2);
                }
            }

            break;
        }
    }

    inputFile.close();

    //--------------------------------------------------------------------------
    setPairsCapturedNum(human, hCapturedPairs);
    setPairsCapturedNum(computer, cCapturedPairs);

    t->setTotalScore(hScore, cScore);

    // also get the current and next player and their colors
    if (currPlayer == "Human")
    {
        currentPlayer = computer; // the reason i am setting current player as computer even though currPlayer reads Human
        // is in Pente.cpp, it changes turn as soon as the game loads up. so even tho it should be human's turn, computer plays first
        // that is why i set the currentPlayer as enemy, so it changes turn and switched to human
        // i have setTurnNum to turnNum -1 for this exact reason.
        nextPlayer = human;
    }
    else
    {
        currentPlayer = human;
        nextPlayer = computer;
    }
    if (currColor == "White")
    {
        currentPlayer->setColor('B');
        nextPlayer->setColor('W');
    }
    else
    {
        currentPlayer->setColor('W');
        nextPlayer->setColor('B');
    }

    // determine the turn number
    //  a captured pair is 2 moves
    //  get the count of all the non zero characters in the board
    int turnNum = getTurnNum();
    turnNum = turnNum + hCapturedPairs * 2 + cCapturedPairs * 2;
    setTurnNum(turnNum - 1);
}

bool Round::coinToss()
{
    char humanChoice;
    do
    {
        std::cout << "Coin toss: Enter 'H' for heads or 'T' for tails: ";
        std::cin >> humanChoice;
    } while (humanChoice != tolower('h') && humanChoice != tolower('t'));
    // Use the current time as a seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Generate a random number
    humanChoice = toupper(humanChoice);
    char toss = (std::rand() % 2) ? 'H' : 'T';
    std::cout << "It was : " << toss;

    if (humanChoice == toss)
    {
        std::cout << ". Human won the toss!\n";
        return true;
    }
    else
    {
        std::cout << ". Computer won the toss.\n";
        return false;
    }
}

void Round::startRound(Tournament *t, Board *b)
{
    // Implementation for startRound
    std::cout << "Starting round " << t->getRoundsCount() << ".";
    b->resetBoard();
    // intialize white and black players
    if (t->getRoundsCount() == 1 || t->getTotalScores(t->getHuman()) == t->getTotalScores(t->getComputer())) // if first round or scores are same, toos coin to determine starter
    {
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
    }
    else
    {
        if (t->getTotalScores(t->getHuman()) > t->getTotalScores(t->getComputer())) // else if scores are different, higher scorer is the starter
        {
            currentPlayer = t->getHuman();
            nextPlayer = t->getComputer();
        }
        else
        {
            nextPlayer = t->getHuman();
            currentPlayer = t->getComputer();
        }
    }

    currentPlayer->setColor('W');
    nextPlayer->setColor('B');
    std::cout << currentPlayer->getName() << " is starting the game\n";
    currentPlayer->makeMove(this, b, nullptr, t);
}

void Round::changeTurn(Board *b, Player *human, Player *computer, Tournament *t)
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

void Round::setTurnNum(int num)
{
    currentTurnNum = num;
}

void Round::incrementTurnNum()
{
    this->currentTurnNum += 1;
}

bool Round::askPositionInput(Board *b, Player *human, Player *computer, Tournament *t, ComputerStrategy *c) // false means the game has ended...possibly quitted by human player
{

    // ask if user wants to continue or save and quit

    char saveState;

    do
    {
        std::cout << "Enter s/S to save and quit your game. Enter c/c to continue with the game.\n";
        std::cin >> saveState;
    } while (tolower(saveState) != 's' && tolower(saveState) != 'c');

    if (tolower(saveState) == 's')
    {

        saveGameToFile(b, human, computer, t);
        return false;
    }
    // if the current player is computer, then only upto this part of this function will execute

    if (currentPlayer == computer)
    {
        return true;
    }

    // ask user if he wants help
    char helpState;

    do
    {
        std::cout << "Enter h/H to get recommendations on where to place your piece, c/c to continue with the game\n";
        std::cin >> helpState;
    } while (tolower(helpState) != 'h' && tolower(helpState) != 'c');

    if (tolower(helpState) == 'h')
    {
        // provide suggestion on where to put next piece
        std::string bestPosition, reason;
        // reasoning is provided in determineBestPosition itself
        bestPosition = c->determineBestPosition(b, getCurrentPlayer(), getNextPlayer(), this);
        std::cout << "Recommended position would be " << bestPosition << std::endl;
    }

    // asking for user input
    bool isValidPos = false;
    std::string position;
    while (!isValidPos)
    {
        std::cout << "Enter the intersection you want to put your piece in. Follow the format A10, B2, K16.\n";
        std::cin >> position;

        if (!b->parsePosition(position))
            continue;
        isValidPos = b->checkValidity(this);
    }
    std::cout << "Human entered " << position << std::endl;
    return true;
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

void Round::setPairsCapturedNum(Player *p, int captureCount)
{
    pairsCaptured[p] = captureCount;
}

void Round::setFourConsecutive(Player *p, int foursCount)
{
    // Implementation for setFourConsecutive
    fourConsecutive[p] = foursCount;
}

void Round::setGamePoints(Player *p, Tournament *t)
{
    // Implementation for setGamePoints
    gamePoints[p] = 5;

    // Winner of The Round is the player with most scores in the tournament up to that point
    winnerOfTheRound = t->getTotalScores(currentPlayer) < t->getTotalScores(nextPlayer) ? nextPlayer : currentPlayer;

    loserOFTheRound = winnerOfTheRound == currentPlayer ? nextPlayer : currentPlayer;
}

void Round::displayClosingStats()
{
    // Implementation for displayClosingStats
    std::cout << currentPlayer->getName() << " scored " << getPairsCapturedNum(currentPlayer) + getFourConsecutivesNum(currentPlayer) + getGamePoints(currentPlayer)
              << " points. "
              << "Pairs captured = " << getPairsCapturedNum(currentPlayer);
    std::cout << " Four consecutives = " << getFourConsecutivesNum(currentPlayer) << " Game Points " << getGamePoints(currentPlayer) << std::endl;
    std::cout << nextPlayer->getName() << " scored " << getPairsCapturedNum(nextPlayer) + getFourConsecutivesNum(nextPlayer) + getGamePoints(nextPlayer)
              << " points. "
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

Player *Round::getLoser()
{
    // Implementation for getWinner
    return loserOFTheRound;
}

void Round::saveGameToFile(Board *b, Player *human, Player *computer, Tournament *t)
{
    // ask the name for the txt file
    std::string fileName;
    std::cout << "Enter the name for a file for this game to be saved\n";
    std::cin >> fileName;
    // save the board into the txt file
    std::ofstream outputFile(fileName + ".txt");

    if (outputFile.is_open())
    {
        outputFile << "Board:" << std::endl;
        for (int i = 1; i < 20; i++)
        {
            for (int j = 1; j < 20; j++)
            {
                outputFile << b->getPiece(i, j);
            }
            outputFile << std::endl;
        }
        outputFile << "Human: " << std::endl;
        outputFile << "Captured pairs: " << getPairsCapturedNum(human) << std::endl;
        outputFile << "Score: " << t->getTotalScores(human, true) << std::endl
                   << std::endl;

        outputFile << "Computer: " << std::endl;
        outputFile << "Captured pairs: " << getPairsCapturedNum(computer) << std::endl;
        outputFile << "Score: " << t->getTotalScores(computer, true) << std::endl
                   << std::endl;

        // everytime human saves the game, so when he is saving and quitting the game he cannot place any moves, so it is always
        // his turn when he loads up a game
        std::string colorNext = currentPlayer->getColor() == 'W' ? "White" : "Black";
        std::string nextPlayerCategory = currentPlayer->getName() != "ROBOT" ? "Human" : "Computer";
        outputFile << "Next Player: " << nextPlayerCategory << " - " << colorNext << std::endl;
        outputFile.close();
        std::cout << "File written successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error opening the file." << std::endl;
    }

    // save the stats into the txt file
}
