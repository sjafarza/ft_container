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
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
            << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;



    delete  ft_pointer_default_m;
    delete  std_pointer_default_m;
    out.close();   
}

void  test_map_begin_end_rbegin_rend()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/begin ";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map,std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    std::string                result = RD"✘";
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }

    /* Begin    - for map normal*/
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.begin();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.begin();
    ft_time = ft_time_calcul();

    if(out.is_open())
        out << printMapAttributes( std_map,ft_map, "Test begin()", 0);
      
    if ( map_is_equal(std_map, ft_map) == GREEN"✔" &&  (*(std_map.begin())).first == (*(ft_map.begin())).first  &&
        (*(std_map.begin())).second == (*(ft_map.begin())).second)
        {
            result = GREEN "✔"; 
        }   
    std::cout << NORMAL "*****************************Test Iterator***********************************************." << std::endl;
    std::cout << NORMAL" test begin() \t\t\t\t\t\t\t" << result 
               <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.begin();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mpty_map.begin();
    ft_time = ft_time_calcul();

    if ( map_is_equal(std_mpty_map, ft_mpty_map) == GREEN"✔" &&  (*(std_mpty_map.begin())).first == (*(ft_mpty_map.begin())).first  &&
        (*(std_mpty_map.begin())).second == (*(ft_mpty_map.begin())).second)
        {
            result = GREEN "✔"; 
        }
    std::cout << NORMAL" test begin() for empty map \t\t\t\t\t" << result
               <<GREEN"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
               << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;       
    
    /* rBegin  */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.rbegin();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.rbegin();
    ft_time = ft_time_calcul();
    if ( map_is_equal(std_map, ft_map) == GREEN"✔" &&  (*(std_map.rbegin())).first == (*(ft_map.rbegin())).first  &&
        (*(std_map.rbegin())).second == (*(ft_map.rbegin())).second)
        {
            result = GREEN "✔"; 
        }  
    std::cout << NORMAL" test rbegin() \t\t\t\t\t\t\t" << result
              <<GREEN"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
              
              
    //std::cout << "std::rbegin = [ " << (*(std_mpty_map.rbegin())).first << ", " << (*(std_mpty_map.rbegin())).second  <<" ]\n";
    /*clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.rbegin();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
   ft_mpty_map.rbegin();
    ft_time = ft_time_calcul();

    if ( map_is_equal(std_mpty_map, ft_mpty_map) == GREEN"✔" && (*(std_mpty_map.rbegin())).second  == (*(ft_mpty_map.rbegin())).second )
        {
            result = GREEN "✔"; 
        }
    std::cout << NORMAL" test rbegin() for empty map    ?  \t\t\t\t"
              <<GREEN"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;*/
                       
    
    /* end */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.end();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.end();
    ft_time = ft_time_calcul();

    if ( map_is_equal(std_map, ft_map) == GREEN"✔" &&  (*(std_map.end())).first == (*(ft_map.end())).first &&
        (*(std_map.end())).second == (*(ft_map.end())).second)
        {
            result = GREEN "✔"; 
        }  
    std::cout << NORMAL" test end() \t\t\t\t\t\t\t" << result
              <<GREEN"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.end();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mpty_map.end();
    ft_time = ft_time_calcul();
    if ( map_is_equal(std_mpty_map, ft_mpty_map) == GREEN"✔" &&  (*(std_map.rend())).first == (*(ft_map.rend())).first &&
        (*(std_map.rend())).second == (*(ft_map.rend())).second)
        {
            result = GREEN "✔"; 
        }  
    std::cout << NORMAL" test end() for empty map \t\t\t\t\t" << result
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
  


    /* rend */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.rend();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.rend();
    ft_time = ft_time_calcul();

    if ( map_is_equal(std_map, ft_map) == GREEN"✔" &&  (*(std_map.rend())).first == (*(ft_map.rend())).first &&
        (*(std_map.rend())).second == (*(ft_map.rend())).second)
        {
            result = GREEN "✔"; 
        }  
    std::cout << NORMAL" test rend() \t\t\t\t\t\t\t" << result
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
  

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.rend();
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mpty_map.rend();
    ft_time = ft_time_calcul(); 
    if ( map_is_equal(std_mpty_map, ft_mpty_map) == GREEN"✔" &&  (*(std_map.rend())).first == (*(ft_map.rend())).first &&
        (*(std_map.rend())).second == (*(ft_map.rend())).second)
        {
            result = GREEN "✔"; 
        }  
    std::cout << NORMAL" test rend()for empty map \t\t\t\t\t"<< result
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;          
}

void    test_map_size()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/size ";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    //const int rang_big_int[];
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map, std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    std::string                result = RD"✘";
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }

    if(out.is_open())
        out << printMapAttributes( std_map,ft_map, "Test size()", 0);
    /*normal size */ 
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.size();
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.size();
    ft_time = ft_time_calcul();

    if ( std_map.size() == ft_map.size()) 
        result = GREEN "✔";     
    std::cout << NORMAL "*****************************Test size******************************************************." << std::endl;
    std::cout << NORMAL"Test size() for size normal \t\t\t\t\t" << result 
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
      

    /*Zero size */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.size();
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.size();
    ft_time = ft_time_calcul();

    if ( std_mpty_map.size() == ft_mpty_map.size()) 
        result = GREEN "✔";     
    std::cout << NORMAL"Test size() for zero size \t\t\t\t\t" << result
               <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;   
}

void    test_map_empty()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/empty";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map, std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    std::string                result = RD"✘";
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }

    if(out.is_open())
        out << printMapAttributes( std_map,ft_map, "Test size()", 0);
    /* empty map  */ 
    
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.empty();
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mpty_map.empty();
    ft_time = ft_time_calcul();

    if ( std_mpty_map.empty() == ft_mpty_map.empty()) 
        result = GREEN "✔";     
    std::cout << NORMAL "*****************************Test capacity *************************************************." << std::endl;
    std::cout << NORMAL"Test empty() for empty map \t\t\t\t\t"<< result
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
  

    /* Not empty map */ 
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.empty();
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.empty();
    ft_time = ft_time_calcul();

    if ( std_map.empty() == ft_map.empty()) 
        result = GREEN "✔";     
    std::cout << NORMAL"Test empty() for full map \t\t\t\t\t" << result
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 

}

void    test_map_element_access()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/element_access";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map, std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    std::string                result = GREEN "✔";
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }

    std::map<int, std::string >::const_iterator     std_it = std_map.begin();
    ft::map<int, std::string >::const_iterator      ft_it = ft_map.begin();

    /* mapped_type &at(const key_type &key) */
    if(out.is_open())
        out << printMapAttributes( std_map,ft_map, "Test at()", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.at((*std_it).first);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.at((*ft_it).first);
    ft_time = ft_time_calcul();
        
    while(std_it != std_map.end())
    {
        if ( std_map.at((*std_it).first) != ft_map.at((*ft_it).first))
        {
            result =  RD"✘"; 
            break ;
        }
        std_it++; ft_it++;
    }
    std::cout << NORMAL "*****************************Test Element access ********************************************." << std::endl;    
    std::cout << NORMAL"Test at()  \t\t\t\t\t\t\t" << result 
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
              << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 

    /* Test operator[]*/
    std_it = std_map.begin();
    ft_it = ft_map.begin();

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map[(*std_it).first];
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map[(*ft_it).first];
    ft_time = ft_time_calcul();
    while(std_it != std_map.end())
    {
        if ( std_map[(*std_it).first] != ft_map[(*ft_it).first])
        {
            result =  RD"✘"; 
            break ;
        }
        std_it++; ft_it++;
    }    
    std::cout << NORMAL"Test operator[]  \t\t\t\t\t\t" << result  
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
}

void    test_map_insert()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/insert";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    std::map<int, std::string> std_map, std_map1;/* = { {1, "saray"}, {2, "Arnika"}, {3, "Abtin"}};     Prb !!!!*/
    ft::map<int, std::string> ft_map, ft_map1; /*= {{1, "saray"}, {2, "Arnika"}, {3, "Abtin"}};*/
    std_map1[1] = "saray"; ft_map1[1] = "saray";
    std_map1[2] = "Arnika";ft_map1[2] = "Arnika";
    std_map1[3] = "Abtin"; ft_map1[3] = "Abtin";
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Original map ", 0);
    //(1) insert singel
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.insert(std::pair<int,std::string>(4, "Sanaz"));
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.insert(ft::pair<int, std::string>(4, "Sanaz"));  
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test after insert(4, sanaz)", 0);

     std::cout << NORMAL"Test insert function version (single parameter):  \t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    //(2) insert with hint  
    std::map<int, std::string>::iterator    std_it = std_map1.begin();
    ft::map<int, std::string>::iterator     ft_it = ft_map1.begin();
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.insert(std_it, std::pair<int,std::string>(5, "Nick"));
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.insert(ft_it, ft::pair<int, std::string>(5, "Nick"));  
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test after insert(it, 5, Nick)", 0);

     std::cout << NORMAL"Test insert with hint:  \t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
    //(3) third insert function version (range insertion)
     if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "Another map, empty  ", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.insert(std_it, std_map1.find(3));
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.insert(ft_it, ft_map1.find(3)); 
    ft_time = ft_time_calcul();
   
    if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "Test after insert(it, find(3))", 0);

     std::cout << NORMAL"Test insert range :  \t\t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;    

}

void    test_map_erase()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/erase";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    std::map<int, std::string> std_map, std_map1;
    ft::map<int, std::string> ft_map, ft_map1; 
    std_map1[1] = "saray"; ft_map1[1] = "saray";
    std_map1[2] = "Arnika";ft_map1[2] = "Arnika";
    std_map1[3] = "Abtin"; ft_map1[3] = "Abtin";
    std_map1[4] = "Sanaz"; ft_map1[4] = "Sanaz";
    std_map1[5] = "Nick"; ft_map1[5] = "Nick";
    std_map1[6] = "Khoob"; ft_map1[6] = "Khoob";
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Original map ", 0);

    std::map<int, std::string>::iterator    std_it = std_map1.find(2);
    ft::map<int, std::string>::iterator     ft_it = ft_map1.find(2);  
    //(1) erase (iterator position)   
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.erase(std_it);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.erase(ft_it); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test after erase(2)", 0);

     std::cout << NORMAL"Test  erasing by iterator  \t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

    //(2) erasing by key 
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.erase(1);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.erase(1); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test erasing by key=1  ", 0);

     std::cout << NORMAL"Test  erasing by key   \t\t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 

    // (3)  erasing by range 
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.erase( std_map1.find(4), std_map1.end());
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.erase( ft_map1.find(4), ft_map1.end()); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test erasing it=4 to it=end  ", 0);

     std::cout << NORMAL"Test  erasing  by range   \t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 

    /* clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map1.erase( std_map1.find(4), std_map1.end());
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map1.erase( ft_map1.find(4), ft_map1.end()); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map1, ft_map1, "Test erasing it=4 to it=end  ", 0);

     std::cout << NORMAL"Test  erasing  by range   \t\t\t\t\t" << map_is_equal(std_map1 , ft_map1) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;     */       
           
}

void    test_map_swap()
{
    std::ofstream        out;
    long double          std_time, ft_time;
    std::string const   file = "./Log_map/swap";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map, std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }
    // void swap (map& x);  
    if(out.is_open())
        out << printMapAttributes( std_mpty_map, ft_mpty_map, "std_mpty_map", 0);
    if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "map", 0); 

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mpty_map.swap(std_map);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mpty_map.swap(ft_map); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "map after swap(map&  map_mpty) ", 0);
     if(out.is_open())
        out << printMapAttributes( std_mpty_map, ft_mpty_map, " map_mpty after swap(map&  map)", 0);    

     std::cout << NORMAL"Test  swap(map& x)   \t\t\t\t\t\t" << map_is_equal(std_mpty_map , ft_mpty_map) <<map_is_equal(std_map , ft_map)
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
}

void    test_map_clear()
{
    std::ofstream        out;
    long double          std_time, ft_time;
   

    std::string const   file = "./Log_map/clear";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    std::string                result = RD"✘";
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }
     if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "Test clear()  ", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_map.clear();
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_map.clear(); 
    ft_time = ft_time_calcul();
    
    if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "Test  after clear()  ", 0);
    if ( std_map.empty() && ft_map.empty())
        {
            result =  GREEN"✔";
        }

     std::cout << NORMAL"Test  clear()   \t\t\t\t\t\t" <<  result /*map_is_equal(std_map1 , ft_map1) */
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl; 
}

void    test_observers()
{
    std::ofstream        out;
    long double          std_time, ft_time;
   
    std::string const   file = "./Log_map/observers";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::string                result = GREEN"✔";

    std::map<char,int>  std_mymap;
    ft::map<char, int>  ft_mymap;

    std_mymap['a']=100; std_mymap['b']=200; std_mymap['c']=300;
    ft_mymap['a']=100; ft_mymap['b']=200; ft_mymap['c']=300;

    std::map<char,int>::key_compare     std_mycomp = std_mymap.key_comp();
    ft::map<char,int>::key_compare      ft_mycomp = ft_mymap.key_comp();

//    key_compare key_comp() const;
    char std_highest = std_mymap.rbegin()->first;     // key value of last element
    char ft_highest = ft_mymap.rbegin()->first;

    std::map<char,int>::iterator std_it = std_mymap.begin();
    ft::map<char,int>::iterator ft_it = ft_mymap.begin();

    do {
        if(std_mycomp((*std_it).first , (*ft_it).first) || ft_mycomp((*std_it).first , (*ft_it).first))
            {
                result = RD"✘";
                break ;
            }
            ft_it++;
        } while ( std_mycomp((*std_it++).first, std_highest) );
    if (std_it != std_mymap.end() || ft_it != ft_mymap.end())
          result = RD"✘"; 

    std_it = std_mymap.begin();
    ft_it = ft_mymap.begin();           

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    do {
        out << std_it->first << " => " << std_it->second << '\n';
        } while ( std_mycomp((*std_it++).first, std_highest) );
    std_time = std_time_calcul(); 
  
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    do {
        out << ft_it->first << " => " << ft_it->second << '\n';
        } while ( ft_mycomp((*ft_it++).first, ft_highest) );
    ft_time = ft_time_calcul();

    std::cout << NORMAL "*****************************Test observers()********************************************." << std::endl;
     std::cout << NORMAL"Test key_compare key_comp() const   \t\t\t\t" <<  result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

//  while ( mymap.value_comp()(*it++, highest) );
    std::pair<char,int>     std_highes = *std_mymap.rbegin();
    ft::pair<char,int>     ft_highes = *ft_mymap.rbegin();
   
    std_it = std_mymap.begin();
    ft_it = ft_mymap.begin();
    result = GREEN"✔";
     do {
        if( !(std_mycomp((*std_it).first , (*ft_it).first) || !ft_mycomp((*std_it).first , (*ft_it).first)))
            {
                result = RD"✘";
                break ;
            }
        } while ( std_mymap.value_comp()(*std_it++, std_highes) || ft_mymap.value_comp()(*ft_it++, ft_highes));
        
    if (std_it != std_mymap.end() || ft_it != ft_mymap.end())
          result = RD"✘";


    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    do {
        out << std_it->first << " => " << std_it->second << '\n';
        } while ( std_mymap.value_comp()(*std_it++, std_highes) );
    std_time = std_time_calcul(); 

ft_it = ft_mymap.begin();     
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    do {
        out << ft_it->first << " => " << ft_it->second << '\n';
        } while ( ft_mymap.value_comp()(*ft_it++, ft_highes) );
    ft_time = ft_time_calcul();

     std::cout << NORMAL"Test ( mymap.value_comp()(*it++, highest) \t\t\t" <<  result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;    
}

void    test_operations()
{
    std::ofstream        out;
    long double          std_time, ft_time;
   
    std::string const   file = "./Log_map/operations";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::string                result = GREEN"✔";
   // std::string                result = RD"✘";

    const int range_int[] = {1, 2, 3, 4, 5};
    const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
    std::map<int, std::string> std_map,std_mpty_map;
    ft::map<int, std::string> ft_map, ft_mpty_map;
    
    for (int i = 0; i < 5; i++)
    {
        std_map.insert(std::make_pair(range_int[i], range_str[i]));
        ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
    }
     if(out.is_open())
        out << printMapAttributes( std_map, ft_map, "Test operations  ", 0);
    std::map<int,std::string>::iterator std_it ;
    ft::map<int,std::string>::iterator ft_it ;
    
    /*find exite */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_it = std_map.find(2);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_it = ft_map.find(2); 
    ft_time = ft_time_calcul();

    if (std_it->second != ft_it->second )
        result = RD"✘";
    out <<"\n***find exit : " << std::endl<< std::endl;
    out<<"std_map.find(2) = " << std_it->second << "  ft_map.find(2) = " << ft_it->second << "\n";

    std::cout << NORMAL "*****************************Test operation ********************************************." << std::endl;
    std::cout << NORMAL"Test find exit \t\t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    /*find not exite */
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_it = std_map.find(42);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_it = ft_map.find(42); 
    ft_time = ft_time_calcul();

    if (std_it != std_map.end() || ft_it != ft_map.end())
        result = RD"✘";

    std::cout << NORMAL"Test find exit \t\t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;            
    /* Const it Find */
    std::map<int,std::string>::const_iterator std_cst_it ;
    ft::map<int,std::string>::const_iterator ft_cst_it ;

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_cst_it = std_map.find(2);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_cst_it = ft_map.find(2); 
    ft_time = ft_time_calcul();

    if (std_cst_it->second != ft_cst_it->second )
        result = RD"✘";
    out <<"\n***Const find exit : " << std::endl<< std::endl;
    out<<"std_map.find(2) = " << std_cst_it->second << "  ft_map.find(2) = " << ft_cst_it->second << "\n";

    std::cout << NORMAL"Test Const find exit \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;


    //count element exist
    result = GREEN"✔";
    bool    std_cnt, ft_cnt;
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_cnt = std_map.count(2);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_cnt = ft_map.count(2); 
    ft_time = ft_time_calcul();

    if (std_cnt != ft_cnt)
        result = RD"✘";

    std::cout << NORMAL"Test count \t\t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    //count   element not exist 
    result = GREEN"✔";        
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_cnt = std_map.count(22);
    std_time = std_time_calcul();
 
    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_cnt = ft_map.count(22); 
    ft_time = ft_time_calcul();

    if (std_cnt != ft_cnt)
        result = RD"✘";

    std::cout << NORMAL"Test count for not fond element \t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;             
    //lower_bound
    result = GREEN"✔";
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_it = std_map.lower_bound(3);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_it = ft_map.lower_bound(3);
    ft_time = ft_time_calcul();

    if (std_it->second != ft_it->second )
        result = RD"✘";
    out <<"\n***lower_bound : " << std::endl<< std::endl;
    out<<"stl_map.lower_bound(2) = " << std_it->second << " ft_it = ft_map.lower_bound(2)) = " << ft_it->second << "\n\n";

    std::cout << NORMAL"Test lower_bound \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    
	/* Const it Lower bound */
    result = GREEN"✔";
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_cst_it = std_map.lower_bound(3);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_cst_it = ft_map.lower_bound(3);
    ft_time = ft_time_calcul();

    if (std_cst_it->second != ft_cst_it->second )
        result = RD"✘";
    out <<"\n***lower_bound : " << std::endl<< std::endl;
    out<<"std_map.lower_bound(2) = " << std_cst_it->second << " ft_it = ft_map.lower_bound(2)) = " << ft_cst_it->second << "\n\n";

    std::cout << NORMAL"Test Const lower_bound \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    

    //upper_bound
    result = GREEN"✔";
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_it = std_map.upper_bound(4);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_it = ft_map.upper_bound(4);
    ft_time = ft_time_calcul();

    if (std_it->second != ft_it->second )
        result = RD"✘";
    out <<"\n***upper_bound : " << std::endl<< std::endl;
    out<<"stl_map.upper_bound(4) = " << std_it->second << " ft_it = ft_map.upper_bound(4)) = " << ft_it->second << "\n\n";

    std::cout << NORMAL"Test upper_bound \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;
    /* Const it Upper bound */
    result = GREEN"✔";
    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_cst_it = std_map.upper_bound(4);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_cst_it = ft_map.upper_bound(4);
    ft_time = ft_time_calcul();

    if (std_cst_it->second != ft_cst_it->second )
        result = RD"✘";
    out <<"\n***upper_bound : " << std::endl<< std::endl;
    out<<"std_map.upper_bound(4) = " << std_cst_it->second << " ft_it = ft_map.upper_bound(4)) = " << ft_cst_it->second << "\n\n";

    std::cout << NORMAL"Test upper_bound \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;

    //equal_range
    result = GREEN"✔";
    std::pair<std::map<int,std::string>::iterator, std::map<int,std::string>::iterator>     std_ret;
    ft::pair<ft::map<int,std::string>::iterator, ft::map<int,std::string>::iterator>        ft_ret;

    std_ret = std_map.equal_range(2);
    ft_ret = ft_map.equal_range(2);

    out << "equal_range ,lower bound  points to: ";
    out << std_ret.first->first << " => " << std_ret.first->second << "\n\n";

    out << "equal_range ,upper bound points to: ";
    out << ft_ret.second->first << " => " << ft_ret.second->second << "\n\n";

    if (std_ret.first->first != ft_ret.first->first || std_ret.first->second != ft_ret.first->second ||
        std_ret.second->first != ft_ret.second->first || std_ret.second->second != ft_ret.second->second)
        result = RD"✘";

    std::cout << NORMAL"Test equal_bound \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;    
}

void    test_map_get_allocator()
{
    std::ofstream        out;
    long double          std_time, ft_time;
   
    std::string const   file = "./Log_map/allocator";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::string                result = GREEN"✔";

    int std_psize;
    std::map<char,int> std_mymap;
    std::pair<const char,int>* std_p;

    int ft_psize;
    ft::map<char,int> ft_mymap;
    ft::pair<char,int>* ft_p;

    // allocate an array of 5 elements using mymap's allocator:
    std_p=std_mymap.get_allocator().allocate(5);
    ft_p=ft_mymap.get_allocator().allocate(5);

    // assign some values to array
    std_psize = sizeof(std::map<char,int>::value_type)*5;
    ft_psize = sizeof(ft::map<char,int>::value_type)*5;

    out << "The allocated array has a size of " << std_psize << " bytes.\n";
    out << "The allocated array has a size of " << ft_psize << " bytes.\n";

    clock_gettime(CLOCK_MONOTONIC, &std_map_start);
    std_mymap.get_allocator().deallocate(std_p,5);
    std_time = std_time_calcul();

    clock_gettime(CLOCK_MONOTONIC, &ft_map_start);
    ft_mymap.get_allocator().deallocate(ft_p,5);
    ft_time = ft_time_calcul();

    if (std_psize != ft_psize)
        result = RD"✘";

    std::cout << NORMAL"Test get_allocator \t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << tim_is_ok(ft_time, std_time) << std::endl;   
}

void    test_map(void)
{
    test_map_constructor_assign();
    
   // test_map_operator_assign();
	test_map_begin_end_rbegin_rend();
	test_map_size();
	//test_max_size() and test_capacity() done in befor tests
    test_map_empty();
	test_map_element_access();
	test_map_insert();
	test_map_erase();
    test_map_swap();
	test_map_clear();
    test_observers();
    test_operations();
    test_map_get_allocator();
}

