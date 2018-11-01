#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <boost/lexical_cast.hpp>

template<typename T>
class Operand : public IOperand
{
	eOperandType	type;
	std::string		stringValue;

public:
	Operand()
	{}

	// Operand(Operand const& other)
	// {}

	// Operand & operator=(Operand const& other)
	// {}

	Operand(eOperandType operandType, T operandValue)
	:	type(operandType),
		stringValue(boost::lexical_cast<std::string>(static_cast<long double>(operandValue)))
	{}

	~Operand()
	{}

	//	undefined behaviour while swapping types within enumeration.
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
		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				T	tmpVal;

				tmpVal = boost::numeric_cast<T>(std::stold(this->toString()) + std::stold(rhs.toString()));
				return (new Operand<T>(this->getType(), tmpVal));
			}
			else
			{
				return (rhs + *this);
			}
		} catch(boost::numeric::negative_overflow & e) {
			throw std::logic_error("Negative overflow");
		} catch(boost::numeric::positive_overflow & e) {
			throw std::logic_error("Positive overflow");
		}
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				T	tmpVal;

				tmpVal = boost::numeric_cast<T>(std::stold(this->toString()) - std::stold(rhs.toString()));
				return (new Operand<T>(this->getType(), tmpVal));
			}
			else
			{
				return (rhs - *this);
			}
		} catch(boost::numeric::negative_overflow & e) {
			throw std::logic_error("Negative overflow");
		} catch(boost::numeric::positive_overflow & e) {
			throw std::logic_error("Positive overflow");
		}
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				T	tmpVal;

				tmpVal = boost::numeric_cast<T>(std::stold(this->toString()) * std::stold(rhs.toString()));
				return (new Operand<T>(this->getType(), tmpVal));
			}
			else
			{
				return (rhs * *this);
			}
		} catch(boost::numeric::negative_overflow & e) {
			throw std::logic_error("Negative overflow");
		} catch(boost::numeric::positive_overflow & e) {
			throw std::logic_error("Positive overflow");
		}
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				T	tmpVal;

				if (std::stold(rhs.toString()) == 0)
					throw std::logic_error("Divide by zero");
				else
					tmpVal = boost::numeric_cast<T>(std::stold(this->toString()) / std::stold(rhs.toString()));
				return (new Operand<T>(this->getType(), tmpVal));
			}
			else
			{
				return (rhs / *this);
			}
		} catch(boost::numeric::negative_overflow & e) {
			throw std::logic_error("Negative overflow");
		} catch(boost::numeric::positive_overflow & e) {
			throw std::logic_error("Positive overflow");
		}
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		try {
			if (this->getPrecision() >= rhs.getPrecision())
			{
				T	tmpVal;

				if (std::stold(rhs.toString()) == 0)
					throw std::logic_error("Modulo by zero");
				else
					tmpVal = boost::numeric_cast<T>(static_cast<long>(roundl(std::stold(this->toString()))) % static_cast<long>(roundl(std::stold(rhs.toString()))));
				return (new Operand<T>(this->getType(), tmpVal));
			}
			else
			{
				return (rhs % *this);
			}
		} catch(boost::numeric::negative_overflow & e) {
			throw std::logic_error("Negative overflow");
		} catch(boost::numeric::positive_overflow & e) {
			throw std::logic_error("Positive overflow");
		}
	}

	bool	operator==(IOperand const & rhs) const
	{
		return (this->toString() == rhs.toString()) && (this->getType() == rhs.getType());
	}

	std::string const & toString( void ) const
	{
		return stringValue;
	}
};

#endif