#ifndef BOARD_H
#define BOARD_H

#include <string>

// Forward declaration of the Player and Round class
class Player;
class Round;
class Board
{
private:
    char board[20][20]; // 2D array for the game board
    int row;            // current row passed the current player
    int col;            // current column passed by the current player

public:
    // Constructor
    Board();

    // Member functions
    void resetBoard();                                        // done
    bool placeYourPiece(Round *r);                            // done incomplete
    bool checkValidity();                                     // done
    bool checkAndCapture(Round *r, Player *p, Player *e);     // done
    bool checkForPairs(Player *p, Player *e, int dx, int dy); // dome
    bool capturePairs(Round *r, Player *p, int dx, int dy);   // done incomplete
    bool checkForFive(Round *r);                              // done incomplete
    int checkForFours(Round *r, char piece, Player *p);       // this could be a function of strategy class... done
    int checkForFoursHorizontal(char piece);
    int checkForFoursVertical(char piece);
    void DisplayBoard(Round *r);                  // done incomplete
    bool parsePosition(const std::string &input); // done
    void showComment(const std::string &comment); // done
    bool isWithinBounds(int row, int col);        // done
    char getPiece(int row, int col);

private:
    // Private helper functions
};

#endif // BOARD_H
