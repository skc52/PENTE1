#include "Tournament.h"
#include "Round.h"
#include "Board.h"
#include "Player.h"

Tournament::Tournament()
{
}
Tournament::~Tournament()
{
    if (human != nullptr)
    {
        delete human;
        human = nullptr;
    }
    if (computer != nullptr)
    {
        delete computer;
        computer = nullptr;
    }
    if (winner != nullptr)
    {
        delete winner;
        winner = nullptr;
    }
}

void Tournament::setUpPlayers(Player *h, Player *c)
{
    human = h;
    computer = c;
}

Round *Tournament::createANewRound()
{
    Round *r = new Round();
    this->rounds.push_back(r);
    return r;
}
Player *Tournament::getPreviousWinner()
{
    int ind = getRoundsCount() - 2;
    return rounds[ind]->getWinner();
}
Player *Tournament::getPreviousLoser()
{
    int ind = getRoundsCount() - 2;
    return rounds[ind]->getLoser();
}
bool Tournament::LoadGame(std::string filename, Board *b, Round *r)
{
    // read from the file
    //   // Open the file for reading
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return false;
    }

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return false;
    }

    // Find and skip the "Board:" line
    std::string line;
    while (std::getline(inputFile, line) && line != "Board:")
    {
        // Skip lines until "Board:" is found
    }

    // initalize the board with the data there
    //  // Read the board data character by character
    int turnNum = 0;

    for (int i = 0; i < 19; ++i)
    {
        std::getline(inputFile, line); // Read the line with the board data
        if (line.length() < 19)
        {
            std::cerr << "Error: Insufficient characters in the board data." << std::endl;
            return false;
        }

        // Store the first 19 characters in the board
        for (int j = 0; j < 19; ++j)
        {
            // if character is not zero, increment turn number
            if (line[j] != 'O' && line[j] != '0')
            {
                b->setPiece(i + 1, j + 1, line[j]); // since the board content starts from 1 row and 1 col
                turnNum++;
            }
            else
            {
                b->setPiece(i + 1, j + 1, '0');
            }
        }
    }
    r->setTurnNum(turnNum);

    // Close the file
    inputFile.close();
    // set the turn to the next player mentioned in the file
    // set the scores
    return true;
}
void Tournament::setTotalScore(int humanScore, int comScore)
{
    loadedScores[human] = humanScore;
    loadedScores[computer] = comScore;
}
int Tournament::getRoundsCount()
{
    return rounds.size();
}
int Tournament::getTotalScores(Player *p, bool saving)
{
    int totalScore = 0;
    for (int i = 0; i < this->rounds.size(); i++)
    {
        Round *r = rounds[i];
        // if saving is true && then dont include the score for the current round
        if (saving && i == this->rounds.size() - 1)
        {
            break;
        }
        totalScore += r->getPairsCapturedNum(p);
        totalScore += r->getFourConsecutivesNum(p);
        totalScore += r->getGamePoints(p);
    }
    return totalScore + loadedScores[p];
}
void Tournament::showTotalScoresForBoth()
{
    std::cout << "Showing Tournament Scores: \n";
    std::cout << "Human : " << getTotalScores(human) << std::endl;
    std::cout << "Computer : " << getTotalScores(computer) << std::endl;
}
void Tournament::announceWinner()
{
    if (getTotalScores(human) > getTotalScores(computer))
    {
        winner = human;
    }
    else if (getTotalScores(human) < getTotalScores(computer))
    {
        winner = computer;
    }
    else
    {
        winner = nullptr;
    }

    if (winner)
    {
        std::cout << winner->getName() << " won the tournament" << std::endl;
    }
    else
    {
        std::cout << "It's a draw" << std::endl;
    }
}
void Tournament::displayScoresForAllRounds()
{
    std::cout << "DISPLAYING TOURNAMENT STATS BY ROUND" << std::endl;
    for (int i = 0; i < rounds.size(); i++)
    {

        std::cout << "Round " << i + 1 << " scores" << std::endl;
        std::cout << human->getName() << " : "
                  << "Pairs captured = " << rounds[i]->getPairsCapturedNum(human);
        std::cout << " Four consecutives = " << rounds[i]->getFourConsecutivesNum(human) << " Game Points " << rounds[i]->getGamePoints(human) << std::endl;
        std::cout << computer->getName() << " : "
                  << "Pairs captured = " << rounds[i]->getPairsCapturedNum(computer);
        std::cout << " Four consecutives = " << rounds[i]->getFourConsecutivesNum(computer) << " Game Points " << rounds[i]->getGamePoints(computer) << std::endl;
        if (rounds[i]->getWinner())
        {
            std::cout << "ROUND WINNER " << rounds[i]->getWinner()->getName() << std::endl;
        }
        else
        {
            std::cout << "ROUND WAS A DRAW" << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------------------------\n";
    }
}

Player *Tournament::getHuman()
{
    return human;
}

Player *Tournament::getComputer()
{
    return computer;
}