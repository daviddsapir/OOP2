#include "Sin.h"
#include <iostream>

using std::cout;


//----------- print -----------
// Print sin function.
//-----------------------------
void Sin::print()
{
	cout << "sin(x)";
}


//------------------- comp -------------------
// Performs a composition of functions on
// this function.
//--------------------------------------------
void Sin::comp(std::shared_ptr<Equation> e)
{
	cout << "sin(";
	e->print();
	cout << ")";
}


//---------------- evalEquation --------------
// Returns the value of the function sin 
// that receives value.
//--------------------------------------------
double Sin::evalEquation(const double value)
{
	return sin(value);
}


//---------------- printWithVal -----------------
// Print the sin function  with value inside.
// i.e. print sin(value). 
//-----------------------------------------------
void Sin::printWithVal(const double val) const
{
	cout << "sin(" << val << ")";
}

//-------------------- printCompWithVal -------------------
// Print the sin function with the value returned from the
// composition of the functions
//---------------------------------------------------------
void Sin::printCompWithVal(std::shared_ptr<Equation> e,
	const double val)
{
	cout << "sin(";
	e->printWithVal(val);
	cout<< ")";
}
