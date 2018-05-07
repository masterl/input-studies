#include <iostream>
#include <sstream>
#include <string>

bool read_line( std::string &line );
bool read_integer( int &value );

int main()
{
    int number;
    std::string user_input;

    std::cout << "Input a number: ";

    if( !read_integer( number ) )
    {
        std::cerr << "Oops, looks like you didn't type a number" << std::endl;

        return -1;
    }

    std::cout << "\nYou typed [" << number << "]" << std::endl;

    return 0;
}

bool read_line( std::string &line )
{
    std::getline( std::cin, line );

    return !std::cin.fail();
}

bool read_integer( int &value )
{
    std::string line;

    if( !read_line( line ) )
    {
        return false;
    }

    std::istringstream stream( line );

    stream >> value;

    return !stream.fail();
}
