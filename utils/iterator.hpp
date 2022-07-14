#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
    /*
    ** @brief Validity of an iterator from is tag.
    ** This is the base struct for all is_..._iterator_tag.
    ** A boolean is defined by the template and saved in
    ** structure. Type too.
    */
    template <bool is_valid, typename T>
        struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };
    
    /*
    ** @brief Basic to check if the typename given
    ** is an input_iterator. Based on valid_iterator_tag_res.
    ** In this if the typename is not from the possible
    ** input iterator form, validity is set to false.
    */
    template <typename T>
        struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

    /* Check is_input_iterator_tagged from ft::random_access_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::bidirectional_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::forward_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::input_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };


    /*
    ** @brief This will return a structure
    ** that contain a boolean "value" true if the
    ** iterator given is tagged with a ft iterator
    ** tag, otherwise "value" is false.
    */
    template <typename T>
        struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    
    /* Check is_ft_iterator_tagged from ft::random_access_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::bidirectional_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::input_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::output_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::output_iterator_tag>
            : public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

    //*******************************************************************************************************************************

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template <class T>
    class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category; 
    
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;

        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;

    };


}

*/
#endif
