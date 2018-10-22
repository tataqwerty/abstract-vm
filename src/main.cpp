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

int main()
{
	return 0;
}