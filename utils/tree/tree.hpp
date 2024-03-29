
#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <iomanip>
#include "tree_iterator.hpp"
#include "../../header_utils.hpp"


#define BLACK false
#define RED true

// ref https://www.programiz.com/dsa/insertion-in-a-red-black-tree

namespace ft
{
	template <class T>
	struct _rb_node
	{
		typedef T 	value_type;
		_rb_node 	*parent;
		_rb_node 	*left;
		_rb_node 	*right;
		bool 		color;
		T 			data;
		_rb_node(T const &data) : data(data) {}
	};

	template <class T, class Compare, class Allocator = std::allocator<_rb_node<T> > >
	class _rb_tree
	{
	public:
		// typedef

		typedef Compare 								compare;
		typedef Allocator 								allocator;
		typedef T 										value_type;
		typedef size_t 									size_type;
		typedef _rb_node<value_type> 					node;
		typedef node*									node_ptr;
		typedef std::ptrdiff_t 							difference_type;
		typedef ft::tree_iterator<node> 				iterator;
		typedef ft::tree_iterator<node> 				const_iterator;
		typedef ft::reverse_iterator<iterator> 			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		private:
		node_ptr root;
		node_ptr NIL;		  	//sentinel
		compare _compare;	  	// used to compare nodes
		allocator _alloc; 		// used to allocate nodes
		size_type _size;	  	// number of nodes in the tree (to have O(1) size())


		public:

		// constructors
		_rb_tree(allocator alloc = allocator()) : _compare(compare()), _size(0)
		{
			_alloc = alloc;

			NIL = _alloc.allocate(1);
			_alloc.construct(NIL, value_type());
			NIL->parent = NIL;
			NIL->left = NIL;
			NIL->right = NIL;
			NIL->color = BLACK;
			root = NIL;
		}

		_rb_tree(_rb_tree const &other)
		{
			_alloc = other._alloc;
			_compare = other._compare;
			_size = other._size;
			NIL = _alloc.allocate(1);
			NIL->parent = NIL;
			NIL->left = NIL;
			NIL->right = NIL;
			NIL->color = BLACK;

			root = NIL;
			other.print();
			_recursive_copy(*this, other.root, other.NIL);
		}

		~_rb_tree()
		{
			clear();
			_alloc.destroy(NIL);
			_alloc.deallocate(NIL, 1);
		}

		// iterators
		iterator begin()
		{
			return iterator(_minimum(root), root, NIL);
		}

		const_iterator begin() const
		{
			return const_iterator(_minimum(root), root, NIL);
		}

		iterator end()
		{
			return iterator(NIL, root, NIL);
		}

		const_iterator end() const
		{
			return const_iterator(NIL, root, NIL);
		}

		reverse_iterator rbegin()
		{
			iterator it = end();
			return reverse_iterator(it);
		}

		const_reverse_iterator rbegin() const
		{
			const_iterator it = end();
			return const_reverse_iterator(it);
		}

		reverse_iterator rend()
		{
			iterator it = begin();
			return reverse_iterator(it);
		}

		const_reverse_iterator rend() const
		{
			const_iterator it = begin();
			return const_reverse_iterator(it);
		}

		_rb_tree &operator=(_rb_tree const &other)
		{
			clear();
			_recursive_copy(*this, other.root, other.NIL);
			return *this;
		}

		iterator find(value_type const &value)
		{
			node_ptr found = _find_node(value);

			if (!found)
				return end();
			else
				return iterator(found, root, NIL);
		}

		const_iterator find(value_type const &value) const
		{
			node_ptr found = _find_node(value);

			if (!found)
				return end();
			else
				return iterator(found, root, NIL);
		}

		ft::pair<iterator, bool> insert(value_type const &value)
		{
			node_ptr n = _new_node(value);

			ft::pair<node_ptr, bool> r = _insert_recursive(root, n);

			if (r.second)
			{
				_size++;
				if (n->parent == NIL)
					n->color = BLACK;
				else
					_insert_fixup(n);
				//search for new root
				root = n;
				while (root->parent != NIL)
					root = root->parent;
				return ft::make_pair(iterator(n, root, NIL), true);
			}
			else
			{
				_alloc.destroy(n);
				_alloc.deallocate(n, 1);
				return ft::make_pair(iterator(r.first, root, NIL), false);
			}
		}

		iterator insert(iterator hint, const value_type &value)
		{
			node_ptr next = _next(hint.node);

			// check if hint is valid

			if (_compare(*hint, value) && _compare(value, next->data))
			{
				node_ptr n = _new_node(value);

				ft::pair<node_ptr, bool> r = _insert_recursive(hint.node, n);
				_size++;
				return iterator(r.first, root, NIL);
			}
			else
				return insert(value).first;
		}

		size_type erase(value_type const &value)
		{
			node_ptr n = _find_node(value);

			if (n)
			{
				_delete_node(n);
				return (1);
			}
			else
				return (0);
		}

		void erase(iterator pos)
		{
			if (pos.node != NIL)
				_delete_node(pos.node);
		}

		void clear()
		{
			_recursive_clear(root);
			root = NIL;
			_size = 0;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		void swap(_rb_tree &other)
		{
			std::swap(_alloc, other._alloc);
			std::swap(_compare, other._compare);
			std::swap(_size, other._size);
			std::swap(NIL, other.NIL);
			std::swap(root, other.root);
		}

		iterator lower_bound(const value_type &value)
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (_compare(value, it.node->data)
					|| _compare(it.node->data, value) == 0)
					return it;
			}
			return end();
		}

		const_iterator lower_bound(const value_type &value) const
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (_compare(value, it.node->data)
					|| _compare(it.node->data, value) == 0)
					return it;
			}
			return end();
		}

		iterator upper_bound(const value_type &value)
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (_compare(value, it.node->data))
					return it;
			}
			return end();
		}

		const_iterator upper_bound(const value_type &value) const
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (_compare(value, it.node->data))
					return it;
			}
			return end();
		}

		void print(node *p = NULL, int indent = 0) const
		{
			if (p == NULL)
				p = root;
			if (p != NIL)
			{
				if (p->right != NIL)
				{
					print(p->right, indent + 4);
				}
				if (indent)
				{
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right != NIL)
					std::cout << " /\n"
							  << std::setw(indent) << ' ';
				if (p->color == RED)
					std::cout << "\033[0;31m";
				std::cout << p->data << "\n ";
				std::cout << "\033[0m";
				if (p->left != NIL)
				{
					std::cout << std::setw(indent) << ' ' << " \\\n";
					print(p->left, indent + 4);
				}
			}
		}

	
		private:
		// new node
		node*	_new_node(value_type const &data)
		{
			node *node = _alloc.allocate(1);
			_alloc.construct(node, data);
			node->color = RED;
			node->left = node->right = NIL;
			node->parent = NIL;
			return node;
		}

		node_ptr _grand_parent(node_ptr const node) const
		{
			node_ptr grand_parent = node->parent->parent;
			return grand_parent;
		}

		node_ptr _sibling(node_ptr const node) const
		{
			node_ptr parent = node->parent;
			if (node == parent->left)
				return parent->right;
			else
				return parent->left;
		}

		node_ptr _uncle(node_ptr const node) const
		{
			node_ptr grand_parent = _grand_parent(node);
			return _sibling(grand_parent);
		}

		// rotate left
		void _rotate_left(node_ptr x)
		{
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != NIL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NIL)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		// rotate right
		void _rotate_right(node_ptr x)
		{
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != NIL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NIL)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		// insert do not allow duplicates
		// return the new node or the node that already exists
		ft::pair<node_ptr, bool> _insert_recursive(node_ptr root, node_ptr n)
		{
			if (root != NIL && _compare(n->data, root->data))
			{
				if (root->left != NIL)
					return _insert_recursive(root->left, n);
				else
					root->left = n;
			}
			else if (root != NIL && _compare(root->data, n->data))
			{
				if (root->right != NIL)
					return _insert_recursive(root->right, n);
				else
					root->right = n;
			}
			else if (root != NIL)
				return ft::make_pair(root, false);
			n->parent = root;
			n->color = RED;
			n->left = n->right = NIL;
			return ft::make_pair(n, true);
		}

		// insert fixup
		void _insert_fixup(node_ptr k)
		{
			node_ptr u;

			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rotate_right(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_left(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_rotate_left(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_right(k->parent->parent);
					}
				}
				if (k == root)
					break;
			}
			root->color = BLACK;
		}

		node_ptr _find_node(value_type const &data) const
		{
			node_ptr current = root;
			while (current != NIL)
			{
				if (_compare(data, current->data))
					current = current->left;
				else if (_compare(current->data, data))
					current = current->right;
				else
					return current;
			}
			return NULL;
		}

		void _transplant(node_ptr u, node_ptr v)
		{
			if (u->parent == NIL)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		node_ptr _minimum(node_ptr x) const
		{
			while (x->left != NIL)
				x = x->left;
			return x;
		}

		node_ptr _maximum(node_ptr x) const
		{
			while (x->right != NIL)
				x = x->right;
			return x;
		}

		void _delete_node(node_ptr z)
		{
			node_ptr y = z;
			node_ptr x;
			bool y_original_color = y->color;
			if (z->left == NIL)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == NIL)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = _minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			_size--;
			if (y_original_color == BLACK)
				_delete_fixup(x);
		}

		void _delete_fixup(node_ptr x)
		{
			node_ptr s;
			while (x != root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							_rotate_right(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						_rotate_left(x->parent);
						x = root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == BLACK && s->left->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							_rotate_left(s);
							s = x->parent->left;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						_rotate_right(x->parent);
						x = root;
					}
				}
			}
			x->color = BLACK;
		}

		void _recursive_clear(node_ptr x = NULL)
		{
			if (x == NULL)
				x = root;
			if (x != NIL)
			{
				_recursive_clear(x->left);
				_recursive_clear(x->right);
				_alloc.destroy(x);
				_alloc.deallocate(x, 1);
			}
		}

		void _recursive_copy(_rb_tree &dst, node_ptr x, node_ptr x_nil)
		{
			if (x != x_nil)
			{
				_recursive_copy(dst, x->left, x_nil);
				dst.insert(x->data);
				_recursive_copy(dst, x->right, x_nil);
			}
		}

		node_ptr _prev(node_ptr node) const
		{
			node_ptr previous = NIL;

			if (node->left != NIL)
				return _minimum(node->left);
			previous = node->parent;
			while (previous != NIL && node == previous->left)
			{
				node = previous;
				previous = previous->parent;
			}
			return previous;
		}

		//find the next node in the tree
		node_ptr _next(node_ptr node) const
		{
			node_ptr next = NIL;

			if (node->right != NIL)
				return _minimum(node->right);

			next = node->parent;
			while (next != NIL && node == next->right)
			{
				node = next;
				next = next->parent;
			}
			return next;
		}
	};
}

#endif
