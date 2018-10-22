#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>
#include <cstring>
#include <fstream>

class Application
{
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flag = 0);
};

#endif