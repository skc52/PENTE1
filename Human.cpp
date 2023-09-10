

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Human.h"

// Implementation of Human class
Human::Human(const std::string &name) : Player(name) {}

bool Human::makeMove(Round *r, Board *b, ComputerStrategy *c)
{
    // call askinput from board
    // call askinput from board
    if (r->getTurnNum() != 0)
    {
        r->askPositionInput(b);
    }
    // call placeyourpiece function from the board
    return b->placeYourPiece(r);
    // call change turn from round here
}
