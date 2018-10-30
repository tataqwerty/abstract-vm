#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
{
	createOperandFunctions[Int8] = &OperandFactory::createInt8;
	createOperandFunctions[Int16] = &OperandFactory::createInt16;
	createOperandFunctions[Int32] = &OperandFactory::createInt32;
	createOperandFunctions[Float] = &OperandFactory::createFloat;
	createOperandFunctions[Double] = &OperandFactory::createDouble;
}

// OperandFactory::OperandFactory(OperandFactory const & other)
// {}

// OperandFactory & OperandFactory::OperandFactory(OperandFactory const & other)
// {}

OperandFactory::~OperandFactory()
{}

IOperand const * OperandFactory::createInt8(std::string const & value) const
{
	char		numericValue;

	try {
		numericValue = boost::numeric_cast<char>(boost::lexical_cast<long double>(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Underflow exception");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Overflow exception");
	}

	return (new Operand<char>(numericValue, Int8, value));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	(void)value;
	return NULL;
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
	(void)value;
	return NULL;
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	(void)value;
	return NULL;
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	(void)value;
	return NULL;
}

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	return (this->*(createOperandFunctions[type]))(value);
}
