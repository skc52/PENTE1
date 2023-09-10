

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Computer.h"
#include <string>
#include "ComputerStrategy.h"
// Implementation of Computer class
Computer::Computer(const std::string &name) : Player(name) {}

bool Computer::makeMove(Round *r, Board *b, ComputerStrategy *c)
{
    // determine position from the strategy class
    // for now ask input for computer too,
    // call askinput from board
    if (r->getTurnNum() != 0)
    {
        r->askPositionInput(b);
    }
    // call place your piece function from board
    // std::string inputString = c->determineBestPosition(b, r->getCurrentPlayer(), r->getNextPlayer());
    // b->parsePosition(inputString);
    // strategy will call bestPosition,
    return b->placeYourPiece(r);
    // call change turn from round here
}