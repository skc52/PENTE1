#pragma once
#ifndef ROUND_H
#define ROUND_H
#include <string>
#include <vector>
#include <map>
// Forward declaration of the Player and Round class
class Player;
class Board;
class Tournament;

class Round
{
public:
    Round();
    // ~Round(){};
    void loadRound(std::string filename, Player *human, Player *computer, Tournament *t);
    bool coinToss();                          // will determine currentPlayer and nextPlayer
    void startRound(Tournament *t, Board *b); // reset board and start the game
    void changeTurn();                        // swap currentPlayer and nextPlayer
    void incrementTurnNum();
    int getTurnNum(); // if currentPlayer is white increment number by 1, before beginning the game it would be -1
    void setTurnNum(int num);
    bool askPositionInput(Board *b, Player *human, Player *computer, Tournament *t); // ask human player for position
    int getPairsCapturedNum(Player *p);
    int getFourConsecutivesNum(Player *p);
    int getGamePoints(Player *p);
    void setPairsCapturedNum(Player *p);
    void setPairsCapturedNum(Player *p, int captureCount);
    void setFourConsecutive(Player *p, int foursCount);
    void setGamePoints(Player *p);   // set winner too , game ends here, 5 consecutive pieces
    void announceWinnerOfTheRound(); // whichever player has game points is the winner
    void displayClosingStats();      // show the pairsCaptured, fourConsecutives, and the game points for both players
    bool askToContinueGame();        // ask human to continue the round
    Player *getCurrentPlayer();
    Player *getNextPlayer();
    Player *getWinner();
    Player *getLoser();
    void saveGameToFile(Board *b, Player *human, Player *computer, Tournament *t);

private:
    Player *currentPlayer;
    Player *nextPlayer;
    Player *winnerOfTheRound;
    Player *loserOFTheRound;
    std::map<Player *, int> pairsCaptured;
    std::map<Player *, int> fourConsecutive;
    std::map<Player *, int> gamePoints;
    // std::vector<int> pairsCaptured = {0, 0};   // first is human, second is computer
    // std::vector<int> fourConsecutive = {0, 0}; // first is human, second is computer
    int currentTurnNum;
};
#endif