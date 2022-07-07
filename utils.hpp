
#ifndef UTILS_HPP
# define UTILS_HPP

# include <type_traits>

namespace ft
{
    /*The type T is enabled as member type enable_if::type
    ** if Cond is true. Otherwise, enable_if::type is not defined.
    ** Usefull when a particular condition is not met, in this case
    ** the member enable_if::type will ne be defined and attempting
    ** to compile using to should fail. (If this is use in template
    ** of a function, for exemple, like the type is not defined the 
    ** compiler will not compile and use the function).
    */
    template<bool Cond, class T = void>
    struct enable_if {};
 
    template<class T>
    struct enable_if<true, T> { typedef T type; };
    //******************************************************************************************
    //strauct of   is_integral 
    //******************************************************************************************
    template<bool is_integral, typename T>
    struct is_integral_r
    {
        typedef T type;
        static const bool valude = is_integral;
    };

    template<typename>
    struct is_integral_type : public is_integral_r<false,bool> { };

    template<>
    struct is_integral_type<bool>:public is_integral_r<true,bool> { };

    template<>
    struct is_integral_type<char>:public is_integral_r<true,char> { };

    template<>
    struct is_integral_type<signed char>: public is_integral_r<true,signed char> { };

    template<>
    struct is_integral_type<unsigned char>:public is_integral_r<true,unsigned char> { };

    template<>
    struct is_integral_type<int>: public is_integral_r<true,int> { };

     template<>
    struct is_integral_type<unsigned int>: public is_integral_r<true, unsigned int> { };

    template<>
    struct is_integral_type<short int>: public is_integral_r<true,short int> { };

    template<>
    struct is_integral_type<unsigned short int>: public is_integral_r<true,unsigned short int> { };

    template<>
    struct is_integral_type<long int>: public is_integral_r<true,long int> { };

    template<>
    struct is_integral_type<unsigned long int>:  public is_integral_r<true,unsigned long int> { };
    
    template<>
    struct is_integral_type<long long int>: public is_integral_r<true,long long int> { };

    template<>
    struct is_integral_type<unsigned long long int>: public is_integral_r<true, unsigned long long int> { };

    template <typename T>
        struct is_integral : public is_integral_type<T> { };





    //*******************************************************************************************
	// Pair
	//*******************************************************************************************

	template <class T1, class T2>
	struct pair 
    {
		typedef			T1			first_type;
		typedef			T2			second_type;

        first_type		first;
		second_type		second;

		pair() : first(), second() {}

		template <class U, class V>
		pair(const pair<U,V> &  pr): first(pr.first), second(pr.second) {}
		pair(const first_type & a, const second_type & b) : first(a), second(b) {}

		
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y) { return (pair<T1, T2>(x, y)); }


    /********************************************************************************************/
	// lexicographical_compare
    /*********************************************************************************************/

     template <typename  InputIterator1, typename InputIterator2>
     bool   lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
     {
        while(first1 != last1)
        {
            if(first2 == last2 || (*first1 < *first2))
                return false;
            if(*first2 < *first1)
                return true;
            ++first1;
            ++first2;    
        }
        return true;
     }

    //*******************************************************************************************
	// equal
	//********************************************************************************************/

} // namespace ft

    template <typename  InputIterator1, typename InputIterator2>
     bool   lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
     {
        while(first1 != last1)
        {
            if(first2 == last2 || (*first1 != *first2))
                return false;
            ++first1;
            ++first2;    
        }
        return true;
     }

#endif