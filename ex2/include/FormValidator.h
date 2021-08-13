#pragma once
#include <string>


//--------------------- class FormValidator --------------------
class FormValidator
{
public:
	
	// Returns if a fields is valid.
	virtual bool isFieldsValid() = 0;

	// Sets the fields validation.
	virtual void setFieldsValidations(const bool) = 0;

	// Sets the fields validation.
	virtual void setValid(bool valid);

	// Returns if the form is valid.
	virtual bool getValid();

	// Sets the error message form this validator.
	void setMsgError(const std::string);

	// Returns the error message for this validator.
	const std::string getMsgErr() const;

private:

	// To hold the message error.
	std::string m_msgError = " ";

	// To hold the correctness of the field.
	bool isValid = false;
};