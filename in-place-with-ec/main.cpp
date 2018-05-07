#include <iostream>
#include <sstream>
#include <string>

int main()
{
    int number;
    std::string user_input;

    std::cout << "Input a number: ";

    std::getline( std::cin, user_input );

    std::istringstream input_stream( user_input );

    input_stream >> number;

    if( input_stream.fail() )
    {
        std::cerr << "\nOops, [" << user_input << "] is not a number!" << std::endl;

        return -1;
    }

    std::cout << "\nYou typed [" << number << "]" << std::endl;

    return 0;
}
