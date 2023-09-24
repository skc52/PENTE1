#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>

// Forward declaration of the Player and Round class
class Player;
class Round;
class Tournament;
class Board
{
private:
    char board[20][20]; // 2D array for the game board
    int row;            // current row passed by the current player
    int col;            // current column passed by the current player

public:
    // Constructor
    Board();

    // Member functions
    void resetBoard();
    bool placeYourPiece(Round *r, Tournament *t);
    bool checkValidity(Round *r);

    bool checkAndCapture(Round *r, Player *p, Player *e);
    bool checkForPairs(Player *p, Player *e, int dx, int dy);
    bool capturePairs(Round *r, Player *p, int dx, int dy);
    bool checkForFive(Round *r, Tournament *t);
    int checkForFours(Round *r, char piece, Player *p);
    int checkForFoursHorizontal(char piece);
    int checkForFoursVertical(char piece);
    void DisplayBoard(Round *r, Tournament *t);
    bool parsePosition(const std::string &input);
    void showComment(const std::string &comment);
    bool isWithinBounds(int row, int col);
    char getPiece(int row, int col);
    void setPiece(int row, int col, char c);
};

#endif // BOARD_H
