#include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <vector>
# include <stack>
# include <iterator>
# include <sys/stat.h>

#include "./containers/vector.hpp"
#include "./containers/stack.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define RED    "\033[1;31m"
# define GREEN  "\033[032m"

/* calcule time ******************************************************************/
struct timespec std_start;
struct timespec ft_start;

double   std_time_calculator(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - std_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - std_start.tv_nsec)) * 1e-9;
	clock_gettime(CLOCK_MONOTONIC, &std_start);
    return(time_taken);
}

double    ft_time_calculator(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - ft_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - ft_start.tv_nsec)) * 1e-9;
	clock_gettime(CLOCK_MONOTONIC, &ft_start);
    return(time_taken);
}

std::string    time_is_ok ( long double ft_t, long double std_t)
{
    if(ft_t < (std_t * 20))
        return("ok");
    else
        return("ko");    
}


/* Generic functions for comparison ******************************************************************/
template <class T, class Container = ft::vector<T> >
std::string stack_is_equal(const std::stack<T, Container> & std_stack, const ft::stack<T, Container> & ft_stack)
{
    while (1)
    {
        if (std_stack.size() == 0 || ft_stack.size() == 0)
            break;
        if (ft_stack.top() != std_stack.top())
            return (RED"✘");
        ft_stack.pop();
        std_stack.pop();
    }
    return (GREEN"✔");
}
    
template <class T, class Container = ft::vector<T> >
std::string print_stack(const std::stack<T, Container> & std_stack)
{
    std::ostringstream  ss;
    if(std_stack.size() == 0)
        ss << "{ }";
    else    
        while (1)
        {
            if (std_stack.size() == 0)
                break;
            ss << std_stack.top();
            std_stack.pop();
            if (std_stack.size() != 0)
                ss << ", ";   
        }
       ss << " } ";   
    return (ss.str());
}

template <class T, class Container = ft::vector<T> >
std::string print_stack(const ft::stack<T, Container>& ft_stack)
{
    std::ostringstream  ss;
    if(ft_stack.size() == 0)
        ss << "{ }";
    else    
        while (1)
        {
            if (ft_stack.size() == 0)
                break;
            ss << ft_stack.top();
            ft_stack.pop();
            if (ft_stack.size() != 0)
                ss << ", ";   
        }
       ss << " } ";   
    return (ss.str());
}

template <class T, class Container = ft::vector<T> >
std::string printStackAttributes(std::stack<T, Container>& std_stack,ft::stack<T, Container>& ft_stack , std::string titre)
{
    std::ostringstream fs;
    fs  << YELLOW << titre << "**********************************************************************" NORMAL << std::endl 
        << "***" YELLOW"std::stack" NORMAL"*******************************************************" << std::endl
        <<"Content = " << print_stack(std_stack) << std::endl;
    fs << "Size = " << std_stack.size() <<std::endl<<std::endl;

    fs  <<  "***" YELLOW"ft::stack" NORMAL"*******************************************************\n"
        <<"Content = " << print_stack(ft_stack) << std::endl; 
        fs << "Size = " << ft_stack.size() <<std::endl<<std::endl; 

}

/* Test Stack ******************************************************************/
void    test_stack(void)
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_stack/log_test_pop_back";
    if (mkdir("Log_stack", 0777) == -1)
        std::cerr << "Error : faild to creat directory Log_vector" << std::endl;
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
   
    /* Default Constructor */
    
    

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::stack<int, std::vector<int> >  std_default;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::stack<int, ft::vector<int>> ft_default;
    ft_time = ft_time_calculator();
    
    out << printStackAttributes(std_default, ft_default, "Test default constructor");

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << " test default constructor \t\t\t\t\t\t\t\t"<< stack_is_equal(std_default , ft_default) 
             <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    /* Empty true  False*/
    /* Size */
    /* Top */
    /* Push */
    /* Pop */
    /* RL = relational operator */

}