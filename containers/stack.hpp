#ifndef STACK_HPP
#define STACK_HPP

#include "./vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		/* relational operator friend */
		template <class U, class V>
		friend bool operator==(const stack<U, V> &, const stack<U, V> &);
		template <class U, class V>
		friend bool operator!=(const stack<U, V> &, const stack<U, V> &);
		template <class U, class V>
		friend bool operator<(const stack<U, V> &, const stack<U, V> &);
		template <class U, class V>
		friend bool operator>(const stack<U, V> &, const stack<U, V> &);
		template <class U, class V>
		friend bool operator<=(const stack<U, V> &, const stack<U, V> &);
		template <class U, class V>
		friend bool operator>=(const stack<U, V> &, const stack<U, V> &);

	public:

		/* typedefs */
		typedef T value_type;
		typedef Container container_type;
		typedef typename container_type::size_type size_type;

		/* constructors */
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
		stack(const stack &other) : c(other.c) {}

		/* destructor */
		~stack(void) {}

		/* assignment operator */
		stack &operator=(const stack &other)
		{
			if (this != &other)
				c = other.c;
			return (*this);
		}
		
		bool empty(void) const
		{
			return (c.empty());
		}

		size_type size(void) const
		{
			return (c.size());
		}

		value_type &top(void)
		{
			return (c.back());
		}

		const value_type &top(void) const
		{
			return (c.back());
		}

		void push(const value_type &val)
		{
			c.push_back(val);
		}

		void pop(void)
		{
			c.pop_back();
		}

	protected:
		container_type c;
	};
	
	/* non relational operators */
	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
