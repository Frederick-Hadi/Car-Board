#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{
    //Initialises an empty board
    this->board = new std::vector<std::vector<Cell>>(DEFAULT_BOARD_DIMENSION, std::vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));
}

Board::~Board()
{
    // TODO
    delete this->board;
}

void Board::load(int boardId)
{
    const std::vector<std::vector<Cell>>* chosenTemplate;
    // bool loadSuccess = false;

    // while (loadSuccess == false) {
    //     if (boardId == 0 || boardId == 1) {
    //         chosenTemplate = &BOARD_1;
    //     } else if (boardId == 2) {
    //         chosenTemplate = &BOARD_2;
    //     } else {
    //         Helper::printInvalidInput();
    //         loadSuccess = !loadSuccess;
    //     }
    //     loadSuccess = !loadSuccess;
    // }

    if (boardId == 0 || boardId == 1) {
        chosenTemplate = &BOARD_1;
    } else {
        chosenTemplate = &BOARD_2;
    }

    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; i++) {
        for (int j = 0; j < DEFAULT_BOARD_DIMENSION; j++) {
            (*board)[i][j] = (*chosenTemplate)[i][j];
        }
    }
}

/*
 * also handles range checking of position
*/
bool Board::placePlayer(Position position)
{
    bool success = false;
    if (position.x >= 0 && position.x < DEFAULT_BOARD_DIMENSION && position.y >= 0 && position.y < DEFAULT_BOARD_DIMENSION) {
        if ((*board)[position.x][position.y] == EMPTY) {
            (*board)[position.x][position.y] = PLAYER;
            success = true;
        }
    }

    return success; // feel free to revise this line, depending on your implementation.
}

PlayerMove Board::movePlayerForward(Player* player)
{
    // TODO
    return PLAYER_MOVED;
}

void Board::display(Player* player)
{
    std::cout << std::endl;
    
    //output column headings
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION + 1; i++) {
        std::cout << LINE_OUTPUT;
        if (i > 0) {
            std::cout << i - 1;
        } else {
            std::cout << " ";
        }
    }
    std::cout << LINE_OUTPUT <<std::endl;

    //print out rows
    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; i++) { //num remaining rows
        for (int j = -1; j < DEFAULT_BOARD_DIMENSION; j++) { //num columns
            std::cout << LINE_OUTPUT;
            if (j == -1) {
                // output the row numbers first
                std::cout << i;
            } else {
                // print out contents of board
                Cell currentCell = (*this->board)[i][j];

                if (currentCell == EMPTY) { 
                    std::cout << EMPTY_OUTPUT;
                } else if (currentCell == BLOCKED) {
                    std::cout << BLOCKED_OUTPUT;
                } else {
                    //TODO: add case for Player
                    if (player->direction == NORTH) {
                        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
                    } else if (player->direction == EAST) {
                        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
                    } else if (player->direction == SOUTH) {
                        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
                    } else if (player->direction == WEST) {
                        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
                    } 
                }
            }
        }
        std::cout << LINE_OUTPUT << std::endl;
    }
    std::cout << std::endl;
}



