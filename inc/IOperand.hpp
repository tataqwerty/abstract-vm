#ifndef IOPERAND_HPP
# define IOPERAND_HPP

	class IOperand
	{
	public:
		IOperand();
		IOperand(IOperand const& other);
		~IOperand();
		IOperand & operator=(IOperand const& other);
	};
#endif