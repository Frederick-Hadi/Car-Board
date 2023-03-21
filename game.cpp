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
        std::cout << "  init <x> <y> <direction>" << std::endl;
    }
    std::cout << "  quit" << std::endl;
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

    
    // while (userInput != COMMAND_QUIT) {
    //     Game::loadBoard();
        
        
    //     //replace later with input validation function
    //     if (boardLoaded && command[0] == "init") {
    //         // fill in
    //         Game::initializePlayer();
    //     } else if (command[0] == "load") {

    //     }
        
    //     else {
    //         Helper::printInvalidInput();
    //     }
        
        
    //     std::cout << std::endl << "Please enter command: ";
    //     userInput = Helper::readInput();
    //     Helper::splitString(userInput, command, " ");
    // }
            
    // play();
}

// bool handleLoadBoardCommand(std::vector<std::string> command) {
//      uuuuh
// }

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
        if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1])) {
            int boardID = std::stoi(command[1]);
            if (boardID >= 0 && boardID <= 2) {
                board->load(boardID);
                board->display(player);
                loadSuccess = true;
            }
        }

        if (!loadSuccess) {
            Helper::printInvalidInput();
            std::cout << "Please enter command: ";
            std::string userInput = Helper::readInput();
            std::vector<std::string> command;
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
        
        // replace with dedicated input validation function later
        if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1])) {
            int boardID = std::stoi(command[1]);
            if (boardID >= 0 && boardID <= 2) {
                board->load(boardID);
                board->display(player);
                loadSuccess = true;
            } else {
                Helper::printInvalidInput();
            }
        } else if (command[0] == COMMAND_INIT) {
            //assuming it is a valid command and valid coordinate
            Position pos = Position(std::stoi(command[1]), std::stoi(command[2]));
            player->position = pos;

            bool successfulPlacement = board->placePlayer(pos);

            if (successfulPlacement) {
                if (command[3] == DIRECTION_NORTH) {
                    player->direction = NORTH;
                } else if (command[3] == DIRECTION_EAST) {
                    player->direction = EAST;
                } else if (command[3] == DIRECTION_SOUTH) {
                    player->direction = SOUTH;
                } else if (command[3] == DIRECTION_WEST) {
                    player->direction = WEST;
                }

                board->display(player);

                initSuccess = true;
            } else {
                std::cout << "cannot place player here" << std::endl;
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
    
}