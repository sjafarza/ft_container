#include <iostream>
# include <sstream>
# include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sys/stat.h>

#include "./containers/vector.hpp"

# define NORMAL "\033[0;37m"
# define YELLOW "\033[0;33m"
# define REDD    "\033[1;31m"
# define GREEN  "\033[032m"

/* calule time */
struct timespec std_start;
struct timespec ft_start;

double   std_time_calculator(void)
{
	struct timespec end;
	double time_taken;
    
	clock_gettime(CLOCK_MONOTONIC, &end);
	time_taken = (end.tv_sec - std_start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - std_start.tv_nsec)) * 1e-9;
	//std::cout << "<<< " << std::fixed << time_taken << std::endl;
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
	//std::cout << "<<< " << std::fixed << time_taken << std::endl;
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


template <class T>
std::string vector_is_equal(const std::vector<T> & std_vector, const ft::vector<T> & ft_vector)
{
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
    if(std_vector.capacity() != ft_vector.capacity()) /* != */
        return (REDD"✘ \t\t Capacity");
    if(std_vector.size() != ft_vector.size())
        return (REDD"✘ \t\t Size");
    if(std_vector.max_size() != ft_vector.max_size())
        return (REDD"✘ \t\t Max_size");
    /*if (!std_vector.empty() && !ft_vector.empty())
    {    
        if (*(std_vector.begin()) != *(ft_vector.begin()))
            return (RED"✘ /t/t begin()");
        //if (*(std_vector.end()) != *(ft_vector.end()))
         //   return (RED"✘ \t\t end()");
        if (*(std_vector.rbegin()) != *(ft_vector.rbegin()))
            return (RED"✘ \t\t rbegin()");
        if (*(std_vector.rend()) != *(ft_vector.rend()))
            return (RED"✘ \t\t rend()");
    } */        
    if(std_vector.size() == 0 && ft_vector.size() == 0)  
        return (GREEN"✔");  

    while(*st_it == *ft_it && st_it != std_vector.end() && ft_it != ft_vector.end()) 
    {
        st_it++; ft_it++;
    }
    if(st_it == std_vector.end() && ft_it == ft_vector.end())
        return (GREEN"✔");
    return (REDD"✘ \t\tContent");  
}

template <class T>
std::string print_vector(const std::vector<T> & std_vector)
{
    std::ostringstream  ss;
    if(std_vector.size() == 0)
        ss << "{ }";
    else
    {
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
    }
    return (ss.str());
}

template <class T>
std::string print_vector(const ft::vector<T> & ft_vector)
{
    std::ostringstream  ss;
     typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
     ss << " { ";
    
    while(ft_it < ft_vector.end())
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
std::string printVectorAttributes(std::vector<T>& std_vector,ft::vector<T>& ft_vector , std::string titre, int idx)
{
    std::ostringstream fs;
    fs  << YELLOW << titre << "**********************************************************************" NORMAL << std::endl 
        << "***" YELLOW"std::vector" NORMAL"*******************************************************" << std::endl
        <<"Content = " << print_vector(std_vector) << std::endl;
       fs << "Size = " << std_vector.size() << "\t" << "Capacity = " << std_vector.capacity() << "\t" << "Max_size = " << std_vector.max_size()
          << std::endl << std::endl;
        
        if (idx == 1)
            fs << "*begin() = " << *(std_vector.begin() /*- 1*/) << "\t\t" << "*end() = " <<*(std_vector.end() - 1)<< std::endl<< std::endl;
        if (idx == 2)
            fs << "*rbegin() = " << *(std_vector.rbegin()) << "\t\t" << "*rend() = " <<*(std_vector.rend() - 1)<< std::endl<< std::endl;
        



      fs  <<  "***" YELLOW"ft::vector" NORMAL"*******************************************************\n"
        <<"Content = " << print_vector(ft_vector) << std::endl
        << "Size = " << ft_vector.size() << "\t" << "Capacity = " << ft_vector.capacity() << "\t" << "Max_size = " << ft_vector.max_size()
        << std::endl << std::endl;
        if (idx == 1)
            fs  << "*begin() = " << *(ft_vector.begin()) << "\t\t" << "*end() = " << *(ft_vector.end() - 1) << std::endl << std::endl;
        if (idx == 2)
            fs << "*rbegin() = " << *(std_vector.rbegin()) << "\t\t" << "*rend() = " <<*(std_vector.rend() - 1)<< std::endl<< std::endl;

        fs << "*******************************************************************\n\n\n\n";
    return (fs.str());    

}

void    test_constructor()
{
    std::ofstream        out;
    long double              std_time, ft_time;
    std::string const   file = "./Log_vector/log_test_constructor";
    if (mkdir("Log_vector", 0777) == -1)
        std::cerr << "Error : faild to creat directory Log_vector" << std::endl;
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    
    /* Detault constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>     std_v1;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>      ft_v1;
    ft_time = ft_time_calculator();
    
    out << printVectorAttributes(std_v1,ft_v1, "Test default constructor", 0);

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << " test default constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) 
             <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    /* Detault pointer constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>*    std_pointer_default_v =  new std::vector<int>;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>*    ft_pointer_default_v =  new ft::vector<int>;
    ft_time = ft_time_calculator();

    out << printVectorAttributes( *std_pointer_default_v,*ft_pointer_default_v, "Test default pointer constructor", 0);
    std::cout << NORMAL " test default pointer constructor \t\t\t\t\t\t\t"<< vector_is_equal(*std_pointer_default_v, *ft_pointer_default_v) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << "\t" << time_is_ok(ft_time, std_time) << std::endl;

    /* Fill constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>    std_v2(5);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>     ft_v2(5);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v2,ft_v2, "Test fill constructor", 0);
    std::cout << NORMAL " test fill constructor \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) 
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    /*Fill constructor size*/
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>    std_v3(5, 100);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>     ft_v3(5, 100);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v3,ft_v3, "Test fill constructor size", 0);
    std::cout << NORMAL " test fill constructor  size\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v3 , ft_v3) 
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    /*Range constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>    s_test(5, 7);
    std::vector<int>    std_v4(s_test.begin() + 1, s_test.end() - 2);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>     ft_test(5, 7);
    ft::vector<int>     ft_v4(ft_test.begin() + 1, ft_test.end() - 2);
    ft_time = ft_time_calculator();

    
    out << printVectorAttributes(std_v4,ft_v4, "Test range of another vector constructor", 0);
    std::cout << NORMAL " test range of another vector constructor \t\t\t\t\t\t"<< vector_is_equal(std_v4 , ft_v4) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;
    


    int range_array[] = { 15, 65397429, 1299, 965, 5 , 88, 9};
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>::iterator std_itr(&(range_array[1]));
    std::vector<int>    std_arr_v4(std_itr , std_itr + 3);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>::iterator ft_itr(&(range_array[1]));
    ft::vector<int>     ft_arr_v4(ft_itr , ft_itr + 3);
    ft_time = ft_time_calculator();

    
    out << printVectorAttributes(std_arr_v4,ft_arr_v4, "Test range of array constructor", 0);
    std::cout << NORMAL " test range of array constructor \t\t\t\t\t\t\t"<< vector_is_equal(std_arr_v4 , ft_arr_v4) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    /*Copy constructor */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>    std_v5(s_test);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>     ft_v5(ft_test);
    ft_time = ft_time_calculator();

     out << printVectorAttributes(std_v5,ft_v5, "Test copy constructor", 0);
    std::cout << NORMAL " test copy  constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v5 , ft_v5) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;

    delete  ft_pointer_default_v;
    delete  std_pointer_default_v;
    out.close();
   
}

void    test_operator_assign(void)
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_operator_assign";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

        
    
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>    std_ref(5, 731);
    std::vector<int>     std_v = std_ref;
    std_time = std_time_calculator();

    
    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>     ft_ref(5, 731);
    ft::vector<int>      ft_v = ft_ref;
    ft_time = ft_time_calculator();


    out << printVectorAttributes(std_v,ft_v, "Test operatot assign", 0);
    std::cout << std::endl << NORMAL " test operator assign \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl<< std::endl;
    out.close();
}    

void    test_begin_end_rbegin_rend()
{
    std::string                result = REDD"✘";
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_begin_end";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    /*Iterator  begin() end ()*/
    int rang_array[] = {32, 66, 824, -2453, 0, 77};
    ft::vector<int>::iterator   ft_it(&rang_array[0]);
    std::vector<int>::iterator   std_it (&rang_array[0]);
    

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::vector<int>     std_v(std_it ,std_it + 4);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::vector<int>      ft_v (ft_it , ft_it + 4);
    ft_time = ft_time_calculator();
    
    out << printVectorAttributes(std_v,ft_v, "Test Iterator begin()  end()", 1);
    std::cout << "*****************************Test Iterator***********************************************." << std::endl;
    if ( vector_is_equal(std_v, ft_v) == GREEN"✔" &&  *(std_v.begin()) == *(ft_v.begin())  && *(std_v.end()) == *(ft_v.end()))
        result = GREEN "✔";     
    std::cout << NORMAL "Test Iterator begin end\t\t\t\t\t\t\t\t\t"<< result<< std::endl;
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;    
   
    /* Reverse Iterator   begin() end ()*/
    out << printVectorAttributes(std_v,ft_v, "Test reverse Iterator rbegin() rend ()", 2);
    if ( vector_is_equal(std_v, ft_v) == GREEN"✔" &&  *(std_v.rbegin()) == *(ft_v.rbegin())  && *(std_v.rend()) == *(ft_v.rend()))
        result = GREEN "✔";     
    std::cout << NORMAL "Test Iterator rbegin rend\t\t\t\t\t\t\t\t"<< result << std::endl;

    /* Const Iterator   begin() end ()*/
    {
        int rang_array[] = {32, 66, 824, -2453, 0, 77};
        ft::vector<int>::const_iterator   ft_it(&rang_array[0]);
        std::vector<int>::const_iterator   std_it (&rang_array[0]);
        std::vector<int>     std_v(std_it + 1 ,std_it + 4);
        ft::vector<int>      ft_v (ft_it + 1, ft_it + 4);
        out << printVectorAttributes(std_v,ft_v, "Test Const  Iterator begin() end ()", 1);
        if ( vector_is_equal(std_v, ft_v) == GREEN"✔" &&  *(std_v.begin()) == *(ft_v.begin())  && *(std_v.end()) == *(ft_v.end()))
        result = GREEN "✔";     
        std::cout << NORMAL "Test const Iterator begin end\t\t\t\t\t\t\t\t"<< result<< std::endl;  
    
    /* Reverse const Iterator   begin() end ()*/
        out << printVectorAttributes(std_v,ft_v, "Test Const reverse Iterator rbegin() rend ()", 1);
        if ( vector_is_equal(std_v, ft_v) == GREEN"✔" &&  *(std_v.begin()) == *(ft_v.begin())  && *(std_v.end()) == *(ft_v.end()))
        result = GREEN "✔";     
        std::cout << NORMAL "Test Iterator begin end\t\t\t\t\t\t\t\t\t"<< result<< std::endl;
    }
    out.close();
}

void    test_size(void)
{
    
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_size";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    
    /* zero size */
    std::vector<int>     std_v1(0);
    ft::vector<int>      ft_v1(0);
    out << printVectorAttributes(std_v1,ft_v1, "Test zero size", 0);

    std::cout << "*****************************Test capacity***********************************************." << std::endl;
    std::cout <<NORMAL " test for zero size \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;
    
    /*normal size */
    std::vector<int>     std_v2(100);
    ft::vector<int>      ft_v2(100);
    out << printVectorAttributes(std_v2,ft_v2, "Test normal size", 0);
    std::cout <<NORMAL " test for normal size \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;

    /*big size */
    std::vector<int>     std_v3(100000);
    ft::vector<int>      ft_v3(100000);
    //out << printVectorAttributes(std_v3,ft_v3, "Test big size", 0);
    std::cout <<NORMAL " test for big size \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v3 , ft_v3) << std::endl;
    out.close();
}

void    test_resize(void)
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_resize";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::vector<int>     std_v1(10, 5);
    ft::vector<int>      ft_v1(10, 5);
    out << printVectorAttributes(std_v1,ft_v1, "fist definition", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.resize(4);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.resize(4);
    ft_time = std_time_calculator();

    out << printVectorAttributes(std_v1,ft_v1, "After resize to 4 ", 0);
    std::cout <<NORMAL " test for resize to smaller size \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) 
            << std::endl;
    
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.resize(10);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.resize(10);
    ft_time = std_time_calculator();

    out << printVectorAttributes(std_v1,ft_v1, "After resize to 12 size", 0);
    std::cout <<NORMAL " test for resize to biger size \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) 
            << std::endl;
    
    out.close();
}

void    test_empty(void)
{
    std::vector<char>   std_v1;
    ft::vector<char>    ft_v1;

    std::vector<char>   std_v2(5);
    ft::vector<char>    ft_v2(5);

    std::vector<int>   std_v3(5, 3);
    ft::vector<int>    ft_v3(5, 3);

    std::cout << "*****************************Test empty()***********************************************." << std::endl;
        if(std_v1.empty() ==ft_v1.empty())
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t"<< GREEN"✔"<< std::endl;
        else
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;

            
        if(std_v2.empty() ==ft_v2.empty())
            std::cout <<NORMAL " test for empty() for vector(size)* \t\t\t\t\t\t\t"<< GREEN"✔"<< std::endl;
        else     
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;

        
        if(std_v3.empty() ==ft_v3.empty())
            std::cout <<NORMAL " test for empty() for Fill value(s, v)* \t\t\t\t\t\t"<< GREEN"✔" << std::endl;
        else
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
               
}

void    test_reserve(void)
{
    long double              std_time, ft_time;
    std::vector<int> std_v(7, 11);
    ft::vector<int> ft_v(7, 11);

    std::vector<int> std_v1(1);
    ft::vector<int> ft_v1(1);

    std::vector<int>:: size_type   std_v_capacity= std_v.capacity();
    ft::vector<int>::size_type      ft_v_capacity= ft_v.capacity();
    
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.reserve(std_v_capacity + 50);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.reserve(ft_v_capacity + 50);
    ft_time = ft_time_calculator();
    
    std::vector<int>:: size_type    std_v1_capacity= std_v1.capacity();
    ft::vector<int>::size_type    ft_v1_capacity= ft_v1.capacity();
    std::cout << "*****************************Test reserv()***********************************************." << std::endl;
    if (std_v1_capacity == ft_v1_capacity)
        std::cout <<NORMAL " test for reserve* \t\t\t\t\t\t\t\t\t"<< GREEN"✔" ;
    else
        std::cout <<NORMAL " test for reserve* \t\t\t\t\t\t\t\t\t\t\t"<< REDD"✘" ;

    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;    
}


void    test_element_access(void)
{
    //operator []
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_element_access";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    int range_array[] = { 15, 65397429, 1299, 965, 5 , 88, 9};
    std::vector<int>::iterator std_itr(&(range_array[1]));
    ft::vector<int>::iterator ft_itr(&(range_array[1]));

    std::vector<int>    std_arr_v4(std_itr , std_itr + 4);
    ft::vector<int>     ft_arr_v4(ft_itr , ft_itr + 4);
    out << printVectorAttributes(std_arr_v4,ft_arr_v4, "Test operato access", 0);
    
    // operator []
    for (std::vector<int>::size_type i = 0 ; i < std_arr_v4.size(); ++i)
    {
        out << "std_arr_arr["<<i<<"] = " << std_arr_v4[i] << "\t\t" << "ft_arr_arr[" <<i << "] = " << ft_arr_v4[i] << "\n";
        if (std_arr_v4[i] != ft_arr_v4[i])
            {
               std::cout <<NORMAL " test for operator [] \t\t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
               return ;
            }   
    }
    std::cout <<NORMAL " test for operator [] \t\t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl;

    out << "\n============================================================================\n\n";
    // at
    for (std::vector<int>::size_type i = 0 ; i < std_arr_v4.size(); ++i)
    {
        out << "std_arr_v4.at("<< i << ") = " << std_arr_v4.at(i) << "\t\t" << "ft_arr_arr.at("<< i << ") = " << ft_arr_v4.at(i) << "\n";
        if (std_arr_v4.at(i) != ft_arr_v4.at(i))
            {
               std::cout <<NORMAL " test for operator at \t\t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
               return ;
            }   
    }
    std::cout <<NORMAL " test for operator at \t\t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl;

    
    //front,  back
    out << "\n============================================================================\n\n";
    out << "std_arr_v4.front() = " << std_arr_v4.front() << "\t\t" << "ft_arr_v4.front() = " << ft_arr_v4.front()<< std::endl;
    if (std_arr_v4.front() != ft_arr_v4.front())
    {
        std::cout <<NORMAL " test for front() \t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<<  std::endl;
        return ;
    }

    out << "std_arr_v4.back() = " << std_arr_v4.back() << "\t" << "ft_arr_v4.back() = " << ft_arr_v4.back()<< std::endl;
    if (std_arr_v4.back() != ft_arr_v4.back())
    {
        std::cout <<NORMAL " test for back() \t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
        return ;
    }

    /** chenge vector for test front et back **/
    std_arr_v4.push_back(2323);std_arr_v4.push_back(-7);
    ft_arr_v4.push_back(2323);ft_arr_v4.push_back(-7);
    out << printVectorAttributes(std_arr_v4,ft_arr_v4, "Test front() back() after chenging vector", 0);

    /** test front et back after push_back **/
    out << "std_arr_v4.front() = " << std_arr_v4.front() << "\t\t" << "ft_arr_v4.front() = " << ft_arr_v4.front()<< std::endl;
    if (std_arr_v4.front() != ft_arr_v4.front())
    {
        std::cout <<NORMAL " test for front() \t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
        return ;
    }

    out << "std_arr_v4.back() = " << std_arr_v4.back() << "\t\t" << "ft_arr_v4.back() = " << ft_arr_v4.back()<< std::endl;
    if (std_arr_v4.back() != ft_arr_v4.back())
    {
       std::cout <<NORMAL " test for back() \t\t\t\t\t\t\t\t\t\t"<< REDD"✘"<< std::endl;
       return ;
    }
    std::cout <<NORMAL " test for front() back() \t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl; 
     out.close();    
 }

 void   	test_assign()
 {
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_assign";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    std::vector<int>    std_v1(2), std_v2,  std_v3;
    ft::vector<int>     ft_v1(2), ft_v2, ft_v3;

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.assign(7, 100);
    std_time = std_time_calculator();
    
    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.assign(7, 100);
    ft_time = ft_time_calculator();
    
    out << printVectorAttributes(std_v1,ft_v1, "Test assign(n, val) ", 0);
    std::cout << "*****************************Test assign()***********************************************." << std::endl;
    std::cout << NORMAL" Test assign(n, val) \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) 
              << std::endl; 

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v2.assign(std_v1.begin() + 1, std_v1.end() - 1);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v2.assign(ft_v1.begin()+ 1, ft_v1.end() - 1);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v2,ft_v2, "Test assign(it_first,  it_last) ", 0);
    std::cout << NORMAL" Test assign(it_first,  it_last) \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) 
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) 
              << std::endl;  
 
    int arr[] = {12, -4567654, 0, 10, 58};
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v3.assign(arr, arr + 3);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v3.assign(arr, arr + 3);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v3,ft_v3, "Test assign(it_first_arr,  it_last_arr) ", 0);
    std::cout << NORMAL" Test assign(it_first_arr,  it_last_arr) \t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) 
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time) 
              << std::endl;
    out.close();
 }

void    test_push_back()
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_push_back";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
        
    std::vector<int>    std_v1, std_v2(45),  std_v3(5, 87);
    ft::vector<int>     ft_v1, ft_v2(45), ft_v3(5, 87);
    /*empty vector */
    out << printVectorAttributes(std_v1,ft_v1, "Test push_back() ", 0);
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.push_back(42);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.push_back(42);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v1,ft_v1, "After push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << "*****************************Test push_back()***********************************************." << std::endl;
    std::cout << NORMAL" Test push_back for empty vector \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) 
            <<"\t\t   std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
            << std::endl;  
   
    /* vector fill size */
    out << printVectorAttributes(std_v2,ft_v2, "Test push_back() for vector(size) ", 0);
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v2.push_back(42);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v2.push_back(42);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v2,ft_v2, "After push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test push_back for vector fill size \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) 
             <<"\t\tstd_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
             << std::endl;  

    /* vector fill size and value */
    out << printVectorAttributes(std_v3,ft_v3, "Test push_back() for vector(size, val) ", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.push_back(42);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.push_back(42);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v3,ft_v3, "after push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test push_back for vector fill size  and value\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
                <<"\t\t   std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl; 
     out.close();

    
}

void    test_pop_back()
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_pop_back";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    int arr[] = {12, -4567654, 0, 10, 58};
    std::vector<int>    std_v1(5, 99),  std_v2;
    ft::vector<int>     ft_v1(5, 99), ft_v2;
    std_v2.assign(arr, arr + 3);
    ft_v2.assign(arr, arr + 3); 

    
    out << printVectorAttributes(std_v2,ft_v2, "Test pop_back() ", 0);


    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v2.pop_back();
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v2.pop_back();
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v2,ft_v2, "After pop_back() ", 0);
    out << std::endl << std::endl;
    std::cout << "*****************************Test pop_back()***********************************************." << std::endl;
    std::cout << NORMAL" Test pop_back for vector rang const  \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2)
                <<"\t\t   std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl;

    out << printVectorAttributes(std_v1,ft_v1, "Test pop_back() for vector(n, v) ", 0);
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.pop_back();
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.pop_back();
    ft_time = ft_time_calculator();

    out << print_vector(ft_v1);
    out << print_vector(std_v1);
    out << printVectorAttributes(std_v1,ft_v1, "After pop_back() ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test pop_back for vector(n, v)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
              <<"\t\t   std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    out.close();
}



void    test_insert()
{
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_insert";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    int arr[] = {12, -4567654, 0, 10, 58};
    std::vector<int>    std_v, std_v1(5, 99),  std_v2(1, 66);
    ft::vector<int>     ft_v , ft_v1(5, 99), ft_v2(1, 66);
    out << printVectorAttributes(std_v,ft_v, "Test insert(it, value) ", 0);
    // model 1   insert(itr, value)
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v.insert(std_v.begin(), 22);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v.insert(ft_v.begin(), 22);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v,ft_v, "After insert(begin, 22) ", 0);
    out << std::endl << std::endl;
     std::cout << "*****************************Test insert()***********************************************." << std::endl;
    std::cout << NORMAL" Test insert(it, val)  \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v)
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    // model 2  insert(itr, size n , value val) 
    out << printVectorAttributes(std_v1,ft_v1, "Test insert(it, size, value) ", 0);

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.insert(std_v1.begin() + 2  , 15, 300);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.insert(ft_v1.begin() + 2 , 15, 300);
    ft_time = ft_time_calculator();
    
    out << printVectorAttributes(std_v1,ft_v1, "After insert(begin+1, 2, 300) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test insert(it, size, val)  \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    // model 3     insert(it, it_first, it_end)
    out << printVectorAttributes(std_v2,ft_v2, "Test insert(it, it_first, it_end) ", 0);
    out << "arr[] = {12, -4567654, 0, 10, 58}" << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v2.insert(std_v2.begin() + 1, arr, arr + 3);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v2.insert(ft_v2.begin() + 1,arr, arr + 3);
    ft_time = ft_time_calculator();
    
    out << printVectorAttributes(std_v2,ft_v2, "After insert(begin, arr, arr + 3) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test insert(it, arr, arr + n)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2)
              <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    out.close();

}

void test_erase()
{  
     long double              std_time, ft_time;
     /* log */
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_erase";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    int arr[] = {12, -4567654, 0, 10, 58, -5, 77, 52, 66, 45};
    std::vector<int>    std_v;
    ft::vector<int>     ft_v ;
    std_v.assign(arr, arr + 7);
    ft_v.assign(arr, arr + 7);
    out << printVectorAttributes(std_v,ft_v, "Test erase(it)  vector ", 0);

    /*test erase one positin */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v.erase(std_v.begin()+ 2);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v.erase(ft_v.begin() + 2);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v,ft_v, "After erase(begin + 2) ", 0);
    out << std::endl << std::endl;
    std::cout << "*****************************Test erase()***********************************************." << std::endl;
    std::cout << NORMAL" Test erase(itr position)  \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v)
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    
    /*test erase  of range[first,last) */
    
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v.erase(std_v.begin()+ 2, std_v.begin() + 5);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v.erase(ft_v.begin() + 2, ft_v.begin() + 5);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v,ft_v, "After erase(begin + 2 , begin + 5) ", 0);
    std::cout << NORMAL" Test erase of range[first,last)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v)
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
              << std::endl;
    out.close();

}

void    test_swap()
{
    long double              std_time, ft_time;
    /* log */
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_swap";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    /* product 2 vec */
    int arr1[] = {1458, -98, 745, 62, 9, 52, 0, 22};
    int arr2[] = {12, -4567654, 0, 10, 58, -5, 77, 52, 66, 45};
    std::vector<int>    std_v1, std_v2;
    ft::vector<int>     ft_v1 , ft_v2;
    std_v1.assign(arr1, arr1 + 7);
    ft_v1.assign(arr1, arr1 + 7);
    out << printVectorAttributes(std_v1,ft_v1, "vectors_one ", 0);
    std_v2.assign(arr2, arr2 + 4);
    ft_v2.assign(arr2, arr2 + 4);
    out << printVectorAttributes(std_v2,ft_v2, "vector_two", 0);
    out << std::endl << std::endl;

    /*swap(x)*/
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.swap(std_v2);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.swap(ft_v2);
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v1,ft_v1, "vectors_one after swap(vector_two) ", 0);

    std::cout << "*****************************Test swap(x)**********************************************." << std::endl;
    std::cout << NORMAL" Test swap(x)  \t\t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl;

    out.close();
}

void    test_clear()
{

    long double              std_time, ft_time;
    /* log */
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_clear";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    /* product  vectors */
    int arr1[] = {1458, -98, 745, 62, 9, 52, 0, 22};
    std::vector<int>    std_v1, std_v2;
    ft::vector<int>     ft_v1 , ft_v2;
    std_v1.assign(arr1, arr1 + 7);
    ft_v1.assign(arr1, arr1 + 7);
    out << printVectorAttributes(std_v1,ft_v1, "vectors origin ", 0);
    
    //clear() for vector non empty
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1.clear();
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1.clear();
    ft_time = ft_time_calculator();

    out << printVectorAttributes(std_v1,ft_v1, "vectors,clear() ", 0);
    out << std::endl << std::endl;

    std::cout << "*****************************Test clear()**********************************************." << std::endl;
    std::cout << NORMAL" Test clear()  \t\t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl;
    //clear() for empty vector 
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v2.clear();
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v2.clear();
    ft_time = ft_time_calculator();

    std::cout << NORMAL" Test clear() for empty vector \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1)
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl;

   
    out.close();
}

void   test_relational_operators()
{
     /* log */
    long double              std_time, ft_time;
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_operator";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    
    /* product  vectors */
    int arr1[] = {1458, -98, 745, 62, 9, 52, 0, 22};
    std::vector<int>    std_v1, std_v2, std_v3(5, 22);
    ft::vector<int>     ft_v1 , ft_v2 ,ft_v3(5, 22);
    
    std_v1.assign(arr1, arr1 + 7); std_v2.assign(arr1, arr1 + 7);
    
    ft_v1.assign(arr1, arr1 + 7); ft_v2.assign(arr1, arr1 + 7);
    out << printVectorAttributes(std_v1,ft_v1, "vectors_V1 ", 1);
    out << printVectorAttributes(std_v2,ft_v2, "vectors_V2 ", 1);
    out << printVectorAttributes(std_v3,ft_v3, "vectors_V3 ", 1);
    
    /* operator == */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1 == std_v2;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1 == ft_v2;
    ft_time = ft_time_calculator();

    std::cout << "***************************** operator ==  **********************************************." << std::endl;
    if (std_v1 == std_v2 && ft_v1 == ft_v2)
         std::cout << NORMAL" Test operator == for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔"; 
         
    else
       std::cout << NORMAL" Test operator == for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘" ;
     
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;   
/* ==  in False condition*/
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1 == std_v3;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1 == ft_v3;
    ft_time = ft_time_calculator();

    if ((std_v1 == std_v3) == (ft_v1 == ft_v3))
         std::cout << NORMAL" Test operator == for 2 vectors differents \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator == for 2 vectors differents \t\t\t\t\t\t"<< REDD"✘" ; 
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;  

    out << GREEN"************  std_v1 == std_v2   return :  "<< ((std_v1 == std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 == ft_v2     return :  "<< ((ft_v1 == ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 == std_v3   return :  "<< ((std_v1 == std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 == ft_v3     return :  "<< ((ft_v1 == ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;   

    /* operator != */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1 != std_v2;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1 != ft_v2;
    ft_time = ft_time_calculator();

    if ((std_v1 != std_v3) == (ft_v1 != ft_v3))
         std::cout << NORMAL" Test operator != for 2 vectors differents \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator != for 2 vectors differents \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;
    /* in False condition */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v1 != std_v2;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v1 != ft_v2;
    ft_time = ft_time_calculator();

    if ((std_v1 != std_v2) == (ft_v1 != ft_v2))
         std::cout << NORMAL" Test operator != for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator != for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘" ;
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;

    out << NORMAL"======================================================================"<<std::endl;
    out << GREEN"************  std_v1 != std_v2   return :  "<< ((std_v1 != std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 != ft_v2     return :  "<< ((ft_v1 != ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 != std_v3   return :  "<< ((std_v1 != std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 != ft_v3     return :  "<< ((ft_v1 != ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;              
    
    /* operator < */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v3 < std_v1;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v3 < ft_v1;
    ft_time = ft_time_calculator();
    /* True cond */
    if (std_v3 < std_v1 == ft_v3 < ft_v1)
         std::cout << NORMAL"1 Test operator < for 2 vectors differents in smal<big \t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator < for 2 vectors differents in smal<big \t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time <<"\t" << time_is_ok(ft_time, std_time)
         << std::endl;
    /* False cond */
    if (std_v3 < std_v1 == ft_v3 < ft_v1)
         std::cout << NORMAL"2 Test operator < for 2 vectors big<small \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator <  for 2 vectors big<small \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if ((std_v1 < std_v2) == (ft_v1 < ft_v2))
         std::cout << NORMAL"3 Test operator < for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator < for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;      


    out << NORMAL"======================================================================"<<std::endl;
    out << GREEN"************  std_v3 < std_v1   return :  "<< ((std_v3 < std_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v3 < ft_v1     return :  "<< ((ft_v3 < ft_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 < std_v3   return :  "<< ((std_v1 < std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 < ft_v3     return :  "<< ((ft_v1 < ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 < std_v2   return :  "<< ((std_v1 < std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 < ft_v2     return :  "<< ((ft_v1 < ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    
    /* operator <= */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v3 <= std_v1;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v3 <= ft_v1;
    ft_time = ft_time_calculator();

    if (std_v3 <= std_v1 == ft_v3 <= ft_v1)
         std::cout << NORMAL" Test operator <= for 2 vectors differents in smal<=big \t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator <= for 2 vectors differents in smal<=big \t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if (std_v3 <= std_v1 == ft_v3 <= ft_v1)
         std::cout << NORMAL" Test operator <= for 2 vectors big<=small \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator <=  for 2 vectors big<=small \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if ((std_v1 <= std_v2) == (ft_v1 <= ft_v2))
         std::cout << NORMAL" Test operator <= for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator <= for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;      


    out << NORMAL"======================================================================"<<std::endl;
    out << GREEN"************  std_v3 <= std_v1   return :  "<< ((std_v3 <= std_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v3 <= ft_v1     return :  "<< ((ft_v3 <= ft_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 <= std_v3   return :  "<< ((std_v1 <= std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 <= ft_v3     return :  "<< ((ft_v1 <= ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 <= std_v2   return :  "<< ((std_v1 <= std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 <= ft_v2     return :  "<< ((ft_v1 <= ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    
    /* operator > */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v3 > std_v1;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v3 > ft_v1;
    ft_time = ft_time_calculator();

    if ((std_v3 > std_v1) == (ft_v3 > ft_v1))
         std::cout << NORMAL" Test operator > for 2 vectors differents in smal>big \t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator > for 2 vectors differents in smal>big \t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if ((std_v3 > std_v1) == (ft_v3 > ft_v1))
         std::cout << NORMAL" Test operator > for 2 vectors big>small \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator >  for 2 vectors big>small \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if ((std_v1 > std_v2) == (ft_v1 > ft_v2))
         std::cout << NORMAL" Test operator > for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator > for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘";   
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;

    out << NORMAL"======================================================================"<<std::endl;
    out << GREEN"************  std_v3 > std_v1   return :  "<< ((std_v3 > std_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v3 > ft_v1     return :  "<< ((ft_v3 > ft_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 > std_v3   return :  "<< ((std_v1 > std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 > ft_v3     return :  "<< ((ft_v1 > ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 > std_v2   return :  "<< ((std_v1 > std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 > ft_v2     return :  "<< ((ft_v1 > ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    
    /* operator >= */
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std_v3 >= std_v1;
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft_v3 >= ft_v1;
    ft_time = ft_time_calculator();

    if ((std_v3 >= std_v1) == (ft_v3 >= ft_v1))
         std::cout << NORMAL" Test operator >= for 2 vectors differents in smal>=big \t\t\t\t"<< GREEN"✔" ;
    else
       std::cout << NORMAL" Test operator >=for 2 vectors differents in smal>=big \t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if (std_v3 >= std_v1 == ft_v3 >= ft_v1)
         std::cout << NORMAL" Test operator >= for 2 vectors big>=small \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator >= for 2 vectors big>=small \t\t\t\t\t\t"<< REDD"✘";
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl;

    if ((std_v1 >= std_v2) == (ft_v1 >= ft_v2))
         std::cout << NORMAL" Test operator >= for 2 vectors identity \t\t\t\t\t\t"<< GREEN"✔";
    else
       std::cout << NORMAL" Test operator >= for 2 vectors identity \t\t\t\t\t\t"<< REDD"✘"; 
    std::cout << "\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
         << std::endl<<std::endl;     


    out << NORMAL"======================================================================"<<std::endl;
    out << GREEN"************  std_v3 >= std_v1   return :  "<< ((std_v3 >= std_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v3 >= ft_v1     return :  "<< ((ft_v3 >= ft_v1 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 >= std_v3   return :  "<< ((std_v1 >= std_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 >= ft_v3     return :  "<< ((ft_v1 >= ft_v3 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;
    out << GREEN"************  std_v1 >= std_v2   return :  "<< ((std_v1 >=std_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl;
    out << std::endl<< GREEN"************  ft_v1 >= ft_v2     return :  "<< ((ft_v1 >= ft_v2 ) ? "True" : "False") << NORMAL" . "<<std::endl<<std::endl<<std::endl;

    out.close();
}

void    test_swap_nonmember()
{
     long double              std_time, ft_time;
    /* log */
    std::ofstream        out;

    std::string const   file = "./Log_vector/log_test_swap_nonmember";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    
    /* product  vectors */
    int arr1[] = {1458, -98, 745, 62, 9, 52, 0, 22};
    std::vector<int>    std_v2, std_v1(5, 22);
    ft::vector<int>     ft_v2 ,ft_v1(5, 22);
    
    std_v2.assign(arr1, arr1 + 7); 
    ft_v2.assign(arr1, arr1 + 7); 

    out << printVectorAttributes(std_v1,ft_v1, "vectors_one ", 1);
    out << printVectorAttributes(std_v2,ft_v2, "vectors_two ", 1);
   
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    std::swap(std_v1, std_v2);
    std_time = std_time_calculator();

    
    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    ft::swap(ft_v1, ft_v2);
    ft_time = std_time_calculator();

    out <<GREEN" ================================ fater swap(v1, v2)==================="<<NORMAL"."   << std::endl << std::endl;
    out << printVectorAttributes(std_v1,ft_v1, "vectors_one ", 1);
    out << printVectorAttributes(std_v2,ft_v2, "vectors_two ", 1);

    std::cout << "*****************************Test swap(v1, v2)**********************************************." << std::endl;
    std::cout << NORMAL" Test swap(v1, v2)  \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << vector_is_equal(std_v2 , ft_v2)
            <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " << ft_time << " \t" << time_is_ok(ft_time, std_time)
                << std::endl;
out.close();
}

void    test_vector_get_allocator()
{
    std::ofstream        out;
    long double          std_time, ft_time;
   
    std::string const   file = "./Log_vector/allocator";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::string                result = GREEN"✔";


    //****************
    std::vector<int> myvector;
  int * p;
  unsigned int i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

  //std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p,5);


//*******

    std::vector<int> std_myvector;
    int*         std_p;
    unsigned int std_i;
    
    ft::vector<int> ft_myvector;
    int*            ft_p;
    unsigned int    ft_i;

    // allocate an array with space for 5 elements using vector's allocator:
    std_p = std_myvector.get_allocator().allocate(5);
    ft_p = ft_myvector.get_allocator().allocate(5);
     
    // construct values in-place on the array:
    clock_gettime(CLOCK_MONOTONIC, &std_start);
    for (std_i=0; std_i<5; std_i++) std_myvector.get_allocator().construct(&std_p[std_i], std_i);
    std_time = std_time_calculator();

    clock_gettime(CLOCK_MONOTONIC, &ft_start);
    for (ft_i=0; ft_i<5; ft_i++) ft_myvector.get_allocator().construct(&ft_p[ft_i], ft_i);
    ft_time = ft_time_calculator();

    out << "The allocated array std_contains:";
    for (std_i=0; std_i<5; std_i++) out << ' ' << std_p[std_i];
    out << '\n';

    out << "The allocated array std_contains:";
    for (ft_i=0; ft_i<5; ft_i++) out << ' ' << ft_p[ft_i];
    out << '\n';
    // destroy and std_deallocate:
    for (std_i=0; std_i<5; std_i++) std_myvector.get_allocator().destroy(&std_p[std_i]);
    std_myvector.get_allocator().deallocate(std_p,5);

    // destroy and ft_deallocate:
    for (ft_i=0; ft_i<5; ft_i++) ft_myvector.get_allocator().destroy(&ft_p[ft_i]);
    ft_myvector.get_allocator().deallocate(ft_p,5);

    for (std_i=0; std_i<5; std_i++) out << ' ' << std_p[i];
    {
        if (std_p[std_i] != ft_p[std_i])
        {
            result = REDD"✘";
        }
    }
    std::cout << "*****************************Test get_allocator**********************************************." << std::endl;
    std::cout << NORMAL"Test get_allocator \t\t\t\t\t\t\t\t\t" << result 
                <<"\t\t std_time  = " << std_time  << "\t\t ft_time = " 
                << ft_time << " \t" << time_is_ok(ft_time, std_time) << std::endl;  
}

void    test_vector(void)
{
    
    test_constructor();
    test_operator_assign();
	test_begin_end_rbegin_rend();
	test_size();
	/*test_max_size() and test_capacity() done in befor tests*/
    test_resize();
    test_empty();
    test_reserve();
	test_element_access();/*test_at();  test_front_back();*/
	test_assign();
	test_push_back();
	test_pop_back();
	test_insert();
	test_erase();
	test_swap();
	test_clear();
	test_vector_get_allocator();
	test_relational_operators();
	test_swap_nonmember();

}
