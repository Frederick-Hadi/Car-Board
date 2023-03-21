#include "game.h"

//MOVE THIS SOMEWHERE LATER??? HOW DO YOU STRUCTURE THIS CODE
#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"




/*
 * Show board loading options
 * @param showPlayerInitCommand: tis a bool my friend
*/
void showOptions(bool showPlayerInitCommand) {
    std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
    std::cout << "  load <g>" << std::endl;
    if (showPlayerInitCommand) {
        std::cout << "  init <x>,<y>,<direction>" << std::endl;
    }
    std::cout << "  quit" << std::endl;
}

void showControls() {
    std::cout << "At this stage of the program, only four commands are acceptable:" << std::endl;
    std::cout << "  forward" << std::endl;
    std::cout << "  turn_left (or l)" << std::endl;
    std::cout << "  turn _right (or r)" << std::endl;
    std::cout << "  quit" << std::endl << std::endl;
}

Game::Game()
{
    board = nullptr;
    player = nullptr;
}

Game::~Game()
{
    delete board;
    delete player;
}


void Game::start()
{
    //bool boardLoaded = false;

    board = new Board();
    board->display(player);
    
    bool loadSuccess = true;

    while (loadSuccess) {
        loadSuccess = loadBoard();
        if (loadSuccess) {
            loadSuccess = initializePlayer();
            if (loadSuccess) {
                play();
                // after you finish playing, you must have exited
                loadSuccess = false;
            }   
        }
    }
}

// bool handleLoadBoardCommand(std::vector<std::string> command) {
//      uuuuh
// }

bool isValidLoadCommand(std::vector<std::string> command) {
    bool isValid = false;
    if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1])) {
            int boardID = std::stoi(command[1]);
            if (boardID >= 0 && boardID <= 2) {
                isValid = true;
            }
    }
    return isValid;
}

bool isValidInitCommand(std::vector<std::string> command) {
    bool isValid = false;

    if (command[0] == COMMAND_INIT) {
        std::vector<std::string> args;
        Helper::splitString(command[1], args, ",");
        // std::cout << args[0] << std::endl;
        // std::cout << args[1] << std::endl;
        // std::cout << args[2] << std::endl;
        if (Helper::isNumber(args[0]) && Helper::isNumber(args[1])) {
            if (args[2] == DIRECTION_NORTH || args[2] == DIRECTION_EAST || args[2] == DIRECTION_SOUTH || args[2] == DIRECTION_WEST) {
                isValid = true;
            }
        }
    }
    return isValid;
}

bool Game::loadBoard()
{
    bool loadSuccess = false;
    
    showOptions(loadSuccess);
    std::cout << "Please enter command: ";
    std::string userInput = Helper::readInput();
    std::vector<std::string> command;
    Helper::splitString(userInput, command, " ");

    while (command[0] != COMMAND_QUIT && loadSuccess == false) {
        // replace with dedicated input validation function later
        if (isValidLoadCommand(command)) {
            int boardID = std::stoi(command[1]);
            board->load(boardID);
            board->display(player);
            loadSuccess = true;
        }

        if (!loadSuccess) {
            Helper::printInvalidInput();
            std::cout << "Please enter command: ";
            userInput = Helper::readInput();
            Helper::splitString(userInput, command, " ");
        }
    }

    return loadSuccess;
}

bool Game::initializePlayer()
{
    //TODO
    this->player = new Player();

    
    bool initSuccess = false;
    bool loadSuccess = false;

    showOptions(true);
    std::cout << "Please enter command: ";
    std::string userInput = Helper::readInput();
    std::vector<std::string> command;
    Helper::splitString(userInput, command, " ");

    while (command[0] != COMMAND_QUIT && initSuccess == false) {
        loadSuccess = false;
        
        if (isValidLoadCommand(command)) {
            int boardID = std::stoi(command[1]);
            board->load(boardID);
            board->display(player);
            loadSuccess = true;
        } else if (isValidInitCommand(command)) {
            std::vector<std::string> args;
            Helper::splitString(command[1], args, ",");
            Position pos = Position(std::stoi(args[0]), std::stoi(args[1]));
            player->position = pos;

            bool successfulPlacement = board->placePlayer(pos);

            if (successfulPlacement) {
                if (args[2] == DIRECTION_NORTH) {
                    player->direction = NORTH;
                } else if (args[2] == DIRECTION_EAST) {
                    player->direction = EAST;
                } else if (args[2] == DIRECTION_SOUTH) {
                    player->direction = SOUTH;
                } else if (args[2] == DIRECTION_WEST) {
                    player->direction = WEST;
                } else {
                    std::cout << "THIS SHOULD NEVER HAPPEN";
                }

                board->display(player);

                initSuccess = true;
            } else {
                std::cout << "Cannot place player here because it is blocked." << std::endl;
            }
        }

        if (initSuccess == false) {
            if (loadSuccess == false) {
                Helper::printInvalidInput();
            }
            showOptions(true);
            std::cout << "Please enter command: ";
            userInput = Helper::readInput();
            Helper::splitString(userInput, command, " ");
        }
    }
    

    return initSuccess; // feel free to revise this line.
}

void Game::play()
{
    //TODO
    showControls();
    std::cout << "enter command: ";
    std::string userInput = Helper::readInput();

    while (userInput != COMMAND_QUIT) {
        std::cout << "cool beans" << std::endl;
        board->display(player);


        showControls();
        std::cout << "enter command: ";
        userInput = Helper::readInput();
    }
    
}