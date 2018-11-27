#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IterStack.hpp"
#include "Exceptions.hpp"
#include <list>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <boost/regex.hpp>

#define READ_FROM_STDIN			1
#define END_OF_STDIN			";;"
#define COMMENT_SYMBOL			';'

class Application
{
	/* basic structure for all commands */
	typedef struct				s_cmd
	{
		std::string			name;
		void (Application::*function)();
	}							t_cmd;

	boost::regex							regExp;

	/* vector of commands {push, pop, dump, ...} */
	std::vector<t_cmd>						commands;

	std::map<std::string, eOperandType>		types;

	/* vector of strings read from given stream */
	std::vector<std::string>				stringList;

	/* array of pairs {(line on which token has been read) => (result of regex_match)} */
	std::map<size_t, boost::smatch>			tokens;

	IterStack<IOperand const *>				stack;
	OperandFactory							operandFactory;

	std::pair<size_t, boost::smatch>	tokenize(std::string & str, size_t line);
	bool								lexer();
	void								readStream(std::istream & stream, bool flagReadFromSTDIN);
	void								execute();
	std::string const&					typeToString(eOperandType type) const;

	/* commands */
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
	Application(Application const & other);
	Application & operator=(Application const & other);
	~Application();

	/* main function of application */
	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);
};

#endif