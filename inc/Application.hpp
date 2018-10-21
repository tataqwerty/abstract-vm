#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>

class Application
{
public:
	Application();
	~Application();

	void	process(FILE * stream, bool flag = 0);
};

#endif