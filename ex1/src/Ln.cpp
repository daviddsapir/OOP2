#include <cmath>
#include "Ln.h"
#include <iostream>

using std::cout;

//----------------- comp ------------------
// Preforms a composition of functions.
//-----------------------------------------
void Ln::comp(std::shared_ptr<Equation> e)
{
	cout << "ln(";
	e->print();
	cout << ")";
}


//------------- evalEquation --------------
// Evaluate the ln value.
//-----------------------------------------
double Ln::evalEquation(const double num)
{
	return log(num);
}


//--------- print ----------
// Print ln function
//--------------------------
void Ln::print()
{
	cout << "ln(x)";
}


//--------------- printWithVal ---------------
// Print the function with the value that 
// should be evaluated.
//--------------------------------------------
void Ln::printWithVal(const double val) const
{
	cout << "ln(" << val << ")";
}


//------------------- printCompWithVal ----------------
// Prints the function composition with the value that 
// should be evaluated.
//-----------------------------------------------------
void Ln::printCompWithVal(std::shared_ptr<Equation> e,
	const double val)
{
	cout << "ln(";
	e->printWithVal(val);
	cout << ")";
}


