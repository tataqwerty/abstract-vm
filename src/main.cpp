// #include "Application.hpp"

// int main(int ac, char *av[])
// {
// 	Application		app;
// 	std::ifstream	file;

// 	if (ac == 1)
// 	{
// 		app.readStream(std::cin, READ_FROM_STDIN);
// 		app.execute();
// 	}
// 	else
// 	{

// 		for (int i = 1; i < ac; i++)
// 		{
// 			errno = 0;
// 			file.open(av[i]);

// 			try {
// 				app.readStream(file);
// 				app.execute();
// 			} catch(std::exception & e) {
// 				std::cout << "Error: " << (std::strrchr(av[0], '/') + 1) << ": " << e.what() << std::endl;
// 			};

// 			file.close();
// 		}

// 	}
// 	return 0;
// }

#include <iostream>
// #include <regex>

// void	pushHandler(std::smatch & match)
// {
// 	for (std::string param : match)
// 	{
// 		std::cout << param << std::endl;
// 	}
// }

// void	assertHandler(std::smatch & match)
// {
// 	std::cout << "assertHandler" << std::endl;
// }


// void	basicCommandsHandler(std::smatch & match)
// {
// 	std::cout << "basicCommandsHandler" << std::endl;
// }

#include <boost/regex.hpp>

int main()
{
	boost::regex	regExp("(?|(?:(push) (candy|kiss))|(?:(pop) (candy|kiss)))");
	// boost::smatch	m;
	// std::string		s = "";

	// std::cout << boost::regex_match(s, m, regExp) << std::endl;

	// for (std::string s : m)
	// {
	// 	std::cout << s << std::endl;
	// }

	return 0;
}


// #include <utility>

// int main()
// {
// 	std::vector<std::pair<std::regex, std::function<void(std::smatch &)>>> arr = {
// 		{std::regex("^\\s*(push)\\s*(?:(?:(int8|int16|int32)\\s*\\(\\s*([-]?\\d+)\\s*\\)\\s*)|(?:(float|double)\\s*\\(\\s*([-]?\\d+\\.\\d+)\\s*\\)\\s*))$"), &pushHandler},
// 		{std::regex("^\\s*(assert)\\s*(?:(?:(int8|int16|int32)\\s*\\(\\s*([-]?\\d+)\\s*\\)\\s*)|(?:(float|double)\\s*\\(\\s*([-]?\\d+\\.\\d+)\\s*\\)\\s*))$"), &assertHandler},
// 		{std::regex("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*$"), &basicCommandsHandler}
// 	};
// 	std::smatch	m;
// 	std::string str = "push int8(32)";

// 	std::vector<std::pair<std::regex, std::function<void(std::smatch &)>>>::iterator it = arr.begin();
// 	std::vector<std::pair<std::regex, std::function<void(std::smatch &)>>>::iterator end = arr.end();

// 	while (it != end)
// 	{
// 		if (std::regex_match(str, m, it->first))
// 		{
// 			it->second(m);
// 			break ;
// 		}
// 		it++;
// 	}
// 	return 0;
// }

// ^\s*(push)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
// ^\s*(assert)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
// ^\s*(pop|dump|add|sub|mul|div|mod|print|exit)\s*$