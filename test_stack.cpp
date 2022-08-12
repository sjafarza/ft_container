#include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <vector>
# include <stack>
# include <iterator>
# include <sys/stat.h>

//#include "./containers/vector.hpp"
#include "./containers/stack.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define REEDD    "\033[1;31m"
# define GREEN  "\033[032m"

/* calcule time ******************************************************************/

struct timespec std_stack_start;
struct timespec ft_stack_start;

double   std_time_calcul_stack(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - std_stack_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - std_stack_start.tv_nsec)) * 1e-9;
	clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    return(time_taken);
}

double    ft_time_calcul_stack(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - ft_stack_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - ft_stack_start.tv_nsec)) * 1e-9;
	clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    return(time_taken);
}

std::string    time_stack_is_ok ( long double ft_t, long double std_t)
{
    if(ft_t < (std_t * 20))
        return("ok");
    else
        return("ko");    
}


/* Generic functions for comparison ******************************************************************/
template <class T, class Container = ft::vector<T>, class container = std::vector<T> >
std::string stack_is_equal( std::stack<T, container> & std_stack,  ft::stack<T, Container> & ft_stack)
{
    while (1)
    {
        if (std_stack.size() == 0 || ft_stack.size() == 0)
            break;
        if (ft_stack.top() != std_stack.top())
            return (REEDD"✘");
        ft_stack.pop();
        std_stack.pop();
    }
    return (GREEN"✔");
}
    
template <class T, class Container = std::vector<T> >
std::string print_stack(std::stack<T, Container> & std_stack)
{
    std::ostringstream  ss;
    ss << " { ";
    if(std_stack.size() == 0)
        ss << " }";
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
std::string print_stack( ft::stack<T, Container>& ft_stack)
{
    std::ostringstream  ss;
      ss << " { ";
    if(ft_stack.size() == 0)
        ss << " }";
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

template <class T, class Container = ft::vector<T>, class container = std::vector<T> >
std::string printStackAttributes(std::stack<T, container>& std_stack,ft::stack<T, Container>& ft_stack , std::string titre)
{
    double long     std_size = std_stack.size();
    double long     ft_size = ft_stack.size();

    std::ostringstream fs;
    fs  << YELLOW << titre << "**********************************************************************" NORMAL << std::endl 
         << "***" YELLOW"std::stack" NORMAL"*******************************************************" << std::endl
        <<"Content = " <<print_stack(std_stack) << std::endl;
    fs << "Size = " << std_size <<std::endl<<std::endl;

    fs  <<  "***" YELLOW"ft::stack" NORMAL"*******************************************************\n"
        <<"Content = " << print_stack(ft_stack) << std::endl; 
        fs << "Size = " << ft_size <<std::endl<<std::endl; 
    return (fs.str());
}

/* Test Stack ******************************************************************/
void    test_stack(void)
{
    long double              std_time, ft_time;
    std::string             res_stack_test;
    std::ofstream        out;
    std::string const   file = "./Log_stack/log_stack";
    if (mkdir("Log_stack", 0777) == -1)
        std::cerr << "Error : faild to creat directory Log_stack" << std::endl;
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
   std::cout << "in stack \n";

    /* Default Constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std::stack<int, std::vector<int> >  std_default;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft::stack<int, ft::vector<int> >    ft_default;
    ft_time = ft_time_calcul_stack();
    
    out << printStackAttributes(std_default, ft_default, "Test default constructor");

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << "Test  default constructor \t\t\t\t\t\t"<< stack_is_equal(std_default , ft_default) 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;

    /* Empty true  False*/
    // True
    std::stack<int>     std_empty;
    ft::stack<int>      ft_empty;

    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_empty.empty();
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_empty.empty();
    ft_time = ft_time_calcul_stack();

    if (std_empty.empty() &&  ft_empty.empty())
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘"; 
    std::cout << "Test Empty true \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    // False
    std::stack<int>     std_no_empty;std_no_empty.push(42);     
    ft::stack<int>      ft_no_empty;ft_no_empty.push(42);

    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_no_empty.empty();
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_no_empty.empty();
    ft_time = ft_time_calcul_stack();

    if (!std_no_empty.empty() &&  !ft_no_empty.empty())
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘"; 
    std::cout << "Test Empty false \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;                

    /* Size */
    std::stack<int> std_size;
    ft::stack<int> ft_size;

    for (int i = 0; i < 12; i++)
    {
        std_size.push(i);
        ft_size.push(i);
    }
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_size.size();
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_size.size();
    ft_time = ft_time_calcul_stack();

    if (std_size.size() ==  ft_size.size())
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘"; 
    std::cout << "Test size \t\t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl; 

    /* Top */
    //out << printStackAttributes(std_size,ft_size, "Test Top ");
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_size.top();
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_size.top();
    ft_time = ft_time_calcul_stack();
    if (std_size.top() == ft_size.top())
        res_stack_test = GREEN"✔";
        else
            res_stack_test = REEDD"✘"; 
        std::cout << "Test Top \t\t\t\t\t\t\t\t"<< res_stack_test 
                <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
                << time_stack_is_ok(ft_time, std_time) << std::endl; 
    /* Push */
    std::stack<int>     std_push;     
    ft::stack<int>      ft_push;

    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_push.push(42);
    std_time = std_time_calcul_stack();
    
    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_push.push(42);
    ft_time = ft_time_calcul_stack();

    if (std_push.top() ==  ft_push.top())
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘"; 
    std::cout << "Test push \t\t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    /* Pop */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_push.pop();
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_push.pop();
    ft_time = ft_time_calcul_stack();

    if (std_push.empty() &&  ft_push.empty())
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘"; 
    std::cout << "Test pop() \t\t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;

    /* RL = relational operator */
    std::stack<int>     std_stack1,std_stack2, std_mpty, std_mpty1;     
    ft::stack<int>      ft_stack1,ft_stack2,ft_mpty, ft_mpty1;
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);

    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);

    out <<  printStackAttributes(std_stack1,ft_stack1 , "stackes1 for test relational operator");
    out <<  printStackAttributes(std_stack2,ft_stack2 , "stackes2 for test relational operator");
    
    // ==
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 == std_stack2;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 == ft_stack2;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 == std_stack2) == (ft_stack1 == ft_stack2))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";
    out << "ft_stack1 == ft_stack2  " << ((ft_stack1 == ft_stack2) ? " True" : "False" ) <<  std::endl;       
    std::cout << "*****************************RL = relational operator***********************************************." << std::endl;
    std::cout << "Test == in result true \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    if ((std_stack1 == std_mpty) == (ft_stack1 == ft_mpty))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";
    out << "ft_stack1 == ft_empty_stack  " << ((ft_stack1 == ft_mpty) ? "False" : "True" ) <<  std::endl<<std::endl;      
    std::cout << "Test == in result  False \t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<<std::endl;
    
    // !=
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 != std_mpty;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 != ft_mpty;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 != std_mpty) == (ft_stack1 != ft_mpty))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 != ft_mpty  " << ((ft_stack1 != ft_mpty) ? " False" : "True" ) <<  std::endl;       
    std::cout << "Test != in result true \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    if ((std_stack1 != std_stack2) == (ft_stack1 != ft_stack2))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";
    out << "ft_stack1 != ft_stack2  " << ((ft_mpty1 != ft_mpty) ? "True" : "False" ) <<  std::endl<<std::endl;      
    std::cout << "Test != in result False \t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<< std::endl;

    // <
    /*true condition */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 < std_mpty;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 < ft_mpty;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 < std_mpty) == (ft_stack1 < ft_mpty))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);

    out << "ft_mpty < ft_stack1  " << ((ft_mpty < ft_stack1) ? " True" : "False" ) << std::endl;       
    std::cout << "Test < in result true \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    /* in False condition */ 
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);

    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);


    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 < std_stack2;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 < ft_stack2;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 < std_stack2) == (ft_stack1 < ft_stack2))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";
    out << "ft_stack2 < ft_stack2  " << ((ft_stack2 < ft_stack2) ? "True" : "False" ) <<  std::endl<<std::endl;      
    std::cout << "Test < in result False \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<<std::endl;
    // <=
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    /* False condtion */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 <= std_empty;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 <= ft_mpty;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 <= std_mpty) == (ft_stack1 <= ft_mpty))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 <= ft_empty  " << ((ft_stack1 <= ft_empty) ? " True" : "False" ) << std::endl;       
    std::cout << "Test <= in result False \t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;
    /* True condtion */         
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 <= std_stack1;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 <= ft_stack1;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 <= std_stack1) == (ft_stack1 <= ft_stack1))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 <= ft_stack1  " << ((ft_stack1 <= ft_stack1) ? " True" : "False" ) << std::endl<<std::endl;       
    std::cout << "Test <= in result False \t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<<std::endl;

    // >
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    /* False condtion */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 > std_stack2;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 > ft_stack2;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 > std_stack1) == (ft_stack1 > ft_stack1))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 > ft_stack2  " << ((ft_stack1 > ft_stack2) ? " True" : "False" ) << std::endl;       
    std::cout << "Test > in result False \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;

    /* True condtion */         
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 > std_empty;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 > ft_empty;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 > std_stack1) == (ft_stack1 > ft_stack1))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 > ft_stack1  " << ((ft_stack1 > ft_empty) ? " True" : "False" ) << std::endl<<std::endl;       
    std::cout << "Test > in result True \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<<std::endl;

    // >=
     ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    /* False condtion */
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_mpty >= std_stack2;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_mpty >= ft_stack2;
    ft_time = ft_time_calcul_stack();

    if ((std_mpty >= std_stack2) == (ft_mpty >= ft_stack2))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_mpty >= ft_stack2  " << ((ft_mpty >= ft_stack2) ? " True" : "False" ) << std::endl;       
    std::cout << "Test >= in result False \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl;

    /* True condtion */         
    ft_stack1.push(42);ft_stack1.push(41);ft_stack1.push(40);ft_stack1.push(39);
    ft_stack2.push(42);ft_stack2.push(41);ft_stack2.push(40);ft_stack2.push(39);
    std_stack1.push(42);std_stack1.push(41);std_stack1.push(40);std_stack1.push(39);
    std_stack2.push(42);std_stack2.push(41);std_stack2.push(40);std_stack2.push(39);
    
    clock_gettime(CLOCK_MONOTONIC, &std_stack_start);
    std_stack1 >= std_stack1;
    std_time = std_time_calcul_stack();

    clock_gettime(CLOCK_MONOTONIC, &ft_stack_start);
    ft_stack1 >= ft_stack1;
    ft_time = ft_time_calcul_stack();

    if ((std_stack1 >= std_stack1) == (ft_stack1 >= ft_stack1))
        res_stack_test = GREEN"✔";
    else
        res_stack_test = REEDD"✘";

    out << "ft_stack1 >= ft_stack1  " << ((ft_stack1 >= ft_stack1) ? " True" : "False" ) << std::endl<<std::endl;       
    std::cout << "Test >= in result True \t\t\t\t\t\t\t"<< res_stack_test 
             <<NORMAL"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" 
             << time_stack_is_ok(ft_time, std_time) << std::endl<<std::endl;

}