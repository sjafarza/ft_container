#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>

# include "./header_utils.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class Vector
    {
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
         typedef standard_iterator< pointer, Vector >           iterator;                        
         typedef standard_iterator< const_pointer, Vector >     const_iterator;
         typedef reverse_iterator<iterator>                     reverse_iterator;
         typedef reverse_iterator< const_iterator>              const_reverse_iterator;

        
        
        // membre 
        protected:
            allocator_type      _alloc;
            pointer             _start;       /* an iterator pointing to first element in vectot */
            pointer             _end;                                                      
            size_type           _size;        /* len of vector */
            size_type           _capacity;    /* size of the storage space currentrl allocated != size of vector */
            //size_type           _g; /* _gold_tatio*/
        

       
        
        public:
        //*****************************************************************************************
        //*                                  Constrauctors                                        *
        //*****************************************************************************************
        explicit vector (const allocator_type& alloc = allocator_type()) :  /* exlicit : used to mark consts not implicitly convert types */
                _alloc(alloc), _start(u_nullptr), _end(u_nullptr), _size(0), _capacity(0) 
                {}


        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
                _alloc(alloc), _start(u_nullptr),_end(u_nullptr), _size(n), _capacity(n)
                {
                    _start = _alloc.allocate(n);
                    _end = _start;
                    while (--n)
                    {
                        _alloc.construct(_end, val);
                        _end++;
                    }
                }

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
            _alloc(alloc), _start(u_nullptr),_end(u_nullptr), _size(0), _capacity(0)
            {
               difference_type  n = 0;  /*   ????  */
               iterator         it = first;

               while(it != last)
               {
                 ++n;
                 ++it;
               }
               _start = _alloc.allocate(n);
               _end = _start + n; 
               _capcity = n;
            }


        Vector(Vector<T, Alloc> const&    other) :
             _alloc(other._alloc), _start(u_nullptr), _end(u_nullptr), _size(0), _capacity(0)
             {
                this->insert(this->begin(), other.begin(), other.end()); // insert() in Modifiers Member func */
             }
        //*****************************************************************************************
        //*                                  Deconstructors                                       *
        //*****************************************************************************************
        virtual ~Vector()
            {
                this->clear();
                _alloc.deallocate(_start, this->capacity());
            };

        //*****************************************************************************************
        //*                                 perator                                               *
        //*****************************************************************************************
        Vector&   operator = (const Vector& rhs)
           {
               if (*this == rhs)
                   return (*this);
               this->clear();
               /*this->insert(this->end(), rhs.begin(), rhs.end());
               return (*this)*/ 
           }

        // Iterators*********************************************************************
                iterator                begin() { return iterator(_start);};
                const_iterator          begin() const { return const_iterator(_start);};

                iterator                end() {return  iteratot (_end;);};
                const_iterator          end() const{ return const_iterator (_end;);};

                reverse_iterator        rbeing() {return reverse_iterator( end());};
                const_reverse_iterator  rbegin() const { return const_reverse_iterator( end());}; 

                reverse_iterator        rend() {return reverse_iterator(begin()); };
                const_reverse_iterator  rend() const { return const_reverse_iterator(begin());};

        //*****************************************************************************************
        //*                                 Capacity                                              *
        //*****************************************************************************************
        size_type size() const{ return (_size);};

        size_type max_size() const{ return (_alloc.max_size());

        void resize (size_type n, value_type val = value_type())
        {
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
            if (n > _capacity)
                reserve(n);
        }
        
        size_type capacity() const {return (_capacity);};

        bool empty() const{return (_size ? false : true );};
        
        void reserve (size_type n)
            {
                    if (n > _malloc.max_size())
                        throw std::length_error("n greater than vector::max_size()");
                    if(n > _capacity)
                    {
                        value_type*     tmp_start = alloc::allocate(n);
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
            };
        //*****************************************************************************************
        //*                                Element access                                         *
        //*****************************************************************************************
        reference       operator[] (size_type n) { return _start[n]; };

        const_reference operator[] (size_type n) const { return _start[n];};

        reference       back() {return _start[_size - 1]; };

        const_reference back() const { return _start[_size -1] ;};

                
        reference front(){ return (_start[0]); };

        const_reference front() const { return (_start[0])};


        reference        at (size_type n)
            { 
                std::stringstream ss;
                ss << "vector::_M_rang_chek: __n (which is " << n << ") >= this->size() (wich is " << _size << ")";
                if (n >= _size)
                    throw std::out_of_range(ss.rdbuf()->str());
                return  _start[n];
            };

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
            size_t  n = std::distance(fist, last);
        }

        void assign (size_type n, const value_type& val);

        iterator insert (iterator position, const value_type& val);

        void push_back (const value_type& val);

        void pop_back();

        iterator insert (iterator position, const value_type& val);

        void insert (iterator position, size_type n, const value_type& val);

        template <class InputIterator>
        void    insert (iterator position, InputIterator first, InputIterator last)
        {

        }

        iterator erase (iterator position);

        iterator erase (iterator first, iterator last);

        void swap (vector& x);

        void clear();
        
    };

    //*****************************************************************************************
    //*                                les fonctions non-membres                              *              *
    //***************************************************************************************** 
    template <class T, class Alloc>
    bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if(lhs._size != rhs._size)
            return falce;
        retun(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));    
    }

    template <class T, class Alloc>
    bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if(lhs._size != rhs._size)
            return true;
        retun( !(lhs == rhs));    
    }

    template <class T, class Alloc>
    bool operator <  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
    }

    template <class T, class Alloc>
    bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ((lhs < rhs) || (lhs == rhs));

    }

    template <class T, class Alloc>
    bool operator >  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
           return (!( lhs <= rhs)); 
    }

    template <class T, class Alloc>
    bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
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
