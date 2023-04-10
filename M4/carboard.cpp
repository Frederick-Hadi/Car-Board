#include "game.h"
#include "helper.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

#define BOARD_HEIGHT 10
#define BOARD_LENGTH 10

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
    std::cout << std::endl;
}

int main()
{
    std::string userInput;
    bool quit = false;

    do {
        Helper::showMainMenu();
        std::cout << std::endl << "Please enter your choice: ";
        userInput = Helper::readInput();

        if (userInput == PLAY_COMMAND) {
            Game game = Game();
            game.start();
        } else if (userInput == SHOW_INFO_COMMAND) {
            showStudentInformation(STUDENT_NAME, STUDENT_ID, STUDENT_EMAIL);
        } else if (userInput == QUIT_GAME || std::cin.eof()) {
            quit = true;
        } else {
            Helper::printInvalidInput();
        }
    } while (!quit);

    std::cout << "Good bye!\n\n";
    return EXIT_SUCCESS;
}