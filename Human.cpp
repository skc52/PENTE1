

#include "Board.h"
#include "Player.h"
#include "Round.h"
#include <iostream>
#include "Human.h"
#include "Tournament.h"

// Implementation of Human class
Human::Human(const std::string &name) : Player(name) {}

bool Human::makeMove(Round *r, Board *b, ComputerStrategy *c, Tournament *t)
{
    // call askinput from board
    // call askinput from board
    if (r->getTurnNum() != 0)
    {
        if (!r->askPositionInput(b, t->getHuman(), t->getComputer(), t, c))
        {
            t->setPause(); // willl pause and quit game
            return false;
        }
    }

    // call placeyourpiece function from the board
    return b->placeYourPiece(r, t);
    // call change turn from round here
}
