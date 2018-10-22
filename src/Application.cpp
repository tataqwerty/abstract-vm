#include "Application.hpp"

Application::Application()
{}

Application::~Application()
{}

void	Application::readStream(std::istream & stream, bool flag)
{
	std::string	buffer;

	//	delete all nodes from the list of commands
	commands.erase(commands.begin(), commands.end());

	if (errno)
		throw std::logic_error(std::strerror(errno));

	while (std::getline(stream, buffer))
	{
		//	end of input from stdin
		if (flag && buffer == END_OF_STDIN)
			break ;

		// comment
		if (buffer.find(";") != buffer.npos && !stream.eof())
			buffer = buffer.substr(0, buffer.find(";"));

		// if string was "; tralalalala" -> here this string is empty
		if (buffer.size())
			commands.push_back(buffer);

		buffer.clear();
	}

	//	when read from stdin, last line must be ";;"
	if (flag && buffer != END_OF_STDIN)
		throw std::logic_error("Unexpected end of input");
}

void	Application::execute()
{
	std::list<std::string>::iterator it(commands.begin());
	std::list<std::string>::iterator end(commands.end());

	while (it != end)
	{
		it++;
	}
}
