#include "Application.hpp"

int main(int ac, char *av[])
{
	Application		app;
	FILE			*file;

	errno = 0;
	try {

		if (ac == 1)
		{
			app.process(stdin);
		}
		else
		{

			for (int i = 1; i < ac; i++)
			{
				file = fopen(av[1], "r");
				
				try {
					app.process(file, 1);
				} catch(std::exception & e) {
					fclose(file);
				} throw;

				fclose(file);
			}

		}

	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
