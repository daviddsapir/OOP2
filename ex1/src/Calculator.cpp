#include "Calculator.h"
#include <iostream>
#include <string>
#include "Polynom.h"
#include "Macros.h"
#include "Sin.h"
#include "Ln.h"
#include "LogN.h"
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;


//------------------------- constructor --------------------------
// Calls a function that inserts the initial function sin(x)
// and ln(x) into the the data structure (the vector m_equations)
// that hold all the functions.
//----------------------------------------------------------------
Calculator::Calculator()
{
	// Inserts the initial function sin(x) and ln(x)
	insertIntialFunctions();
}


//---------------------------- run ------------------------------
// The main function that receives requests and performs the 
// operations of the calculator using auxiliary functions.
// The calculator will run until it's getting a request to exit.
//---------------------------------------------------------------
void Calculator::run()
{
	// Print the initial list of equations 
	printPromt();

	// Read request from the user till
	// he wants to exit.
	auto operation = getOperation();
	while (operation != EXIT)
	{
		// preform the wanted operation if the operation is legal
		preformRequestedOperation(operation);

		// Print the list of equations and invite
		// the user to enter another command.
		printPromt();

		// Read another request operation.
		operation = getOperation();
	}

	// The user wants to exit ==> print goodbye.
	cout << "Goodbye" << endl;
}


//------------------ insertIntialFunctions ----------------
// Inserts the initial function sin(x) and ln(x) into the 
// the data structure (the vector m_equations) that hold
// all the functions.
//---------------------------------------------------------
void Calculator::insertIntialFunctions()
{
	// Insert the sin(x) function into the functions list
	m_equations.push_back(std::make_shared<Sin>());

	// Insert the ln(x) function into the functions list
	m_equations.push_back(std::make_shared<Ln>());
}


//---------------------- getOperation -------------------------
// Read and return the wanted operation from the user/client.
//-------------------------------------------------------------
std::string Calculator::getOperation() const
{
	// to hold the wanted operation
	std::string operation;

	// Read the first desired operation.
	cin >> operation;
	cout << endl;

	// Return the wanted operation the user requested
	return operation;
}


//------------------- preformRequestedOperation ------------------
// The function receives as a parameter the operation it must
// perform.
// The function checks what is the operation, sends to the
// appropriate function which will perform the required action
//-----------------------------------------------------------------
void Calculator::preformRequestedOperation(std::string operation) 
{
	if (operation == EVAL)
	{
		// Evaluates the function.
		evalEquation();
	}
	else if (operation == POLY)
	{
		// Insert a new polynomial into the functions list
		insertPolyEquation();
	}
	else if (operation == ADD)
	{
		// Preforms the addition operation between 2 function.
		doOperation(ADD);
	}
	else if (operation == MUL)
	{
		// Preforms the multiplication operation between 2 function.
		doOperation(MUL);
	}
	else if (operation == COMP)
	{
		// Preforms the composition operation between 2 function.
		doOperation(COMP);
	}
	else if (operation == LOG)
	{
		// Insert a new function that is log with base N 
		// into the functions list.
		insertLogBaseN();
	}
	else if (operation == DEL)
	{
		// Removes a function from the functions list.
		deleteEquation();
	}
	else if (operation == HELP)
	{
		// Prints the instructions to the user.
		printInstructions();
	}
}


//--------------- getEquationNum -----------------
// Read and return the wanted function from
// the listed list of functions avaible number.
//------------------------------------------------
unsigned int Calculator::getEquationNum() const
{
	int equationNum;

	// read the number of the equation
	cin >> equationNum;

	// return the number of the equation
	return equationNum;
}


//------------------ getVal ------------------
// Read and return the value the user entered.
//--------------------------------------------
double Calculator::getVal() const
{
	// Read a value from the user
	double val;
	cin >> val;

	// Return the value.
	return val;
}


 //------------------- getCoefficient ------------------
 // Read and return the coefficient of the polynomial. 
 //-----------------------------------------------------
 double Calculator::getCoefficient() const
 {
	 // Read from the user the Coefficient.
	 double Coefficient;
	 cin >> Coefficient;

	 // Return the Coefficient.
	 return Coefficient;
 }


//---------------- getPolyPower ------------------
// Read and return the Polynomial power.
//------------------------------------------------
 unsigned int Calculator::getPolyPower() const
 {
	 // Read from the user the polynomial power.
	 int polyPower;
	 cin >> polyPower;

	 // Return the polynomial power.
	 return polyPower;
 }


//--------------------- doOperation ----------------------
// Preform the wanted operation.
// The function works as follows:
// 1. Reads from the user the 2 functions numbers.
// 2. Insert a new function that is made up of two
// functions with the requested operation between them.
//--------------------------------------------------------
void Calculator::doOperation(const std::string op)
{
	// Reads from the user the 2 functions numbers.
	auto func_num1 = getEquationNum(),
		func_num2 = getEquationNum();

	// Insert a new function.
	m_equations.push_back(std::make_shared<Equation>
		(m_equations[func_num1],
			m_equations[func_num2], op));
}


//------------------ readPolyData ------------------
// Read the Polynomial data. i.e read the polyPower
// of the Polynomial and its Coefficients.
//--------------------------------------------------
void Calculator::readPolyData
(std::vector <double>& Coefficients) const
{
	auto polyPower = getPolyPower();
	for (int i = 0; i < polyPower; i++)
	{
		Coefficients.push_back(getCoefficient());
	}
}


//---------------------- insertPolyEquation ------------------------
// Insert and new Polynomial into the functions list data structure
// (the vector m_equations).
//------------------------------------------------------------------
void Calculator::insertPolyEquation()
{
	std::vector <double> Coefficients;

	// Read from the user the polynomial data
	readPolyData(Coefficients);

	// Insert the Coefficients into the vector.
	m_equations.push_back(std::make_shared<Polynom>(Coefficients));
}


//----------------------- insertLogBaseN -----------------------
// Insert and new log with base N into the functions
// list data structure (the vector m_equations). 
// The function works as follows:
// 1. Reads from the user the log base N and the function is
// going to work upon.
// 2. Inserts the new logN function into the functions list.
// i.e. inserts the new function into the vector that holds all 
// the functions avaiable for the user to use.
//--------------------------------------------------------------
void Calculator::insertLogBaseN()
{
	// Reads needed data from the user. 
	unsigned int base, func_num;
	cin >> base >> func_num;

	// Inserts the new logN function into the functions list.
	m_equations.push_back(std::make_shared<Equation>
		(std::make_shared<LogN>(base, m_equations[func_num]),
		m_equations[func_num], COMP));
}


//------------------ printPromt --------------------
// Prints a prompt that displays to the user a 
// list of available functions and invites 
// the user to insert a new command.
//--------------------------------------------------
void Calculator::printPromt() const
{
	std::cout << "This is the function list:\n";

	printEquations();

	cout << "Please enter a command "
		<< "(""help"" for command list): ";
}


//----------------- printEquations ------------------
//       Print the list of available equations
//----------------------------------------------------
void Calculator::printEquations() const
{
	for (int i = 0; i < m_equations.size(); i++)
	{
		printEquation(i);
	}
}


//----------------- printEquation ----------------
// Print the current equation in index i.
//------------------------------------------------
void Calculator::printEquation(const int i) const
{
	cout << i << ": ";
	m_equations[i]->print();
	cout << std::endl;
}


//------------------evalEquation----------------------
//Evaluate the value of the requasted equation
//----------------------------------------------------
void Calculator::evalEquation() const
{
	auto func_num = getEquationNum();
	auto val = getVal();
	if (func_num < m_equations.size()) 
	{
		printWithVal(func_num, val);
		PrintEvalAnswer(func_num, val);
	}
}


//------------------------ PrintEvalAnswer -----------------------
// prints the answer of the equation after evaluating.
// Prints the answer with precision of 2.
//----------------------------------------------------------------
void Calculator::PrintEvalAnswer(const unsigned int func_num,
	const double val) const
{	
	cout << " = "
		<< getValFixed
		(std::to_string(m_equations[func_num]->evalEquation(val)))
		<< std::endl;
}


//-------------------------- getValFixed -------------------------
// return value with precision of 2 digits after the period(.)
// if the 2 digits are 00 remove them from the value.
//----------------------------------------------------------------
const std::string Calculator::getValFixed(std::string value) const
{		
	if (value.find('.') != std::string::npos)
		value = value.substr(0, value.find('.') + 3);

	if (value[value.find('.') + 1] == '0' &&
		value[value.find('.') + 2] == '0') 
		value = value.substr(0, value.find('.'));

	return value;
}


//---------------------- printWithVal -----------------------
// Print the equation with value it needs to evaluate. 
//-----------------------------------------------------------
void Calculator::printWithVal(const unsigned int func_num,
	const double val) const
{
	m_equations[func_num]->printWithVal(val);
}


//--------------- deleteEquation --------------------
// Delete requasted equations from the list
//--------------------------------------------------
void Calculator::deleteEquation()
{
	auto funcNum = getEquationNum();
	m_equations[funcNum].reset();
	m_equations.erase(m_equations.begin() + funcNum);
}


//------------ printInstructions -------------
// Print calculator commands list
//--------------------------------------------
void Calculator::printInstructions() const 
{
	cout << INSTRUCTION;
}

