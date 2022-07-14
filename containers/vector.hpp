#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <sstream>
# include <cmath>
# include <iostream>
# include <iterator>
# include <memory>
# include <sstream>
# include <stdexcept>

# include "./header_utils.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
        // typedef

         typedef Alloc                                          allocator_type;
         typedef std::size_t                                    size_type;
         typedef T                                              value_type;
         typedef T*                                             pointer;
         typedef T&                                             reference;
       
         typedef typename Alloc::const_reference                const_reference;
         typedef typename  Alloc::const_pointer                 const_pointer;
         typedef typename   std::ptrdiff_t                      difference_type; 

        // Iterators
         typedef T*                                                iterator;                         
         typedef const T*                                          const_iterator; 
         typedef ft::reverse_iterator<iterator>                   reverse_iterator;
         typedef ft::reverse_iterator< const_iterator>            const_reverse_iterator;

        
        
        // membre 
        protected:
            allocator_type      _alloc;
            pointer             _start;       /* an iterator pointing to first element in vectot */
            pointer             _end;                                                      
            size_type           _size;        /* len of vector */
            size_type           _capacity;    /* size of the storage space currentrl allocated != size of vector */
           
            void                _shift_right(iterator positon, size_type n)
            {
                if(empty())
                    return ;
                size_type   k = _end - &(*positon);
                for(size_type i = 0 ; i <= k ; ++i)
                {
                    _alloc.construct(_end + n - i, *(_end - i) );
                    _alloc.destroy(_end + i);
                }
                //_size += n;
                _end += n;
                /*size_type   k = &(*position) - _start;
                for(size_type i = _size - 1 ; i >=  k ; --i)
                {
                    _alloc.construct(&_start[i + n], _start[i]);
                    _alloc.destroy(&start[i]);
                }*/  
            }

            void                _shif_left(iterator positon, size_type n)
            {
                if(empty())
                    return ;
                size_type   k = &(*positon) - _start;
                for(size_type i = 1 ; i <= k ; ++i)
                {
                    _alloc.construct(&_start[k - i] + n , _start[k - i]);
                    _alloc.destroy(_start + k - i);
                }
                _start -= n;
               // _size += n;
               /* size_type   k = &(*position) - &(*begin());
                for(size_type i = k ; i < _size - n ; ++i)
                {
                    _alloc.construct(&_start[i], _size[i + n]);
                    _alloc.destroy(&_start[i + n]);
                } */         
            }


        public:
        //*****************************************************************************************
        //*                                  Constrauctors                                        *
        //*****************************************************************************************
        explicit vector (const allocator_type& alloc = allocator_type()) :  /* exlicit : used to mark consts not implicitly convert types */
                _alloc(alloc), _start(NULL), _end(NULL), _size(0), _capacity(0) 
                {}


        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
                _alloc(alloc), _start(NULL),_end(NULL), _size(n), _capacity(n)
                {
                    _start = _alloc.allocate(n);
                    _end = _start;
                    while (n--)
                    {
                        _alloc.construct(_end, val);
                        _end++;
                    }
                }

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value , InputIterator>::type* = NULL):
            _alloc(alloc), _start(NULL),_end(NULL), _size(0), _capacity(0)
            {
                size_type   n = std::distance(first, last);
                _start = _alloc.allocate(n);
                _size = n;
                _capacity = n;
                _end = _start + n;

                for(size_type i = 0; i < n ; ++i)
                    _alloc.construct(&_start[i], *(first + i));

            }

        vector (const vector& other):
             _alloc(other._alloc), _start(NULL), _end(NULL), _size(other._size), _capacity(other._capacity)
             {
                this->insert(this->begin(), other.begin(), other.end()); 
             }

        //*****************************************************************************************
        //*                                  Deconstructors                                       *
        //*****************************************************************************************
        virtual ~vector()
            {
                this->clear();
                _alloc.deallocate(_start, this->capacity());
            }

        //*****************************************************************************************
        //*                                 perator                                               *
        //*****************************************************************************************
        vector&   operator = (const vector& rhs)
           {
               if (*this == rhs)
                   return (*this);
               this->clear();
               this->insert(this->end(), rhs.begin(), rhs.end());
               return (*this);
           }

        // Iterators*********************************************************************
                iterator                begin() { return iterator(_start);}
                const_iterator          begin() const { return const_iterator(_start);}

                iterator                end() {return  iterator (_end);}
                const_iterator          end() const{ return const_iterator (_end);}

                reverse_iterator        rbeing() {return reverse_iterator( end());}
                const_reverse_iterator  rbegin() const { return const_reverse_iterator( end());}

                reverse_iterator        rend() {return reverse_iterator(begin()); }
                const_reverse_iterator  rend() const { return const_reverse_iterator(begin());}

        //*****************************************************************************************
        //*                                 Capacity                                              *
        //*****************************************************************************************
        size_type size() const{ return (_size);}

        size_type max_size() const{ return (_alloc.max_size());}

        size_type capacity() const {return (_capacity);}

        bool empty() const{return (_size ? false : true );}
        
        void reserve (size_type n)
            {
                    if (n > max_size())
                        throw std::length_error("n greater than vector::max_size()");
                    if(n > _capacity)
                    {
                        value_type*     tmp_start = _alloc.allocate(n);
                        for(size_type i = 0; i < n; ++i)
                        {
                            _alloc.construct(&tmp_start[i], _start[i]);
                            _alloc.destroy(&_start[i]);
                        }
                        if(_start)
                            _alloc.deallocate(_start, _capacity);
                        _start = tmp_start;
                        _end = _start + n;
                        _capacity = n;
                       _size = n;
                    }
            }

        void resize (size_type n, value_type val = value_type())
        {
             if (n > _capacity)
                reserve(n);
            if(n < _size)
                while(++n < _size)
                {
                     _alloc.destroy(_end);
                     _end--;   
                }
            else if (n > _size)
                while(--n > _size)
                {
                     _alloc.construct(_end, (val ? val : NULL));
                     _end++;   
                }
           
        }

        
        //*****************************************************************************************
        //*                                Element access                                         *
        //*****************************************************************************************
        reference       operator[] (size_type n) { return _start[n]; };

        const_reference operator[] (size_type n) const { return _start[n];}

        reference       back() {return _start[_size - 1]; }

        const_reference back() const { return _start[_size -1] ;}

                
        reference front(){ return (_start[0]); }

        const_reference front() const { return (_start[0]);}


        reference        at (size_type n)
            { 
                std::stringstream ss;
                ss << "vector::_M_rang_chek: __n (which is " << n << ") >= this->size() (wich is " << _size << ")";
                if (n >= _size)
                    throw std::out_of_range(ss.rdbuf()->str());
                return  _start[n];
            }

        const_reference at (size_type n) const
            { 
                std::stringstream ss;
                ss << "vector::_M_rang_chek: _n (which is " << n << ") >= this->size() (wich is " << _size << ")";
                if (n >= _size)
                    throw std::out_of_range(ss.rdbuf()->str());
                return  _start[n];
            }

        //*****************************************************************************************
        //*                                Modifiers                                              
        //***************************************************************************************** 
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
            size_t  n = std::distance(first, last);
            if(n > _capacity)
                reserve(n);
            for(size_type  i = 0; i < _size; ++i)
                _alloc.destroy(&_start[i]);
            _size = n;    
            for(size_type   i = 0 ; i < n ; ++i)
                _alloc.construct(&_start[i], *first++);
            _end = _start + n;    

        }

        void assign (size_type n, const value_type& val)
        {
            if(n > _capacity)
                reserve(n);
            for(size_type  i = 0; i < _size; ++i)
                _alloc.destroy(&_start[i]);
            _size = n;    
            for(size_type   i = 0 ; i < n ; ++i)
                _alloc.construct(&_start[i], val);
            _end = _start + n;           
        }

        void push_back (const value_type& val)
        {
            if(_size + 1 > _capacity)
                reserve(_size + 1);
            _size++;
            _alloc.construct(_end, val);
            _end++;    
        }

        void    pop_back()
        {
            _alloc.destroy(_end);
            _size--;

        }

        iterator insert (iterator position, const value_type& val)
        {
            iterator    r;
            size_type   len = &(*position) - _start;
            if(1 + _size > _capacity)
                reserve (1 + _size);
            _shif_rigth(position , 1 );
            _alloc.constrauctors(&(*position), val);
            _size++;
            return (iterator(_start + len));

        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            if(n + _size > _capacity)
                reserve(n + _size);   
            _shift_right(position, n);
            for(size_type i = 0 ; i < n ; ++i)
                _alloc.construct(&(*position)+ i , val);
            _size += n;      
        }

        template <class InputIterator>
        void    insert (iterator position, InputIterator first, InputIterator last,
                        typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
            size_type n = std::distance(first, last);
            if (n + _size > _capacity)
                reserve(n + _size);   
            _shift_right(position, n);
            for(size_type i = 0 ; i < n  ; i++)
                _alloc.construct(&(*position) + i  , *(first + i));
            _size += n;                  
        }

        iterator erase (iterator position)
        {
            size_type  i = &(*position) - _start;
           _alloc.destroy(&_start[i]);
           _shift_left(position, 1);
           _size--;
           //_start++;  it before change in _shift_left
           return iterator(_start[i]);
        }

        iterator erase (iterator first, iterator last)
        {
            size_type  i = &(*first) - _start;
            size_type   n = std::distance(first, last);
            iterator    it = first;
            while(it != last)
            {
                _alloc.destroy(it);
                ++it;
            }
            _shif_left(first , n);
            _size -= n;
           // _end -= n;
            return iterator(_start[i]);
        }

        void swap (vector& x)
        {
            pointer     tmp_start = _start;
            pointer     tmp_end = _end;
            size_type   tmp_capacity = _capacity;
            size_type   tmp_size = _size;

            _start = x._start;
            _end = x._end;
            _size = x._size;
            _capacity = x._capacity;

            x._start = tmp_start;
            x._end = tmp_end;
            x._size = tmp_size;
            x._capacity = tmp_capacity;
        }

        void clear()
        {
            for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_start[i]);
			_size = 0;
        }
     //*****************************************************************************************
     //*                               Allocator                                               *
     //***************************************************************************************** 
     allocator_type get_allocator() const
     {
        return (_alloc);
     }

    };

    //*****************************************************************************************
    //*                                les fonctions non-membres                              *    
    //***************************************************************************************** 
    template <class T, class Alloc>
    bool operator == (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
    {
        if(lhs._size != rhs._size)
            return false;
        retun(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));    
    }

    template <class T, class Alloc>
    bool operator != (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        if(lhs._size != rhs._size)
            return true;
        retun( !(lhs == rhs));    
    }

    template <class T, class Alloc>
    bool operator <  (const vector<T,Alloc> & lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ((lhs < rhs) || (lhs == rhs));

    }

    template <class T, class Alloc>
    bool operator >  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
           return (!( lhs <= rhs)); 
    }

    template <class T, class Alloc>
    bool operator >= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T> 
    void swap (T& a, T& b)
    {
      T c(a); a=b; b=c;  
    }
} // fin namespase ft

#endif
