#include "game.h"

using std::cout;
using std::endl;
using std::string;

// Additional helpful functions within this file
Direction directionCommandToEnum(std::string command);
bool isValidLoadCommand(std::vector<std::string> command);
bool isValidGenerateCommand(std::vector<std::string> command);
void showOptions(bool showPlayerInitCommand);
void showControls();

/*
 * Show board loading options with option to show init command details
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

bool isValidLoadCommand(std::vector<std::string> command) {
    bool isValid = false;
    if (command.size() > 0) {
        if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1]) && command.size() == 2) {
                int boardID = std::stoi(command[1]);
                if (boardID >= 0 && boardID <= 2) {
                    isValid = true;
                }
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
    // std::string directionList[] = {
    //     DIRECTION_NORTH,
    //     DIRECTION_EAST,
    //     DIRECTION_SOUTH,
    //     DIRECTION_WEST,
    // };

    if (command.size() > 0 && command[0] == COMMAND_INIT) {
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

/**
 * Takes a direction command and converts to corresponding enum
 * Assumes correct input. Any incorrect input will return "WEST"
*/
Direction directionCommandToEnum(std::string command) {
    Direction direction;
    if (command == DIRECTION_NORTH) {
        direction = NORTH;
    } else if (command == DIRECTION_EAST) {
        direction = EAST;
    } else if (command == DIRECTION_SOUTH) {
        direction = SOUTH;
    } else {
        direction = WEST;
    }
    return direction;
}

bool Game::loadBoard()
{
    bool quit = false;
    bool loadSuccess = false;
    
    std::string userInput;
    std::vector<std::string> command;

    do {
        showOptions(false);
        std::cout << "Please enter command (load): ";
        userInput = Helper::readInput();
        Helper::splitString(userInput, command, " ");

        if (isValidLoadCommand(command)) {
            int boardID = std::stoi(command[1]);
            board->load(boardID);
            board->display(player);
            loadSuccess = true;
            quit = true;
        } else if (userInput == COMMAND_QUIT || std::cin.eof()) {
            quit = true;
        } else {
            Helper::printInvalidInput();
        }
    } while (!quit);

    return loadSuccess;
}

bool Game::initializePlayer()
{
    this->player = new Player();
    bool quit = false;

    bool initSuccess = false;

    std::string userInput;
    std::vector<std::string> command;

    do {
        showOptions(true);
        std::cout << "Please enter command (init): ";
        userInput = Helper::readInput();
        Helper::splitString(userInput, command, " ");
        
        if (isValidLoadCommand(command)) {
            int boardID = std::stoi(command[1]);
            board->load(boardID);
            board->display(player);
        } else if (isValidInitCommand(command)) {
            std::vector<std::string> args;
            Helper::splitString(command[1], args, ",");
            int x = std::stoi(args[0]);
            int y = std::stoi(args[1]);

            bool successfulPlacement = board->placePlayer(Position(x, y));

            if (successfulPlacement) {
                Direction direction = directionCommandToEnum(args[2]);
                
                Position* pos = new Position(x, y);
                player->initialisePlayer(pos, direction);

                // Successful init, so exit out of menu and return true
                initSuccess = true;
                quit = true;
            } else {
                std::cout << "Cannot place player here because it is blocked or out of bounds." << std::endl;
            }
        } else if (userInput == COMMAND_QUIT || std::cin.eof()) {
            quit = true;
        } else {
            Helper::printInvalidInput();
        }
    } while (!quit);
    
    return initSuccess;
}

void Game::play()
{
    std::string userInput;
    bool quit = false;

    do {
        board->display(player);
        showControls();
        std::cout << "Enter command (move): ";
        userInput = Helper::readInput();

        if (userInput == COMMAND_FORWARD || userInput == COMMAND_FORWARD_SHORTCUT) {
            PlayerMove moveStatus = board->movePlayerForward(player);
            if (moveStatus == CELL_BLOCKED) {
                std::cout << "Cannot move there because the road is blocked" << std::endl;
            } else if (moveStatus == OUTSIDE_BOUNDS) {
                std::cout << "Cannot move there because it is out of bounds" << std::endl;
            } else {
                player->moves++;
            }
        } else if (userInput == COMMAND_TURN_LEFT || userInput == COMMAND_TURN_LEFT_SHORTCUT) {
            player->turnDirection(TURN_LEFT);
        } else if (userInput == COMMAND_TURN_RIGHT || userInput == COMMAND_TURN_RIGHT_SHORTCUT) {
            player->turnDirection(TURN_RIGHT);
        } else if (userInput == COMMAND_QUIT || std::cin.eof()) {
            quit = true;
        } else {
            Helper::printInvalidInput();
        }
    } while (!quit);

    std::cout << "Total Player Moves: " << player->moves << std::endl << std::endl;
}