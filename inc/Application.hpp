#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "IterStack.hpp"
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
	std::map<std::string, void (Application::*)()>	commands;

	bool							flagVerbose;
	boost::regex					regExp;

	std::vector<std::string>		stringList;
	std::map<size_t, boost::smatch>	tokens;
	std::list<std::string>			errors;

	std::pair<size_t, boost::smatch>	token;
	IterStack										stack;

	std::pair<size_t, boost::smatch>	tokenize(std::string & str, size_t line);
	void			lexer();
	void			readStream(std::istream & stream, bool flagReadFromSTDIN);
	void			execute();
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);

	void	setFlagVerbose(bool	val);

	void	push();
	void	pop();
};

#endif