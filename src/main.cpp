#include "Application.hpp"

int main(int ac, char *av[])
{
	Application					app;
	std::ifstream				file;
	std::vector<std::string>	args(&av[1], &av[ac]);

	//	check if arguments have verbose flag, if so remember it, and delete this argument
	if (std::find(args.begin(), args.end(), std::string(VERBOSE_FLAG_SIGNATURE)) != args.end())
	{
		app.setFlagVerbose(1);
		args.erase(std::remove(args.begin(), args.end(), std::string(VERBOSE_FLAG_SIGNATURE)), args.end());
	}

	if (!args.size())
	{
		app.process(std::cin, READ_FROM_STDIN);
	}
	else
	{

		for (std::string filename : args)
		{
			errno = 0;
			file.open(filename);

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
