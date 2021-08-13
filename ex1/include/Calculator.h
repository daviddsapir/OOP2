#pragma once
#include "Equation.h"
#include <vector>
#include <iostream>


//---------------------- class Calculator ----------------------
class Calculator 
{
public:

	// c-tor
	Calculator();

	// Turn on the calculator
	// (more info in function definition)
	void run();

private:

	// Read and return the wanted operation
	// from the user/client.
	std::string getOperation() const;

	// Preform the requested operation.
	void preformRequestedOperation(std::string);

	// Read and return the wanted function from
	// the listed list of functions avaible number.
	unsigned int getEquationNum() const;

	// Read and return the value the user entered.
	double getVal() const;

	// Read and return the coefficient of the polynomial.
	double getCoefficient() const;

	// Read and return the Polynomial power.
	unsigned int getPolyPower() const;

	// Preform the wanted operation. 
	// (more information in function definition)
	void doOperation(const std::string);

	// Read the Polynomial data. i.e read the power
	// of the Polynomial and its Coefficients
	void readPolyData(std::vector <double>&) const;

	// Insert and new Polynomial into the functions list
	// data structure (the vector m_equations).
	void insertPolyEquation();

	// Insert and new log with base N into the functions
	// list data structure (the vector m_equations). 
	void insertLogBaseN();

	// Prints a prompt that displays to the user a 
	// list of available functions and invites 
	// the user to insert a new command.
	void printPromt() const;

	// Print the list of available equations
	void printEquations() const;

	// Prints an equation in index i 
	void printEquation(const int) const;

	// evaluate the wanted equation
	void evalEquation() const;

	// prints the answer of the equation after evaluating
	void PrintEvalAnswer(const unsigned int func_num,
		const double val) const;

	// return numeric value with precision of 2 after the '.'
	const std::string getValFixed(std::string) const;

	// Print the equation with value it needs to evaluate. 
	void printWithVal(const unsigned int, const double) const;

	// Delete and equation from the data
	// structure (the vector m_equations).
	void deleteEquation();

	// Display the instructions of how to use the calculator.
	void printInstructions() const;

	// Inserts the initial function sin(x) 
	// and ln(x) into the the data structure.
	void insertIntialFunctions();

	// Vector - the data structure that hold the equations.
	std::vector <std::shared_ptr<Equation>> m_equations;
};
