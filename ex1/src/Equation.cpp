#include "Equation.h"
#include"Macros.h"

using std::cout;

//-------------------------- c-tor ------------------------------
// This c-tor gets 2 pointer to equations and also holds 
// the operation between them.
//---------------------------------------------------------------
Equation::Equation(
	std::shared_ptr<Equation> e1, std::shared_ptr<Equation> e2,
	std::string operation)
	:m_operation(operation), m_e1(e1), m_e2(e2)
{}


//--------------------- printWithVal ---------------------
// Prints the equation with the value the user wanted
// to evaluate.
//--------------------------------------------------------
void Equation::printWithVal(const double value) const
{
	if (m_operation == ADD) 
	{
		printWithOperationVal(ADDITION, value);
	}
	else if (m_operation == MUL)
	{
		printWithOperationVal(MULT, value);
	}
	else if (m_operation == COMP)
	{
		m_e1->printCompWithVal(m_e2, value);
	}
}


//--------------------------- evalEquation ----------------------------
// Calculates the value of the function with the desired value the
// user wants to evaluate.
//---------------------------------------------------------------------
double Equation::evalEquation(const double value)
{
	if (m_operation == ADD) 
		return m_e1->evalEquation(value) + m_e2->evalEquation(value);

	if (m_operation == MUL) 
		return m_e1->evalEquation(value) * m_e2->evalEquation(value);

	if (m_operation == COMP)
		return m_e1->evalEquation(m_e2->evalEquation(value));

	return 0;
}


//---------------------------- comp -------------------------------
// Building a function composition.
// Makes a composition of function from the internal function
// and then performs composition between the external ones.
//-----------------------------------------------------------------
void Equation::comp(std::shared_ptr<Equation> e)
{
	if (m_operation == ADD)
	{
		compWithOperation(e, ADDITION);
	}
	else if (m_operation == MUL)
	{
		compWithOperation(e, MULT);
	}
	else
	{
		m_e1->comp(std::make_shared <Equation>(m_e2, e, COMP));
	}
}


//---------------------- printCompWithVal ----------------------
// Prints a composition of function with the value that needs 
// to be evaluated.
//--------------------------------------------------------------
void Equation::printCompWithVal(std::shared_ptr<Equation> e,
	const double val)
{
	if (m_operation == ADD)
	{
		compWithOperationVal(e, ADDITION, val);
	}
	else if (m_operation == MUL)
	{
		compWithOperationVal(e, MULT, val);
	}
	else
	{
		m_e1->printCompWithVal
		(std::make_shared <Equation>(m_e2, e, COMP), val);
	}
}


//---------------------- print ----------------------
// The function prints the equation with the needed 
// operations.
//---------------------------------------------------
void Equation::print()
{
	if (m_operation == ADD)
	{
		printWithOperation(ADDITION);
	}
	else if (m_operation == MUL)
	{
		printWithOperation(MULT);
	}
	else if (m_operation == COMP)
	{
		m_e1->comp(m_e2);
	}
}



//----------------- printWithOperationVal ------------------
// Prints a composition of function with the value that
// needs to be evaluated.
//----------------------------------------------------------
void Equation::printWithOperationVal(const std::string op,
	const double val) const
{
	cout << "(";
	m_e1->printWithVal(val);
	cout << ")" << op << "(";
	m_e2->printWithVal(val);
	cout << ")";
}


//------------------- compWithOperation ------------------------
// Prints composition of function with the with 
// the needed operation
//--------------------------------------------------------------
void Equation::compWithOperation(std::shared_ptr<Equation> e,
	const std::string op) const
{
	cout << "(";
	m_e1->comp(e);
	cout << ")" << op << "(";
	m_e2->comp(e);
	cout << ")";
}


//-------------------- printWithOperation --------------------
// Prints the functions and the operations between them.
// i.e. prints the functions and the addition or mulipication 
// operation between them.
//------------------------------------------------------------
void Equation::printWithOperation(const std::string op) const
{
	cout << "(";
	m_e1->print();
	cout << ")" << op << "(";
	m_e2->print();
	cout << ")";
}


//------------------- compWithOperationVal ---------------------
// Prints composition of function with the with 
// the value that need to be evaluated.
//--------------------------------------------------------------
void Equation::compWithOperationVal(std::shared_ptr<Equation> e, 
	const std::string op, const double val) const
{
	cout << "(";
	m_e1->printCompWithVal(e, val);
	cout << ")" << op << "(";
	m_e2->printCompWithVal(e, val);
	cout << ")";
}


