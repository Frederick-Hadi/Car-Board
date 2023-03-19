#include "game.h"

//MOVE THIS SOMEWHERE LATER??? HOW DO YOU STRUCTURE THIS CODE
#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"

#define PLAY_COMMAND "1"
#define SHOW_INFO_COMMAND "2"
#define QUIT_GAME "3"

void showStudentInformation(std::string name, std::string id, std::string email){
    Helper::printSeparator();
    std::cout << "Name: " << name << std::endl;
    std::cout << "No: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
    Helper::printSeparator();
}

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
    //TODO
    
    Helper::showMainMenu();
    std::cout << std::endl << "Please enter your choice: ";
    
    // read user input
    std::string userInput;
    userInput = Helper::readInput();

    //TODO: REPLACE "3" AND STUFF WITH #DEFINES
    // quit once user inputs 3
    while (userInput != QUIT_GAME && !std::cin.eof()) {
        if (userInput == SHOW_INFO_COMMAND) {
            showStudentInformation(STUDENT_NAME, STUDENT_ID, STUDENT_EMAIL);
        }
        else if (userInput == PLAY_COMMAND) {
            board = new Board();
            Helper::showPlayMenu();
            board->display(player);
            
            bool boardLoaded = false;
            while (userInput != COMMAND_QUIT) {
                showOptions(boardLoaded);
                boardLoaded = Game::loadBoard();

                if (boardLoaded) {
                    showOptions(boardLoaded);
                    std::cout << std::endl << "Please enter command: ";
                    userInput = Helper::readInput();
                    std::vector<std::string> command;
                    Helper::splitString(userInput, command, " ");
                    

                } else {
                    Helper::printInvalidInput();
                }
                
                
                std::cout << std::endl << "Please enter command: ";
                userInput = Helper::readInput();
            }
        }
        else {
            Helper::printInvalidInput();
        }

        // main start menu asking for input again
        std::cout << std::endl << "Please enter your choice: ";
        userInput = Helper::readInput();
    }
    play();
}

bool Game::loadBoard()
{
    bool loadSuccess = false;
    
    
    std::string userInput = Helper::readInput();

    std::vector<std::string> command;
    Helper::splitString(userInput, command, " ");

    if (command[0] == COMMAND_LOAD && Helper::isNumber(command[1])) {
        int boardID = std::stoi(command[1]);
        if (boardID >= 0 && boardID <= 2) {
            board->load(boardID);
            board->display(player);
            loadSuccess = true;
        }
    }

    return loadSuccess;

    // //TODO
    // this->board = new Board();
    // bool successfulBoardLoad = false;

    // Helper::showPlayMenu();

    // board->display(player);

    // std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
    // std::cout << "  load <g>" << std::endl;
    // std::cout << "  quit" << std::endl;

    // std::string userInput = Helper::readInput();

    // // loop until the user either quits or successfully loads a board
    // while (userInput != COMMAND_QUIT || successfulBoardLoad == false) {
    //     std::vector<std::string> command;
    //     Helper::splitString(userInput, command, " ");

    //     if (command[0] == COMMAND_LOAD) {
    //         std::string boardID = command[1];
    //         //TODO: you can use Helper::isNumber() instead
    //         if (boardID == "0" || boardID == "1" || boardID == "2" ) {
    //             board->load(std::stoi(boardID));
    //             board->display(player);
    //             successfulBoardLoad = true;
                
    //         } else {
    //             Helper::printInvalidInput();
    //         }
    //     } else {
    //         Helper::printInvalidInput();
    //     }

    //     std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
    //     std::cout << "  load <g>" << std::endl;
    //     std::cout << "  quit" << std::endl;
    //     userInput = Helper::readInput();
    // }


    // return successfulBoardLoad; // feel free to revise this line, depending on your implementation.
    // //     ^^^ used to be false, changed to true for now
}

bool Game::initializePlayer()
{
    //TODO
    this->player = new Player();

    return false; // feel free to revise this line.
}

void Game::play()
{
    //TODO

}