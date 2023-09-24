#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

// Forward declaration of the Player and Round class
class Player;
class Round;
class Board;

class Tournament
{
public:
    Tournament();
    ~Tournament();
    void setUpPlayers(Player *h, Player *c);
    Round *createANewRound();
    int getTotalScores(Player *p, bool saving = false);
    void showTotalScoresForBoth();
    void announceWinner();
    void displayScoresForAllRounds();
    Player *getHuman();
    Player *getComputer();
    int getRoundsCount();
    Player *getPreviousWinner(); // this will be helpful in setting up colors in the next round
    Player *getPreviousLoser();  // this will be helpful in setting up colors in the next round
    bool LoadGame(std::string filename, Board *b, Round *r);
    void setTotalScore(int humanScore, int comScore);
    void setPause()
    {
        pauseState = !pauseState;
    }
    bool getPause()
    {
        return pauseState;
    }

private:
    std::map<Player *, int> loadedScores;
    Player *human;
    Player *computer;
    std::vector<Round *> rounds;
    Player *winner;
    bool pauseState = false;
};

#endif
