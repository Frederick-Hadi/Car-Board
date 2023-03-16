#include "game.h"
#include "helper.h"

using std::string;
using std::cin;
using std::cout;

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

    std::cout << "Welcome to Car Board" << std::endl;
    
    Helper::showMenu();
    
    string userInput;
    userInput = Helper::readInput();

    while (userInput != "3") {




        userInput = Helper::readInput();
    }

    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}

