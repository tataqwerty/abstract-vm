#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

#include "eOperandType.hpp"
#include "IOperand.hpp"

class OperandFactory
{
public:
	OperandFactory();
	// OperandFactory(OperandFactory const& other);
	// OperandFactory & operator=(OperandFactory const& other);
	~OperandFactory();

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;
};

#endif