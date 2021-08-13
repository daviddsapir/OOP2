#pragma once
#include "Equation.h"



class Ln : public Equation
{
public:

	// c-tor
	Ln() = default;

	// Preforms a composition of functions.
	virtual void comp(std::shared_ptr<Equation>) override;

	// Evaluate ln value.
	virtual double evalEquation(const double num) override;

	// Print the ln function.
	virtual void print() override;

	// Print the function with the value that should be evaluated
	virtual void printWithVal(const double) const override;

	// Prints the function composition with the value that 
	// should be evaluated.
	virtual void printCompWithVal(std::shared_ptr<Equation> e,
		const double);
};