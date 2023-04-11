#include "board.h"
#include "random"

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
    this->board = new std::vector<std::vector<Cell>>(
        DEFAULT_BOARD_DIMENSION,
        std::vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY)
        );
    this->dimension = DEFAULT_BOARD_DIMENSION;
}

Board::~Board()
{
    delete this->board;
}

void Board::load(int boardId)
{
    const std::vector<std::vector<Cell>>* chosenTemplate;

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

void Board::generateBoard(int d, float p) {
    //Initialises an empty board with specified dimension
    delete this->board;
    this->board = new std::vector<std::vector<Cell>>(
        d, std::vector<Cell>(d, EMPTY)
        );
    this->dimension = d;
    
    /** Create an array of coordinates to randomly choose from
      * Already selected coordinates are swapped to be at the end
      * and end index updated so they cannot be selected again
      */
    Position coords[d*d];
    int i = 0;
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            coords[i] = Position(x,y);
            i++;
        }
    }

    // the amount of blocked cells to achieve
    int blockedCellsAmount = std::floor((d * d) * p);
    int blocksGenerated = 0;

    // keep selecting random coordinates from the array
    std::random_device engine;

    while (blocksGenerated < blockedCellsAmount) {
        // Update max range of random coordinate index to exclude chosen points
        std::uniform_int_distribution<int> uniform_dist(0, d*d - 1 - blocksGenerated);

        // Select a random coordinate from the array
        int randCoord = uniform_dist(engine);
        int _x = (coords[randCoord]).x;
        int _y = (coords[randCoord]).y;
        
        (*board)[_y][_x] = BLOCKED;
        
        // Swap coordinate to the end to be ignored and avoid duplicates
        Position temp = coords[randCoord];
        coords[randCoord] = coords[(d*d - 1) - blocksGenerated];
        coords[(d*d - 1) - blocksGenerated] = temp;

        blocksGenerated++;
    }
}

/*
 * also handles range checking of position
*/
bool Board::placePlayer(Position position)
{
    bool success = false;
    if (position.x >= 0 && position.x < this->dimension 
        && position.y >= 0 && position.y < this->dimension) {
        if ((*board)[position.y][position.x] == EMPTY) {
            (*board)[position.y][position.x] = PLAYER;
            success = true;
        }
    }

    return success;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    PlayerMove moveStatus = PLAYER_MOVED;
    Position nextPos = player->getNextForwardPosition();
    
    if (nextPos.x > this->dimension - 1 || nextPos.y > this->dimension - 1
        || nextPos.x < 0 || nextPos.y < 0) {
        moveStatus = OUTSIDE_BOUNDS;
    } else if ((*board)[nextPos.y][nextPos.x] == BLOCKED) {
        moveStatus = CELL_BLOCKED;
    } else {
        (*board)[player->position.y][player->position.x] = EMPTY;
        player->updatePosition(nextPos);
        (*board)[player->position.y][player->position.x] = PLAYER;
    }

    return moveStatus;
}

void Board::display(Player* player)
{
    std::cout << std::endl;
    
    //output column headings
    for (int i = 0; i < this->dimension + 1; i++) {
        std::cout << LINE_OUTPUT;
        if (i > 0) {
            std::cout << std::to_string(i - 1).back();
        } else {
            std::cout << " ";
        }
    }
    std::cout << LINE_OUTPUT <<std::endl;

    //print out rows
    for (int i = 0; i < this->dimension; i++) { 
        for (int j = -1; j < this->dimension; j++) { 
            std::cout << LINE_OUTPUT;
            if (j == -1) {
                // output the row numbers first
                std::cout << std::to_string(i).back();
            } else {
                // print out contents of board
                Cell currentCell = (*this->board)[i][j];

                if (currentCell == EMPTY) { 
                    std::cout << EMPTY_OUTPUT;
                } else if (currentCell == BLOCKED) {
                    std::cout << BLOCKED_OUTPUT;
                } else {
                    // display player
                    player->displayDirection();
                }
            }
        }
        std::cout << LINE_OUTPUT << std::endl;
    }
    std::cout << std::endl;
}



