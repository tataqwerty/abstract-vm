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
#include <regex>
#include <vector>

int main()
{
	std::map<std::regex, std::string> regexPairs = {
		{regex("(push|assert)"), ""}
	};

	return 0;
}

// ^\s*(push|assert)\s*(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*$
// ^\s*(push|assert)\s*(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*$
// ^\s*(pop|dump|add|sub|mul|div|mod|print|exit)\s*$

^\s*(push)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
^\s*(assert)\s*(?:(?:(int8|int16|int32)\s*\(\s*([-]?\d+)\s*\)\s*)|(?:(float|double)\s*\(\s*([-]?\d+\.\d+)\s*\)\s*))$
^\s*(pop|dump|add|sub|mul|div|mod|print|exit)\s*$