#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
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

    }


}// namespace ft

#endif
