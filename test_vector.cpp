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
# define RED    "\033[1;31m"
# define GREEN  "\033[032m"

template <class T>
std::string vector_is_equal(const std::vector<T> & std_vector, const ft::vector<T> & ft_vector)
{
    typename std::vector<T>::const_iterator  st_it = std_vector.begin();
    typename ft::vector<T>::const_iterator   ft_it = ft_vector.begin();
    if(std_vector.capacity() != ft_vector.capacity()) /* != */
        return (RED"✘ \t\t Capacity");
    if(std_vector.size() != ft_vector.size())
        return (RED"✘ \t\t Size");
    if(std_vector.max_size() != ft_vector.max_size())
        return (RED"✘ \t\t Max_size");
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
    return (RED"✘ \t\tContent");  
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
            fs << "begin() = " << *(std_vector.begin() - 1) << "\t" << "end() = " <<*(std_vector.end() - 1)<< std::endl<< std::endl;
        if (idx == 2)
            fs << "rbegin() = " << *(std_vector.rbegin()) << "\t" << "rend() = " <<*(std_vector.rend() - 1)<< std::endl<< std::endl;
        



      fs  <<  "***" YELLOW"ft::vector" NORMAL"*******************************************************\n"
        <<"Content = " << print_vector(ft_vector) << std::endl
        << "Size = " << ft_vector.size() << "\t" << "Capacity = " << ft_vector.capacity() << "\t" << "Max_size = " << ft_vector.max_size()
        << std::endl << std::endl;
        if (idx == 1)
            fs  << "begin() = " << *(ft_vector.begin()) << "\t" << "end() = " << *(ft_vector.end() - 1) << std::endl << std::endl;
        if (idx == 2)
            fs << "rbegin() = " << *(std_vector.rbegin()) << "\t" << "rend() = " <<*(std_vector.rend() - 1)<< std::endl<< std::endl;

        fs << "*******************************************************************\n\n\n\n";
    return (fs.str());    

}

void    print_vector();
void    test_constructor()
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_constructor";
    if (mkdir("Log_vector", 0777) == -1)
        std::cerr << "Error : faild to creat directory Log_vector" << std::endl;
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    
    /* Detault constructor */
    std::vector<int>     std_v1;
    ft::vector<int>      ft_v1;
    out << printVectorAttributes(std_v1,ft_v1, "Test default constructor", 0);

    std::cout << "*****************************Test constructor***********************************************." << std::endl;
    std::cout << " test default constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;

    /* Detault pointer constructor */
    std::vector<int>*    std_pointer_default_v =  new std::vector<int>;
    ft::vector<int>*    ft_pointer_default_v =  new ft::vector<int>;
    out << printVectorAttributes( *std_pointer_default_v,*ft_pointer_default_v, "Test default pointer constructor", 0);
    std::cout << NORMAL " test default pointer constructor \t\t\t\t\t\t\t"<< vector_is_equal(*std_pointer_default_v, *ft_pointer_default_v) << std::endl;

    /* Fill constructor */
    std::vector<int>    std_v2(5);
    ft::vector<int>     ft_v2(5);
    out << printVectorAttributes(std_v2,ft_v2, "Test fill constructor", 0);

    /*Fill constructor size*/
    std::vector<int>    std_v3(5, 100);
    ft::vector<int>     ft_v3(5, 100);
    out << printVectorAttributes(std_v3,ft_v3, "Test fill constructor size", 0);
    std::cout << NORMAL " test fill constructor  size\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v3 , ft_v3) << std::endl;

    /*Range constructor */
    std::vector<int>    s_test(5, 7);
    ft::vector<int>     ft_test(5, 7);
    std::vector<int>    std_v4(s_test.begin() + 1, s_test.end() - 2);
    ft::vector<int>     ft_v4(ft_test.begin() + 1, ft_test.end() - 2);
    out << printVectorAttributes(std_v4,ft_v4, "Test range of another vector constructor", 0);
    std::cout << NORMAL " test range of another vector constructor \t\t\t\t\t\t"<< vector_is_equal(std_v4 , ft_v4) << std::endl;
    
    int range_array[] = { 15, 65397429, 1299, 965, 5 , 88, 9};
    std::vector<int>::iterator std_itr(&(range_array[1]));
    ft::vector<int>::iterator ft_itr(&(range_array[1]));

    std::vector<int>    std_arr_v4(std_itr , std_itr + 3);
    ft::vector<int>     ft_arr_v4(ft_itr , ft_itr + 3);
    out << printVectorAttributes(std_arr_v4,ft_arr_v4, "Test range of array constructor", 0);
    std::cout << NORMAL " test range of array constructor \t\t\t\t\t\t\t"<< vector_is_equal(std_arr_v4 , ft_arr_v4) << std::endl;

    /*Copy constructor */
    std::vector<int>    std_v5(s_test);
    ft::vector<int>     ft_v5(ft_test);
     out << printVectorAttributes(std_v5,ft_v5, "Test copy constructor", 0);
    std::cout << NORMAL " test copy  constructor \t\t\t\t\t\t\t\t"<< vector_is_equal(std_v5 , ft_v5) << std::endl;

    delete  ft_pointer_default_v;
    delete  std_pointer_default_v;
    out.close();
}

void    test_operator_assign(void)
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_operator_assign";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    std::vector<int>    std_ref(5, 731);
    ft::vector<int>     ft_ref(5, 731); 
    std::vector<int>     std_v = std_ref;
    ft::vector<int>      ft_v = ft_ref;
    out << printVectorAttributes(std_v,ft_v, "Test operatot assign", 0);
    std::cout << std::endl << NORMAL " test operator assign \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) << std::endl<< std::endl;
}    

void    test_begin_end_rbegin_rend()
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_begin_end";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    /*Iterator  begin() end ()*/
    int rang_array[] = {32, 66, 824, -2453, 0, 77};
    ft::vector<int>::iterator   ft_it(&rang_array[0]);
    std::vector<int>::iterator   std_it (&rang_array[0]);
    std::vector<int>     std_v(std_it ,std_it + 4);
    ft::vector<int>      ft_v (ft_it , ft_it + 4);
    out << printVectorAttributes(std_v,ft_v, "Test Iterator begin()  end()", 1);
    std::cout << "*****************************Test Iterator***********************************************." << std::endl;
    std::cout << NORMAL " test Iterator begin \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) && 
               *(std_v.begin()) == *(ft_v.begin()) && *(std_v.end()) == *(ft_v.end());
    std::cout << std::endl;    
   
    /* Reverse Iterator   begin() end ()*/
    out << printVectorAttributes(std_v,ft_v, "Test reverse Iterator rbegin() rend ()", 2);
    std::cout << NORMAL " test reverse Iterator rbegin ,rend \t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) << std::endl;

    /* Const Iterator   begin() end ()*/
    {
        int rang_array[] = {32, 66, 824, -2453, 0, 77};
        ft::vector<int>::const_iterator   ft_it(&rang_array[0]);
        std::vector<int>::const_iterator   std_it (&rang_array[0]);
        std::vector<int>     std_v(std_it + 1 ,std_it + 4);
        ft::vector<int>      ft_v (ft_it + 1, ft_it + 4);
        out << printVectorAttributes(std_v,ft_v, "Test Const  Iterator begin() end ()", 1);
        std::cout <<  NORMAL " test Const Iterator begin, end \t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) << std::endl;    
    
    /* Reverse const Iterator   begin() end ()*/
        out << printVectorAttributes(std_v,ft_v, "Test Const reverse Iterator rbegin() rend ()", 1);
        std::cout << NORMAL " test Const reverse Iterator, rbegin ,rend \t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) << std::endl;
    }
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
}

void    test_resize(void)
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_resize";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
    std::vector<int>     std_v1(10, 5);
    ft::vector<int>      ft_v1(10, 5);
    out << printVectorAttributes(std_v1,ft_v1, "fist definition", 0);

    std_v1.resize(4);
    ft_v1.resize(4);
    out << printVectorAttributes(std_v1,ft_v1, "After resize to 4 definition", 0);
    
    std_v1.resize(10);
    ft_v1.resize(10);
    out << printVectorAttributes(std_v1,ft_v1, "After resize to 12 size", 0);
    
    std::cout <<NORMAL " test for resize \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;
}

void    test_empty(void)
{
    /*std::ofstream        out;
    std::string const   file = "./Log_vector/log_empty()";
    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;*/

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
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t"<< RED"✘"<< std::endl;

            
        if(std_v2.empty() ==ft_v2.empty())
            std::cout <<NORMAL " test for empty() for vector(size)* \t\t\t\t\t\t\t"<< GREEN"✔"<< std::endl;
        else     
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t"<< RED"✘"<< std::endl;

        
        if(std_v3.empty() ==ft_v3.empty())
            std::cout <<NORMAL " test for empty() for Fill value(s, v)* \t\t\t\t\t\t"<< GREEN"✔" << std::endl;
        else
            std::cout <<NORMAL " test for empty() for  empty vector* \t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;       
}

void    test_reserve(void)
{
    std::vector<int> std_v(7, 11);
    ft::vector<int> ft_v(7, 11);

    std::vector<int> std_v1(1);
    ft::vector<int> ft_v1(1);

    std::vector<int>:: size_type   std_v_capacity= std_v.capacity();
    ft::vector<int>::size_type      ft_v_capacity= ft_v.capacity();
    
    std_v1.reserve(std_v_capacity + 50);
    ft_v1.reserve(ft_v_capacity + 50);
    
    std::vector<int>:: size_type    std_v1_capacity= std_v1.capacity();
    ft::vector<int>::size_type    ft_v1_capacity= ft_v1.capacity();
    std::cout << "*****************************Test reserv()***********************************************." << std::endl;
    if (std_v1_capacity == ft_v1_capacity)
        std::cout <<NORMAL " test for reserve* \t\t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl;
    else
        std::cout <<NORMAL " test for reserve* \t\t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
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
               std::cout <<NORMAL " test for operator [] \t\t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
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
               std::cout <<NORMAL " test for operator at \t\t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
               return ;
            }   
    }
    std::cout <<NORMAL " test for operator at \t\t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl;

    
    //front,  back
    out << "\n============================================================================\n\n";
    out << "std_arr_v4.front() = " << std_arr_v4.front() << "\t\t" << "ft_arr_v4.front() = " << ft_arr_v4.front()<< std::endl;
    if (std_arr_v4.front() != ft_arr_v4.front())
    {
        std::cout <<NORMAL " test for front() \t\t\t\t\t\t\t\t\t\t"<< RED"✘"<<  std::endl;
        return ;
    }

    out << "std_arr_v4.back() = " << std_arr_v4.back() << "\t" << "ft_arr_v4.back() = " << ft_arr_v4.back()<< std::endl;
    if (std_arr_v4.back() != ft_arr_v4.back())
    {
        std::cout <<NORMAL " test for back() \t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
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
        std::cout <<NORMAL " test for front() \t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
        return ;
    }

    out << "std_arr_v4.back() = " << std_arr_v4.back() << "\t\t" << "ft_arr_v4.back() = " << ft_arr_v4.back()<< std::endl;
    if (std_arr_v4.back() != ft_arr_v4.back())
    {
       std::cout <<NORMAL " test for back() \t\t\t\t\t\t\t\t\t\t"<< RED"✘"<< std::endl;
       return ;
    }
    std::cout <<NORMAL " test for front() back() \t\t\t\t\t\t\t\t"<< GREEN"✔" << std::endl;      
 }

 void   	test_assign()
 {
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_assign";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
        
    std::vector<int>    std_v1(2), std_v2,  std_v3;
    ft::vector<int>     ft_v1(2), ft_v2, ft_v3;

    std_v1.assign(7, 100);
    ft_v1.assign(7, 100); 
    
    out << printVectorAttributes(std_v1,ft_v1, "Test assign(n, val) ", 0);
    std::cout << "*****************************Test assign()***********************************************." << std::endl;
    std::cout << NORMAL" Test assign(n, val) \t\t\t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;  


    std_v2.assign(std_v1.begin() + 1, std_v1.end() - 1);
    ft_v2.assign(ft_v1.begin()+ 1, ft_v1.end() - 1);
    out << printVectorAttributes(std_v2,ft_v2, "Test assign(it_first,  it_last) ", 0);
    std::cout << NORMAL" Test assign(it_first,  it_last) \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;  
 
    int arr[] = {12, -4567654, 0, 10, 58};
    std_v3.assign(arr, arr + 3);
    ft_v3.assign(arr, arr + 3);
    out << printVectorAttributes(std_v3,ft_v3, "Test assign(it_first_arr,  it_last_arr) ", 0);
    std::cout << NORMAL" Test assign(it_first_arr,  it_last_arr) \t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;
 }

void    test_push_back()
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_push_back";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;
        
    std::vector<int>    std_v1, std_v2(45),  std_v3(5, 87);
    ft::vector<int>     ft_v1, ft_v2(45), ft_v3(5, 87);
    /*empty vector */
    out << printVectorAttributes(std_v1,ft_v1, "Test push_back() ", 0);
    std_v1.push_back(42); ft_v1.push_back(42);
    out << printVectorAttributes(std_v1,ft_v1, "After push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << "*****************************Test push_back()***********************************************." << std::endl;
    std::cout << NORMAL" Test push_back for empty vector \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;  
   
    /* vector fill size */
    out << printVectorAttributes(std_v2,ft_v2, "Test push_back() for vector(size) ", 0);
    std_v2.push_back(42); ft_v2.push_back(42);
    out << printVectorAttributes(std_v2,ft_v2, "After push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test push_back for vector fill size \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;  

    /* vector fill size and value */
    out << printVectorAttributes(std_v3,ft_v3, "Test push_back() for vector(size, val) ", 0);
    std_v3.push_back(42); ft_v3.push_back(42);
    out << printVectorAttributes(std_v3,ft_v3, "after push_back(42) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test push_back for vector fill size  and value\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;  

    
}

void    test_pop_back()
{
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
    std_v2.pop_back(); ft_v2.pop_back();
    out << printVectorAttributes(std_v2,ft_v2, "After pop_back() ", 0);
    out << std::endl << std::endl;
    std::cout << "*****************************Test pop_back()***********************************************." << std::endl;
    std::cout << NORMAL" Test pop_back for vector rang const  \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;

    out << printVectorAttributes(std_v1,ft_v1, "Test pop_back() for vector(n, v) ", 0);
    std_v1.pop_back(); ft_v1.pop_back();
    out << print_vector(ft_v1);
    out << print_vector(std_v1);
    out << printVectorAttributes(std_v1,ft_v1, "After pop_back() ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test pop_back for vector(n, v)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;
}

void test_erase()
{
    
}

void    test_insert()
{
    std::ofstream        out;
    std::string const   file = "./Log_vector/log_test_insert";

    out.open(file.c_str(), std::fstream::trunc | std::ostream::out);
    if(!out.is_open())
        std::cerr << "Error : faild to open file" << std::endl;

    int arr[] = {12, -4567654, 0, 10, 58};
    std::vector<int>    std_v, std_v1(5, 99),  std_v2(1, 66);
    ft::vector<int>     ft_v , ft_v1(5, 99), ft_v2(1, 66);
    out << printVectorAttributes(std_v,ft_v, "Test insert(it, value) ", 0);
    std_v.insert(std_v.begin(), 22);
    ft_v.insert(ft_v.begin(), 22);
    out << printVectorAttributes(std_v,ft_v, "After insert(begin, 22) ", 0);
    out << std::endl << std::endl;
     std::cout << "*****************************Test insert()***********************************************." << std::endl;
    std::cout << NORMAL" Test insert(it, val)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v , ft_v) << std::endl;

    out << printVectorAttributes(std_v1,ft_v1, "Test insert(it, size, value) ", 0);
    std_v1.insert(std_v1.begin() + 2  , 15, 300);
    ft_v1.insert(ft_v1.begin() + 2 , 15, 300);
    out << printVectorAttributes(std_v1,ft_v1, "After insert(begin+1, 2, 300) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test insert(it, size, val)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v1 , ft_v1) << std::endl;
    
    out << printVectorAttributes(std_v2,ft_v2, "Test insert(it, it_first, it_end) ", 0);
    out << "arr[] = {12, -4567654, 0, 10, 58}" << std::endl;
    std_v2.insert(std_v2.begin() + 1, arr, arr + 3);
    ft_v2.insert(ft_v2.begin() + 1,arr, arr + 3); 
    out << printVectorAttributes(std_v2,ft_v2, "After insert(begin, arr, arr + 3) ", 0);
    out << std::endl << std::endl;
    std::cout << NORMAL" Test insert(it, arr, arr + n)  \t\t\t\t\t\t\t"<< vector_is_equal(std_v2 , ft_v2) << std::endl;
    

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
	test_element_access();
	/*test_at();
	test_front_back();*/
	test_assign();
	test_push_back();
	test_pop_back();
	test_insert();
	test_erase();
	/*test_swap();
	test_clear();
	test_get_allocator();
	test_relational_operators();
	test_swap_nonmember();*/

}
