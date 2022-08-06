#include <iostream>
# include <sstream>
# include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <sys/stat.h>

#include "./containers/map.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define RD    "\033[1;31m"
# define GREEN  "\033[032m"

/* calule time */
struct timespec std_map_start;
struct timespec ft_map_start;

double   std_time_calcul(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - std_map_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - std_map_start.tv_nsec)) * 1e-9;
	//std::cout << "<<< " << std::fixed << time_taken << std::endl;
	clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    return(time_taken);
}

double    ft_time_calcul(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - ft_map_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - ft_map_start.tv_nsec)) * 1e-9;
	//std::cout << "<<< " << std::fixed << time_taken << std::endl;
	clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    return(time_taken);
}

std::string    tim_is_ok ( long double ft_t, long double std_t)
{
    if(ft_t < (std_t * 20))
        return("ok");
    else
        return("ko");    
}
//************************ fin of tim

/* print and compare of result */
template <class Ta, class Tb>
std::string map_is_equal(const std::map<Ta, Tb> & std_map, const ft::map<Ta, Tb> & ft_map)
{
    typename std::map<Ta, Tb>::const_iterator  st_it = std_map.begin();
    typename ft::map<Ta, Tb>::const_iterator   ft_it = ft_map.begin();

    if(std_map.size() != ft_map.size())
        return (RD"✘ \t\t Size");
    if(std_map.size() == 0 && ft_map.size() == 0)  
        return (GREEN"✔");  

    while ( (*st_it).first == (*ft_it).first  &&  (*st_it).second == (*ft_it).second 
            && st_it != std_map.end() && ft_it != ft_map.end()) 
    {
        st_it++; ft_it++;
    }
    if(st_it == std_map.end() && ft_it == ft_map.end())
        return (GREEN"✔");
    return (RD"✘ \t\tContent");  
}

template <class Ta, class Tb>
std::string print_map(const std::map<Ta, Tb> & std_map)
{
    std::ostringstream  ss;
    if(std_map.size() == 0)
        ss << "{ }";
    else
    {
        typename std::map<Ta, Tb>::const_iterator   std_it/* = std_map.begin()*/;
        ss << " { ";
        
        //while(std_it < std_map.end())
        for(std_it = std_map.begin();  std_it != std_map.end(); std_it++)
        {
            ss<< "[ " << (*std_it).first << ", "<<(*std_it).second << " ]";
            //if(std_it + 1 != std_map.end())
            ss << " , " ;
            //std_it++;
        }
        ss << " } ";
    }
    return (ss.str());
}

template <class Ta, class Tb>
std::string print_map(const ft::map<Ta, Tb> & ft_map)
{
    std::ostringstream  ss;
    
    if(ft_map.size() == 0)
        ss << "{ }";
        
    else
    {
        typename ft::map<Ta, Tb>::const_iterator   ft_it /*= ft_map.begin()*/;
        ss << " { ";
        
       // while(ft_it < ft_map.end())
        for(ft_it = ft_map.begin();  ft_it != ft_map.end(); ft_it++)
        {
            
            ss<< "[ " << (*ft_it).first << ", " <<(*ft_it).second << " ]";
            //if(ft_it + 1 != ft_map.end())
            ss << " , " ;
            //ft_it++;
        }
        ss << " } ";
    }
    return (ss.str());
}

template <class Ta, class Tb>
std::string printMapAttributes(std::map<Ta, Tb>& std_map,ft::map<Ta, Tb>& ft_map , std::string titre, int idx)
{
    
    std::ostringstream fs;
    fs  << YELLOW << titre << "**********************************************************************" NORMAL << std::endl 
        << "***" YELLOW"std::map" NORMAL"*******************************************************" << std::endl
        <<"Content = " << print_map(std_map) << std::endl;
    
       fs << "Size = " << std_map.size() << "\t" << "Max_size = " << std_map.max_size()<< std::endl << std::endl;
       
        if (idx == 1)
            fs << "*begin() = " << "[ "<< (*(std_map.begin())).first <<", " << (*(std_map.begin())).second << " ]" 
                << "\t\t" 
                << "*end() = " <<"[ "<< (*(std_map.end() /*- 1*/)).first<<", " << (*(std_map.end()/* - 1*/)).second << " ]"
                << std::endl<< std::endl;
                
        if (idx == 2)
            fs << "*rbegin() = " << "[ "<< (*(std_map.rbegin())).first <<", " << (*(std_map.rbegin())).second << " ]"
            << "\t\t" <<
             "*rend() = " <<"[ "<< (*(std_map.rend()/* - 1*/)).first<<", " << (*(std_map.rend() /*- 1*/)).second << " ]"
             << std::endl<< std::endl;
        

      fs  <<  "***" YELLOW"ft::map" NORMAL"*******************************************************\n"
        <<"Content = " << print_map(ft_map) << std::endl
        << "Size = " << ft_map.size() << "\t" << "Max_size = " << ft_map.max_size()<< std::endl << std::endl;
        
        if (idx == 1)
            fs  << "*begin() = " <<"[ "<< (*(ft_map.begin())).first <<", " << (*(ft_map.begin())).second << " ]"
                << "\t\t" 
                << "*end() = " <<"[ "<< (*(ft_map.end()/* - 1*/)).first<<", " << (*(ft_map.end() /*- 1*/)).second << " ]" 
                << std::endl << std::endl;
        if (idx == 2)
            fs << "*rbegin() = " << "[" << (*(std_map.rbegin())).first << ", " << (*(ft_map.rbegin())).second << "]"
                <<"\t\t" 
                << "*rend() = "<<"[ "<< (*(ft_map.rend()/* - 1*/)).first<<", " << (*(ft_map.rend()/* - 1*/)).second << " ]"
                << std::endl<< std::endl;
            fs << "*******************************************************************\n\n\n\n";
            
    return (fs.str());    
}


void    test_map_constructor_assign()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/map_constructor_test";
    
    if (mkdir("./Log_map", 0777) == -1)
    {
        
        std::cerr << "Error : faild to creat directory Log_map" << std::endl;
       // return ;
       
    }
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
   
    /* Detault constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std::map<int, std::string>     std_m1;
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft::map<int, std::string>      ft_m1;
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes(std_m1,ft_m1, "Test default constructor", 0);

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << " test default constructor \t\t\t\t\t"<< map_is_equal(std_m1 , ft_m1) 
             <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
   
    /* Detault pointer constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std::map<int, std::string>*    std_pointer_default_m =  new std::map<int, std::string>;
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft::map<int, std::string>*    ft_pointer_default_m =  new ft::map<int, std::string>;
    ft_time = ft_time_calcul();

    if(out.is_open())
        out << printMapAttributes( *std_pointer_default_m,*ft_pointer_default_m, "Test default pointer constructor", 0);
    std::cout << NORMAL " test default pointer constructor \t\t\t\t"<< map_is_equal(*std_pointer_default_m, *ft_pointer_default_m) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << "\t" << tim_is_ok(ft_time, std_time) << std::endl;

   /* Range constructor */
    const int range_int[] = {-652, -4, 98, 54, -210}; 
	const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map;
	ft::map<int, std::string> ft_map;

    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std::map<int, std::string>    std_m2(std_map.begin() , std_map.end());
    std_time = std_time_calcul();
   
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft::map<int, std::string>     ft_m2(ft_map.begin(), ft_map.end());
    ft_time = ft_time_calcul();

    
    out << printMapAttributes(std_m2,ft_m2, "Test range  constructor of map",0);
    std::cout << NORMAL " test range of another vector constructor \t\t\t"<< map_is_equal(std_m2 , ft_m2) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

    /*Copy constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std::map<int, std::string>    std_m3(std_m2);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft::map<int, std::string>     ft_m3(ft_m2);
    ft_time = ft_time_calcul();

    if(out.is_open())
        out << printMapAttributes(std_m3,ft_m3, "Test copy constructor", 0);
    std::cout << NORMAL " test copy  constructor \t\t\t\t\t"<< map_is_equal(std_m3 , ft_m3) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

    /* Assign operator */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std::map<int, std::string> std_m4 = std_m3;
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
	ft::map<int, std::string> ft_m4 = ft_m3;
    ft_time = ft_time_calcul();

    if(out.is_open())
        out << printMapAttributes(std_m4,ft_m4, "Test Assign operator", 0);
    std::cout << NORMAL " test Assign operator \t\t\t\t\t\t"<< map_is_equal(std_m4 , ft_m4) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;



    delete  ft_pointer_default_m;
    delete  std_pointer_default_m;
    out.close();   
}

void  test_begin_end_rbegin_rend()
{

} 


void    test_map(void)
{
    test_map_constructor_assign();
    
   // test_map_operator_assign();
	test_begin_end_rbegin_rend();
	/*test_size();
	test_max_size() and test_capacity() done in befor tests
    test_resize();
    test_empty();
    test_reserve();
	test_element_access();
	test_assign();
	test_push_back();
	test_pop_back();
	test_insert();
	test_erase();
	test_swap();
	test_clear();
	//test_get_allocator();
	test_relational_operators();
	test_swap_nonmember();*/

}

