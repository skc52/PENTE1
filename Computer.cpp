

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Computer.h"
// Implementation of Computer class
Computer::Computer(const std::string &name) : Player(name) {}

bool Computer::makeMove(Round *r, Board *b)
{
    // determine position from the strategy class
    // for now ask input for computer too,
    r->askPositionInput(b);
    // call place your piece function from board
    return b->placeYourPiece(r);
    // call change turn from round here
}