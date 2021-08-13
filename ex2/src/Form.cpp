#include "Form.h"


//---------------- fillForm ----------------
// sets data into the form.
// Runs over the feilds and gets input from
// the user.
//------------------------------------------
void Form::fillForm()
{
	for (auto i : m_fields) i->setData();
}


//---------------- addValidator ----------------
// Inserts a new validator into the vector 
// that hold all the validators
//----------------------------------------------
void Form::addValidator(FormValidator* valid)
{
	m_valid.push_back(valid);
}


//---------------------- printFieldsMsgErr ---------------------
// Prints the fields error message.
//--------------------------------------------------------------
void Form::printFieldsMsgErr(std::ostream& os) const
{

	// Print the fields.
	for (auto i: m_fields) i-> printField(os);

	if (fieldsDataValid)
	{
		for (auto i : m_valid) 
		{
			// Print only one validation error if existed.
			if (!i->isFieldsValid()) {
				os << i->getMsgErr() << '\n';

				// Print and exit if error found.
				return;
			}
		}
	}
}


//------------------- checkFieldsValid --------------------
// Check the fields validators are correct.
//---------------------------------------------------------
void Form::checkFieldsValid(bool &isValidForm)
{
	for (auto i : m_fields)
	{
		if (!i->isValid())
		{
			// Update the field statues is not correct.
			i->setFieldValidation(false);
			fieldsDataValid = false;
			isValidForm = false;
		}
		else i->setFieldValidation(true);
	}

	if (isValidForm)
	{
		fieldsDataValid = true;
	}
}


//--------------- checkFormValid ----------------
// Check the form validators are correct.
//-----------------------------------------------
void Form::checkFormValid(bool& isValidForm)
{
	// Runs over the Forms' validators.
	for (auto i : m_valid)
	{
		// Checks if the fields are valid.
		if (!(i->isFieldsValid()))
		{
			i->setValid(false);

			i->setFieldsValidations(false);

			isValidForm = false;

			break;
		}
	}
}


//------------------- validateForm --------------------
// Validate input data from the costumer.
//-----------------------------------------------------
bool Form::validateForm()
{
	// Form fields' validators validation statues
	bool isFieldsValid = true,
	// Form's validators validation statues
		isFormValid = true;;
	
	// Checks if the field is valid.
	checkFieldsValid(isFieldsValid);

	if (fieldsDataValid)
		checkFormValid(isFormValid);

	if (isFieldsValid && isFormValid)
		return true;


	return false;
}


//-------------------- operator<< ----------------------
// Operator to print the errors messages.
//------------------------------------------------------
std::ostream& operator<<(std::ostream& os, Form form)
{
	form.printFieldsMsgErr(os);
	return os;
}
