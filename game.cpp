#include "game.h"

//MOVE THIS SOMEWHERE LATER??? HOW DO YOU STRUCTURE THIS CODE
#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"


using std::cout;
using std::endl;
using std::string;

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
    std::cout << "  quit" << std::endl << std::endl;
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
    if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1]) && command.size() == 2) {
            int boardID = std::stoi(command[1]);
            if (boardID >= 0 && boardID <= 2) {
                isValid = true;
            }
    }
    return isValid;
}

/* 
 * does not do range input validation on coordinates
 * but does check valid direction
*/
bool isValidInitCommand(std::vector<std::string> command) {
    bool isValid = false;

    if (command[0] == COMMAND_INIT) {
        std::vector<std::string> args;
        Helper::splitString(command[1], args, ",");
        if (Helper::isNumber(args[0]) && Helper::isNumber(args[1]) && args.size() == 3) {
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

    while (command[0] != COMMAND_QUIT && loadSuccess == false && !std::cin.eof()) {
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
    this->player = new Player();

    bool initSuccess = false;
    bool loadSuccess = false;

    showOptions(true);
    std::cout << "Please enter command: ";
    std::string userInput = Helper::readInput();
    std::vector<std::string> command;
    Helper::splitString(userInput, command, " ");

    while (command[0] != COMMAND_QUIT && initSuccess == false && !std::cin.eof()) {
        loadSuccess = false;
        
        if (isValidLoadCommand(command)) {
            int boardID = std::stoi(command[1]);
            board->load(boardID);
            board->display(player);
            loadSuccess = true;
        } else if (isValidInitCommand(command)) {
            std::vector<std::string> args;
            Helper::splitString(command[1], args, ",");

            bool successfulPlacement = board->placePlayer(Position(std::stoi(args[0]), std::stoi(args[1])));

            if (successfulPlacement) {
                Direction direction;
                if (args[2] == DIRECTION_NORTH) {
                    direction = NORTH;
                } else if (args[2] == DIRECTION_EAST) {
                    direction = EAST;
                } else if (args[2] == DIRECTION_SOUTH) {
                    direction = SOUTH;
                } else {
                    direction = WEST;
                }

                Position* pos = new Position(std::stoi(args[0]), std::stoi(args[1]));
                player->initialisePlayer(pos, direction);
                board->display(player);

                initSuccess = true;
            } else {
                std::cout << "Cannot place player here because it is blocked or out of bounds." << std::endl;
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
    board->display(player);
    showControls();
    std::cout << "Enter command: ";
    std::string userInput = Helper::readInput();

    while (userInput != COMMAND_QUIT && !std::cin.eof()) {
        
        

        if (userInput == COMMAND_FORWARD || userInput == COMMAND_FORWARD_SHORTCUT) {
            cout << "move forward" << endl;



        } else if (userInput == COMMAND_TURN_LEFT || userInput == COMMAND_TURN_LEFT_SHORTCUT) {
            
            player->turnDirection(TURN_LEFT);

        } else if (userInput == COMMAND_TURN_RIGHT || userInput == COMMAND_TURN_RIGHT_SHORTCUT) {
            cout << "turn right" << endl;

            player->turnDirection(TURN_RIGHT);
        } else {
            Helper::printInvalidInput();
        }



        board->display(player);
        showControls();
        std::cout << "Enter command: ";
        userInput = Helper::readInput();
    }
    
}