#include "player.h"

Position::Position()
{
    this->x = 0;
    this->y = 0;
}


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Player::Player()
{
    //TODO
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    //TODO
}

void Player::turnDirection(TurnDirection turnDirection)
{
    //TODO
}

Position Player::getNextForwardPosition()
{
    //TODO

    return this->position;
}

void Player::updatePosition(Position position)
{
    //TODO
}

void Player::displayDirection()
{
    //TODO
}
