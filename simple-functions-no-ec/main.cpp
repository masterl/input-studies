#include <iostream>
#include <sstream>
#include <string>

std::string read_line();
int read_integer();

int main()
{
    int number;
    std::string user_input;

    std::cout << "Input a number: ";

    number = read_integer();

    std::cout << "\nYou typed [" << number << "]" << std::endl;

    return 0;
}

std::string read_line()
{
    std::string line;

    std::getline( std::cin, line );

    return line;
}

int read_integer()
{
    int value;

    std::string line = read_line();

    std::istringstream stream( line );

    stream >> value;

    return value;
}
