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

	Operand(T operandVal, eOperandType operandType, std::string const & operandStringVal)
	:	numericValue(operandVal),
		type(operandType),
		stringValue(operandStringVal)
	{}

	~Operand()
	{}

	//	undefined behaviour while swapping them within enumeration.
	int				getPrecision( void ) const
	{
		return (type);
	}

	eOperandType	getType( void ) const
	{
		return (type);
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		T	tmpVal;

		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				tmpVal = numerical_cast<T>(numericValue + lexical_cast<T>(rhs.toString()));
			}
			else
			{
				
			}
		} catch(boost::numeric_undeflow & e) {
			throw std::logic_error("Underflow exception");
		} catch(boost::numeric_overflow & e) {
			throw std::logic_error("Overflow exception");
		}

		return ();
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
		return stringValue;
	}
};

#endif