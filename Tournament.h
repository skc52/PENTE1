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
    Player *getHuman();
    Player *getComputer();
    int getRoundsCount();
    Player *getPreviousWinner(); // this will be helpful in setting up colors in the next round
    Player *getPreviousLoser();  // this will be helpful in setting up colors in the next round

private:
    Player *human;
    Player *computer;
    std::vector<Round *> rounds;
    Player *winner;
};

#endif
