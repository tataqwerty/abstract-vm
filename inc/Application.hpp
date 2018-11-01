#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "IterStack.hpp"
#include "Exceptions.hpp"
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
	typedef struct				s_cmd
	{
		std::string			name;
		void (Application::*function)();
	}							t_cmd;

	bool											flagVerbose;
	boost::regex									regExp;
	std::vector<t_cmd>								commands;
	std::map<std::string, eOperandType>				types;

	std::vector<std::string>						stringList;
	std::map<size_t, boost::smatch>					tokens;
	std::list<std::string>							errors;
	IterStack<IOperand const *>						stack;
	OperandFactory									operandFactory;

	std::pair<size_t, boost::smatch>	tokenize(std::string & str, size_t line);
	void								lexer();
	void								readStream(std::istream & stream, bool flagReadFromSTDIN);
	void								execute();

	void	pushHandler();
	void	popHandler();
	void	dumpHandler();
	void	addHandler();
	void	subHandler();
	void	mulHandler();
	void	divHandler();
	void	modHandler();
	void	assertHandler();
	void	printHandler();
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);
	void	setFlagVerbose(bool	val);
};

#endif