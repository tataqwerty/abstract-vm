#include "Exceptions.hpp"

// ----- GeneralException -----

Exceptions::GeneralException::GeneralException(std::string const & s)
:	msg(s.c_str())
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
	return (this->msg);
}

// ----- NotEqualValuesException -----

Exceptions::NotEqualValuesException::NotEqualValuesException()
{}

Exceptions::NotEqualValuesException::~NotEqualValuesException()
{}

const char * Exceptions::NotEqualValuesException::what() const throw()
{
	return ("Stack is empty!");
}

// ----- InvalidOperandsQuantityException -----

Exceptions::InvalidOperandsQuantityException::InvalidOperandsQuantityException()
{}

Exceptions::InvalidOperandsQuantityException::~InvalidOperandsQuantityException()
{}

const char * Exceptions::InvalidOperandsQuantityException::what() const throw()
{
	return ("Invalid quantity of operands!");
}

// ----- UndefinedTokenException -----

Exceptions::UndefinedTokenException::UndefinedTokenException()
{}

Exceptions::UndefinedTokenException::~UndefinedTokenException()
{}

const char * Exceptions::UndefinedTokenException::what() const throw()
{
	return ("Undefined token!");
}

// ----- NoExitCMDException -----

Exceptions::NoExitCMDException::NoExitCMDException()
{}

Exceptions::NoExitCMDException::~NoExitCMDException()
{}

const char * Exceptions::NoExitCMDException::what() const throw()
{
	return ("Error : no exit command!");
}
