#ifndef PLAYER_H
#define PLAYER_H
// Forward declaration of the Board class
class Board;
class Round;
class ComputerStrategy;
#include <iostream>
// Abstract base class Player
class Player
{
public:
    Player(const std::string& name);
    virtual ~Player();

    // Abstract method to make a move (to be implemented by derived classes)
    virtual bool makeMove(Round* r, Board* b, ComputerStrategy* c) = 0; // return false if the game has ended

    // Getters
    const std::string& getName() const;
    char getColor() const;

    // Setters
    void setColor(char c);

    // Other member functions or data members common to all players
private:
    std::string name;
    char color;
};

#endif
