#include "Application.hpp"

int main(int ac, char *av[])
{
	Application					app;
	std::ifstream				file;

	if (ac == 1)
	{
		try {
			app.process(std::cin, READ_FROM_STDIN);
		} catch(std::exception & e) {
			std::cout << e.what() << std::endl;
		};
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
				std::cout << e.what() << std::endl;
			};

			file.close();
		}

	}
	return 0;
}
