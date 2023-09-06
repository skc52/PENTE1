#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>

// Forward declaration of the Player and Round class
class Player;
class Round;

class Tournament
{
public:
    Tournament();
    ~Tournament();
    void setUpPlayers(Player *h, Player *c);
    Round *createANewRound();
    int getTotalScores(Player *p);
    void showTotalScoresForBoth();
    void announceWinner();
    void displayScoresForAllRounds();

private:
    Player *human;
    Player *computer;
    std::vector<Round *> rounds;
    Player *winner;
};

#endif
