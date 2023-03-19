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






int main()
{
    /**
     * TODO: here's the main function. You can write the "main menu" loop/code
     * here or you can make separate functions - up to you.
     */
    Game* game = new Game();
    game->start();


    std::cout << "Good bye!\n\n";
    delete game;
    return EXIT_SUCCESS;
}

