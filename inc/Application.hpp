#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>
#include <cstring>
#include <fstream>
#include <boost/regex.hpp>

#define READ_FROM_STDIN			1
#define END_OF_STDIN			";;"
#define VERBOSE_FLAG_SIGNATURE	"-v"

class Application
{
	bool						flagVerbose;
	boost::regex				regExp;

	boost::smatch	tokenize(std::string & str, size_t line);
	bool			lexer(std::list<boost::smatch> & tokens, std::vector<std::string> & stringList);
	void			readStream(std::istream & stream, std::vector<std::string> & stringList, bool flagReadFromSTDIN);
	void			execute(std::list<boost::smatch> & tokens);
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);

	void	setFlagVerbose(bool	val);
};

#endif