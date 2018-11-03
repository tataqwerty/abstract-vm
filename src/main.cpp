#include "Application.hpp"
#include <sys/stat.h>
#include "errno.h"

/*
** @param fileStat - to check whether file is a directory
*/

int main(int ac, char *av[])
{
	Application					app;
	std::ifstream				file;
	struct stat					fileStat;

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
			stat(av[1], &fileStat);

			try {
				if (errno)
					throw Exceptions::General("Error : " + std::string(std::strerror(errno)));
				else if (fileStat.st_mode & S_IFDIR)
					throw Exceptions::Directory();
				else
					app.process(file);
			} catch(std::exception & e) {
				std::cout << e.what() << std::endl;
			};

			file.close();
		}

	}
	return 0;
}
