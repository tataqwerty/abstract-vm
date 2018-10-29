#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <boost/lexical_cast.hpp>

template<typename T>
class Operand : public IOperand
{
	T				numericValue;
	eOperandType	type;
	std::string		stringValue;

public:
	Operand()
	{}

	// Operand(Operand const& other)
	// {}

	// Operand & operator=(Operand const& other)
	// {}

	Operand(T operandVal, eOperandType operandType)
	:	numericValue(operandVal),
		type(operandType)
		// ,
		// stringValue(boost::lexical_cast<std::string>(operandVal))
	{}

	~Operand()
	{}

	int				getPrecision( void ) const
	{
		return 0;
	}

	eOperandType	getType( void ) const
	{
		return (type);
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		(void)rhs;
		return NULL;
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		(void)rhs;
		return NULL;
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		(void)rhs;
		return NULL;
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		(void)rhs;
		return NULL;
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		(void)rhs;
		return NULL;
	}

	std::string const & toString( void ) const
	{
		return boost::lexical_cast<std::string>(numericValue);
	}
};

#endif