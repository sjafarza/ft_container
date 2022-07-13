#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
//# include "random_access_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        typedef Iterator    iterator_type;
        typedef typename    iterator_traits<Iterator>::iterator_category	iterator_category;
        typedef typename    iterator_traits<Iterator>::value_type           value_type;
        typedef typename    iterator_traits<Iterator>::difference_type      difference_type;
        typedef typename    iterator_traits<Iterator>::pointer              pointer;
        typedef typename    iterator_traits<Iterator>::reference            reference;

        private:
            iterator_type   _base;    

        public:
        //*****************************************************************************************
        //*                                  Constrauctors                                        *
        //*****************************************************************************************
         
        reverse_iterator() : _base(Iterator()) {}

        explicit reverse_iterator (iterator_type it): _base(it) {}

        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}

        //*****************************************************************************************
        //*                                  bases                                                *
        //*****************************************************************************************

        iterator_type base() const {return (_base);}

        //*****************************************************************************************
        //*                                  operators                                            *
        //*****************************************************************************************

        reference operator * () const
        {
            Iterator    tmp = _bas;
            retun(*(--tmp));
        }

        reverse_iterator operator + (difference_type n) const
        {
           reverse_iterator   tmp = *this;
           tmp -= n;
           return (tmp);
        }

        reverse_iterator& operator ++ ()
        {
            --(_bas);
            return (*this);
        }

        reverse_iterator  operator ++ (int)
        {
            reverse_iterator temp = *this;
            ++(*this);
            return temp;
        }

        reverse_iterator& operator += (difference_type n)
        {
            _bas -= n;
            return (*this);
        }


        reverse_iterator operator - (difference_type n) const
        {
            reverse_iterator   tmp = *this;
            tmp += n;
            return (tmp);
        }

        reverse_iterator& operator --()
        {
            ++(_bas);
            return (*this);
        }

        reverse_iterator  operator -- (int)
        {
            reverse_iterator temp = *this;
            --(*this);
            return temp;
        }

        reverse_iterator& operator -= (difference_type n)
        {
            _bas += n;
            return (*this);
        }

        pointer operator -> () const { return (&(operator *())); }

        reference operator [] (difference_type n) const
        {
            return (*(_bas - n - 1));
        }
    };
    //*****************************************************************************************
    //*                                les fonctions non-membres                              *              *
    //*****************************************************************************************

    template <class Iterator>
    bool operator == (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>
    bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <class Iterator>
    bool operator <  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <class Iterator>
    bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <class Iterator>
    bool operator >  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <class Iterator>
    bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator + (
        typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n)
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator - (
        const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return((lhs.base() - rhs.base()));
    }


} // namespace ft

#endif