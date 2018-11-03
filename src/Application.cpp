#include "Application.hpp"
#include "Operand.hpp"

Application::Application()
:	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))[\\s;]*$"),
	commands({
		{.name = "push", .function = &Application::pushHandler},
		{.name = "pop", .function = &Application::popHandler},
		{.name = "dump", .function = &Application::dumpHandler},
		{.name = "add", .function = &Application::addHandler},
		{.name = "sub", .function = &Application::subHandler},
		{.name = "mul", .function = &Application::mulHandler},
		{.name = "div", .function = &Application::divHandler},
		{.name = "mod", .function = &Application::modHandler},
		{.name = "assert", .function = &Application::assertHandler},
		{.name = "print", .function = &Application::printHandler}
	}),
	types({
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	})
{}

Application::Application(Application const & other)
:	Application()
{
	*this = other;
}

Application & Application::operator=(Application const & other)
{
	this->stringList = other.stringList;
	this->tokens = other.tokens;
	this->stack = other.stack;
	return *this;
}

Application::~Application()
{
	while (!stack.empty())
	{
		delete stack.top();
		stack.pop();
	}
}

#include <stdio.h>

void	Application::readStream(std::istream & stream, bool flagReadFromSTDIN)
{
	std::string	buffer;

	while (std::getline(stream, buffer))
	{
		/* end of input when read from stdin */
		if (flagReadFromSTDIN && buffer == END_OF_STDIN)
			break ;
		stringList.push_back(buffer);
		buffer.clear();
	}
}

std::pair<size_t, boost::smatch>	Application::tokenize(std::string & str, size_t line)
{
	boost::smatch	m;

	if (boost::regex_match(str, m, regExp))
		return std::make_pair(line, m);
	else
		throw Exceptions::UndefinedToken();
}

bool	Application::lexer()
{
	bool	error = 0;

	for (size_t i = 0; i < stringList.size(); i++)
	{
		/* if first character of a string is not a ';' */
		if (!stringList[i].empty() && stringList[i][0] != COMMENT_SYMBOL) /* kostil */
		{
			try {
				tokens.insert(tokenize(stringList[i], i + 1));
			} catch(std::exception & e) {
				std::cout << "Line " + std::to_string(i + 1) + " : Error : " +  e.what() + " -> " + stringList[i] << std::endl;
				error = 1;
			}
		}
	}

	return error == 0;
}

void	Application::execute()
{
	boost::smatch	token;
	size_t			line;

	while (!tokens.empty())
	{
		/* get first element of tokens */
		token	= tokens.begin()->second;
		line	= tokens.begin()->first;

		/* token.command.name == exit; to check after loop that the last executed command is exit */
		if (token["cmd"] == "exit")
			break ;

		for (t_cmd &command : commands)
		{
			if (command.name == token["cmd"])
			{
				try {
					(this->*(command.function))();
				} catch(std::exception & e) {
					throw Exceptions::General("Line " + std::to_string(line) + " : Error : " + e.what());
				}
				break ;
			}
		}

		/* after processing token, delete this token */
		tokens.erase(tokens.begin());
	}

	/* there are must be token with exit command */
	if (tokens.empty())
		throw Exceptions::NoExitCMD();
}

void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
{
	tokens.erase(tokens.begin(), tokens.end());
	stringList.erase(stringList.begin(), stringList.end());
	while (!stack.empty())
	{
		delete stack.top();
		stack.pop();
	}

	readStream(stream, flagReadFromSTDIN);

	/* if error occurs, won't execute commands */
	if (lexer())
		execute();
}

/*
** ----- COMMANDS -----
**
** access to token happens by getting the first element of tokens
*/

void	Application::pushHandler()
{
	boost::smatch	token = tokens.begin()->second;

	stack.push(operandFactory.createOperand(types[token["type"]], token["value"]));
}

void	Application::popHandler()
{
	const IOperand * tmp;

	tmp = stack.top();
	stack.pop();
	delete tmp;
}

void	Application::dumpHandler()
{
	IterStack<const IOperand *>::iterator it = stack.end();

	for (size_t i = 0; i < stack.size(); i++)
	{
		it--;
		std::cout << (*it)->toString() << std::endl;
	}
}

void	Application::addHandler()
{
	const IOperand *op1;
	const IOperand *op2;

	if (stack.size() >= 2)
	{
		op2 = stack.top();
		stack.pop();
		op1 = stack.top();
		stack.pop();
 
		try {
			stack.push(*op1 + *op2);
		} catch(...) {
			delete op1;
			delete op2;
			throw;
		}

		delete op1;
		delete op2;
	}
	else
		throw Exceptions::InvalidOperandsQuantity();
}

void	Application::subHandler()
{
	const IOperand *op1;
	const IOperand *op2;

	if (stack.size() >= 2)
	{
		op2 = stack.top();
		stack.pop();
		op1 = stack.top();
		stack.pop();

		try {
			stack.push(*op1 - *op2);
		} catch(...) {
			delete op1;
			delete op2;
			throw;
		}

		delete op1;
		delete op2;
	}
	else
		throw Exceptions::InvalidOperandsQuantity();
}

void	Application::mulHandler()
{
	const IOperand *op1;
	const IOperand *op2;

	if (stack.size() >= 2)
	{
		op2 = stack.top();
		stack.pop();
		op1 = stack.top();
		stack.pop();

		try {
			stack.push(*op1 * *op2);
		} catch(...) {
			delete op1;
			delete op2;
			throw;
		}

		delete op1;
		delete op2;
	}
	else
		throw Exceptions::InvalidOperandsQuantity();
}

void	Application::divHandler()
{
	const IOperand *op1;
	const IOperand *op2;

	if (stack.size() >= 2)
	{
		op2 = stack.top();
		stack.pop();
		op1 = stack.top();
		stack.pop();

		try {
			stack.push(*op1 / *op2);
		} catch(...) {
			delete op1;
			delete op2;
			throw;
		}

		delete op1;
		delete op2;
	}
	else
		throw Exceptions::InvalidOperandsQuantity();
}

void	Application::modHandler()
{
	const IOperand *op1;
	const IOperand *op2;

	if (stack.size() >= 2)
	{
		op2 = stack.top();
		stack.pop();
		op1 = stack.top();
		stack.pop();

		try {
			stack.push(*op1 % *op2);
		} catch(...) {
			delete op1;
			delete op2;
			throw;
		}

		delete op1;
		delete op2;
	}
	else
		throw Exceptions::InvalidOperandsQuantity();
}

void	Application::assertHandler()
{
	boost::smatch	token = tokens.begin()->second;
	const IOperand	*tmp;

	tmp = operandFactory.createOperand(types[token["type"]], token["value"]);
	try {
		if (!(*tmp == *stack.top()))
			throw Exceptions::NotEqualValues();
	} catch(std::exception & e) {
		delete tmp;
		throw;
	}
	delete tmp;
}

void	Application::printHandler()
{
	if (stack.top()->getType() == types["int8"])
		std::cout << boost::numeric_cast<char>(std::stoi(stack.top()->toString())) << std::endl;
	else
		throw Exceptions::NotEqualValues();
}
