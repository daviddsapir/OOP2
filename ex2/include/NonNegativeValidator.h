#pragma once
#include "Macros.h"


//----------------- class NonNegativeValidator -----------------
template<class T>
class NonNegativeValidator: public Validator<T>
{
public:

	// C-tor
	NonNegativeValidator();

	// Returns the validation of the input.
	virtual bool isInputValid(T) override;
};


//------------- NonNegativeValidator C-tor ---------------
template<class T>
inline NonNegativeValidator<T>::NonNegativeValidator()
{
	// Sets the error message.
	Validator<T>::setMsgError(NON_NEGATIVE_MSG_ERROR);
}


//---------------------- isInputValid ---------------------
// Returns the validation of the input.
// Check if the input data is not negative.
//---------------------------------------------------------
template<class T>
inline bool NonNegativeValidator<T>::isInputValid(T input)
{	
	return input >= 0;
}