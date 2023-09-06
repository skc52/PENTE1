

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Human.h"

// Implementation of Human class
Human::Human(const std::string &name) : Player(name) {}

bool Human::makeMove(Round *r, Board *b)
{
    // call askinput from board
    r->askPositionInput(b);
    // call placeyourpiece function from the board
    b->placeYourPiece(r);
    // call change turn from round here
}
