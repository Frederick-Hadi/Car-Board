#include "helper.h"

using std::string;
using std::vector;

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

void Helper::showMainMenu()
{
    std::cout << "Welcome to Car Board" << std::endl;
    Helper::printSeparator();
    std::cout << "1. Play game" << std::endl;
    std::cout << "2. Show student's information" << std::endl;
    std::cout << "3. Quit" << std::endl;
}

// When the player first chooses 1. Play Game from the main menu
void Helper::showPlayMenu()
{
    std::cout << "You can use the following commands to play the game:" << std::endl;
    std::cout << "load <g>" << std::endl;
    std::cout << "   g: the id of the game board to load" << std::endl;
    std::cout << "init <x>,<y>,<direction>" << std::endl;
    std::cout << "   x: horizontal position of the car on the board (between 0 & 9)" << std::endl;
    std::cout << "   y: vertical position of the car on the board (between 0 & 9)" << std::endl;
    std::cout << "   direction: direction of the car's movement (north, east, south, west)" << std::endl;
    std::cout << "forward (or f)" << std::endl;
    std::cout << "turn_left (or l)" << std::endl;
    std::cout << "turn_right (or r)" << std::endl;
    std::cout << "quit" << std::endl;
}

void Helper::printSeparator()
{
    std::cout << "--------------------" << std::endl;
}