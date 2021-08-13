#include "Polynom.h"
#include <cmath>

using std::cout;


//--------------------- C-tor ----------------------
// Gets a vector that hold the holds the 
// cofficients of the polynomial and saves them in 
// a private member m_coefficients.
//--------------------------------------------------
Polynom::Polynom(std::vector<double> coefficients)
	: m_coefficients(coefficients) {}


//------------------------- print ------------------------------
// Prints the polynomial.
// Runs over the cofficients and for every non-zero cofficient
// prints it's x variable and exponent.
//--------------------------------------------------------------
void Polynom::print()
{
	for (double i = m_coefficients.size() - 1; i >= 0; i--) 
	{
		if (m_coefficients[i] != 0)
		{
			cout << m_coefficients[i] << "*x^" << i;
			printOperation(i);
		}
	}
}


//-------------------- evalEquation -------------------
// Evaluate the polynomial with a wanted value.
// Returns the answer after evaluating.
//-----------------------------------------------------
double Polynom::evalEquation(const double value)
{
	double sum = 0;

	for (int i = 0; i < m_coefficients.size(); i++)
	{
		sum += m_coefficients[i] * pow(value, i);
	}

	return sum;
}


//---------------------------- printWithVal ----------------------------
// Print the polynomial with the value to be calculated.
//----------------------------------------------------------------------
void Polynom::printWithVal(const double val) const
{
	for (double i = m_coefficients.size() - 1; i >= 0; i--)
	{
		if (m_coefficients[i] != 0)
		{
			cout << m_coefficients[i] << "*(" << val << ")^" << i;
			printOperation(i);
		}
	}
}



//--------------------------- comp -----------------------------
// Performs a composition of functions on this function.
//--------------------------------------------------------------
void Polynom::comp(std::shared_ptr<Equation> e)
{
	for (double i = m_coefficients.size() - 1; i >= 0; i--)
	{
		if (m_coefficients[i] != 0)
		{
			cout << m_coefficients[i] << "*(";
			e->print();
			cout << ")^" << i;
			printOperation(i);
		}
	}
}



//---------------------- printCompWithVal ----------------------
// Print the polynomial with the value returned from the
// composition of the functions.
//--------------------------------------------------------------
void Polynom::printCompWithVal(std::shared_ptr<Equation> e, 
	const double val)
{
	for (double i = m_coefficients.size() - 1; i >= 0; i--)
	{
		if (m_coefficients[i] != 0)
		{
			cout << m_coefficients[i] << "*(";
			e->printWithVal(val);
			cout << ")^" << i;
			printOperation(i);
		}
	}
}


//------------------- posCofficientAhead --------------------
// Returns if there are more non-zero cofficients 
// ahead in the polynomial.
// Needed for printing the plus(+) operation between the
// leading terms of the polynomial correctly.
//-----------------------------------------------------------
bool Polynom::posCofficientAhead(const double index) const
{
	for (double i = index - 1; i >= 0; i--)
	{
		if (m_coefficients[i] != 0)
		{
			return true;
		}
	}

	return false;
}


//------------------ printOperation ------------------
// Prints the plus operation between the leading 
// terms of the polynomial.
//----------------------------------------------------
void Polynom::printOperation(const double i) const
{
	if (i != 0 && posCofficientAhead(i))
		cout << " + ";
}

