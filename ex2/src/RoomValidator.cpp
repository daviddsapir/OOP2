#include "RoomValidator.h"
#include "FormValidator.h"


//----------------- RoomValidator C-tor -----------------
RoomValidator::RoomValidator(const std::string msgError,
	Field<int>* f1, Field<int>* f2, Field<int>* f3)
	:m_pairRoomsField(f1), 
	m_familyRoomsField(f2),
	m_totalPeopleField(f3)
{
	// Set error message.
	setMsgError(msgError);
}


//------------------ isFieldsValid -------------------
// Returns the validation of the field.
//----------------------------------------------------
bool RoomValidator::isFieldsValid()
{
	return (m_familyRoomsField->getContent()
		* 5 + m_pairRoomsField->getContent() * 2)
		== m_totalPeopleField->getContent();
}


//--------------- setFieldsValidations -----------------
// Sets the fields validation.
// Sets the validation fields to false.
//------------------------------------------------------
void RoomValidator::setFieldsValidations(const bool statues)
{
	m_totalPeopleField->setFieldValidation(statues);
	m_pairRoomsField->setFieldValidation(statues);
	m_familyRoomsField->setFieldValidation(statues);
}
