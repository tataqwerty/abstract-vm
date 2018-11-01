#include "Application.hpp"

void	Application::setFlagVerbose(bool value) { flagVerbose = value; }

Application::Application()
:	flagVerbose(0),
	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$"),
	commands({
		{"push", &Application::pushHandler},
		{"pop", &Application::popHandler},
		{"dump", &Application::dumpHandler},
		{"add", &Application::addHandler},
		{"sub", &Application::subHandler},
		{"mul", &Application::mulHandler},
		{"div", &Application::divHandler},
		{"mod", &Application::modHandler},
		{"assert", &Application::assertHandler},
		{"print", &Application::printHandler}
	}),
	types({
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	})
{}

Application::~Application()
{}

void	Application::readStream(std::istream & stream, bool flagReadFromSTDIN)
{
	std::string	buffer;

	if (errno)
		throw std::logic_error(std::strerror(errno));

	while (std::getline(stream, buffer))
	{
		//	end of input from stdin
		if (flagReadFromSTDIN && buffer == END_OF_STDIN)
			break ;

		// comment
		if (buffer.find(";") != buffer.npos && !stream.eof())
			buffer = buffer.substr(0, buffer.find(";"));

		stringList.push_back(buffer);

		buffer.clear();
	}
}

std::pair<size_t, boost::smatch>	Application::tokenize(std::string & str, size_t line)
{
	boost::smatch						m;

	if (boost::regex_match(str, m, regExp))
		return std::make_pair(line, m);
	else
		throw std::logic_error("Line " + std::to_string(line) + " : Error : undefined token");
}

void	Application::lexer()
{
	for (size_t i = 0; i < stringList.size(); i++)
	{
		if (!stringList[i].empty())
		{

			try {
				tokens.insert(tokenize(stringList[i], i + 1));
			} catch(std::exception & e) {
				errors.push_back(e.what());

				if (errors.size() >= 5 && !flagVerbose)
				{
					errors.push_back("Error : too much errors occured (use " + std::string(VERBOSE_FLAG_SIGNATURE) + " to see more)");
					return ;
				}
			}

		}
	}
}

void	Application::execute()
{
	std::map<size_t, boost::smatch>::iterator	token;

	while (!tokens.empty())
	{
		token = tokens.begin();

		// token.command.name == exit, to check after loop that the last command executed is exit.
		if (token->second["cmd"] == "exit")
			break ;

		for (std::pair<std::string, void (Application::*)()> command : commands)
		{
			// command.name == token.command.name, execute it
			if (command.first == token->second["cmd"])
			{
				try {
					(this->*(command.second))();
				} catch(std::exception & e) {
					throw std::logic_error("Line " + std::to_string(token->first) + " : Error : " + e.what());
				}
				break ;
			}
		}

		tokens.erase(token);
	}

	//	there are must be token with exit command.
	if (tokens.empty())
		throw std::logic_error("Error : no exit command.");
}

void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
{
	tokens.erase(tokens.begin(), tokens.end());
	errors.erase(errors.begin(), errors.end());
	stringList.erase(stringList.begin(), stringList.end());

	readStream(stream, flagReadFromSTDIN);
	lexer();
	if (errors.size())
	{
		for (std::string err : errors)
			std::cout << err << std::endl;
	}
	else
		execute();
}

/*
** ----- COMMANDS -----
*/

void	Application::pushHandler()
{
	boost::smatch	token = tokens.begin()->second;

	stack.push(operandFactory.createOperand(types[token["type"]], token["value"]));
}

void	Application::popHandler()
{
	const IOperand * tmp;

	if (!stack.empty())
	{
		tmp = stack.top();
		stack.pop();
		delete tmp;
	}
	else
		throw std::logic_error("Pop on empty stack");
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
		throw std::logic_error("Invalid quantity of operands");
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
		throw std::logic_error("Invalid quantity of operands");
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
		throw std::logic_error("Invalid quantity of operands");
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
		throw std::logic_error("Invalid quantity of operands");
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
		throw std::logic_error("Invalid quantity of operands");
}

void	Application::assertHandler()
{
	boost::smatch	token = tokens.begin()->second;
	const IOperand	*tmp;

	if (!stack.empty())
	{
		try {
			tmp = operandFactory.createOperand(types[token["type"]], token["value"]);
			
			if (!(*tmp == *stack.top()))
				throw std::logic_error("Values are not equal");

			delete tmp;
		} catch(std::exception & e) {
			delete tmp;
			throw;
		};

	}
	else
		throw std::logic_error("There are no elements in stack");
}

void	Application::printHandler()
{
	if (!stack.empty())
	{

		if (stack.top()->getType() == types["int8"])
			std::cout << boost::numeric_cast<char>(std::stoi(stack.top()->toString())) << std::endl;
		else
			throw std::logic_error("Values are not equal");

	}
	else
		throw std::logic_error("There are no elements in stack");
}
