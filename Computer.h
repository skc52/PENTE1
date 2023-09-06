#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
#include "Round.h"

// Computer class (inherits from Player)
class Computer : public Player
{
public:
    Computer(const std::string &name);

    // Implement the pure virtual function
    bool makeMove(Round *r, Board *b) override;

    // Other member functions specific to the Computer player
};

#endif