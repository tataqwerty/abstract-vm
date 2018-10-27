// #include "Application.hpp"

// void	Application::setFlagVerbose(bool value) { flagVerbose = value; }

// Application::Application()
// :	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$")
// {}

// Application::~Application()
// {}

// std::pair<size_t, boost::smatch>	Application::tokenize(std::string & str, size_t line)
// {
// 	boost::smatch						m;

// 	if (boost::regex_match(str, m, regExp))
// 		return std::make_pair(line, m);
// 	else
// 		throw std::logic_error("Line " + std::to_string(line) + " : Error : undefined token");
// }

// void	Application::parse(std::istream & stream, std::map<size_t, boost::smatch> & tokens, std::list<std::string> & errors, bool flagReadFromSTDIN)
// {
// 	size_t		i = 1;
// 	std::string	buffer;

// 	if (errno)
// 		throw std::logic_error(std::strerror(errno));

// 	while (std::getline(stream, buffer))
// 	{
// 		//	end of input from stdin
// 		if (flagReadFromSTDIN && buffer == END_OF_STDIN)
// 			break ;

// 		// comment
// 		if (buffer.find(";") != buffer.npos && !stream.eof())
// 			buffer = buffer.substr(0, buffer.find(";"));

// 		if (buffer.size())
// 		{

// 			try {
// 				tokens.insert(tokenize(buffer, i));
// 			} catch(std::exception & e) {
// 				errors.push_back(e.what());

// 				if (errors.size() >= 5 && !flagVerbose)
// 				{
// 					errors.push_back("Error : too much errors occured (use " + std::string(VERBOSE_FLAG_SIGNATURE) + " to see more)");
// 					return ;
// 				}
// 			}

// 		}

// 		buffer.clear();
// 		i++;
// 	}
// }

// void	Application::execute(std::map<size_t, boost::smatch> & tokens)
// {
// 	(void)tokens;
// }

// void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
// {
// 	std::map<size_t, boost::smatch>	tokens;
// 	std::list<std::string>			errors;

// 	parse(stream, tokens, errors, flagReadFromSTDIN);
// 	if (errors.size())
// 	{
// 		for (std::string err : errors)
// 			std::cout << err << std::endl;
// 	}
// 	else
// 		execute(tokens);
// }







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
}

std::pair<size_t, boost::smatch>	Application::tokenize(std::string & str, size_t line)
{
	boost::smatch						m;

	if (boost::regex_match(str, m, regExp))
		return std::make_pair(line, m);
	else
		throw std::logic_error("Line " + std::to_string(line) + " : Error : undefined token");
}

void	Application::lexer(std::map<size_t, boost::smatch> & tokens, std::vector<std::string> & stringList, std::list<std::string> & errors)
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

void	Application::execute(std::map<size_t, boost::smatch> & tokens)
{
	(void)tokens;
}

void	Application::process(std::istream & stream, bool flagReadFromSTDIN)
{
	std::vector<std::string>		stringList;
	std::map<size_t, boost::smatch>	tokens;
	std::list<std::string>			errors;

	readStream(stream, stringList, flagReadFromSTDIN);
	lexer(tokens, stringList, errors);

	if (errors.size())
	{
		for (std::string err : errors)
			std::cout << err << std::endl;
	}
	else
		execute(tokens);
}
