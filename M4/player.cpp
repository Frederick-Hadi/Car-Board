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
    this->position = Position();
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
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
    //remember, arr[y][x]
    Position nextPos = Position(this->position.x, this->position.y);

    if (this->direction == NORTH) {
        nextPos.y--;
    } else if (this->direction == EAST) {
        nextPos.x++;
    } else if (this->direction == SOUTH) {
        nextPos.y++;
    } else if (this->direction == WEST) {
        nextPos.x--;
    } else {
        //what
        abort();
    }

    return nextPos;
}

void Player::updatePosition(Position position)
{
    this->position.x = position.x;
    this->position.y = position.y;
}


void Player::displayDirection()
{
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
