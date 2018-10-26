#include "Application.hpp"

int main(int ac, char *av[])
{
	Application		app;
	std::ifstream	file;

	if (ac == 1)
	{
		app.process(std::cin, READ_FROM_STDIN);
	}
	else
	{

		for (int i = 1; i < ac; i++)
		{
			errno = 0;
			file.open(av[i]);

			try {
				app.process(file);
			} catch(std::exception & e) {
				std::cout << "Error: " << (std::strrchr(av[0], '/') + 1) << ": " << e.what() << std::endl;
			};

			file.close();
		}

	}
	return 0;
}







// #include <boost/regex.hpp>
// #include <iostream>
// #include <vector>

// int main(int ac, char *av[])
// {
// 	if (ac == 2)
// 	{
// 		boost::regex	regExp("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$");
// 		boost::smatch	m;

// 		if (boost::regex_match(std::string(av[1]), m, regExp))
// 		{
// 			std::cout << "Found" << std::endl;

// 			for (std::string s : m)
// 			{
// 				std::cout << s << std::endl;
// 			}
// 			std::cout << "cmd -> " << m["cmd"] << std::endl;
// 			std::cout << "type -> " << m["type"] << std::endl;
// 			std::cout << "value -> " << m["value"] << std::endl;
// 		}
// 		else
// 		{
// 			std::cout << "Not found" << std::endl;
// 		}
// 	}
// 	return 0;
// }

// ^\s*(?|(?:(?<cmd>push|assert)\s+(?<type>int8|int16|int32)\s*\(\s*[-]?\d+\s*\))|(?:(?<cmd>push|assert)\s+(?<type>float|double)\s*\(\s*[-]?\d+.\d+\s*\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\s*$

// ^\s*(push)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
// ^\s*(assert)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
// ^\s*(pop|dump|add|sub|mul|div|mod|print|exit)\s*$