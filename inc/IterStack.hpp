#ifndef ITERSTACK_H__
#define ITERSTACK_H__

#include <stack>

template<typename T>
class IterStack : public std::stack<T>
{
	IterStack(IterStack const& other);
	IterStack & operator=(IterStack const& other);
public:
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	
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
};

#endif