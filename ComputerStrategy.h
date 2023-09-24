#pragma once
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
    ComputerStrategy(Tournament *t);
    // convert the best position to string input form A10
    std::string convertPosToString(int row, int col);
    std::string determineBestPosition(Board *board, Player *computerPlayer, Player *humanPlayer, Round *r);
    std::string provideReasonForBestPos(int priority);

private:
    // Helper methods for each criterion
    std::pair<int, std::string> calculateConsecutivesPriority(int row, int col, Board *board, Player *computerPlayer);
    std::pair<int, std::string> calculateCapturePairsPriority(int row, int col, Board *board, Player *computerPlayer, Round *r, bool checkingOwn = true);
    std::pair<int, std::string> calculatePriorityWith4Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r);
    std::pair<int, std::string> calculateOpponentPriorityWith4Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r);

    std::pair<int, std::string> calculateEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *computerPlayer, Round *r);
    std::pair<int, std::string> calculateOpponentsEndGamePriorityWith5Consectuives(int row, int col, Board *board, Player *opponentPlayer, Round *r);

    std::pair<int, std::string> calculateStopOpponentPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer);
    std::pair<int, std::string> calculateCaptureRiskPriority(int row, int col, Board *board, Player *computerPlayer, Player *humanPlayer, Round *r);

    Tournament *t;
    std::map<int, std::string> reasons;
};
#endif