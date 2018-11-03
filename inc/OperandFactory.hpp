#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# define COUNT_CMD 5

#include "eOperandType.hpp"
#include "IOperand.hpp"
#include <vector>

class OperandFactory
{
	typedef IOperand const* (OperandFactory::*MemberFunction)(std::string const &) const;

	MemberFunction		createOperandFunctions[COUNT_CMD];

public:
	OperandFactory();
	~OperandFactory();

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;
};

#endif