
#include "Player.h"
#include "Board.h"
#include <iostream>

// Implementation of Player class
Player::Player(const std::string &name) : name(name) {}

Player::~Player() {}

const std::string &Player::getName() const
{
    return name;
}
void Player::setColor(char c)
{
    color = c;
}
char Player::getColor() const
{
    return color;
}