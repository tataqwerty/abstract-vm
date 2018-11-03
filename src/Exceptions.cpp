#include "Exceptions.hpp"

// ----- General -----

Exceptions::General::General(std::string const & s)
:	msg(s)
{}

Exceptions::General::General(Exceptions::General const & other)
{
	*this = other;
}

Exceptions::General & Exceptions::General::operator=(Exceptions::General const & other)
{
	this->msg = other.msg;
	return *this;
}

Exceptions::General::~General()
{}

const char * Exceptions::General::what() const throw()
{
	return (this->msg.c_str());
}

// ----- NotEqualValues -----

Exceptions::NotEqualValues::NotEqualValues()
{}

Exceptions::NotEqualValues::~NotEqualValues()
{}

const char * Exceptions::NotEqualValues::what() const throw()
{
	return ("Values are not equal");
}

// ----- InvalidOperandsQuantity -----

Exceptions::InvalidOperandsQuantity::InvalidOperandsQuantity()
{}

Exceptions::InvalidOperandsQuantity::~InvalidOperandsQuantity()
{}

const char * Exceptions::InvalidOperandsQuantity::what() const throw()
{
	return ("Invalid quantity of operands");
}

// ----- UndefinedToken -----

Exceptions::UndefinedToken::UndefinedToken()
{}

Exceptions::UndefinedToken::~UndefinedToken()
{}

const char * Exceptions::UndefinedToken::what() const throw()
{
	return ("Undefined token");
}

// ----- NoExitCMD -----

Exceptions::NoExitCMD::NoExitCMD()
{}

Exceptions::NoExitCMD::~NoExitCMD()
{}

const char * Exceptions::NoExitCMD::what() const throw()
{
	return ("Error : no exit command");
}

// ----- EmptyStack -----

Exceptions::EmptyStack::EmptyStack()
{}

Exceptions::EmptyStack::~EmptyStack()
{}

const char * Exceptions::EmptyStack::what() const throw()
{
	return ("Stack is empty");
}

// ----- DivideByZero -----

Exceptions::DivideByZero::DivideByZero()
{}

Exceptions::DivideByZero::~DivideByZero()
{}

const char * Exceptions::DivideByZero::what() const throw()
{
	return ("Divide by zero");
}

// ----- ModuloByZero -----

Exceptions::ModuloByZero::ModuloByZero()
{}

Exceptions::ModuloByZero::~ModuloByZero()
{}

const char * Exceptions::ModuloByZero::what() const throw()
{
	return ("Modulo by zero");
}

// ----- PositiveOverflow -----

Exceptions::PositiveOverflow::PositiveOverflow()
{}

Exceptions::PositiveOverflow::~PositiveOverflow()
{}

const char * Exceptions::PositiveOverflow::what() const throw()
{
	return ("Positive Overflow");
}

// ----- NegativeOverflow -----

Exceptions::NegativeOverflow::NegativeOverflow()
{}

Exceptions::NegativeOverflow::~NegativeOverflow()
{}

const char * Exceptions::NegativeOverflow::what() const throw()
{
	return ("Negative Overflow");
}
