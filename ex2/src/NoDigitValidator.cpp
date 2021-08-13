#include "Macros.h"
#include "NoDigitValidator.h"


//--------- NoDigitValidator C-tor ---------
NoDigitValidator::NoDigitValidator()
{
	// Set the error message.
	setMsgError(NO_DIGIT_MSG_ERROR);
}


//-------------------- isInputValid -------------------
// Returns if the input is valid.
// Checks if the data is not empty and also does not
// contain digits.
//-----------------------------------------------------
bool NoDigitValidator::isInputValid(std::string input)
{
	// Checks if None-empty input.
	if (input.size() == 0)
	{
		return false;
	}

	// Checks if the input is digitless.
	for (auto i : input)
	{
		if (isdigit(i))
		{
			return false;
		}
	}
	
	return true;
}
