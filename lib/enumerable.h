#pragma once

#include <iostream>
#include <stdint.h>
#include <exception>

template <class T>
class Enumerable
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Class Node									////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	template <class U>
	class Node
	{
	private:
		T * val_;
		Node * next_;
		Node * last_;

	public:
		//////////////////////////////////////////////////////////////////////////
		// constructors
		//////////////////////////////////////////////////////////////////////////
		Node() : val_(nullptr), next_(nullptr), last_(nullptr) {};
		Node(const T & val) : val_(new T(val)), next_(nullptr), last_(nullptr) {};
		Node(const Node & node) { copy_data(node); }
		void operator=(const Node & node) { copy_data(node); }

		~Node()
		{
			delete val_;
			next_ = nullptr;
			last_ = nullptr;
		}

	private:
		// This function is used to copy a node data
		void copy_data(const Node & node)
		{
			val_ = new T(&node->val_);

			Node * last_next = this;
			Node * next = node.next_;
			Node * copy_next = next_;
			while (next != nullptr)
			{
				copy_next = new Node(next->val_);
				copy_next->last_ = last_next;
				last_next = copy_next;
				copy_next = copy_next->next_;
				next = next->next_;
			}

			Node * next_last = this;
			Node * last = node.last_;
			Node * copy_last = last_;
			while (last != nullptr)
			{
				copy_last = new Node(last->val_);
				copy_last->next_ = next_last;
				next_last = copy_last;
				copy_last = copy_last->last_;
				last = last->last_;
			}
		};

	public:
		//////////////////////////////////////////////////////////////////////////
		// Getters
		//////////////////////////////////////////////////////////////////////////
		T & get_val() { return *val_; }
		const T & get_val() const { return *val_; }
		Node & get_next() { return *next_; }
		Node & get_last() { return *last_; }

		//////////////////////////////////////////////////////////////////////////
		// Setters
		//////////////////////////////////////////////////////////////////////////
		// val setters
		Node & set_val(const T & val) { val_ = new T(val); return *this; };

		// next setters
		Node & set_next(Node * node) { next_ = node; node->last_ = this; return *this; }
		Node & set_next(const T & val)
		{
			Node * next = new Node(val);
			Node * ancient_next = next_;
			next_ = next;
			next_->last_ = this;
			next_->next_ = ancient_next;
			ancient_next->last_ = next_;
			return *this;
		}

		T remove_next()
		{
			if (next_ != nullptr)
			{
				Node * node = next_;
				T val = node->get_val();
				next_ = next_->next_;
				next_->last_ = this;
				delete node;
				return val;
			}
			throw std::out_of_range("No element to delete before the first one");
		}

		// last setters
		Node & set_last(Node * node) { last_ = node; node->next_ = this; return *this; }
		Node & set_last(const T & val)
		{
			Node * last = new Node(val);
			Node * ancient_last = last_;
			last_ = last;
			last_->next_ = this;
			last_->last_ = ancient_last;
			ancient_last->next_ = last_;
			return *this;
		}

		T remove_last()
		{
			if (last_ != nullptr)
			{
				Node * node = last_;
				T val = node->get_val();
				last_ = last_->last_;
				last_->next_ = this;
				delete node;
				return val;
			}
			throw std::out_of_range("No element to delete after the last one");
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Class Iterator									////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	template <class U>
	class Iterator
	{
	private:
		Node<T> * node_;
	public:
		//////////////////////////////////////////////////////////////////////////
		// Constructor
		//////////////////////////////////////////////////////////////////////////
		Iterator() : node_(nullptr) {};
		Iterator(Node<T> * node) : node_(node) {};
		Iterator(const Iterator & it) : node_(it.node_) {};

		//////////////////////////////////////////////////////////////////////////
		// Movement Operator
		//////////////////////////////////////////////////////////////////////////
		Iterator & operator++() { node_ = &node_->get_next(); return *this; };
		Iterator operator++(int) { Iterator it = Iterator(node_); node_ = &node_->get_next(); return it; };
		Iterator operator+(int n) const
		{
			Iterator it = Iterator(*this);
			for (int i = 0; i < n; ++i)
			{
				++it;
			}
			return it;
		};
		friend Iterator operator+(int n, const Iterator & it) { return (it + n); }

		Iterator & operator--() { node_ = &node_->get_last(); return *this; };
		Iterator operator--(int) { Iterator it = Iterator(node_); node_ = &node_->get_last(); return it; };
		Iterator operator-(int n) const
		{
			Iterator it = &this;
			for (int i = 0; i < n; ++i)
			{
				--it;
			}
			return it;
		}

		T & operator*() { return node_->get_val(); }
		const T & operator*() const { return node_->get_val(); }

		T * operator->() { return &node_->get_val(); }
		const T * operator->() const { return &node_->get_val(); }
		//////////////////////////////////////////////////////////////////////////
		// Boolean Operator
		//////////////////////////////////////////////////////////////////////////
		bool operator==(const Iterator & it) const { return node_ == it.node_; }
		bool operator!=(const Iterator & it) const { return !(*this == it); }

		////////////////////////////////////////////////////////////////////////////////
		// Check functions
		////////////////////////////////////////////////////////////////////////////////
	private:
		void check_valid() const
		{
			if (node_ == nullptr) throw std::logic_error("Iterator pointed to null value");
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Class Enumerable								////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	////////////////////////////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////////////////////////////
	Enumerable()
	: begin_(new Node<T>()), end_(new Node<T>()), size_(0), sub_enum_start_index_(0)
	{ begin_->set_next(end_); }

	Enumerable(const T * data, uint32_t size)
	: begin_(new Node<T>()), end_(new Node<T>()), size_(0), sub_enum_start_index_(0)
	{
		begin_->set_next(end_);
		for(uint32_t i = 0; i < size; ++i)
		{
			push(data[i]);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Getters
	//////////////////////////////////////////////////////////////////////////
	const T & first() const
	{
		check_no_empty();
		return begin_->get_next().get_val();
	}

	const T & last() const
	{
		check_no_empty();
		return end_->get_last().get_val();
	}

	T & operator[](uint32_t n)
	{
		check_index(n);
		Iterator<T> it = begin();
		uint32_t i = 0;
		while (i < n)
		{
			++it; ++i;
		}
		return *it;
	}

	Iterator<T> begin() const { return Iterator<T>(&begin_->get_next()); }

	Iterator<T> end() const { return Iterator<T>(end_); }

	uint32_t size() { return size_; }

	Enumerable & get_sub(uint32_t start_index, uint32_t size)
	{
		if (sub_enum_ == nullptr)
		{
			sub_enum_ = new Enumerable<T>();
			sub_enum_start_index_ = 0;
		}

		check_index(start_index + size - 1);

		// make sure it is initialized properly
		if (sub_enum_->size() == 0 && size_ != 0)
		{
			sub_enum_->begin_ = begin_;
			sub_enum_->size_ = 1;
			sub_enum_->end_ = &begin_->get_next().get_next();
		}

		// find the proper starting node
		while (start_index < sub_enum_start_index_)
		{
			sub_enum_->begin_ = &sub_enum_->begin_->get_last();
			--sub_enum_start_index_;
		}

		while (start_index > sub_enum_start_index_)
		{
			sub_enum_->begin_ = &sub_enum_->begin_->get_next();
			++sub_enum_start_index_;
		}

		// adjust size and end_ node
		sub_enum_->end_ = &sub_enum_->begin_->get_next();
		for (uint32_t i = 0; i < size; ++i)
		{
			sub_enum_->end_ = &sub_enum_->end_->get_next();
		}
		sub_enum_->size_ = size;

		return *sub_enum_;
	}

	//////////////////////////////////////////////////////////////////////////
	// Adding Function
	//////////////////////////////////////////////////////////////////////////

	// Add an element at the end of the Enumerable
	Enumerable & push(const T & val)
	{
		end_->set_last(val);
		++size_;
		return *this;
	}

	// Add an element at the end of the Enumerable
	Enumerable & operator<<(const T & val) { return push(val); }

	// Add an element at the start of the Enumerable
	Enumerable & shift(const T & val)
	{
		begin_->set_next(val);
		++size_;
		return *this;
	}

	// link both enumerable together
	void operator+=(const Enumerable & en)
	{
		for (Iterator<T> it = en.begin(); it != en.end(); ++it)
		{
			push(*it);
		}
		size_ += en.size_;
	}

	// return an enumerable that is a link between both enumerable
	Enumerable operator+(const Enumerable & en) const { Enumerable out = *this; out += en; return en; }

	//////////////////////////////////////////////////////////////////////////
	// Removing Function
	//////////////////////////////////////////////////////////////////////////
	T pop()
	{
		check_no_empty();
		--size_;
		return end_->remove_last();
	}

	void remove(uint32_t n)
	{
		check_index(n);
		Node<T> * node = begin_;
		for (uint32_t i = 0; i < n; ++i)
		{
			node = &node->get_next();
		}
		--size_;
		return node->remove_next();
	}

	T unshift()
	{
		check_no_empty();
		--size_;
		return begin_->remove_next();
	}

	//////////////////////////////////////////////////////////////////////////
	// Group Manipulation
	//////////////////////////////////////////////////////////////////////////

	//This function calls the function on each element of the enumerable and keeps only those wich return true
	template <typename Function>
	Enumerable & select_self(Function fct)
	{
		Node<T> * curr_node = begin_;
		while (&curr_node->get_next() != end_)
		{
			if (!fct(curr_node->get_next().get_val()))
			{
				curr_node->remove_next();
				--size_;
				continue;
			}
			curr_node = &curr_node->get_next();
		}
		return *this;
	}

	template <typename Function>
	Enumerable select(Function fct)
	{
		Enumerable en;
		for (Iterator<T> it = begin(); it != end(); ++it)
		{
			if (fct(*it))
			{
				en << *it;
			}
		}
		return en;
	}

	template <typename Function>
	Enumerable & each(Function fct)
	{
		for (Iterator<T> it = begin(); it != end(); ++it)
		{
			fct(*it);
		}
		return *this;
	}

	template <class U, typename Function>
	Enumerable<U> map(Function fct)
	{
		Enumerable<U> En;
		for (Iterator<T> it = begin(); it != end(); ++it)
		{
			En.push(fct(*it));
		}
		return En;
	}

	template <class U, typename Function>
	U inject(U starting_value, Function fct)
	{
		for (Iterator<T> it = begin(); it != end(); ++it)
		{
			starting_value = fct(starting_value, *it);
		}
		return starting_value;
	}

	T sum()
	{
		return inject(T(), [](const T & i, const T & j) {return i + j; });
	}

	// returns an array containing all the value
	T * to_array() const
	{
		T * arr = new T[size_];
		uint32_t i = 0;
		for(Iterator<T> it = begin(); it != end(); ++it)
		{
			arr[i++] = *it;
		}
		return arr;
	}

	////////////////////////////////////////////////////////////////////////////////
	// Informations
	////////////////////////////////////////////////////////////////////////////////

	friend std::ostream & operator<<(std::ostream & o, const Enumerable & en)
	{
		o << "{";
		if (en.begin() != en.end())
		{
			for(Iterator<T> it = en.begin(); it + 1 != en.end(); ++it)
			{
				o << *it;
				o << ", ";
			}
			o << *(--en.end());
		}
		o << "}";
		return o;
	}

	// return true in a boolean operation if the enumerable is not empty
	explicit operator bool() const
	{
		return size_ > 0;
	}

	// check if the value given id contain inside the array
	bool contains(const T & val) const
	{
		for(Iterator<T> it = begin(); it != end(); ++it)
		{
			if (*it == val)
			{
				return true;
			}
		}
		return false;
	}

	// Check if there is a value in the array that match the given function condition
	template <typename Function>
	bool contains_condition(Function fct) const
	{
		for(Iterator<T> it = begin(); it != end(); ++it)
		{
			if (fct(*it))
			{
				return true;
			}
		}
		return false;
	}



private:
	// check if the index given can be access
	void check_index(uint32_t index) const
	{
		if (index + 1 > size_)
		{
			throw std::out_of_range("Index was out of range");
		}
	}

	void check_no_empty() const
	{
		if (size_ == 0)
		{
			throw std::out_of_range("Array is empty");
		}
	}

private:

	Node<T> * begin_;
	Node<T> * end_;
	uint32_t size_;

	Enumerable<T> * sub_enum_ = nullptr;
	uint32_t sub_enum_start_index_;
};
