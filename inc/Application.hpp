#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>
#include <cstring>
#include <fstream>
// #include <regex>

#define END_OF_STDIN	";;"
#define READ_FROM_STDIN	1

class Application
{
	std::list<std::string>	commands;

public:
	Application();
	~Application();

	void	readStream(std::istream & stream, bool flag = 0);
	void	execute();
};

#endif