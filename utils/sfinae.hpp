
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

    //***************************************************************************************
    //                               enable_if
    //***************************************************************************************

    template<bool B, class T = void>
    struct enable_if {};
 
    template<class T>
    struct enable_if<true, T> { typedef T type; };


    //***************************************************************************************
    //                               is_integral
    //***************************************************************************************

    template <typename T>
	struct is_integral
	{
		const static bool value = false;
	};

	template <>
	struct is_integral<char>
	{
		const static bool value = true;
	};

	template <>	
	struct is_integral<signed char>
	{
		const static bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		const static bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		const static bool value = true;
	};




	template <>
	struct is_integral<int>
	{
		const static bool value = true;
	};

	template <>
	struct is_integral<short int>
	{
		const static bool value = true;
	};

	template <>
	struct is_integral<long int>
	{
		const static bool value = true;
	};

	template <>
	struct is_integral<long long int>
	{
		const static bool value = true;
	};



    template <>
	struct is_integral<unsigned int>
	{
		const static bool value = true;
	};

    template <>
	struct is_integral<unsigned short int>
	{
		const static bool value = true;
	};

    template <>
	struct is_integral<unsigned long int>
	{
		const static bool value = true;
	};

    template <>
	struct is_integral<unsigned long long int>
	{
		const static bool value = true;
	};

} // namespace ft

#endif