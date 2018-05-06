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

    std::cout << "\n"
                 "You typed ["
              << number << "]" << std::endl;

    return 0;
}
