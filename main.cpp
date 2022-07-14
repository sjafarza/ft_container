
#include <iostream>
#include<string>

#include "./containers/vector.hpp"

void test_vector(void);

int main (int ac, char** av)
{
    if (ac != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		
		return 1;
	}
    std::string     str = av[1];
    std::cout << "Start projet containers " << std::endl;

    std::cout << "************************** Test 1**********************************" << std::endl;

    if(str == "vector")
    {
        std::cout << " start test vector" << std::endl;
        test_vector();
    }

    return 0;
}