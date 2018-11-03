#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <boost/lexical_cast.hpp>
#include "OperandFactory.hpp"
#include "Exceptions.hpp"

template<typename T>
class Operand : public IOperand
{
	eOperandType	type;
	std::string		value;
	OperandFactory	operandFactory;

public:
	Operand()
	{}

	Operand(Operand const& other)
	:	type(other.type),
		value(other.alue),
		operandFactory(OperandFactory())
	{}

	Operand & operator=(Operand const& other)
	{
		this->type = other.type;
		this->value = other.value;
		return *this;
	}

	Operand(eOperandType operandType, std::string const & operandValue)
	:	type(operandType),
		value(std::to_string(boost::numeric_cast<T>(convert(operandValue)))),
		operandFactory(OperandFactory())
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

	long double	convert(std::string const & s) const
	{
		try {
			return (boost::numeric_cast<T>(std::stold(s)));
		} catch(boost::numeric::positive_overflow & e) {
			throw Exceptions::PositiveOverflow();
		} catch(boost::numeric::negative_overflow & e) {
			throw Exceptions::NegativeOverflow();
		}
	}

	IOperand const *	dispatcherOperators(IOperand const & left, IOperand const & right, long double (*basicOperation)(long double, long double)) const
	{
		eOperandType	newOperandType;
		std::string		newOperandValue;

		/* convert in type of left operand */
		if (left.getPrecision() >= right.getPrecision())
		{
			newOperandType = left.getType();
			newOperandValue = boost::lexical_cast<std::string>(basicOperation(left.convert(left.toString()), left.convert(right.toString())));
		}
		/* convert in type of right operand */
		else
		{
			newOperandType = right.getType();
			newOperandValue = boost::lexical_cast<std::string>(basicOperation(right.convert(left.toString()), right.convert(right.toString())));
		}

		return (operandFactory.createOperand(newOperandType, newOperandValue));
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal + rightVal;
		};

		return dispatcherOperators(*this, rhs, f);
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal - rightVal;
		};

		return dispatcherOperators(*this, rhs, f);
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal * rightVal;
		};

		return dispatcherOperators(*this, rhs, f);
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			if (!rightVal)
				throw Exceptions::DivideByZero();
			return leftVal / rightVal;
		};

		return dispatcherOperators(*this, rhs, f);
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			if (!rightVal)
				throw Exceptions::ModuloByZero();
			return fmod(leftVal, rightVal);
		};

		return dispatcherOperators(*this, rhs, f);
	}

	bool	operator==(IOperand const & rhs) const
	{
		return (this->toString() == rhs.toString()) && (this->getType() == rhs.getType());
	}

	std::string const & toString( void ) const
	{
		return value;
	}
};

#endif