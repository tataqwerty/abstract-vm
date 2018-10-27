// #ifndef APPLICATION_HPP
// #define APPLICATION_HPP

// #include "OperandFactory.hpp"
// #include "IOperand.hpp"
// #include <errno.h>
// #include <list>
// #include <cstring>
// #include <fstream>
// #include <boost/regex.hpp>

// #define READ_FROM_STDIN			1
// #define END_OF_STDIN			";;"
// #define VERBOSE_FLAG_SIGNATURE	"-v"

// class Application
// {
// 	bool						flagVerbose;
// 	boost::regex				regExp;

// 	std::pair<size_t, boost::smatch>	tokenize(std::string & str, size_t line);
// 	void								parse(std::istream & stream, std::map<size_t, boost::smatch> & tokens, std::list<std::string> & errors, bool flagReadFromSTDIN);
// 	void								execute(std::map<size_t, boost::smatch> & tokens);
// public:
// 	Application();
// 	~Application();

// 	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);

// 	void	setFlagVerbose(bool	val);
// };

// #endif


#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <errno.h>
#include <list>
#include <cstring>
#include <fstream>
#include <boost/regex.hpp>

#define READ_FROM_STDIN			1
#define END_OF_STDIN			";;"
#define VERBOSE_FLAG_SIGNATURE	"-v"

class Application
{
	bool						flagVerbose;
	boost::regex				regExp;

	std::pair<size_t, boost::smatch>	tokenize(std::string & str, size_t line);
	void			lexer(std::map<size_t, boost::smatch> & tokens, std::vector<std::string> & stringList, std::list<std::string> & errors);
	void			readStream(std::istream & stream, std::vector<std::string> & stringList, bool flagReadFromSTDIN);
	void			execute(std::map<size_t, boost::smatch> & tokens);
public:
	Application();
	~Application();

	void	process(std::istream & stream, bool flagReadFromSTDIN = 0);

	void	setFlagVerbose(bool	val);
};

#endif