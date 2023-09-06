#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"
// Human class (inherits from Player)
class Human : public Player
{
public:
    Human(const std::string &name);

    // Implement the pure virtual function
    bool makeMove(Round *r, Board *b) override;

    // Other member functions specific to the Human player
};

#endif