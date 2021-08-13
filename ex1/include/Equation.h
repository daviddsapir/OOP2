#pragma once
#include<iostream>


//----------------------- class Equation -----------------------
class Equation
{
public:
	
	// c-tor
	Equation() {};

	// c-tor
	// This c-tor gets 2 pointer to equations and also holds 
	// the operation between them.
	Equation(std::shared_ptr<Equation> e1,
		std::shared_ptr<Equation> e2, std::string operation);

	// Prints the equation with the value the user wanted
	// to evaluate.
	virtual void printWithVal(const double) const;

	// Calculates the value of the function with the
	// desired value the user wants to evaluate.
	virtual double evalEquation(const double);

	// Virtual function for building a function composition
	virtual void comp(std::shared_ptr<Equation>);

	// Virtual function for printing a composition of function  
	// with the value that needs to be evaluated.
	virtual void printCompWithVal(std::shared_ptr<Equation>,
		const double);

	// Virtual function for printing the desired function.
	virtual void print();


private:

	// Prints the equation with the operation value.
	void printWithOperationVal(const std::string,
		const double) const;

	// Prints composition of function with the with 
	// the needed operation
	void compWithOperation(std::shared_ptr<Equation>, 
		const std::string) const;

	// Prints composition of function with the with 
	// the value that need to be evaluated.
	void compWithOperationVal(std::shared_ptr<Equation>, 
		const std::string, const double) const;

	// Prints the functions and the operations between them.
	void printWithOperation(const std::string) const;

	// The operation between the 2 equations m_e1 and m_e2.
	std::string m_operation;

	// The equations that this equation is build upon. 
	std::shared_ptr<Equation> m_e1, m_e2;
};