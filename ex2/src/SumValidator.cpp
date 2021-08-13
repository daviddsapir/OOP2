#include "SumValidator.h"


//--------------------- SumValidator C-tor -----------------------
// Sets the message error and the stores the fields.
//----------------------------------------------------------------
SumValidator::SumValidator(const std::string str, Field<int>* f1,
	Field<int>* f2, Field<int>* f3) :
	m_totalFeild(f1), m_totalYoung(f2), m_totalAdults(f3)
 {
	// Set error message.
	 setMsgError(str);
 }


//----------------- SumValidator -----------------
// Check if the total people = young + adults.
//------------------------------------------------
bool SumValidator::isFieldsValid()
{
	return (m_totalFeild->getContent() ==
		m_totalYoung->getContent() +
		m_totalAdults->getContent());
}


//--------------- setFieldsValidations ---------------
// Resets the fields validations.
//----------------------------------------------------
void SumValidator::setFieldsValidations(const bool statues)
{
	m_totalFeild->setFieldValidation(statues);
	m_totalYoung->setFieldValidation(statues);
	m_totalAdults->setFieldValidation(statues);
}
