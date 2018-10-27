// #include "Application.hpp"

// int main(int ac, char *av[])
// {
// 	Application					app;
// 	std::ifstream				file;
// 	std::vector<std::string>	args(&av[1], &av[ac]);

// 	//	check if arguments have verbose flag, if so remember it, and delete this argument
// 	if (std::find(args.begin(), args.end(), std::string(VERBOSE_FLAG_SIGNATURE)) != args.end())
// 	{
// 		app.setFlagVerbose(1);
// 		args.erase(std::remove(args.begin(), args.end(), std::string(VERBOSE_FLAG_SIGNATURE)), args.end());
// 	}

// 	if (!args.size())
// 	{
// 		app.process(std::cin, READ_FROM_STDIN);
// 	}
// 	else
// 	{

// 		for (std::string filename : args)
// 		{
// 			errno = 0;
// 			file.open(filename);

// 			try {
// 				app.process(file);
// 			} catch(std::exception & e) {
// 				std::cout << "Error: " << (std::strrchr(av[0], '/') + 1) << ": " << e.what() << std::endl;
// 			};

// 			file.close();
// 		}

// 	}
// 	return 0;
// }

#include <iostream>
#include <boost/regex.hpp>

int main()
{
	std::regex r("^\\s*(?|(?:(?<cmd>push|assert)\\s+(?<type>int8|int16|int32)\\((?<value>[-]?\\d+)\\))|(?:(?<cmd>push|assert)\\s+(?<type>float|double)\\((?<value>[-]?\\d+\\.\\d+)\\))|(?:(?<cmd>pop|dump|add|sub|mul|div|mod|print|exit)))\\s*$");
	std::string s = "push int8(12)";
	for(std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), r);
                             i != std::sregex_iterator();
                             ++i)
    {
        boost::smatch m = *i;
        std::cout << "Match value: " << m.str() << " at Position " << m.position() << '\n';
 
        for(auto index = 1; index < m.size(); ++index ){
        	if (!m[index].str().empty()) {
				std::cout << "Capture group ID: " << index-1 << std::endl;
				break;
        	}
		}
    }
	return 0;
}


