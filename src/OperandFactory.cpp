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
	int8_t	numericValue;

	try {
		numericValue = boost::numeric_cast<int8_t>(std::stold(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Negative overflow");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Positive overflow");
	}

	return (new Operand<int8_t>(Int8, numericValue));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	int16_t	numericValue;

	try {
		numericValue = boost::numeric_cast<int16_t>(std::stold(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Negative overflow");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Positive overflow");
	}

	return (new Operand<int16_t>(Int16, numericValue));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
	int32_t	numericValue;

	try {
		numericValue = boost::numeric_cast<int32_t>(std::stold(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Negative overflow");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Positive overflow");
	}

	return (new Operand<int32_t>(Int32, numericValue));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	float	numericValue;

	try {
		numericValue = boost::numeric_cast<float>(std::stold(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Negative overflow");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Positive overflow");
	}

	return (new Operand<float>(Float, numericValue));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	double	numericValue;

	try {
		numericValue = boost::numeric_cast<double>(std::stold(value));
	} catch (boost::numeric::negative_overflow & e) {
		throw std::logic_error("Negative overflow");
	} catch (boost::numeric::positive_overflow & e) {
		throw std::logic_error("Positive overflow");
	}

	return (new Operand<double>(Double, numericValue));
}

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	return (this->*(createOperandFunctions[type]))(value);
}
