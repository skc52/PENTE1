

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Computer.h"
#include <string>
#include "Tournament.h"
#include "ComputerStrategy.h"
// Implementation of Computer class
Computer::Computer(const std::string &name) : Player(name) {}

bool Computer::makeMove(Round *r, Board *b, ComputerStrategy *c, Tournament *t)
{
    // determine position from the strategy class
    // for now ask input for computer too,
    // call askinput from board
    std::string inputString;
    if (r->getTurnNum() != 0)
    {
        // r->askPositionInput(b);
        inputString = c->determineBestPosition(b, r->getCurrentPlayer(), r->getNextPlayer(), r);
        b->parsePosition(inputString);
    }
    // call place your piece function from board
    // std::string inputString = c->determineBestPosition(b, r->getCurrentPlayer(), r->getNextPlayer());
    // b->parsePosition(inputString);
    // strategy will call bestPosition,
    return b->placeYourPiece(r);
    // call change turn from round here
}