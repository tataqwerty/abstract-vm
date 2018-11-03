#include "OperandFactory.hpp"
#include "Operand.hpp"

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
	return (new Operand<int8_t>(Int8, value));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
	return (new Operand<int16_t>(Int16, value));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
	return (new Operand<int32_t>(Int32, value));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
	return (new Operand<float>(Float, value));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
	return (new Operand<double>(Double, value));
}

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	return (this->*(createOperandFunctions[type]))(value);
}
