#pragma once
#include "Validator.h"


//-------------------- class IDValidator ------------------
class IDValidator: public Validator<uint32_t>
{
public:

	// C-tor
	IDValidator();

	// Returns if the input is valid.
	virtual bool isInputValid(uint32_t input) override;
	
private:

	// Returns the sum of ID digits.
	int getSumOfDIgits(const int*) const;

	// Inserts the ID digits into an array.
	void getDigits(int*, int) const;

	// Return if the ID is valid.
	bool isIDValid(uint32_t id) const;

	// Return the amount of digits in the ID.
	int numDigits(uint32_t number) const;
};