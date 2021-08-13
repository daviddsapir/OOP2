#pragma once
#include "Field.h"
#include "Validator.h"
#include "FormValidator.h"
#include <iostream>
#include <vector>


//-------------------------- class Form ------------------------
class Form
{
public:

	// C-tor
	Form() {};

	// Inserts a new field.
	template< class T >
	void addField(Field<T> *);

	// sets data into the form.
	void fillForm();

	// validates the form.
	bool validateForm();

	// Inserts a new validator.
	void addValidator(FormValidator *field);

	// Prints the fields error message.
	void printFieldsMsgErr(std::ostream&) const;

private:

	// Checks if the Form fields are valid.
	void checkFieldsValid(bool& isValidForm);

	// Checks if the form is valid.
	void checkFormValid(bool& isValidForm);

	// Vector to hold Fields.
	std::vector<BaseField*> m_fields;

	// Vector to hold validators
	std::vector<FormValidator*> m_valid;

	// To update the correctness of the fields.
	bool formValid = false, fieldsDataValid = false;
};


//----------------  addField ----------------
// Inserts a new field into the vector 
// that hold all the feild.
//-------------------------------------------
template< class T >
inline void Form::addField(Field<T>* filed)
{
	m_fields.push_back(filed);
}


// Displays the forms fields.
std::ostream& operator<<(std::ostream& os, Form form);