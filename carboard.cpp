#include "game.h"
#include "helper.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

#define STUDENT_NAME "Frederick_Hadi"
#define STUDENT_ID "s3953344"
#define STUDENT_EMAIL "s3953344@student.rmit.edu.au"

#define BOARD_HEIGHT 10
#define BOARD_LENGTH 10


void showStudentInformation(string name, string id, string email){
    std::cout << "Name: " << name << std::endl;
    std::cout << "No: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
}

int main()
{
    /**
     * TODO: here's the main function. You can write the "main menu" loop/code
     * here or you can make separate functions - up to you.
     */


    Helper::showMainMenu();
    std::cout << std::endl << "Please enter your choice: ";
    
    string userInput;
    userInput = Helper::readInput();

    // quit once user inputs 3
    while (userInput != "3") {
        // show student info for option 2
        if (userInput == "2") {
            Helper::printSeparator();
            showStudentInformation(STUDENT_NAME, STUDENT_ID, STUDENT_EMAIL);
            Helper::printSeparator();
        }
        else if (userInput == "1") {
            Helper::showPlayMenu();
            Player* player = new Player(); // remember to delete later!!!
            Board* board = new Board();

            board->display(player);

        }
        else {
            Helper::printInvalidInput();
        }

        // main start menu asking for input again
        std::cout << std::endl << "Please enter your choice: ";
        userInput = Helper::readInput();
    }

    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}

