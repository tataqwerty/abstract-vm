#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class Exceptions
{
public:
	class	General : public std::exception
	{
		std::string msg;

	public:
		explicit General(std::string const & s);
		General(General const & other);
		General & operator=(General const & other);
		~General();
		const char	*	what() const throw();
	};

	class	NotEqualValues : public std::exception
	{
	public:
		NotEqualValues();
		~NotEqualValues();
		const char	*	what() const throw();
	};

	class	InvalidOperandsQuantity : public std::exception
	{
	public:
		InvalidOperandsQuantity();
		~InvalidOperandsQuantity();
		const char	*	what() const throw();
	};

	class	UndefinedToken : public std::exception
	{
	public:
		UndefinedToken();
		~UndefinedToken();
		const char	*	what() const throw();
	};

	class	NoExitCMD : public std::exception
	{
	public:
		NoExitCMD();
		~NoExitCMD();
		const char	*	what() const throw();
	};

	class	EmptyStack : public std::exception
	{
	public:
		EmptyStack();
		~EmptyStack();
		const char	*	what() const throw();
	};

	class	DivideByZero : public std::exception
	{
	public:
		DivideByZero();
		~DivideByZero();
		const char	*	what() const throw();
	};

	class	ModuloByZero : public std::exception
	{
	public:
		ModuloByZero();
		~ModuloByZero();
		const char	*	what() const throw();
	};

	class	PositiveOverflow : public std::exception
	{
	public:
		PositiveOverflow();
		~PositiveOverflow();
		const char	*	what() const throw();
	};

	class	NegativeOverflow : public std::exception
	{
	public:
		NegativeOverflow();
		~NegativeOverflow();
		const char	*	what() const throw();
	};

	class	Directory : public std::exception
	{
	public:
		Directory();
		~Directory();
		const char	*	what() const throw();
	};
};

#endif