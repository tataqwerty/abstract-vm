#ifndef ITERSTACK_HPP
#define ITERSTACK_HPP

#include <stack>
#include <exception>
#include "Exceptions.hpp"

template<typename T>
class IterStack : public std::stack<T>
{
	typedef typename std::stack<T>::container_type::reference		reference;
	typedef typename std::stack<T>::container_type::const_reference	const_reference;

public:
	typedef typename std::stack<T>::container_type::iterator		iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	IterStack()
	{}

	~IterStack()
	{}

	IterStack(IterStack const& other)
	{
		*this = other;
	}

	IterStack & operator=(IterStack const& other)
	{
		this->c = other.c;
		return *this;
	}

	iterator begin()
	{
		return this->c.begin();
	}
	
	iterator end()
	{
		return this->c.end();
	}
	
	const_iterator begin() const
	{
		return this->c.begin();
	}
	
	const_iterator end() const
	{
		return this->c.end();
	}

	void	pop()
	{
		if (this->empty())
			throw Exceptions::EmptyStackException();
		this->c.pop_back();
	}

	reference top()
	{
		if (this->empty())
			throw Exceptions::EmptyStackException();
		return (this->c.back());
	}

	const_reference top() const
	{
		if (this->empty())
			throw Exceptions::EmptyStackException();
		return (this->c.back());
	}
};

#endif