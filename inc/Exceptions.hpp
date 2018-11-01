#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class Exceptions
{
public:
	class	GeneralException : public std::exception
	{
		const char	*msg;

	public:
		explicit GeneralException(std::string const & s);
		GeneralException(GeneralException const & other);
		GeneralException & operator=(GeneralException const & other);
		~GeneralException();
		const char	*	what() const throw();
	};

	class	NotEqualValuesException : public std::exception
	{
	public:
		NotEqualValuesException();
		~NotEqualValuesException();
		const char	*	what() const throw();
	};

	class	InvalidOperandsQuantityException : public std::exception
	{
	public:
		InvalidOperandsQuantityException();
		~InvalidOperandsQuantityException();
		const char	*	what() const throw();
	};

	class	UndefinedTokenException : public std::exception
	{
	public:
		UndefinedTokenException();
		~UndefinedTokenException();
		const char	*	what() const throw();
	};

	class	NoExitCMDException : public std::exception
	{
	public:
		NoExitCMDException();
		~NoExitCMDException();
		const char	*	what() const throw();
	};
};

#endif