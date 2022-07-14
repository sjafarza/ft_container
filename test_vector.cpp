#include <iostream>
#include<string>
#include<vector>
#include<iterator>

#include "./containers/vector.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define RED "\033[1;31m"
# define GREEN "\033[032m"

template <class T>
std::string vector_is_equal(const std::vector<T> & std_vector, const ft::vector<T> & ft_vector)
{
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();

    if(std_vector.size() != ft_vector.size())
        return (RED"✘");
    if(std_vector.size() == 0 && ft_vector.size() == 0)  
        return (GREEN"✔");  

    while(*st_it == *ft_it && st_it != std_vector.end() && ft_it != ft_vector.end()) 
    {
        st_it++; ft_it++;
    }
    if(st_it == std_vector.end() && ft_it == ft_vector.end())
        return (GREEN"✔");
    return (RED"✘");  
}

template <class T>
void print_vector(const std::vector<T> & std_vector)
{
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    std::cout << " { ";
    while(st_it != std_vector.end())
    {
        std::cout << *st_it ;
        if(st_it + 1 != std_vector.end())
        std::cout << " , " ;
        st_it++;
    }
    std::cout << " } ";
}

template <class T>
void print_vector(const ft::vector<T> & ft_vector)
{
     typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
     std::cout << " { ";
    while(ft_it != ft_vector.end())
    {
        std::cout << *ft_it ;
        if(ft_it + 1 != ft_vector.end())
        std::cout << " , " ;
        ft_it++;
    }
    std::cout << " } ";
}

template <class T>
void    print_vector();
void    test_constructor()
{
    std::cout << "*****************************Test constructor***********************************************." << std::endl;

    std::vector<int>     std_v1; // ft::vector
    ft::vector<int>      ft_v1;
    std::cout << " test default constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;

    std::vector<int>    std_v2(5, 100);
    ft::vector<int>     ft_v2(5, 100);
    std::cout << NORMAL " test fill   constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;

    std::vector<int>    std_v3(std_v2.begin(), std_v2.end());
    ft::vector<int>     ft_v3(ft_v2.begin(), ft_v2.end());
    std::cout << NORMAL " test range  constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v3 , ft_v3) << std::endl;

    std::vector<int>    std_v4(std_v2);
    ft::vector<int>     ft_v4(ft_v2);
    std::cout << NORMAL " test copy  constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v4 , ft_v4) << std::endl;



}

void    test_vector(void)
{
    
    test_constructor();
    /*test_operator_assign();
	test_begin_end();
	test_rbegin_rend();
	test_size();
	test_max_size();
	test_capacity();
	test_operator_at();
	test_at();
	test_front_back();
	test_assign();
	test_push_back();
	test_pop_back();
	test_insert();
	test_erase();
	test_swap();
	test_clear();
	test_get_allocator();
	test_relational_operators();
	test_swap_nonmember();*/

}
