#include "game.h"

//MOVE THIS SOMEWHERE LATER? DOES IT MAKE SENSE TO BE HERE?
#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"

//defining start menu commands
#define PLAY_GAME_COMMAND "1"
#define SHOW_STUDENT_INFO_COMMAND "2"
#define QUIT_GAME_COMMAND "3"

void showStudentInformation(std::string name, std::string id, std::string email){
    Helper::printSeparator();
    std::cout << "Name: " << name << std::endl;
    std::cout << "No: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
    Helper::printSeparator();
}

void showAcceptableCommands(bool boardLoaded) {
    std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
    std::cout << "  load <g>" << std::endl;
    if (boardLoaded) {
        std::cout << "  init <x>, <y>, <direction>" << std::endl;
    }
    std::cout << "  quit" << std::endl << std::endl;
}

Game::Game()
{
    // TODO
    board = nullptr;
    player = nullptr;

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
    bool boardIsLoaded = false;
    
    // read user input
    Helper::showMainMenu();
    std::cout << std::endl << "Please enter your choice: ";
    std::string userInput;
    userInput = Helper::readInput();

    /*
     * While loop handling starting the game
     * and initial board loading
    */
    //TODO: REPLACE "3" AND STUFF WITH #DEFINES
    // quit once user inputs 3
    while (userInput != QUIT_GAME_COMMAND && !std::cin.eof()) {
        // show student info for option 2
        if (userInput == SHOW_STUDENT_INFO_COMMAND) {
            showStudentInformation(STUDENT_NAME, STUDENT_ID, STUDENT_EMAIL);
        }
        else if (userInput == PLAY_GAME_COMMAND) {
            Helper::showPlayMenu();
            board->display(player);
            showAcceptableCommands(boardIsLoaded);

            boardIsLoaded = Game::loadBoard();
        }
        else {
            Helper::printInvalidInput();
        }

        // main start menu asking for input again
        std::cout << std::endl << "Please enter your choice: ";
        userInput = Helper::readInput();
    }

    /*
     * If board is loaded, initialise the player
    */
    if (boardIsLoaded) {
        Game::initializePlayer();
    }


    // finally play game at the end
    play();
}

bool Game::loadBoard()
{
    //TODO
    this->board = new Board();
    bool successfulBoardLoad = false;

    std::string userInput = Helper::readInput();

    // loop until the user either quits or successfully loads a board
    while (userInput != COMMAND_QUIT || successfulBoardLoad == false) {
        std::vector<std::string> command;
        Helper::splitString(userInput, command, " ");

        if (command[0] == COMMAND_LOAD) {
            std::string boardID = command[1];
            //TODO: you can use Helper::isNumber() instead
            if (boardID == "0" || boardID == "1" || boardID == "2" ) {
                board->load(std::stoi(boardID));
                board->display(player);
                successfulBoardLoad = true;
                
            } else {
                Helper::printInvalidInput();
            }
        } else {
            Helper::printInvalidInput();
        }

        std::cout << "At this stage of the program, only two commands are acceptable:" << std::endl;
        std::cout << "  load <g>" << std::endl;
        std::cout << "  quit" << std::endl << std::endl;
        userInput = Helper::readInput();
    }


    return successfulBoardLoad; // feel free to revise this line, depending on your implementation.
    //     ^^^ used to be false, changed to true for now
}

bool Game::initializePlayer()
{
    //TODO
    this->player = new Player();

    std::cout << "At this stage of the program, only three commands are acceptable:" << std::endl;
    std::cout << "  load <g>" << std::endl;
    std::cout << "  init <x>, <y>, <direction>" << std::endl;
    std::cout << "  quit" << std::endl;
    std::string userInput = Helper::readInput();


    return false; // feel free to revise this line.
}

void Game::play()
{
    //TODO

}