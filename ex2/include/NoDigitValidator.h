#pragma once
#include "Validator.h"


//------------------- class NoDigitValidator ------------------
class NoDigitValidator: public Validator<std::string>
{
public:

	// C-tor
	NoDigitValidator();

	// Returns if the input is valid.
	virtual bool isInputValid(std::string input) override;
};