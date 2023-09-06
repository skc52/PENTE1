#ifndef PLAYER_H
#define PLAYER_H
// Forward declaration of the Board class
class Board;
class Round;
#include <iostream>
// Abstract base class Player
class Player
{
public:
    Player(const std::string &name);
    virtual ~Player();

    // Abstract method to make a move (to be implemented by derived classes)
    virtual void makeMove(Round *r, Board *b) = 0;

    // Getters
    const std::string &getName() const;
    char getColor() const;

    // Setters
    void setColor(char c);

    // Other member functions or data members common to all players
private:
    std::string name;
    char color;
};

#endif
