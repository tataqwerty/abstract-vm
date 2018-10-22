#include "Application.hpp"

Application::Application()
{}

Application::~Application()
{}

void	Application::process(std::istream & stream, bool flag)
{
	std::list<std::string>	commands;

	if (errno)
		throw std::logic_error(std::strerror(errno));

	flag = 0;
	(void)stream;
}
