#ifndef ITERSTACK_H__
#define ITERSTACK_H__

#include <stack>

template<typename T>
class IterStack : public std::stack<T>
{
	typedef typename std::stack<T>::container_type::iterator Iter;
	typedef typename std::stack<T>::container_type::const_iterator ConstIter;

	IterStack(IterStack const& other)
	{}
	IterStack & operator=(IterStack const& other)
	{}
public:
	IterStack()
	{}
	~IterStack()
	{}

	Iter begin()
	{
		return this->c.begin();
	}
	
	Iter end()
	{
		return this->c.end();
	}
	
	ConstIter begin() const
	{
		return this->c.begin();
	}
	
	ConstIter end() const
	{
		return this->c.end();
	}
};

#endif