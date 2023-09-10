#ifndef STRATEGY_H
#define STRATEGY_H
#include <string>
#include <vector>
#include <map>

// Forward declaration of the Player and Round class
class Player;
class Board;
class Tournament;
class Round;
class Strategy
{
public:
    // Constructor(s)
    Strategy();

    // scan will return the best position along with their priority number
    // each scenario will be given a priority number
    // return the highest priority move
    void getBestPosition();

    void scanBoardHorizontally();
    void scanBoardHorizontallyReverse();
    void scanBoardVertically();
    void scanBoardVerticallyReverse();
    void scanBoardForwardDiagonal();
    void scanBoardForwardDiagonalReverse();
    void scanBoardBackwardDiagonalReverse();
    void scanBoardBackwardDiagonal();

    // Data Members
private:
    std::vector<std::pair<int, int>> posAndPriority; // first = position && second = priority
    int horizontal[2] = {0, 1};
    int vertical[2] = {1, 0};

    int forwardDiagonal[2] = {-1, 1};
    int backwardDiagonal[2] = {1, 1};

    int dp[20][20] = {{0}};         // 20x20 array of int initialized with 0s
    int dpRev[20][20] = {{0}};      // 20x20 array of int initialized with 0s
    int dpEnemy[20][20] = {{0}};    // 20x20 array of int initialized with 0s
    int dpEnemyRev[20][20] = {{0}}; // 20x20 array of int initialized with 0s

    // Member Functions
    // Add member functions here
};
#endif