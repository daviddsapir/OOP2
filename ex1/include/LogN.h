#pragma once
#include "Equation.h"


//----------------------- class LogN ---------------------------
class LogN : public Equation
{
public:

	// C-tor
	LogN(const unsigned int, std::shared_ptr<Equation>);

	// Preforms a composition of functions.
	virtual void comp(std::shared_ptr<Equation>) override;

	// Evaluate logN value.
	virtual double evalEquation(const double num) override;

	// Print logN function and the
	// function upon it works on
	virtual void print() override;

	// print the function with the value that should be 
	// evaluated.
	virtual void printWithVal(const double) const override;

	// Prints the function with composition with the value 
	// that should be evaluated.
	virtual void printCompWithVal(std::shared_ptr<Equation> e,
		const double);

private:

	// Holds the log base and the equation it works on
	unsigned int m_base;
	std::shared_ptr<Equation> m_equation;
};
