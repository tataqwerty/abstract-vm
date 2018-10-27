#include "Application.hpp"

void	Application::setFlagVerbose(bool value) { flagVerbose = value; }

Application::Application()
:	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$")
{}

Application::~Application()
{}

void	Application::readStream(std::istream & stream, std::vector<std::string> & stringList, bool flagReadFromSTDIN)
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

	//	when read from stdin, last line must be ";;"
	if (flagReadFromSTDIN && buffer != END_OF_STDIN)
		throw std::logic_error("Unexpected end of input");
}

boost::smatch	Application::tokenize(std::string & str, size_t line)
{
	boost::smatch	m;

	if (boost::regex_match(str, m, regExp))
	{
		;
	}
	else
		throw std::logic_error("Line " + std::to_string(line) + " : Error : undefined token");
	return m;
}

bool	Application::lexer(std::list<boost::smatch> & tokens, std::vector<std::string> & stringList)
{
	int				errors = 0;

	for (size_t i = 0; i < stringList.size(); i++)
	{
		if (!stringList[i].empty())
		{

			try {
				tokens.push_back(tokenize(stringList[i], i));
			} catch(std::exception & e) {
				std::cout << e.what() << std::endl;
				errors++;
			}

			if (errors >= 20)
				throw std::logic_error("Error : too much errors occured");

		}
	}

	return errors == 0;
}

void	Application::execute(std::list<boost::smatch> & tokens)
{
	(void)tokens;
}

void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
{
	std::vector<std::string>	stringList;
	std::list<boost::smatch>	tokens;

	readStream(stream, stringList, flagReadFromSTDIN);
	if (lexer(tokens, stringList))
		execute(tokens);
}
