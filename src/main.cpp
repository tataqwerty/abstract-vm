#include "Application.hpp"

int main(int ac, char *av[])
{
	Application		app;
	std::ifstream	file;

	if (ac == 1)
	{
		app.process(std::cin);
	}
	else
	{

		for (int i = 1; i < ac; i++)
		{
			errno = 0;
			file.open(av[i]);

			try {
				app.process(file, 1);
			} catch(std::exception & e) {
				std::cout << "Error: " << (std::strrchr(av[0], '/') + 1) << ": " << e.what() << std::endl;
			};

			file.close();
		}

	}
	return 0;
}
