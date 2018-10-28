#include "Application.hpp"

void	Application::setFlagVerbose(bool value) { flagVerbose = value; }

Application::Application()
:	commands({
		{
			"push", &Application::push
		},
		{
			"pop", &Application::pop
		}
	}),
	flagVerbose(0),
	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$")
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

	//	there is must be token with exit command.
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
** COMMANDS
**
** DIKIY GAVNOKOD, PIZDEC!!!
** access to certain token is made by getting the first element of tokens variable.
*/

void	Application::push()
{
	boost::smatch	m = tokens.begin()->second;
	std::map<std::string, eOperandType>	types = {
		{"int8", Int8},
	};

	// stack.push();
}

void	Application::pop()
{
	// if (!stack.empty())
	// 	stack.pop();
	// else
		throw std::logic_error("Pop on empty stack");
}
