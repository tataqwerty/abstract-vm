#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include "eOperandType.hpp"
#include <iostream>

class IOperand
{
public:
	virtual int					getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType		getType( void ) const = 0; // Type of the instance

	virtual	long double			convert(std::string const & s) const = 0;

	virtual IOperand const *	operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const *	operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const *	operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const *	operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const *	operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual bool				operator==( IOperand const & rhs ) const = 0;

	virtual std::string const & toString( void ) const = 0; // String representation of the instance
	virtual ~IOperand( void ) {}
};

#endif