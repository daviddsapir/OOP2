#include "Macros.h"
#include "IDValidator.h"


//--------- IDValidator C-tor -----------
IDValidator::IDValidator()
{
	// Set error message.
	setMsgError(ID_MSG_ERROR);
}


//----------------- isInputValid -------------------
// Check if the id given is according 'Check digit'.
//--------------------------------------------------
bool IDValidator::isInputValid(uint32_t input) 
{
	return isIDValid(input);
}


//--------------------- getSumOfDIgits --------------------
// Returns the sum of the ID digits.
//---------------------------------------------------------
int IDValidator::getSumOfDIgits(const int* idDigits) const
{
	int sum = 0, incNum = 0;

	for (int i = 0; i < ID_NUM_OF_DIGITS; i++)
	{
		incNum = idDigits[i] * ((i % 2) + 1);

		sum += (incNum > ID_NUM_OF_DIGITS) ?
			incNum - ID_NUM_OF_DIGITS : incNum;
	}

	return sum;
}


//----------------------- getDigits --------------------------
// Inserts the ID digits into an array.
//------------------------------------------------------------
void IDValidator::getDigits(int * idDigits, int id) const
{
	// Turn number into array of digits.
	for (int i = ID_NUM_OF_DIGITS - 1; i >= 0; i--)
	{
		idDigits[i] = id % 10;
		id = id / 10;
	}
}


//----------------------- isIDValid ------------------------
// Return if the ID is valid.
// Checks the ID correctness with the ID checking algorithm
//----------------------------------------------------------
inline bool IDValidator::isIDValid(uint32_t id) const
{
	int idDigits[ID_NUM_OF_DIGITS];

	// Check the id not too short.
	if (numDigits(id) != ID_NUM_OF_DIGITS)
		return false;
	
	// Turn number into array of digits.
	getDigits(idDigits, id);


	return (getSumOfDIgits(idDigits) % 10 == 0);
}


//------------------ numDigits -------------------
// Return the number of digits.
//------------------------------------------------
int IDValidator::numDigits(uint32_t number) const
{
	int digits = 0;
	
	while (number) 
	{
		number /= 10;
		digits++;
	}

	return digits;
}