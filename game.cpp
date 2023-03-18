#include "game.h"

//MOVE THIS SOMEWHERE LATER??? HOW DO YOU STRUCTURE THIS CODE
#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"

void showStudentInformation(std::string name, std::string id, std::string email){
    Helper::printSeparator();
    std::cout << "Name: " << name << std::endl;
    std::cout << "No: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
    Helper::printSeparator();
}

Game::Game()
{
    // TODO

}

Game::~Game()
{
    // TODO
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

    // quit once user inputs 3
    while (userInput != "3" && !std::cin.eof()) {
        // show student info for option 2
        if (userInput == "2") {
            showStudentInformation(STUDENT_NAME, STUDENT_ID, STUDENT_EMAIL);
        }
        else if (userInput == "1") {
            Helper::showPlayMenu();
            Game::loadBoard();
            Game::initializePlayer();

            board->display(player);

            std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
            std::cout << "  load <g>" << std::endl;
            std::cout << "  quit" << std::endl;

            userInput = Helper::readInput();

            while (userInput != COMMAND_QUIT) {
                std::vector<std::string> command;
                Helper::splitString(userInput, command, " ");

                if (command[0] == COMMAND_LOAD) {
                    std::string boardID = command[1];
                    if (boardID == "0" || boardID == "1" || boardID == "2" ) {
                        board->load(std::stoi(boardID));
                        board->display(player);

                        
                    } else {
                        Helper::printInvalidInput();
                    }
                } else {
                    Helper::printInvalidInput();
                }

                std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
                std::cout << "  load <g>" << std::endl;
                std::cout << "  quit" << std::endl;
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
    //TODO
    this->board = new Board();


    return true; // feel free to revise this line, depending on your implementation.
    //     ^^^ used to be false, changed to true for now
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