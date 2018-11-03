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
		value(boost::lexical_cast<std::string>(convert(operandValue))),
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

	IOperand const *	basicOperation(IOperand const & left, IOperand const & right, long double (*f)(long double, long double)) const
	{
		eOperandType	newOperandType;
		std::string		newOperandValue;

		if (left.getPrecision() >= right.getPrecision())
		{
			newOperandType = left.getType();
			newOperandValue = boost::lexical_cast<std::string>(f(left.convert(left.toString()), left.convert(right.toString())));
		}
		else
		{
			newOperandType = right.getType();
			newOperandValue = boost::lexical_cast<std::string>(f(right.convert(left.toString()), right.convert(right.toString())));
		}

		return (operandFactory.createOperand(newOperandType, newOperandValue));
	}

	IOperand const * operator+( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal + rightVal;
		};

		return basicOperation(*this, rhs, f);
	}

	IOperand const * operator-( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal - rightVal;
		};

		return basicOperation(*this, rhs, f);
	}

	IOperand const * operator*( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			return leftVal * rightVal;
		};

		return basicOperation(*this, rhs, f);
	}

	IOperand const * operator/( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			if (!rightVal)
				throw Exceptions::DivideByZero();
			return leftVal / rightVal;
		};

		return basicOperation(*this, rhs, f);
	}

	IOperand const * operator%( IOperand const & rhs ) const
	{
		long double (*f)(long double, long double) = [](long double leftVal, long double rightVal){
			if (!rightVal)
				throw Exceptions::ModuloByZero();
			return static_cast<long double>(static_cast<long>(roundl(leftVal)) % static_cast<long>(roundl(rightVal)));
		};

		return basicOperation(*this, rhs, f);
	}

	// IOperand const * operator+( IOperand const & rhs ) const
	// {
	// 	eOperandType	newOperandType;
	// 	std::string		newOperandValue;

	// 	if (this->getPrecision() >= rhs.getPrecision())
	// 	{
	// 		newOperandType = this->getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(this->convert(this->toString()) + this->convert(rhs.toString()));
	// 	}
	// 	else
	// 	{
	// 		newOperandType = rhs.getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(rhs.convert(this->toString()) + rhs.convert(rhs.toString()));
	// 	}

	// 	return (operandFactory.createOperand(newOperandType, newOperandValue));
	// }

	// IOperand const * operator-( IOperand const & rhs ) const
	// {
	// 	eOperandType	newOperandType;
	// 	std::string		newOperandValue;

	// 	if (this->getPrecision() >= rhs.getPrecision())
	// 	{
	// 		newOperandType = this->getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(this->convert(this->toString()) - this->convert(rhs.toString()));
	// 	}
	// 	else
	// 	{
	// 		newOperandType = rhs.getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(rhs.convert(this->toString()) - rhs.convert(rhs.toString()));
	// 	}

	// 	return (operandFactory.createOperand(newOperandType, newOperandValue));
	// }

	// IOperand const * operator*( IOperand const & rhs ) const
	// {
	// 	eOperandType	newOperandType;
	// 	std::string		newOperandValue;

	// 	if (this->getPrecision() >= rhs.getPrecision())
	// 	{
	// 		newOperandType = this->getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(this->convert(this->toString()) * this->convert(rhs.toString()));
	// 	}
	// 	else
	// 	{
	// 		newOperandType = rhs.getType();
	// 		newOperandValue = boost::lexical_cast<std::string>(rhs.convert(this->toString()) * rhs.convert(rhs.toString()));
	// 	}

	// 	return (operandFactory.createOperand(newOperandType, newOperandValue));
	// }

	// IOperand const * operator/( IOperand const & rhs ) const
	// {
	// 	eOperandType	newOperandType;
	// 	std::string		newOperandValue;

	// 	if (this->getPrecision() >= rhs.getPrecision())
	// 	{
	// 		newOperandType = this->getType();
	// 		if (this->convert(rhs.toString()) == 0)
	// 			throw Exceptions::DivideByZero();
	// 		newOperandValue = boost::lexical_cast<std::string>(this->convert(this->toString()) / this->convert(rhs.toString()));
	// 	}
	// 	else
	// 	{
	// 		newOperandType = rhs.getType();
	// 		if (rhs.convert(rhs.toString()) == 0)
	// 			throw Exceptions::DivideByZero();
	// 		newOperandValue = boost::lexical_cast<std::string>(rhs.convert(this->toString()) / rhs.convert(rhs.toString()));
	// 	}

	// 	return (operandFactory.createOperand(newOperandType, newOperandValue));
	// }

	// IOperand const * operator%( IOperand const & rhs ) const
	// {
	// 	eOperandType	newOperandType;
	// 	std::string		newOperandValue;

	// 	if (this->getPrecision() >= rhs.getPrecision())
	// 	{
	// 		newOperandType = this->getType();
	// 		if (this->convert(rhs.toString()) == 0)
	// 			throw Exceptions::ModuloByZero();
	// 		newOperandValue = boost::lexical_cast<std::string>(static_cast<long>(roundl(this->convert(this->toString()))) % static_cast<long>(roundl(this->convert(rhs.toString()))));
	// 	}
	// 	else
	// 	{
	// 		newOperandType = rhs.getType();
	// 		if (rhs.convert(rhs.toString()) == 0)
	// 			throw Exceptions::ModuloByZero();
	// 		newOperandValue = boost::lexical_cast<std::string>(static_cast<long>(roundl(rhs.convert(this->toString()))) % static_cast<long>(roundl(rhs.convert(rhs.toString()))));
	// 	}

	// 	return (operandFactory.createOperand(newOperandType, newOperandValue));
	// }

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