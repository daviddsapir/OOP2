#include <iostream>
#include "LogN.h"

using std::cout;


//-------------------- LogN ------------------
// The C-tor of the class log with base N.
// The C-tor receives a base and an equation
// that it works on.
//--------------------------------------------
LogN::LogN(const unsigned int base,
	std::shared_ptr<Equation> equation)
	: m_base(base), m_equation(equation) {}


//-------------------- comp -----------------------
// Preforms a composition of functions.
// This function preform a composition of function
// upon the function long with base N.
//-------------------------------------------------
void LogN::comp(std::shared_ptr<Equation> e)
{
	cout << "log" << m_base << "(";
	e->print();
	cout << ")";
}


//--------------- evalEquation --------------
// Evaluate logN value.
// Return the value of the function log 
// with base N upon the function its working
// on.
//-------------------------------------------
double LogN::evalEquation(const double num)
{
	return log(num) / log(m_base);
}


//---------------- print ---------------
// Print logN function and the function
// upon it works on.
//--------------------------------------
void LogN::print()
{
	cout << "log" << m_base << "(";
	m_equation->print();
	cout <<  ")";
}


//------------------ printWithVal ----------------
// print the function with the value that should  
// be evaluated.
//------------------------------------------------
void LogN::printWithVal(const double num) const
{
	cout << "log" << m_base << "(";
	m_equation->printWithVal(num);
	cout << ")";
}


//-------------------- printCompWithVal -----------------
// Prints the function with composition with the value 
// that should be evaluated.
//-------------------------------------------------------
void LogN::printCompWithVal(std::shared_ptr<Equation> e,
	const double val)
{
	cout << "log" << m_base << "(";
	e->printWithVal(val);
	cout << ")";
}

