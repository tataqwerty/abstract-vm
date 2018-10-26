#include "Application.hpp"

Application::Application()
:	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$")
{}

Application::~Application()
{}

// void	Application::readStream(std::istream & stream, bool flag)
// {
// 	std::string	buffer;

// 	//	delete all nodes from the list of commands
// 	commands.erase(commands.begin(), commands.end());

// 	if (errno)
// 		throw std::logic_error(std::strerror(errno));

// 	while (std::getline(stream, buffer))
// 	{
// 		//	end of input from stdin
// 		if (flag && buffer == END_OF_STDIN)
// 			break ;

// 		// comment
// 		if (buffer.find(";") != buffer.npos && !stream.eof())
// 			buffer = buffer.substr(0, buffer.find(";"));

// 		// if string was "; tralalalala" -> here this string is empty
// 		// if string contains space characters -> skip this string
// 		if (buffer.size() && buffer.find_first_not_of(" \t\r") != buffer.npos)
// 			commands.push_back(buffer);

// 		buffer.clear();
// 	}

// 	//	when read from stdin, last line must be ";;"
// 	if (flag && buffer != END_OF_STDIN)
// 		throw std::logic_error("Unexpected end of input");
// }

boost::smatch	Application::lexer(std::string const & buffer)
{
	boost::smatch	match;

	if (boost::regex_match(buffer, match, regExp))
		return match;
	else
		throw std::logic_error("Undefined token");
}

bool	Application::parse(std::istream & stream, std::list<boost::smatch> & tokens, bool flagReadFromSTDIN)
{
	bool		flagError = 0;
	std::string	buffer;

	tokens.erase(tokens.begin(), tokens.end());

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

		//	if buffer is not empty we have to tokenize it, so that in another function we just have to read token and execute it.
		if (!buffer.empty())
		{
			try {
				tokens.push_back(lexer(buffer));
			} catch(std::exception & e) {
				std::cout << e.what() << std::endl;
				flagError = 1;
			}
		}

		buffer.clear();
	}

	//	when read from stdin, last line must be ";;"
	if (flagReadFromSTDIN && buffer != END_OF_STDIN)
		throw std::logic_error("Unexpected end of input");

	return flagError == 0;
}

void	Application::execute(std::list<boost::smatch> & tokens)
{
	(void)tokens;
	// std::list<std::string>::iterator it(commands.begin());
	// std::list<std::string>::iterator end(commands.end());

	// while (it != end)
	// {
	// 	it++;
	// }
}

void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
{
	std::list<boost::smatch>	tokens;

	if (parse(stream, tokens, flagReadFromSTDIN))
		execute(tokens);
}
