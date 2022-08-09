
#include <iostream>
#include<string>

#include "./containers/vector.hpp"
#include "./containers/stack.hpp"



void test_vector(void);
void test_stack(void);
void test_map(void);


int main (int ac, char** av)
{
    if (ac != 2)
	{
		std::cerr << "Usage: ./test vector / stack / map" << std::endl;
		std::cerr << "Provide name of test please" << std::endl;
		
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

	/*if(str == "stack")
    {
        std::cout << " start test stack" << std::endl;
        test_stack();
    }*/

	if(str == "map")
    {
        std::cout << " start test map" << std::endl;
        test_map();
    }

    return 0;
}


/*int std_psize;
    std::map<char,int> std_mymap;
    std::pair<const char,int>* p;

    int ft_psize;
    ft::map<char,int> ft_mymap;
    ft::pair<const char,int>* ft_p;

    // allocate an array of 5 elements using mymap's allocator:
    std_p=std_mymap.get_allocator().allocate(5);
    ft_p=ft_mymap.get_allocator().allocate(5);

    // assign some values to array
    std_psize = sizeof(std::map<char,int>::value_type)*5;
    ft_psize = sizeof(ft::map<char,int>::value_type)*5;

    std::cout << "The allocated array has a size of " << std_psize << " bytes.\n";

    std::cout << "The allocated array has a size of " << ft_psize << " bytes.\n";

    std_mymap.get_allocator().deallocate(p,5);
    //ft_mymap.get_allocator().deallocate(ft_p,5);

*/

/*********** main 42 **********************/
/*
#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE     1 for stl   0 for ft
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map>
	#include <containers/stack.hpp>
	#include <containers/vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
*/