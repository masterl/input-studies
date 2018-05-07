#include <iostream>
#include <sstream>
#include <string>

std::string read_line();

template < typename T >
void read_input( T &value );

int main()
{
    int integer;
    double floating;
    std::string user_input;

    std::cout << "Input an integer number (e.g. 2): ";

    read_input( integer );

    std::cout << "\nYou typed [" << integer << "]" << std::endl;

    std::cout << "Input a real number (e.g. 5.4): ";

    read_input( floating );

    std::cout << "\nYou typed [" << floating << "]" << std::endl;

    return 0;
}

std::string read_line()
{
    std::string line;

    std::getline( std::cin, line );

    return line;
}

template < typename T >
void read_input( T &value )
{
    std::string line = read_line();

    std::istringstream stream( line );

    stream >> value;
}
