#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H
#include <string>
#include <vector>
#include <map>

// Forward declaration of the Player and Round class
class Player;
class Board;
class Tournament;
class Round;

class ComputerStrategy
{
public:
    ComputerStrategy();
    // convert the best position to string input form A10
    std::string convertPosToString(int row, int col);
    std::string determineBestPosition(Board *board, Player *computerPlayer, Player *humanPlayer, Round *r);

private:
    // Helper methods for each criterion
    int calculateConsecutivesPriority(int row, int col, Board *board, Player *computerPlayer);
    int calculateCapturePairsPriority(int row, int col, Board *board, Player *computerPlayer, Round *r);
    int calculateEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *computerPlayer);
    int calculateStopOpponentPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer);
    int calculateStopRuiningPriority(int row, int col, Board *board, Player *computerPlayer);
    int calculateCaptureRiskPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer, Round *r);
    int calculateCenterProximityPriority(int row, int col, Board *board);

    // Other methods and data members as needed
};
#endif