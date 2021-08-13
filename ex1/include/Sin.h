#pragma once
#include "Equation.h"
#include <cmath>

class Sin : public Equation
{
public:

	// C-tor
	Sin() = default;

	// Performs a composition of functions on this function.
	virtual void comp(std::shared_ptr<Equation>) override;

	// Evaluate sin value.
	virtual double evalEquation(const double num) override;

	// Print sin function
	virtual void print() override;

	// Print the sin function  with value inside.
	// i.e. print sin(value).
	virtual void printWithVal(const double) const override;

	// Print the sin function with the value returned from the
	// composition of the functions.
	virtual void printCompWithVal(std::shared_ptr<Equation>,
		const double);
};