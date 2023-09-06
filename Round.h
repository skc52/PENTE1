#ifndef ROUND_H
#define ROUND_H
#include <string>
#include <vector>
#include <map>
// Forward declaration of the Player and Round class
class Player;

class Round
{
public:
    Round(){};
    ~Round(){};
    bool coinToss();
    void startRound();
    void changeTurn();
    void incrementTurnNum();
    void askPositionInput();
    void updatePairsCaptured(Player *p);
    void updateFourConsecutive(Player *p);
    int getPairsCapturedNum(Player *p);
    int getFourConsecutivesNum(Player *p);
    int getGamePoints(Player *p);
    void setPairsCapturedNum(Player *p);
    void setFourConsecutive(Player *p);
    void announceWinnerOfTheRound(Player *p);
    void displayClosingStats();
    void askToContinueGame();
    Player *getCurrentPlayer();
    Player *getNextPlayer();
    Player *getWinner();

private:
    Player *currentPlayer;
    Player *nextPlayer;
    Player *winnerOfTheRound;
    std::map<Player *, int> pairsCaptured;
    std::map<Player *, int> fourConsecutive;
    std::map<Player *, int> gamePoints;
    // std::vector<int> pairsCaptured = {0, 0};   // first is human, second is computer
    // std::vector<int> fourConsecutive = {0, 0}; // first is human, second is computer
    int currentTurnNum;
};
#endif