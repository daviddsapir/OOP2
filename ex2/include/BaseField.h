#pragma once 


//-------------------- class BaseField --------------------
class BaseField
{
public:
	
	// Virtual Function - Sets the field data.
	virtual void setData() = 0;

	// Virtual Function - Return if field is valid
	virtual bool isValid() = 0;

	// Virtual Function - Sets the fields validation.
	virtual void setFieldValidation(bool statues) = 0;

	// Virtual Function - Prints the field data. 
	virtual void printField(std::ostream&) = 0;
};