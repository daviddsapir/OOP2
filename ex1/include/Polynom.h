#include "Equation.h"
#include <vector>
#include <iostream>


//----------------------- class Equation -----------------------
class Polynom : public Equation
{
public:

	// C-tor
	Polynom(std::vector<double>);

	// Prints the polynomial.
	virtual void print() override;

	// Evaluate the polynomial with a wanted value.
	// Returns the answer after evaluating.
	virtual double evalEquation(const double) override;

	// Print the polynomial with the value to be calculated.
	virtual void printWithVal(const double) const override;

	// Performs a composition of functions on this function.
	virtual void comp(std::shared_ptr<Equation>) override;

	// Print the polynomial with the value returned from the
	// composition of the functions.
	virtual void printCompWithVal(std::shared_ptr<Equation> e, 
		const double);

private:
	
	// Returns if there are more non-zero cofficients 
	// ahead in the polynomial.
	bool posCofficientAhead(const double) const;

	// Prints the plus operation between the leading 
	// terms of the polynomial.
	void printOperation(const double i) const;

	// Holds the cofficients of the polynomial.
	std::vector <double> m_coefficients;
};


