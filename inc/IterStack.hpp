#ifndef ITERSTACK_HPP
#define ITERSTACK_HPP

#include <stack>
#include <exception>

template<typename T>
class IterStack : public std::stack<T>
{
	class	EmptyStackException : std::exception
	{
	public:
		EmptyStackException()
		{}
		~EmptyStackException()
		{}
		const char	*	what() const throw()
		{
			return ("Stack is empty!");
		}
	};

	typedef typename std::stack<T>::container_type::reference		reference;
	typedef typename std::stack<T>::container_type::const_reference	const_reference;

	IterStack(IterStack const& other);
	IterStack & operator=(IterStack const& other);
public:
	typedef typename std::stack<T>::container_type::iterator		iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	IterStack()
	{}

	~IterStack()
	{}

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
			throw EmptyStackException();
		this->c.pop_back();
	}

	reference top()
	{
		if (this->empty())
			throw EmptyStackException();
		return (this->c.back());
	}

	const_reference top() const
	{
		if (this->empty())
			throw EmptyStackException();
		return (this->c.back());
	}
};

#endif