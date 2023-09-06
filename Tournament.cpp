#include "Tournament.h"
#include "Round.h"
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
int Tournament::getRoundsCount()
{
    return rounds.size();
}
int Tournament::getTotalScores(Player *p)
{
    int totalScore = 0;
    for (int i = 0; i < this->rounds.size(); i++)
    {
        Round *r = rounds[i];
        totalScore += r->getPairsCapturedNum(p);
        totalScore += r->getFourConsecutivesNum(p);
        totalScore += r->getGamePoints(p);
    }
    return totalScore;
}

void Tournament::showTotalScoresForBoth()
{
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

    if (!winner)
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
        if (!rounds[i]->getWinner())
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