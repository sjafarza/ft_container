
#include <iostream>
#include<string>

#include "./containers/vector.hpp"

void    test_vector(void)
{
    std::cout << "In test_vector function ." << std::endl;
}

int main (int ac, char** av)
{
    std::string     str = av[1];
    std::cout << "Start projet containers " << std::endl;

    std::cout << "************************** Test 1**********************************" << std::endl;

    if(str == "vector")
    {
        std::cout << " start test vector" << std::endl;
        test_vector();
    }
}