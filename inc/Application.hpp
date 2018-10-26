#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>
#include <cstring>
#include <fstream>
#include <boost/regex.hpp>

#define END_OF_STDIN	";;"
#define READ_FROM_STDIN	1

class Application
{
	boost::regex				regExp;

	boost::smatch	lexer(std::string const& buffer);
	bool			parse(std::istream & stream, std::list<boost::smatch> & tokens, bool flagReadFromSTDIN);
	void			execute(std::list<boost::smatch> & tokens);
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);
};

#endif