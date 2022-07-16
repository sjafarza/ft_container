#include <iostream>
# include <sstream>
# include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "./containers/vector.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define RED    "\033[1;31m"
# define GREEN  "\033[032m"

template <class T>
std::string vector_is_equal(const std::vector<T> & std_vector, const ft::vector<T> & ft_vector)
{
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
    if(std_vector.capacity() != ft_vector.capacity())
        return (RED"✘ /t/t Capacity");
    if(std_vector.size() != ft_vector.size())
        return (RED"✘ /t/t Size");
    if(std_vector.max_size() != ft_vector.max_size())
        return (RED"✘ /t/t Size");    
    if(std_vector.size() == 0 && ft_vector.size() == 0)  
        return (GREEN"✔");  

    while(*st_it == *ft_it && st_it != std_vector.end() && ft_it != ft_vector.end()) 
    {
        st_it++; ft_it++;
    }
    if(st_it == std_vector.end() && ft_it == ft_vector.end())
        return (GREEN"✔");
    return (RED"✘ /t/t Content");  
}

template <class T>
std::string print_vector(const std::vector<T> & std_vector)
{
    std::ostringstream  ss;
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    ss << " { ";
    while(st_it != std_vector.end())
    {
        ss << *st_it ;
        if(st_it + 1 != std_vector.end())
        ss << " , " ;
        st_it++;
    }
    ss << " } ";

    return (ss.str());
}

template <class T>
std::string print_vector(const ft::vector<T> & ft_vector)
{
    std::ostringstream  ss;
     typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
     ss << " { ";
    while(ft_it != ft_vector.end())
    {
        ss << *ft_it ;
        if(ft_it + 1 != ft_vector.end())
        ss << " , " ;
        ft_it++;
    }
    ss << " } ";

    return (ss.str());
}

template <class T>
std::string printVectorAttributes(std::vector<T>& std_vector,ft::vector<T>& ft_vector , std::string titre)
{
    std::ostringstream fs;
    fs  << YELLOW << titre << "**********************************************************************" NORMAL << std::endl 
        << "***" YELLOW"std::vector" NORMAL"*******************************************************" << std::endl
        <<"Content = " << print_vector(std_vector) << std::endl
        << "Size = " << std_vector.size() << "\t" << "Capacity = " << std_vector.capacity() << "\t" << "Max_size = " << std_vector.max_size()
        << std::endl << std::endl
        <<  "***" YELLOW"ft::vector" NORMAL"*******************************************************\n"
        <<"Content = " << print_vector(ft_vector) << std::endl
        << "Size = " << ft_vector.size() << "\t" << "Capacity = " << ft_vector.capacity() << "\t" << "Max_size = " << ft_vector.max_size()
        << std::endl << std::endl
        << "*******************************************************************\n\n";
    return (fs.str());    

}

void    print_vector();
void    test_constructor()
{
    std::ofstream        out;
    std::string const   file = "log_test_vector";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
    {
        std::cerr << "Error : faild to open file" << std::endl;
    }
    /* Detault constructor */
    std::vector<int>     std_v1;
    ft::vector<int>      ft_v1;
    out << printVectorAttributes(std_v1,ft_v1, "Test default constructor");

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << " test default constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;

    /* Detault pointer constructor */
    std::vector<int>*    std_pointer_default_v =  new std::vector<int>;
    ft::vector<int>*    ft_pointer_default_v =  new ft::vector<int>;
    out << printVectorAttributes( *std_pointer_default_v,*ft_pointer_default_v, "Test default pointer constructor");
    std::cout << NORMAL " test default pointer constructor \t\t\t\t\t\t\t"<< vector_is_equal(*std_pointer_default_v, *ft_pointer_default_v) << std::endl;

    /* Fill constructor */
    std::vector<int>    std_v2(5);
    ft::vector<int>     ft_v2(5);
    out << printVectorAttributes(std_v2,ft_v2, "Test fill constructor");

    /*Fill constructor size*/
    std::vector<int>    std_v3(5, 100);
    ft::vector<int>     ft_v3(5, 100);
    out << printVectorAttributes(std_v3,ft_v3, "Test fill constructor size");
    std::cout << NORMAL " test fill constructor  size\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v3 , ft_v3) << std::endl;

    /*Range constructor */
    std::vector<int>    s_test(5, 7);
    ft::vector<int>     ft_test(5, 7);
    std::vector<int>    std_v4(s_test.begin() + 1, s_test.end() - 2);
    ft::vector<int>     ft_v4(ft_test.begin() + 1, ft_test.end() - 2);
    out << printVectorAttributes(std_v4,ft_v4, "Test range of another vector constructor");
    std::cout << NORMAL " test range of another vector constructor \t\t\t\t\t\t"<< vector_is_equal(std_v4 , ft_v4) << std::endl;
    
    int range_array[] = { 15, 65397429, 1299, 965, 5 , 88, 9};
    std::vector<int>::iterator std_itr(&(range_array[1]));
    ft::vector<int>::iterator ft_itr(&(range_array[1]));

    std::vector<int>    std_arr_v4(std_itr , std_itr + 3);
    ft::vector<int>     ft_arr_v4(ft_itr , ft_itr + 3);
    out << printVectorAttributes(std_arr_v4,ft_arr_v4, "Test range of array constructor");
    std::cout << NORMAL " test range of array constructor \t\t\t\t\t\t\t"<< vector_is_equal(std_arr_v4 , ft_arr_v4) << std::endl;

    /*Copy constructor */
    std::vector<int>    std_v5(s_test);
    ft::vector<int>     ft_v5(ft_test);
     out << printVectorAttributes(std_v5,ft_v5, "Test copy constructor");
    std::cout << NORMAL " test copy  constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v5 , ft_v5) << std::endl;

    delete  ft_pointer_default_v;
    delete  std_pointer_default_v;
    out.close();
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
