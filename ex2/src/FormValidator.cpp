#include "FormValidator.h"


//--------------- setValid --------------
// Sets the fields validation.
//---------------------------------------
void FormValidator::setValid(bool valid)
{
	isValid = valid;
}


//---------- getValid ----------
// Returns if a fields is valid.
//------------------------------
bool FormValidator::getValid()
{
	return isValid;
}


//------------------ setMsgError ----------------------
// Sets the error message form this validator.
//-----------------------------------------------------
void FormValidator::setMsgError(const std::string str)
{
	m_msgError = str;
}


//------------------ getMsgErr -------------------
// Returns the error message for this validator.
//------------------------------------------------
const std::string FormValidator::getMsgErr() const
{
	return m_msgError;
}

