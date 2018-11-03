#include "Exceptions.hpp"

// ----- GeneralException -----

Exceptions::GeneralException::GeneralException(std::string const & s)
:	msg(s)
{}

Exceptions::GeneralException::GeneralException(Exceptions::GeneralException const & other)
{
	*this = other;
}

Exceptions::GeneralException & Exceptions::GeneralException::operator=(Exceptions::GeneralException const & other)
{
	this->msg = other.msg;
	return *this;
}

Exceptions::GeneralException::~GeneralException()
{}

const char * Exceptions::GeneralException::what() const throw()
{
	return (this->msg.c_str());
}

// ----- NotEqualValuesException -----

Exceptions::NotEqualValuesException::NotEqualValuesException()
{}

Exceptions::NotEqualValuesException::~NotEqualValuesException()
{}

const char * Exceptions::NotEqualValuesException::what() const throw()
{
	return ("Values are not equal");
}

// ----- InvalidOperandsQuantityException -----

Exceptions::InvalidOperandsQuantityException::InvalidOperandsQuantityException()
{}

Exceptions::InvalidOperandsQuantityException::~InvalidOperandsQuantityException()
{}

const char * Exceptions::InvalidOperandsQuantityException::what() const throw()
{
	return ("Invalid quantity of operands");
}

// ----- UndefinedTokenException -----

Exceptions::UndefinedTokenException::UndefinedTokenException()
{}

Exceptions::UndefinedTokenException::~UndefinedTokenException()
{}

const char * Exceptions::UndefinedTokenException::what() const throw()
{
	return ("Undefined token");
}

// ----- NoExitCMDException -----

Exceptions::NoExitCMDException::NoExitCMDException()
{}

Exceptions::NoExitCMDException::~NoExitCMDException()
{}

const char * Exceptions::NoExitCMDException::what() const throw()
{
	return ("Error : no exit command");
}

// ----- EmptyStackException -----

Exceptions::EmptyStackException::EmptyStackException()
{}

Exceptions::EmptyStackException::~EmptyStackException()
{}

const char * Exceptions::EmptyStackException::what() const throw()
{
	return ("Stack is empty");
}

// ----- DivideByZeroException -----

Exceptions::DivideByZeroException::DivideByZeroException()
{}

Exceptions::DivideByZeroException::~DivideByZeroException()
{}

const char * Exceptions::DivideByZeroException::what() const throw()
{
	return ("Divide by zero");
}

// ----- ModuloByZeroException -----

Exceptions::ModuloByZeroException::ModuloByZeroException()
{}

Exceptions::ModuloByZeroException::~ModuloByZeroException()
{}

const char * Exceptions::ModuloByZeroException::what() const throw()
{
	return ("Modulo by zero");
}
