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
    this->position = Position();
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    //TODO
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    //TODO
    if (turnDirection == TURN_LEFT) {
        if (this->direction == NORTH) {
            this->direction = WEST;
        } else if (this->direction == WEST) {
            this->direction = SOUTH;
        } else if (this->direction == SOUTH) {
            this->direction = EAST;
        } else if (this->direction == EAST) {
            this->direction = NORTH;
        } else {
            std::cout << "UNKNOWN DIRECTION";
        }
    } else if (turnDirection == TURN_RIGHT) {
        if (this->direction == NORTH) {
            this->direction = EAST;
        } else if (this->direction == EAST) {
            this->direction = SOUTH;
        } else if (this->direction == SOUTH) {
            this->direction = WEST;
        } else if (this->direction == WEST) {
            this->direction = NORTH;
        } else {
            std::cout << "UNKNOWN DIRECTION";
        }
    } else {
        std::cout << "UNKNOWN TURN DIRECTION";
    }
}

Position Player::getNextForwardPosition()
{
    //TODO
    //remember, arr[y][x]
    // Position nextPos;

    if (this->direction == NORTH) {
        this->position.y++;
    } else if (this->direction == EAST) {
        this->position.x++;
    } else if (this->direction == SOUTH) {
        this->position.y--;
    } else if (this->direction == WEST) {
        this->position.x--;
    } else {
        //what
    }

    return this->position;
}

void Player::updatePosition(Position position)
{
    //TODO
}

void Player::displayDirection()
{
    //TODO
    if (this->direction == NORTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
    } else if (this->direction == EAST) {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
    } else if (this->direction == SOUTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    } else if (this->direction == WEST) {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    } else {
        std::cout << "UNKNOWN DIRECTION";
    }
}
